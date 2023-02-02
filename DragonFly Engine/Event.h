#pragma once

#include <string>

const std::string UNDEFINED_EVENT = "df::undefined";

namespace df {

	class Event
	{
	private:
		std::string m_event_type;				// Stores event type

	public:
		
		Event();

		virtual ~Event();

		// Set event type
		void setType(std::string new_type);
		
		// Get event type;
		std::string getType() const;
	};
}

