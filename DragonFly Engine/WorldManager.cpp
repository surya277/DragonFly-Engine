#include "WorldManager.h"
#include "LogManager.h"
#include "Object.h"
#include "ObjectListIterator.h"
#include "Utility.h"
#include "EventCollision.h"
#include "DisplayManager.h"
#include "EventOut.h"
#include "ViewObject.h"

#include<iostream>


namespace df {

	WorldManager::WorldManager() {
		setType("WorldManager");
	}


	// Get one and only instance of world manager
	WorldManager& WorldManager::getInstance() {
		static WorldManager WorldManagerSingle;
		return WorldManagerSingle;
	}

	int WorldManager::startUp() {
		if (Manager::isStarted())
			LM.writeLog("WorldManager has already been started\n");
		Manager::startUp();
		return 0;
	}

	void WorldManager::shutDown() {
		ObjectList list = m_updates;
		ObjectListIterator li(&list);

		for (li.first(); !li.isDone(); li.next()) {
			delete li.currentObject();
		}

		Manager::shutDown();
	}

	// Insert Objects into world.
	// Return 0 if ok, or else -1 
	int WorldManager::insertObject(Object* p_o) {
		return m_updates.insert(p_o);

	}

	// Remove Obejcts from world
	// Return 0 if ok, or else -1
	int WorldManager::removeObject(Object* p_o) {
		return m_updates.remove(p_o);
	}

	// Return list of all Objects in world
	ObjectList WorldManager::getAllObjects() const {
		return m_updates;
	}

	// Return list of all objects in the world that matches 
	ObjectList WorldManager::ObjectsOfType(std::string type) const {
		ObjectList list;
		ObjectListIterator li(&m_updates);

		for (li.first(); !li.isDone(); li.next()) {
			if (li.currentObject()->getType() == type) {
				list.insert(li.currentObject());
			}
		}

		return list;
	}

	// Update World
	// Delete Objects marked for deletion
	void WorldManager::update() {



		// Delete all marked Objects
		ObjectListIterator li(&m_deletions);
		while (!li.isDone()) {
			delete li.currentObject();
			li.next();
		}

		m_deletions.clear();		// Clear list for next update


		// Update Object position based on their velocity
		ObjectListIterator itr(&m_updates);
		while (!itr.isDone()) {
			Vector new_pos = itr.currentObject()->predictPosition();


			if (new_pos.getX() != itr.currentObject()->getPosition().getX() || new_pos.getY() != itr.currentObject()->getPosition().getY()) {
				moveObject(itr.currentObject(), new_pos);
			}
			itr.next();
		}
	}

	// Indicate Object is to be deleted at end of current game loop
	// Return 0 if ok, or else -1
	int WorldManager::markForDelete(Object* p_o) {
		ObjectListIterator li(&m_deletions);

		// Check if Objects have already been marked
		while (!li.isDone()) {
			if (li.currentObject() == p_o) {
				return 0;
			}
			li.next();
		}

		// if not add to list
		m_deletions.insert(p_o);
	}

	// Draw all Objects
	void WorldManager::draw() {

		ObjectListIterator li(&m_updates);
		for (int i = 0; i < MAX_ALTITUDE; i++) {
			li.first();
			while (!li.isDone()) {
				Object* p_temp_o = li.currentObject();

				if (p_temp_o->getAltitude() == i) {
					Box temp_box = Utility::getWorldBox(p_temp_o);

					// Only draw if Object would be visible on window (Intersects view)
					if(Utility::boxIntersectsBox(temp_box, view) || dynamic_cast<ViewObject*> (p_temp_o))
						p_temp_o->draw();
				}
				li.next();
			}

		}
	}



	// Return list of Objects collided with at given position
	// Collision only with solid Objects
	// Does not consider if P_o is solid or not
	ObjectList WorldManager::getCollision(Object* p_o, Vector where) const
	{
		ObjectList collision_list;
		ObjectListIterator itr(&m_updates);
		Box b = Utility::getWorldBox(p_o, where);

		while (!itr.isDone()) {
			Object* p_temp = itr.currentObject();
			Box b_temp = Utility::getWorldBox(p_temp);
			if (p_temp != p_o) {
				if ((Utility::boxIntersectsBox(b,b_temp)) && (p_temp->isSolid())) {
					collision_list.insert(p_temp);
				}
			}
			itr.next();
		}

		return collision_list;
	}

