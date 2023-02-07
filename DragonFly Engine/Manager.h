#pragma once
#include <string>


#include "Event.h"


namespace df {

	class Manager
	{

	private:
		std::string m_type;
		bool m_is_started;

	protected:
		// Set type identifier of Manager
		// Is protected since we want only the base class and its derived classes to be able set the type
		void setType(std::string type);		

	public:
		Manager();
		virtual ~Manager();

		//Get type identifier of Manager
		std::string getType() const;

		//Startup Manager
		virtual int startUp();
		

		//Shutdown Manager
		virtual void shutDown();

		//returns true if startUp was executed OK else false
		bool isStarted() const;

		int onEvent(const Event* p_event) const;

	};

}