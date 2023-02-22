#pragma once

#include <string>

#include "Object.h"
#include "Event.h"

namespace df {

	enum ViewObjectLocation {
		UNDEFINED = -1,
		TOP_LEFT,
		TOP_CENTER,
		TOP_RIGHT,
		CENTER_LEFT,
		CENTER_CENTER,
		CENTER_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_CENTER,
		BOTTOM_RIGHT
	};


	class ViewObject : public Object
	{
	private:
		std::string view_string;			//Label for value
		int m_value;						// Value dispalyed
		bool m_draw_value;					// True if should draw value
		bool m_border;						// True if border around display
		Color m_color;						// Color for text (and border)
		ViewObjectLocation m_location;		// Location of ViewObject


	public:

		// Construct ViewObject
		// Object settings: SPECTRAL, max alt
		// ViewObject defaults: border, top-center, default color, draw_value
		ViewObject();

		// Draw view string and value
		virtual int draw() override;

		// Handle 'view' event if tag matches view_string (Others ignored) 
		// Return 0 if ignored else 1 if handled
		virtual int eventHandler(const Event* p_e) override;

		// Set General Location of Viewobject on screen
		void setLocation(ViewObjectLocation new_location);

		// Get general Location of Viewobject on screen
		ViewObjectLocation getLocation() const;

		// Set view value
		void setValue(int new_value);

		// Get view value
		int getValue() const;

		// Set view border (true = display border)
		void setBorder(bool new_border);

		// Get view border (true = display border)
		bool getBorder() const;

		// set view color
		void setColor(Color new_color);

		// get view color
		Color getColor() const;

		// set view display string
		void setViewString(std::string new_view_string);

		// Get view display string
		std::string getViewString() const;

		// Set true to draw value with display string
		void setDrawValue(bool new_draw_value = true);

		// Get draw value (true if draw value with display string)
		bool getDrawValue() const;
	};	


}

