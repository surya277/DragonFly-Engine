#include "Manager.h"
#include "GameManager.h"
#include "Vector.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "Object.h"
#include "ObjectList.h"
#include "ObjectListIterator.h";


#include <iostream>
#include <assert.h>

#include<iostream>
void VectorTest();
void ObjectTest();
void WorldManagerTest();

int main(int argc, char* argv[]) {
	std::cout << "Hello";
	GM.startUp();

	GM.run();

	VectorTest();
	ObjectTest();
	WorldManagerTest();

	GM.shutDown();

}

void VectorTest() {
	LM.writeLog("\n\n VECTOR TEST \n\n");

	df::Vector vec = df::Vector(4.0f, 3.0f);
	LM.writeLog("Vector X, Y Coordinate: %f  %f\n", vec.getX(), vec.getY());

	LM.writeLog("Magnitude of Vector: %f \n", vec.getMagnitude());

	vec.scale(2.0);
	LM.writeLog("Scaled Vector: %f  %f \n", vec.getX(),vec.getY());

	df::Vector vec1 = df::Vector(3.0f, 5.0f);
	df::Vector vec2 = vec + vec1;
	LM.writeLog("Vector Addition %f %f \n", vec2.getX(), vec2.getY());
}

void ObjectTest() {
	LM.writeLog("\n\n OBJECT TEST \n\n");

	df::Object* newObj = new df::Object();
	newObj->setType("Saucer");
	std::cout << newObj->getType();

	LM.writeLog("Object Type: %s \n", newObj->getType());
	LM.writeLog("Object ID: %d \n", newObj->getId());

	df::Object* test_object2 = new df::Object();
	test_object2->setType("Hero");

	df::ObjectList test_object_list = WM.getAllObjects();
	LM.writeLog("Object Count: ", test_object_list.getCount());

}


void WorldManagerTest() {
	df::Object* test_object = new df::Object();
	test_object->setType("Saucer");

	df::Object* test_object2 = new df::Object();
	test_object2->setType("Hero");

		
	df::ObjectList test_object_list = WM.getAllObjects();
	std::cout << "\n Count:"<<test_object_list.getCount();
	//df::ObjectListIterator = df::ObjectListIterator(test_object_list);
	
	

}
