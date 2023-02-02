#include "Manager.h"
#include "GameManager.h"
#include "Vector.h"
#include "LogManager.h"
#include "Object.h"
#include <iostream>

#include<iostream>
void VectorTest();
void ObjectTest();

int main(int argc, char* argv[]) {
	std::cout << "Hello";
	GM.startUp();

	GM.run();

	VectorTest();
	ObjectTest();

	GM.shutDown();

}

void VectorTest() {
		df::Vector vec = df::Vector(2.0f, 1.0f);
		vec.setX(3.0f);
		LM.writeLog("Vector X Coordinate: %f \n", vec.getX());
		LM.writeLog("Magnitude of Vector: %f \n", vec.getMagnitude());
		vec.scale(2.0);
		LM.writeLog("Scaled Vector: %f  %f \n", vec.getX(),vec.getY());
		df::Vector vec1 = df::Vector(3.0f, 5.0f);
		df::Vector vec2 = vec + vec1;
		LM.writeLog("Vector Addition %f %f \n", vec2.getX(), vec2.getY());
}

void ObjectTest() {
	df::Object newObj;
	newObj.setType("Saucer");
	std::cout << newObj.getType();
	LM.writeLog("Object Type: %c \n", newObj.getType());
	LM.writeLog("Object ID: %d \n", newObj.getId());
}