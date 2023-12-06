#include "DrawUtil.h"
#include "Event.h"
#include "MenuCreateEvent.h"

#include <iostream>

#include <SFML/Graphics.hpp>

MenuCreateEvent::MenuCreateEvent(Calendar* const P_CALENDAR) : Menu(P_CALENDAR) {
    _font = new sf::Font();
    _font->loadFromFile("assets/Roboto-Regular.ttf");

    std::time_t time = std::time(0);
    std::tm* pNow = std::localtime(&time);

    _day = pNow->tm_mday;
    _month = pNow->tm_mon + 1;
    _year = pNow->tm_year + 1900;

    _eventNameFieldHovered = false;
    _eventYearFieldHovered = false;
    _eventMonthFieldHovered = false;
    _eventDayFieldHovered = false;
    _createButtonHovered = false;
    _creationError = false;
}

void MenuCreateEvent::draw(sf::RenderWindow& window) const {
    drawRect(window, 0, 0, window.getSize().x / 3, window.getSize().y, sf::Color(120, 120, 120));

    drawText(window, *_font, window.getSize().x / 6, 15, true, "Create Event", 32, sf::Color::Black);

    // Event Name Input
    drawText(window, *_font, 15, 103, false, "Name:", 18, sf::Color::Black);
    if (_eventNameFieldSelected) {
        drawOutlineRect(window, 80, 100, 200, 30, sf::Color(80, 80, 80), 2, sf::Color(50, 50, 50));
    } else if (_eventNameFieldHovered) {
        drawOutlineRect(window, 80, 100, 200, 30, sf::Color(80, 80, 80), 2, sf::Color(65, 65, 65));
    } else {
        drawRect(window, 80, 100, 200, 30, sf::Color(80, 80, 80));
    }
    drawText(window, *_font, 85, 105, false, _name, 15, sf::Color::Black);

    drawText(window, *_font, 15, 143, false, "Date:", 18, sf::Color::Black);

    // Event Year Input
    if (_eventYearFieldSelected) {
        drawOutlineRect(window, 80, 140, 50, 30, sf::Color(80, 80, 80), 2, sf::Color(50, 50, 50));
    } else if (_eventYearFieldHovered) {
        drawOutlineRect(window, 80, 140, 50, 30, sf::Color(80, 80, 80), 2, sf::Color(65, 65, 65));
    } else {
        drawRect(window, 80, 140, 50, 30, sf::Color(80, 80, 80));
    }
    if (_year > 0) {
        drawText(window, *_font, 85, 145, false, std::to_string(_year), 15, sf::Color::Black);
    }

    // Event Month Input
    if (_eventMonthFieldSelected) {
        drawOutlineRect(window, 160, 140, 50, 30, sf::Color(80, 80, 80), 2, sf::Color(50, 50, 50));
    } else if (_eventMonthFieldHovered) {
        drawOutlineRect(window, 160, 140, 50, 30, sf::Color(80, 80, 80), 2, sf::Color(65, 65, 65));
    } else {
        drawRect(window, 160, 140, 50, 30, sf::Color(80, 80, 80));
    }
    if (_month > 0) {
        drawText(window, *_font, 165, 145, false, std::to_string(_month), 15, sf::Color::Black);
    }

    // Event Day Input
    if (_eventDayFieldSelected) {
        drawOutlineRect(window, 240, 140, 50, 30, sf::Color(80, 80, 80), 2, sf::Color(50, 50, 50));
    } else if (_eventDayFieldHovered) {
        drawOutlineRect(window, 240, 140, 50, 30, sf::Color(80, 80, 80), 2, sf::Color(65, 65, 65));
    } else {
        drawRect(window, 240, 140, 50, 30, sf::Color(80, 80, 80));
    }
    if (_day > 0) {
        drawText(window, *_font, 245, 145, false, std::to_string(_day), 15, sf::Color::Black);
    }

    // Create Button
    if (_creationError) {
        drawOutlineRect(window, window.getSize().x / 3 - 100, 200, 90, 30, sf::Color(80, 80, 80), 2, sf::Color::Red);
    } else if (_createButtonHovered) {
        drawOutlineRect(window, window.getSize().x / 3 - 100, 200, 90, 30, sf::Color(80, 80, 80), 2, sf::Color(65, 65, 65));
    } else {
        drawRect(window, window.getSize().x / 3 - 100, 200, 90, 30, sf::Color(80, 80, 80));
    }
    drawText(window, *_font, window.getSize().x / 3 - 55, 205, true, "Create", 18, sf::Color::Black);
}