	// Move Object
	// If collision with solid, send collision events
	// If no collision with solid, move ok else don't move
	// If Object is SPECTRAL move ok
	// If moved from inside world boundary to outside, generate EventOut
	// Return 0 if move ok, else -1 if collision with solid

	int WorldManager::moveObject(Object* p_o, Vector where) {

		if (p_o->isSolid()) {
			ObjectList list = getCollision(p_o, where);

			// Check if list is Empty
			if (!list.isEmpty()) {
				bool do_move = true;

				ObjectListIterator li(&list);

				// Iterate over list
				while (!li.isDone()) {
					Object* p_temp_o = li.currentObject();

					// Create Collision Event
					EventCollision c(p_o, p_temp_o, where);

					p_o->eventHandler(&c);
					p_temp_o->eventHandler(&c);


					if (p_o->getSolidness() == HARD && p_temp_o->getSolidness() == HARD)
						do_move = false;

					if (p_o->getNoSoft() && p_temp_o->getSolidness() == SOFT)
						do_move = false;

					li.next();

				}

				if (!do_move)
					return -1;						// Move not allowed
			}
		}

		// if here, Both Objects are not HARD so 
		Box orig_box = Utility::getWorldBox(p_o);			// Original bounding box
		p_o->setPosition(where);							// move object
		Box new_box = Utility::getWorldBox(p_o);			// new bounding box


		// If moved from inside world boundary to outside, generate EventOut
		if (Utility::boxIntersectsBox(orig_box, boundary) && !Utility::boxIntersectsBox(new_box,boundary)) {
			EventOut ov;
			p_o->eventHandler(&ov);
		}

		// If view is following this object, adjust view
		if (p_view_following == p_o)
			setViewPosition(p_o->getPosition());
		return 0;
	}


	// VIEWPORT AND BOUNDARY

	// Set game world boundary
	void WorldManager::setBoundary(Box new_boundary) {
		boundary = new_boundary;
	}

	// Get game world boundary
	Box WorldManager::getBoundary() const {
		return boundary;
	}

	// Set player view of game world
	void WorldManager::setView(Box new_view) {
		view = new_view;
	}

	// Get player view of game world
	Box WorldManager::getView() const {
		return view;
	}

	// Set view to center window on position view_pos
	// View edge will not go beyond world boundary
	void WorldManager::setViewPosition(Vector view_pos) {

		// Make sure horizontal not out of world boundary
		float x = view_pos.getX() - view.getHorizontal() / 2;
		if (x + view.getHorizontal() > boundary.getHorizontal())
			x = boundary.getHorizontal() - view.getHorizontal();

		if (x < 0)
			x = 0;

		// Make sure vertical not out of boundary
		float y = view_pos.getY() - view.getVertical() / 2;
		if (y + view.getVertical() > boundary.getVertical())
			y = boundary.getVertical() - view.getVertical();

		if (y < 0)
			y = 0;


		// Set view
		Vector new_corner(x, y);
		view.setCorner(new_corner);
	}
	

	// Set view to follow Object
	// Set to NULL to stop following
	// if p_new_view_following not legit, return -1 else 0
	int WorldManager::setViewFollowing(Object* p_new_view_following) {
		bool found = false;
		// Set to NULL to turn 'off' following
		if (p_new_view_following == NULL)
			p_view_following = NULL;

		// Iterate over all objects. Make sure p_new_view_following is present]
		ObjectList list = WM.getAllObjects();
		ObjectListIterator list_itr(&list);

		while (!list_itr.isDone()) {
			if (list_itr.currentObject() == p_new_view_following)
				found = true;
			list_itr.next();
		}

		//If found, adjust attribute accordingly and set view position
		if (found) {
			p_view_following = p_new_view_following;
			setViewPosition(p_view_following->getPosition());
			return 0;
		}

		// if reached here, not legit. Return Error
		return -1;
	}
}