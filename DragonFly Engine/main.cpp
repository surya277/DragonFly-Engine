#include "Manager.h"
#include "GameManager.h"

#include<iostream>

int main(int argc, char* argv[]) {
	std::cout << "Hello";
	GM.startUp();

	GM.run();

	GM.shutDown();

}