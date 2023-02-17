#pragma once

#include "Manager.h"
#include "ObjectList.h"

#define WM df::WorldManager::getInstance()

namespace df {
	const int MAX_ALTITUDE = 4;

	class WorldManager : public Manager
	{
	private:
		WorldManager();							// Private (Singleton)
		WorldManager(WorldManager const&);		// Don't Allow copy
		void operator=(WorldManager const&);	// Don't Allow assignment

		ObjectList m_updates;
		ObjectList m_deletions;
		
		Box boundary;							// World Boundary
		Box view;								// Player view of game world

		Object* p_view_following;				// Object view is following
	


	public:
		// Get one and only instance of world manager
		static WorldManager& getInstance();

		

		// Startup Game world
		int startUp();

		// Shutdown game world 
		// Delete all game world Objects
		void shutDown();

		// Insert Objects into world.
		// Return 0 if ok, or else -1 
		int insertObject(Object* p_o);

		// Remove Obejcts from world
		// Return 0 if ok, or else -1
		int removeObject(Object* p_o);

		// Return list of all Objects in world
		ObjectList getAllObjects() const;

		// Return List of all objects in the world that matches
		ObjectList ObjectsOfType(std::string type) const;

		// Update World
		// Delete Objects marked for deletion
		void update();

		// Indicate Object is to be deleted at end of current game loop
		// Return 0 if ok, or else -1
		int markForDelete(Object* p_o);

		// Draw all Objects
		void draw();


		// Return list of Objects collided with at given position
		// Collision only with solid Objects
		// Does not consider if P_o is solid or not
		ObjectList getCollision(Object* p_o, Vector where) const;

		// Move Object
		// If collision with solid, send collision events
		// If no collision with solid, move ok else don't move
		// If Object is SPECTRAL move ok
		// Return 0 if move ok, else -1 if collision with solid
		int moveObject(Object* p_o, Vector where);


		// BOUNDARY AND VIEWPORT

		// Set game world boundary
		void setBoundary(Box new_boundary);

		// Get game world boundary
		Box getBoundary()const;

		// Set player view of game world
		void setView(Box new_view);

		// Get player view of game world
		Box getView() const;

		// Set view to center window on position view_pos
		// View edge will not go beyond world boundary
		void setViewPosition(Vector view_pos);

		// Set to NULL to stop following
		// if p_new_view_following not legit, return -1 else 0
		int setViewFollowing(Object* p_new_view_following);
	};

}


