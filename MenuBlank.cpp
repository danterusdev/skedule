#include "DrawUtil.h"
#include "MenuBlank.h"

#include <iostream>

#include <SFML/Graphics.hpp>

void MenuBlank::draw(sf::RenderWindow& window) const {
    // A blank menu
    drawRect(window, 0, 0, window.getSize().x / 3, window.getSize().y, sf::Color(120, 120, 120));
}

void MenuBlank::handleMouseClick(sf::Event& event) {
    (void) event;
}

void MenuBlank::handleMouseMove(State& state, sf::Event& event) {
    (void) state;
    (void) event;
}

void MenuBlank::handleTextEnter(sf::Event& event) {
    (void) event;
}

void MenuBlank::setWindowSize(const int X, const int Y) {
    (void) X;
    (void) Y;
}
