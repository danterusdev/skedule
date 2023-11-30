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

    srand(time(0));
    rand();

    //for (int i = 0; i < 50; i++) {
    //    calendar.addItem(new Event("whats up pog", Time(2023, 10, rand() % 30, 5, 54)));
    //}

    State state;
    state.cursorType = sf::Cursor::Arrow;

    calendar.setDisplayed(Month(2023, 10));
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                calendar.handleMouseClick(event);
            } else if (event.type == sf::Event::TextEntered) {
                calendar.handleTextEnter(event);
            } else if (event.type == sf::Event::Resized) {
                calendar.setWindowSize(event.size.width, event.size.height);
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
