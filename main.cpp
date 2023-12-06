#include "Calendar.h"
#include "Event.h"
#include "State.h"

#include <cstdlib>
#include <ctime>

#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Skedule");
    window.setFramerateLimit(30);

    Calendar calendar;
    calendar.loadFromFile();

    srand(time(0));
    rand();

    State state;
    state.cursorType = sf::Cursor::Arrow;

    std::time_t time = std::time(0);
    std::tm* now = std::localtime(&time);

    calendar.setWindowSize(1280, 720);

    calendar.setDisplayed(Month(now->tm_year + 1900, now->tm_mon));
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                calendar.handleMouseClick(event);
            } else if (event.type == sf::Event::TextEntered) {
                calendar.handleTextEnter(event);
            } else if (event.type == sf::Event::MouseMoved) {
                state.cursorType = sf::Cursor::Arrow;
                calendar.handleMouseMove(state, event);

                sf::Cursor cursor;
                cursor.loadFromSystem(state.cursorType);
                window.setMouseCursor(cursor);
            }
        }

        window.clear(sf::Color(170, 170, 170, 255));

        calendar.draw(window);

        window.display();
    }

    return 0;
}
