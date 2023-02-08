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
	};

}


