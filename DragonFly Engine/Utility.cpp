#include "Utility.h"
#include<ctime>
#include<iostream>

// Get Current Time
// 
char* df::Utility::getTimeString() {

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