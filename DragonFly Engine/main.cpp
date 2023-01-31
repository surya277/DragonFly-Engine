#include "Manager.h"
#include "LogManager.h"

#include<iostream>

int main(int argc, char* argv[]) {
	std::cout << "Hello";
	LM.writeLog("Hello Log Manager \n");
	LM.writeLog("Log Manager Running. \n");
	LM.writeLog("DisplayManger::startUp() : max X is %d, max Y is %d", 10, 20);

}