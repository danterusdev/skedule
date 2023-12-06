/**
 * Final Project: Skedule
 *
 * This is a gui calendar app where the user can create and delete events
 * and schedule them for a specific date and time.
 */

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

    // getting the current date
    std::time_t time = std::time(0);
    std::tm* pNow = std::localtime(&time);

    calendar.setWindowSize(1280, 720);

    calendar.setDisplayed(Month(pNow->tm_year + 1900, pNow->tm_mon));
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
                // Handle how the change the cursor if hovering over a button
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
