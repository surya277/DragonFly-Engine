#include "DisplayManager.h"
#include "LogManager.h"
#include "Utility.h"

namespace df {
	DisplayManager::DisplayManager() {
		setType("DisplayManager"); 
		m_window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
		m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;
		m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
		m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;
		m_p_window = NULL;
		m_window_background_color = WINDOW_BACKGROUND_COLOR_DEFAULT;
	}

	DisplayManager& DisplayManager::getInstance() {
		static DisplayManager DisplayManagerSingle;
		return DisplayManagerSingle;
	}

	int DisplayManager::startUp() {
		if (Manager::isStarted())
			LM.writeLog("DisplayManager has already been started\n");

		if (m_p_window != NULL)
			return 0;
		
		// Create Window to draw on
		m_p_window = new sf::RenderWindow(sf::VideoMode(m_window_horizontal_pixels, m_window_vertical_pixels), "Dragonfly Engine");

		// Turn off mouse cursor for window
		m_p_window->setMouseCursorVisible(false);

		// Synchronize refresh rate with monitor
		m_p_window->setVerticalSyncEnabled(true);

		// load font
		m_font.loadFromFile("df-font.ttf");

		// Check if everything loaded properly
		if (!m_p_window) {
			Manager::startUp();
			return -1;
		}
		else {
			return 0;
		}

	} 

	// Draw a character at window location with color
	int DisplayManager::drawCh(Vector world_pos, char ch, Color color) const {

		// Check and make sure window is allocated
		if (m_p_window == NULL)
			return -1;
		
		// Convert from world pos to viewport pos
		Vector view_pos = Utility::worldToView(world_pos);

		// Convert spaces to pixels
		Vector pixel_pos = spacesToPixels(view_pos);

		// Draw Rectangular bacground since text is "see through" in SFML
		static sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(charWidth(), charHeight()));
		rectangle.setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);
		rectangle.setPosition(pixel_pos.getX() - charWidth() / 10, pixel_pos.getY() + charHeight() / 5);
		m_p_window->draw(rectangle);


		// Create Character text to draw
		static sf::Text text("", m_font);
		text.setString(ch);
		text.setStyle(sf::Text::Bold);

		// Scale to right size
		if (charWidth() > charHeight())
			text.setCharacterSize(charWidth() * 2);
		else
			text.setCharacterSize(charHeight() * 2);

		switch (color) {
		case YELLOW:
			text.setFillColor(sf::Color::Yellow);
			break;
		case RED:
			text.setFillColor(sf::Color::Red);
			break;
		case BLACK:
			text.setFillColor(sf::Color::Black);
			break;
		case GREEN:
			text.setFillColor(sf::Color::Green);
			break;
		case BLUE:
			text.setFillColor(sf::Color::Blue);
			break;
		case MAGENTA:
			text.setFillColor(sf::Color::Magenta);
			break;
		case CYAN:
			text.setFillColor(sf::Color::Cyan);
			break;
		case WHITE:
			text.setFillColor(sf::Color::White);
			break;
		}

		
		// Set position in window
		text.setPosition(pixel_pos.getX(), pixel_pos.getY());

		// Draw Character
		m_p_window->draw(text);


	}


	// Draw String at window location (x,y) with default color
	// Justified left, center or right
	// Return 0 if ok, else -1
	int DisplayManager::drawString(Vector pos, std::string str, Justification just, Color color) const{
		Vector start_pos = pos;
		switch (just) {
		case CENTER_JUSTIFIED:
			start_pos.setX(pos.getX() - str.size() / 2);
			break;
		case RIGHT_JUSTIFIED:
			start_pos.setX(pos.getX() - str.size());
			break;
		}

		for (int i = 0; i < str.size(); i++) {
			Vector temp_pos(start_pos.getX() + i, start_pos.getY());
			drawCh(temp_pos, str[i], color);
		}

		return 0;
	}

	// Return window's Horizontal characters maximum 
	int DisplayManager::getHorizontal() const {
		return m_window_horizontal_chars;
	}

	// Return window's Vertical characters maximum 
	int DisplayManager::getVertical() const {
		return m_window_vertical_chars;
	}

	// Return window's Horizontal pixels maximum 
	int DisplayManager::getHorizontalPixels() const {
		return m_window_horizontal_pixels;
	}

	// Return window's Vertical pixels maximum 
	int DisplayManager::getVerticalPixels() const {
		return m_window_vertical_pixels;
	}

	// Render Current window buffer
	// Return 0 if okay, else -1
	int DisplayManager::swapBuffers() {
		// Check if window is allocated
		if (m_p_window == NULL)
			return -1;
		
		// Display Current Window
		m_p_window->display();

		// Clear Other window to get ready for next draw
		m_p_window->clear(m_window_background_color);

		return 0;

	}
	
	// Return pointer to SFML window
	sf::RenderWindow* DisplayManager::getWindow() const {
		return m_p_window;
	}

	// Return Character height (window pixel height/ window character height)
	float DisplayManager::charHeight() const {
		return m_window_vertical_pixels / m_window_vertical_chars;
	}

	// Return character width (window pixel width / window character width)
	float DisplayManager::charWidth() const {
		return m_window_horizontal_pixels / m_window_horizontal_chars;
	}

	// Convert ASCII spaces to window pixels
	Vector DisplayManager::spacesToPixels(Vector spaces) const {
		Vector v;
		v.setX(spaces.getX() * charWidth());
		v.setY(spaces.getY() * charHeight());
		return v;
	}

	// Convert window pixels to ASCII spaces
	Vector DisplayManager::pixelsToSpaces(Vector pixels) const {
		Vector v;
		v.setX(pixels.getX() / charWidth());
		v.setY(pixels.getY() / charHeight());
		return v;
	}

	// Set default Background Color
	bool DisplayManager::setBackgroundColor(int new_color) {
		switch (new_color) {
		case YELLOW:
			m_window_background_color = sf::Color::Yellow;
			break;
		case RED:
			m_window_background_color = sf::Color::Red;
			break;
		case WHITE:
			m_window_background_color = sf::Color::White;
			break;
		case BLACK:
			m_window_background_color = sf::Color::Black;
			break;
		case GREEN:
			m_window_background_color = sf::Color::Green;
			break;
		case MAGENTA:
			m_window_background_color = sf::Color::Magenta;
			break;
		case CYAN:
			m_window_background_color = sf::Color::Cyan;
			break;
		case BLUE:
			m_window_background_color = sf::Color::Blue;
			break;

		default:
			return false;
		}
		return true;
	}


	// Close graphics Window
	void DisplayManager::shutDown() {
		Manager::shutDown();
	}
}