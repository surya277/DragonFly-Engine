#include "Utility.h"
#include "WorldManager.h"

#include<ctime>
#include<iostream>
#include <sstream>

// Get Current Time
// 
namespace df {

	char* Utility::getTimeString() {

		static char time_str[30];		//String to return

		//Systen calls to get time
		struct tm buf;
		time_t now;
		time(&now);
		errno_t err = localtime_s(&buf, &now);

		sprintf_s(time_str, "%02d:%02d:%02d",
			buf.tm_hour,
			buf.tm_min,
			buf.tm_sec);

		return time_str;

	}

	bool Utility::positionsIntersect(Vector p1, Vector p2) {
		if (abs(p1.getX() - p2.getX()) <= 1 && abs(p1.getY() - p2.getY()) <= 1)
			return true;
		
		return false;

	}

	// Return true if boxes intersect, else false
	bool Utility::boxIntersectsBox(Box A, Box B)
	{
		// Get Upper Left corner 
		float ax1 = A.getCorner().getX();
		float ay1 = A.getCorner().getY();

		float bx1 = B.getCorner().getX();
		float by1 = B.getCorner().getY();

		// Get Lower Right Corner
		float ax2 = ax1 + A.getHorizontal();
		float ay2 = ay1 + A.getVertical();

		float bx2 = bx1 + B.getHorizontal();
		float by2 = by1 + B.getVertical();

		// Test Horizontal Overlap (X overlap)
		if (((bx1 <= ax1 && ax1 <= bx2) ||
			(ax1 <= bx1 && bx1 <= ax2)) &&
			((by1 <= ay1 && ay1 <= by2) ||						// Test Vertical overlap (y overlap)
				(ay1 <= by1 && by1 <= ay2)))
			return true;

		return false;
	}

	// Convert relative bounding box for object to absolute world box
	Box Utility::getWorldBox(const Object* p_o)
	{
		return getWorldBox(p_o, p_o->getPosition());

	}
	Box Utility::getWorldBox(const Object* p_o, Vector where)
	{
		Box temp_box = p_o->getBox();
		Vector corner = temp_box.getCorner();

		corner.setX(corner.getX() + where.getX());
		corner.setY(corner.getY() + where.getY());
		temp_box.setCorner(corner);
		return temp_box;
	}


	// Convert world position to view position
	Vector Utility::worldToView(Vector world_pos) {
		Vector view_origin = WM.getView().getCorner();
		float view_x = view_origin.getX();
		float view_y = view_origin.getY();

		Vector view_pos(world_pos.getX() - view_x, world_pos.getY() - view_y);
		return view_pos;
	}

	Vector Utility::viewToWorld(Vector view_pos) {
		Vector view_origin = WM.getView().getCorner();
		float view_x = view_origin.getX();
		float view_y = view_origin.getY();

		Vector view_world(view_pos.getX() + view_x, view_pos.getY() + view_y);
		return view_world;
	}


	// Convert int to a string, returning a string
	std::string Utility::toString(int i) {
		std::stringstream ss;			// Create Stringstream
		ss << i;						// Add number to stream
		return ss.str();				// reutnr string 

	}

}