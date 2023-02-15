#include "WorldManager.h"
#include "LogManager.h"
#include "Object.h"
#include "ObjectListIterator.h"
#include "Utility.h"
#include "EventCollision.h"
#include "DisplayManager.h"
#include "EventOut.h"

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

		while (!itr.isDone()) {
			Object* p_temp = itr.currentObject();

			if (p_temp != p_o) {
				if ((Utility::positionsIntersect(p_temp->getPosition(), where)) && (p_temp->isSolid())) {
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
		p_o->setPosition(where);

		if (p_o->getPosition().getX() > DM.getHorizontal() || p_o->getPosition().getX() < 0 || p_o->getPosition().getY() > DM.getVertical() || p_o->getPosition().getY() < 0 ) {
			EventOut ov;
			p_o->eventHandler(&ov);
		}
		return 0;
	}


}