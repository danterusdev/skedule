#include "DrawUtil.h"

void drawText(sf::RenderWindow& window, const sf::Font FONT, const int X, const int Y, const bool CENTERED, const std::string CONTENTS, const size_t CHARACTER_SIZE, const sf::Color COLOR) {
    sf::Text title;
    title.setFont(FONT);
    title.setString(CONTENTS);
    title.setCharacterSize(CHARACTER_SIZE);
    title.setFillColor(COLOR);
    if (CENTERED) {
        title.setPosition(X - title.getLocalBounds().getSize().x / 2, Y);
    } else {
        title.setPosition(X, Y);
    };
    window.draw(title);
}

void drawRect(sf::RenderWindow& window, const int X, const int Y, const int WIDTH, const int HEIGHT, const sf::Color COLOR) {
    sf::RectangleShape newButton;
    newButton.setPosition(X, Y);
    newButton.setSize(sf::Vector2f(WIDTH, HEIGHT));
    newButton.setFillColor(COLOR);
    window.draw(newButton);
}

void drawOutlineRect(sf::RenderWindow& window, const int X, const int Y, const int WIDTH, const int HEIGHT, const sf::Color COLOR, const int OUTLINE_THICKNESS, const sf::Color OUTLINE_COLOR) {
    sf::RectangleShape newButton;
    newButton.setPosition(X, Y);
    newButton.setSize(sf::Vector2f(WIDTH, HEIGHT));
    newButton.setFillColor(COLOR);
    newButton.setOutlineThickness(OUTLINE_THICKNESS);
    newButton.setOutlineColor(OUTLINE_COLOR);
    window.draw(newButton);
}
