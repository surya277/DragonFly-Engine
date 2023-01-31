#include "Manager.h"



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


df::Manager::~Manager() {
	shutDown();

}




