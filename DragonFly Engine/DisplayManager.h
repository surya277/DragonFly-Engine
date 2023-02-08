#pragma once
#include <SFML/Graphics.hpp>

#include "Color.h"
#include "Vector.h"
#include "Manager.h"



#define DM df::DisplayManager::getInstance()

namespace df {
	
	const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
	const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
	const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 80;
	const int WINDOW_VERTICAL_CHARS_DEFAULT = 24;
	const int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar;
	const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black;
	const std::string WINDOW_TITLE_DEFAULT = "Dragonfly Engine";
	const std::string FONT_FILE_DEFAULT = "df-font.ttf";

	enum Justification {
		LEFT_JUSTIFIED,
		RIGHT_JUSTIFIED,
		CENTER_JUSTIFIED
	};

	class DisplayManager : public Manager
	{
	private:
		DisplayManager();										// Private (Singleton)
		DisplayManager(DisplayManager const&);					// Don't allow copy
		void operator=(DisplayManager const&);					// Don't allow assignment
		sf::Font m_font;										// Font used
		sf::RenderWindow* m_p_window;							// pointed to SFML window
		int m_window_horizontal_pixels;							// Horizontal Pixels in Window
		int m_window_vertical_pixels;							// Vertical pixels in Window
		int m_window_horizontal_chars;							// Horizontal ASCII spaces in window
		int m_window_vertical_chars;							// Vertical ASCII spaces in window

		sf::Color m_window_background_color;

	public:

		// Get one and only instance of display manger
		static DisplayManager& getInstance();

		// Open graphics window
		// Return 0 if ok, else -1
		int startUp();

		// Close graphics window
		void shutDown();

		// Draw Character at window location
		int drawCh(Vector worl_pos, char ch, Color color) const;

		// Return window horizontal characters maximum
		int getHorizontal() const;

		// Return window Vertical character maximum
		int getVertical() const;

		// Return window Horizontal pixels maximum
		int getHorizontalPixels() const;

		// Return window Vertical pixels maximum
		int getVerticalPixels() const;


		// Render current window buffer
		// Return 0 if ok, else -1
		int swapBuffers();

		// Return pointer to SFML graphics window
		sf::RenderWindow* getWindow() const;

		// Compute Character height, based on window size and font
		float charHeight() const;

		// Compute Character width, based on window size and font
		float charWidth() const;

		// Convert ASCII spaces to window pixels
		Vector spacesToPixels(Vector spaces) const;

		// Convert window pixels to ASCII spaces
		Vector pixelsToSpaces(Vector pixels) const;


		// Draw String at window location (x,y) with default color
		// Justified left, center or right
		// Return 0 if ok, else -1
		int drawString(Vector pos, std::string str, Justification just, Color color) const;


		// Set default Color
		// Return true if ok else false
		bool setBackgroundColor(int new_color);
	};

}

