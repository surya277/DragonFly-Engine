#include "Manager.h"
#include "GameManager.h"
#include "Vector.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "Object.h"
#include "ObjectList.h"
#include "ObjectListIterator.h";
#include "Clock.h"
#include "Event.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "EventStep.h"
#include "EventOut.h"
#include "DisplayManager.h"
#include "InputManager.h"

#include <iostream>
#include <Windows.h>
#include <assert.h>

#include<iostream>

bool gameManagerTest();
bool vectorTest();
void objectTest();
bool clockTest();
bool eventTest();
bool worldManagerTest();
bool DisplayTest();
bool InputTest();

int main(int argc, char* argv[]) {
	std::cout << "Hello";
	//GM.startUp();
	//if (clockTest())
	//	puts("\nPASS");
	//else
	//	puts("\nFAIL");

	//if (vectorTest())
	//	puts("\nPASS");
	//else
	//	puts("\nFAIL");
	

	gameManagerTest();
	
	//GM.run();
	//objectTest();
	//worldManagerTest();
	//eventTest();
	//GM.shutDown();

}

bool gameManagerTest() {
	GM.startUp();

	DisplayTest();

	GM.run();
	
	GM.shutDown();
	return true;
}

// INPUT TEST, OBJECT TEST, EVENT TEST
class Hero : public df::Object {

public:
	Hero() {
		setType("Hero");

		df::Vector pos(7.0f, DM.getVertical() / 2.0f);
		setPosition(pos);
	}

	// TEST EVENTS
	int eventHandler(const df::Event* p_e) {
		if (p_e->getType() == df::KEYBOARD_EVENT) {
			const df::EventKeyboard* p_keyboard_event = dynamic_cast <const df::EventKeyboard*> (p_e);
			kbd(p_keyboard_event);
			return 1;
		}

		if (p_e->getType() == df::MSE_EVENT) {
			const df::EventMouse* p_mouse_event = dynamic_cast <const df::EventMouse*> (p_e);
			mouse(p_mouse_event);
			return 1;
		}

		if (p_e->getType() == df::COLLISION_EVENT) {
			LM.writeLog("COLLISION OCCURED\n");
		}

		if (p_e->getType() == df::STEP_EVENT) {
			LM.writeLog("STEP EVENT\n");
			return 1;
		}

		if (p_e->getType() == df::OUT_EVENT) {
			LM.writeLog("OUT EVENT\n");
			return 1;
		}

		// If get here, have ignored this event.
		return 0;
	}

	void mouse(const df::EventMouse* p_mouse_event) {
		// Pressed button?
		if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
			(p_mouse_event->getMouseButton() == df::Mouse::LEFT))
			std::cout << "Left Mouse Button Clicked\n";

		if ((p_mouse_event->getMouseAction() == df::MOVED))
			std::cout << "MOUSE MOVED\n";
	}

	// Take appropriate action according to key pressed.
	void kbd(const df::EventKeyboard* p_keyboard_event) {

		switch (p_keyboard_event->getKey()) {
		case df::Keyboard::W:			// up
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
				move(-1);
			break;
		case df::Keyboard::S:			// down
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
				move(+1);
			break;
			break;
		case df::Keyboard::Q:			// quit
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
				WM.markForDelete(this);
			break;
		};

		return;
	}

	void move(int dy) {
		df::Vector new_pos(getPosition().getX(), getPosition().getY() + dy);
		// If stays on screen, allow move.
		//if ((new_pos.getY() >= 0) &&
		//	(new_pos.getY() < DM.getVertical()))
			WM.moveObject(this, new_pos);
	}


};



bool DisplayTest() {

	df::Object* test_object = new df::Object();
	test_object->setType("Hero");
	//test_object->setAltitude(2);
	test_object->setPosition(df::Vector(0, 0));
	test_object->setSolidness(df::HARD);
	test_object->setDirection(df::Vector(1, 0));
	test_object->setSpeed(0.5f);

	new Hero;

	df::Object* block_object = new df::Object();
	block_object->setType("Blocker");
	block_object->setAltitude(2);
	block_object->setPosition(df::Vector(30, 0));
	block_object->setSolidness(df::HARD);

	df::Object* block_object2 = new df::Object();
	block_object2->setPosition(df::Vector(7, 20));
	block_object2->setSolidness(df::SOFT);

	//df::Object* block_object2 = new df::Object();
	//block_object2->setPosition(df::Vector(7, 20));
	//block_object2->setSolidness(df::SPECTRAL);

	DM.drawString(df::Vector(7, 10), "HELLO", df::CENTER_JUSTIFIED, df::BLUE);
	return true;

}













