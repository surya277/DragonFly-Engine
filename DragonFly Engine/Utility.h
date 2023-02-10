#pragma once
#include "Vector.h"

namespace df {

	class Utility
	{

	public:
		static char* getTimeString();

		// Return true if two positions intersect, else false
		static bool positionsIntersect(Vector p1, Vector p2);
	};
}