void MenuCreateEvent::handleMouseClick(sf::Event& event) {
    _eventNameFieldSelected = event.mouseButton.x > 80 && event.mouseButton.x < 280 && event.mouseButton.y > 100 && event.mouseButton.y < 130;
    _eventYearFieldSelected = event.mouseButton.x > 80 && event.mouseButton.x < 130 && event.mouseButton.y > 140 && event.mouseButton.y < 170;
    _eventMonthFieldSelected = event.mouseButton.x > 160 && event.mouseButton.x < 210 && event.mouseButton.y > 140 && event.mouseButton.y < 170;
    _eventDayFieldSelected = event.mouseButton.x > 240 && event.mouseButton.x < 290 && event.mouseButton.y > 140 && event.mouseButton.y < 170;

    // Submit button press handling
    if (event.mouseButton.x > _windowWidth / 3 - 100 && event.mouseButton.x < _windowWidth / 3 - 10 && event.mouseButton.y > 200 && event.mouseButton.y < 230) {
        if (_name.empty() || _month == 0 || _day > Month(_year, _month - 1).getDayCount()) {
            _creationError = true;
        } else {
            _parent->addItem(new Event(_name, Date(_year, _month - 1, _day - 1)));
            _parent->resetMenu();
        }
    }
}

void MenuCreateEvent::handleMouseMove(State& state, sf::Event& event) {
    _eventNameFieldHovered = false;
    _eventYearFieldHovered = false;
    _eventMonthFieldHovered = false;
    _eventDayFieldHovered = false;
    _createButtonHovered = false;

    // Event name field mouse move handling
    if (event.mouseMove.x > 80 && event.mouseMove.x < 280 && event.mouseMove.y > 100 && event.mouseMove.y < 130) {
        state.cursorType = sf::Cursor::Hand;
        _eventNameFieldHovered = true;
    }

    // Event year field mouse move handling
    if (event.mouseMove.x > 80 && event.mouseMove.x < 130 && event.mouseMove.y > 140 && event.mouseMove.y < 170) {
        state.cursorType = sf::Cursor::Hand;
        _eventYearFieldHovered = true;
    }

    // Event month field mouse move handling
    if (event.mouseMove.x > 160 && event.mouseMove.x < 210 && event.mouseMove.y > 140 && event.mouseMove.y < 170) {
        state.cursorType = sf::Cursor::Hand;
        _eventMonthFieldHovered = true;
    }

    // Event day field mouse move handling
    if (event.mouseMove.x > 240 && event.mouseMove.x < 290 && event.mouseMove.y > 140 && event.mouseMove.y < 170) {
        state.cursorType = sf::Cursor::Hand;
        _eventDayFieldHovered = true;
    }

    // Create button mouse move handling
    if (event.mouseMove.x > _windowWidth / 3 - 100 && event.mouseMove.x < _windowWidth / 3 - 10 && event.mouseMove.y > 200 && event.mouseMove.y < 230) {
        state.cursorType = sf::Cursor::Hand;
        _createButtonHovered = true;
    }
}

void MenuCreateEvent::handleTextEnter(sf::Event& event) {
    // Add to the current event name stored if that field is selected
    if (_eventNameFieldSelected) {
        if (event.text.unicode == 8) {
            if (_name.size() > 0) {
                _name.pop_back();
            }
        } else if (_name.size() < 23) {
            _name.push_back((char) event.text.unicode);
        }
    }

    // Change the current event year based on the keyboard input
    if (_eventYearFieldSelected) {
        unsigned short int previous = _year;
        if (event.text.unicode >= '0' && event.text.unicode <= '9') {
            _year = _year * 10 + event.text.unicode - '0';
        } else if (event.text.unicode == 8) {
            _year = _year / 10;
        }

        if (_year > 9999) {
            _year = previous;
        }
    }

    // Change the current event month based on the keyboard input
    if (_eventMonthFieldSelected) {
        unsigned short int previous = _month;
        if (event.text.unicode >= '0' && event.text.unicode <= '9') {
            _month = _month * 10 + event.text.unicode - '0';
        } else if (event.text.unicode == 8) {
            _month = _month / 10;
        }

        if (_month > 12) {
            _month = previous;
        }
    }

    // Change the current event day based on the keyboard input
    if (_eventDayFieldSelected) {
        unsigned short int previous = _day;
        if (event.text.unicode >= '0' && event.text.unicode <= '9') {
            _day = _day * 10 + event.text.unicode - '0';
        } else if (event.text.unicode == 8) {
            _day = _day / 10;
        }

        if (_day > 99) {
            _day = previous;
        }
    }
}

void MenuCreateEvent::setWindowSize(const int X, const int Y) {
    _windowWidth = X;
    _windowHeight = Y;
}
