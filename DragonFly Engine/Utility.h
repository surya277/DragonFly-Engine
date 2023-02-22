#pragma once
#include "Vector.h"
#include "Object.h"
#include "Box.h"

namespace df {

	class Utility
	{

	public:
		static char* getTimeString();

		// Return true if two positions intersect, else false
		static bool positionsIntersect(Vector p1, Vector p2);


		// Return true if boxes interect, else false
		static bool boxIntersectsBox(Box A, Box B);

		// Convert relative bounding box for object to absolute world box 
		static Box getWorldBox(const Object* p_o);

		// Convert relative bounding box for object to absolute world box 
		static Box getWorldBox(const Object* p_o, Vector where);

		// Convert world position to view position
		static Vector worldToView(Vector world_pos);

		// Convert view position to world position
		static Vector viewToWorld(Vector view_pos);

		// Convert int to a string, returning a string
		static std::string toString(int i);
	};
}


