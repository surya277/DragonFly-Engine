#include "Manager.h"
#include "ObjectList.h"
#include "WorldManager.h"



df::Manager::Manager() {
	m_is_started = false;
}


int df::Manager::startUp() {
	m_is_started = true;
	return 0;
}



void df::Manager::shutDown() {
	m_is_started = false;
}



bool df::Manager::isStarted() const {
	return m_is_started;
}


void df::Manager::setType(std::string type) {
	m_type = "Manager";
	//m_type = type;
}



std::string df::Manager::getType() const{
	return m_type;
}


// Sending Events to all Objects
int df::Manager::onEvent(const Event* p_event) const {
	int count = 0;

	ObjectList all_objects = WM.getAllObjects();								// Get all Objects in the World 

	ObjectListIterator all_objects_itr(&all_objects);

	while (!all_objects_itr.isDone()) {
		all_objects_itr.currentObject()->eventHandler(p_event);					// Get Current Object from iterator and access eventHandler function passing p_event to that Objects Function
		all_objects_itr.next();
		count++;
	}
	return count;
}


df::Manager::~Manager() {
	shutDown();

}




