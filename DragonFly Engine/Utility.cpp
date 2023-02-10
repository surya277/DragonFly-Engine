#include "Utility.h"


#include<ctime>
#include<iostream>

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
}