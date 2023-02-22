#include "ViewObject.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "Utility.h"
#include "EventView.h"


namespace df {
	// Construct ViewObject
		// Object settings: SPECTRAL, max alt
		// ViewObject defaults: border, top-center, default color, draw_value
	ViewObject::ViewObject() {

		// Initialize Object attributes
		setSolidness(SPECTRAL);
		setAltitude(MAX_ALTITUDE);
		setType("ViewObject");

		// Initialize ViewObject attributes
		setValue(0);
		setDrawValue();
		setBorder(true);
		setLocation(TOP_CENTER);
		setColor(COLOR_DEFAULT);

		// Register interest in view events
	}

	void ViewObject::setLocation(ViewObjectLocation new_location) {

		// Set new position based on location
		Vector p;
		float y_delta = 0.0f;
		switch (new_location) {
		case TOP_LEFT:
			p.setXY(WM.getView().getHorizontal() * 1 / 6, 1);
			if (getBorder() == false)
				y_delta = -1;
			break;
		case TOP_CENTER:
			p.setXY(WM.getView().getHorizontal() * 3 / 6, 1);
			if (getBorder() == false)
				y_delta = -1;
			break;
		case TOP_RIGHT:
			p.setXY(WM.getView().getHorizontal() * 5 / 6, 1);
			if (getBorder() == false)
				y_delta = -1;
			break;
		case CENTER_RIGHT:
			p.setXY(WM.getView().getHorizontal() * 1 / 6, WM.getView().getVertical() / 2);
			if (getBorder() == false)
				y_delta = 0;
			break;
		case CENTER_CENTER:
			p.setXY(WM.getView().getHorizontal() * 3 / 6, WM.getView().getVertical() / 2);
			if (getBorder() == false)
				y_delta = 0;
			break;
		case CENTER_LEFT:
			p.setXY(WM.getView().getHorizontal() * 5 / 6, WM.getView().getVertical() / 2);
			if (getBorder() == false)
				y_delta = 0;
			break;
		case BOTTOM_RIGHT:
			p.setXY(WM.getView().getHorizontal() * 1 / 6, WM.getView().getVertical() - 1);
			if (getBorder() == false)
				y_delta = 1;
			break;
		case BOTTOM_CENTER:
			p.setXY(WM.getView().getHorizontal() * 3 / 6, WM.getView().getVertical() - 1);
			if (getBorder() == false)
				y_delta = 1;
			break;
		case BOTTOM_LEFT:
			p.setXY(WM.getView().getHorizontal() * 5 / 6, WM.getView().getVertical() - 1);
			if (getBorder() == false)
				y_delta = 1;
			break;
		}

		// Shift, as needed, based on border
		p.setY(p.getY() + y_delta);

		// Set Position of object to new position
		setPosition(p);

		// Set new location
		m_location = new_location;
	}

	// Get general Location of Viewobject on screen
	ViewObjectLocation ViewObject::getLocation() const {
		return m_location;
	}

	// Set view value
	void ViewObject::setValue(int new_value) {
		m_value = new_value;
	}

	// Get view value
	int ViewObject::getValue() const {
		return m_value;
	}

	// Set view border (true = display border)
	void ViewObject::setBorder(bool new_border) {
		if (m_border != new_border) {
			m_border = new_border;

			// Reset location to account for border setting
			setLocation(getLocation());
		}
	}

	// Get view border (true = display border)
	bool ViewObject::getBorder() const {
		return m_border;
	}

	// set view color
	void ViewObject::setColor(Color new_color) {
		m_color = new_color;
	}

	// get view color
	Color ViewObject::getColor() const {
		return m_color;
	}

	// Draw view string and value
	int ViewObject::draw() {

		std::string temp_str;
		// Display view_string + value
		if (m_border == true) {
			temp_str = " " + getViewString() + " " + Utility::toString(m_value) + " ";
		}
		else {
			temp_str = getViewString() + " " + Utility::toString(m_value);
		}

		// Draw centered at position
		Vector pos = Utility::viewToWorld(getPosition());
		DM.drawString(pos, temp_str, CENTER_JUSTIFIED, getColor());

		if (m_border) {
			// draw Border
		}

		return 0;
	}

	// set view display string
	void ViewObject::setViewString(std::string new_view_string) {
		view_string = new_view_string;
	}

	// Get view display string
	std::string ViewObject::getViewString() const {
		return view_string;
	}

	// Set true to draw value with display string
	void ViewObject::setDrawValue(bool new_draw_value) {
		m_draw_value = new_draw_value;
	}

	// Get draw value (true if draw value with display string)
	bool ViewObject::getDrawValue() const {
		return m_draw_value;
	}


	// Handle 'view' event if tag matches view_string (Others ignored) 
	// Return 0 if ignored else 1 if handled
	int ViewObject::eventHandler(const Event* p_e) {
		
		// See if this is view event
		if (p_e->getType() == VIEW_EVENT) {
			const EventView* p_ve = static_cast<const EventView*> (p_e);

			// See if this event is meant for this object
			if (p_ve->getTag() == getViewString()) {
				if (p_ve->getDelta()) {
					setValue(getValue() + p_ve->getValue());
				}
				else {
					setValue(p_ve->getValue());
				}
				return 1;
			}

		}
		// if Here, Event not handled
		return 0;
	}
}
