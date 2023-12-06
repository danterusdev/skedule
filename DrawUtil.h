#include <string>

#include <SFML/Graphics.hpp>

/**
 * Draws text to the screen
 *
 * @param window the window to draw to
 * @param FONT the font to use
 * @param X the x location ot the text
 * @param Y the y location ot the text
 * @param CENTERED whether the text should be centered
 * @param CONTENTS the string to draw
 * @param CHARACTER_SIZE the font size to use
 * @param COLOR the color of the text
 */
void drawText(sf::RenderWindow& window, const sf::Font FONT, const int X, const int Y, const bool CENTERED, const std::string CONTENTS, const size_t CHARACTER_SIZE, const sf::Color COLOR);

/**
 * Draws a filled rectangle
 *
 * @param window the window to draw to
 * @param X the x location of the rect
 * @param Y the y location of the rect
 * @param WIDTH the width of the rect
 * @param HEIGHT the height of the rect
 * @param COLOR the color of the rect
 */
void drawRect(sf::RenderWindow& window, const int X, const int Y, const int WIDTH, const int HEIGHT, const sf::Color COLOR);

/**
 * Draws a filled rectangle with an outline
 *
 * @param window the window to draw to
 * @param X the x location of the rect
 * @param Y the y location of the rect
 * @param WIDTH the width of the rect
 * @param HEIGHT the height of the rect
 * @param COLOR the color of the rect
 * @param OUTLINE_THICKNESS the thickness of the outline to use
 * @param OUTLINE_COLOR the color of the outline
 */
void drawOutlineRect(sf::RenderWindow& window, const int X, const int Y, const int WIDTH, const int HEIGHT, const sf::Color COLOR, const int OUTLINE_THICKNESS, const sf::Color OUTLINE_COLOR);
