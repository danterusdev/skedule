#include "DrawUtil.h"
#include "Event.h"
#include "MenuCreateEvent.h"

#include <iostream>

#include <SFML/Graphics.hpp>

MenuCreateEvent::MenuCreateEvent(Calendar* const CALENDAR) : Menu(CALENDAR) {
    _font = new sf::Font();
    _font->loadFromFile("assets/Roboto-Regular.ttf");
}

void MenuCreateEvent::draw(sf::RenderWindow& window) const {
    drawRect(window, 0, 0, window.getSize().x / 3, window.getSize().y, sf::Color(120, 120, 120));

    drawText(window, *_font, window.getSize().x / 6, 15, true, "Create Event", 32, sf::Color::Black);

    drawText(window, *_font, 15, 103, false, "Name:", 18, sf::Color::Black);
    drawRect(window, 80, 100, 200, 30, sf::Color(80, 80, 80));
    drawText(window, *_font, 85, 105, false, _name, 15, sf::Color::Black);

    drawRect(window, window.getSize().x / 3 - 100, window.getSize().y - 40, 90, 30, sf::Color(80, 80, 80));
}

void MenuCreateEvent::handleMouseClick(sf::Event& event) {
    _eventNameFieldSelected = event.mouseButton.x > 80 && event.mouseButton.x < 300 && event.mouseButton.y > 100 && event.mouseButton.y < 140;

    if (event.mouseButton.x > _windowWidth / 3 - 100 && event.mouseButton.x < _windowWidth / 3 - 10 && event.mouseButton.y > _windowHeight - 40 && event.mouseButton.y < _windowHeight - 10) {
        _parent->addItem(new Event(_name, Time(2023, 10, 5, 3, 30)));
        _parent->resetMenu();
    }
}

void MenuCreateEvent::handleMouseMove(State& state, sf::Event& event) {
    if (event.mouseMove.x > 80 && event.mouseMove.x < 280 && event.mouseMove.y > 100 && event.mouseMove.y < 130) {
        state.cursorType = sf::Cursor::Hand;
    }

    if (event.mouseMove.x > _windowWidth / 3 - 100 && event.mouseMove.x < _windowWidth / 3 - 10 && event.mouseMove.y > _windowHeight - 40 && event.mouseMove.y < _windowHeight - 10) {
        state.cursorType = sf::Cursor::Hand;
    }
}

void MenuCreateEvent::handleTextEnter(sf::Event& event) {
    if (_eventNameFieldSelected) {
        if (event.text.unicode == 8) {
            if (_name.size() > 0) {
                _name.pop_back();
            }
        } else if (_name.size() < 23) {
            _name.push_back((char) event.text.unicode);
        }
    }
    (void) event;
}

void MenuCreateEvent::setWindowSize(const int X, const int Y) {
    _windowWidth = X;
    _windowHeight = Y;
}
