#include <string>

#include <SFML/Graphics.hpp>

void drawText(sf::RenderWindow& window, const sf::Font FONT, const int X, const int Y, const bool CENTERED, const std::string CONTENTS, const size_t CHARACTER_SIZE, const sf::Color COLOR);
void drawRect(sf::RenderWindow& window, const int X, const int Y, const int WIDTH, const int HEIGHT, const sf::Color COLOR);
void drawOutlineRect(sf::RenderWindow& window, const int X, const int Y, const int WIDTH, const int HEIGHT, const sf::Color COLOR, const int OUTLINE_THICKNESS, const sf::Color OUTLINE_COLOR);