bool clockTest() {
	df::Clock clock;

	clock.delta();			// Start Clock
	Sleep(1000);
	int t = (int) clock.split()/1000000;

	LM.writeLog("Split Time is :  %d \n", t);

	if (t != 1) {
		LM.writeLog("%s FAILED \n", __FUNCTION__);
		return false;
	}

	LM.writeLog("%s PASSED \n", __FUNCTION__);
	return true;

}

bool vectorTest() {
	LM.writeLog("\n\n VECTOR TEST \n\n");

	// Create Vector
	df::Vector vec = df::Vector(4.0f, 3.0f);
	LM.writeLog("Vector X, Y Coordinate: %f  %f\n", vec.getX(), vec.getY());

	// Magnitude of Vector
	LM.writeLog("Magnitude of Vector: %f \n", vec.getMagnitude());

	// Scale Vector by 2
	vec.scale(2.0);
	LM.writeLog("Scaling Vector by 2: %f , %f \n", vec.getX(),vec.getY());
	
	// New Vector
	df::Vector vec1 = df::Vector(3.0f, 5.0f);
	df::Vector vec2 = vec + vec1;
	LM.writeLog("Vector Addition with new 3,5 Vector: %f , %f \n", vec2.getX(), vec2.getY());

	// Check Test result
	if (vec2.getX() != 11.0f && vec2.getY() != 11.0f) {
		LM.writeLog("%s FAILED \n", __FUNCTION__);
		return false;
	}
	LM.writeLog("%s PASSED \n", __FUNCTION__);
	return true;

}

void objectTest() {
	LM.writeLog("\n\n OBJECT TEST \n\n");

	//Creating 2 Objects
	LM.writeLog("Creating 2 Objects\n");
	df::Object* newObj = new df::Object();
	newObj->setType("Saucer");

	df::Object* test_object2 = new df::Object();
	test_object2->setType("Hero");

	//Getting ObjectList from WM
	LM.writeLog("Getting ObjectList from World Manager\n");
	df::ObjectList test_object_list = WM.getAllObjects();

	// isFull, isEmpty, Count
	LM.writeLog("is Object List Empty: %d \n", test_object_list.isEmpty());
	LM.writeLog("is Object List Full: %d \n", test_object_list.isFull());
	LM.writeLog("Object Count: %d \n", test_object_list.getCount());

	// Using Iterator
	LM.writeLog("Iterating through List using ListIterator\n");
	df::ObjectListIterator list_itr(&test_object_list);
	for (list_itr.first(); !list_itr.isDone(); list_itr.next()) {
		LM.writeLog(" Object type : % s\n", list_itr.currentObject()->getType().c_str());
		LM.writeLog(" Object ID: %d \n", list_itr.currentObject()->getId());

	}


}

bool worldManagerTest() {
	LM.writeLog("\n\n WORLD MANAGER TEST \n\n");

	// Creating 2 Objects
	LM.writeLog("Creating 2 more Objects\n");
	df::Object* newObj = new df::Object();
	newObj->setType("Saucer");

	df::Object* test_object2 = new df::Object();
	test_object2->setType("Hero");

	// Getting Objects of one type
	df::ObjectList same_type_list = WM.ObjectsOfType("Saucer");
	LM.writeLog("Number of Saucer Objects: %d \n", same_type_list.getCount());

	// Removing one objects
	LM.writeLog("Removing Saucer using object pointer from World\n");
	WM.removeObject(newObj);
	LM.writeLog("Getting all Objects in World\n");
	df::ObjectList test_object_list = WM.getAllObjects();

	LM.writeLog("New Object Count: %d \n", test_object_list.getCount());

	//Marking for Delete
	LM.writeLog("Marking for Delete : ");
	if (WM.markForDelete(test_object2) == 0)
		LM.writeLog(" Success\n");
	else
		LM.writeLog(" Failed\n");

	// Update WM
	test_object_list.clear();
	LM.writeLog("List Count: %d", test_object_list.getCount());
	WM.removeObject(test_object2);
	WM.update();
	
	//LM.writeLog("After Deletion: %d\n", WM.getAllObjects().getCount());

	return true;

}

bool eventTest() {
	LM.writeLog("\n\n EVENT TEST \n\n");

	//Creating Event
	df::Event* new_event = new df::Event();
	new_event->setType("TEST_EVENT");

	df::EventStep step_event;

	LM.writeLog("New Event: %s \n", new_event->getType().c_str());
	if (new_event->getType() == "TEST_EVENT") {
		LM.writeLog("Success\n");
		return true;
	}
	
	return false;
}