#include "Calendar.h"
#include "Event.h"
#include "MenuBlank.h"
#include "MenuCreateEvent.h"
#include "DrawUtil.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

Calendar::Calendar() : _currentMonth(0, 0) {
    resetMenu();

    _pFont = new sf::Font();
    _pFont->loadFromFile("assets/Roboto-Regular.ttf");

    _pBack = new sf::Texture();
    _pBack->loadFromFile("assets/back.png");
    _pBack->setSmooth(true);

    _pForward = new sf::Texture();
    _pForward->loadFromFile("assets/forward.png");
    _pForward->setSmooth(true);

    _pCreate = new sf::Texture();
    _pCreate->loadFromFile("assets/create.png");
    _pCreate->setSmooth(true);

    _backButtonHovered = false;
    _nextButtonHovered = false;
    _createButtonHovered = false;
}

void Calendar::draw(sf::RenderWindow& window) const {
    const float DAY_SIZE = 105;
    const float X_OFFSET = (float) window.getSize().x / 3 * 2 - DAY_SIZE * 3.5f;
    const float Y_OFFSET = 75;

    const float DAY_BORDER = 1;

    std::ostringstream stringStream;
    stringStream << _currentMonth.toString() << " " << _currentMonth.getYear();

    // Rendering of the create event button
    if (_createButtonHovered) {
        drawOutlineRect(window, window.getSize().x / 3 + 15, 15, 30, 30, sf::Color(100, 100, 100), 2, sf::Color(80, 80, 80));
    } else {
        drawRect(window, window.getSize().x / 3 + 15, 15, 30, 30, sf::Color(100, 100, 100));
    }
    sf::RectangleShape createButton;
    createButton.setPosition(window.getSize().x / 3 + 20, 20);
    createButton.setSize(sf::Vector2f(20, 20));
    createButton.setTexture(_pCreate);
    window.draw(createButton);

    // Rendering of the back button (going to the previous month)
    if (_backButtonHovered) {
        drawOutlineRect(window, X_OFFSET + DAY_SIZE * 3.5f - 160 - 30, 22, 30, 30, sf::Color(100, 100, 100), 2, sf::Color(80, 80, 80));
    } else {
        drawRect(window, X_OFFSET + DAY_SIZE * 3.5f - 160 - 30, 22, 30, 30, sf::Color(100, 100, 100));
    }
    sf::RectangleShape backButton;
    backButton.setPosition(X_OFFSET + DAY_SIZE * 3.5f - 160 - 25, 27);
    backButton.setSize(sf::Vector2f(20, 20));
    backButton.setTexture(_pBack);
    window.draw(backButton);

    // Rendering of the next button (going to the next month)
    if (_nextButtonHovered) {
        drawOutlineRect(window, X_OFFSET + DAY_SIZE * 3.5f + 160, 22, 30, 30, sf::Color(100, 100, 100), 2, sf::Color(80, 80, 80));
    } else {
        drawRect(window, X_OFFSET + DAY_SIZE * 3.5f + 160, 22, 30, 30, sf::Color(100, 100, 100));
    }
    sf::RectangleShape forwardButton;
    forwardButton.setPosition(X_OFFSET + DAY_SIZE * 3.5f + 165, 27);
    forwardButton.setSize(sf::Vector2f(20, 20));
    forwardButton.setTexture(_pForward);
    window.draw(forwardButton);

    // Renders the current month name
    drawText(window, *_pFont, (int) (X_OFFSET + DAY_SIZE * 3.5f), 17, true, stringStream.str(), 32, sf::Color::Black);

    int row = 0;
    int column = _currentMonth.getDayOfWeek();
    for (short unsigned int i = 0; i < _currentMonth.getDayCount(); i++) {
        const float DAY_X = (float) column * DAY_SIZE + X_OFFSET;
        const float DAY_Y = (float) row * DAY_SIZE + Y_OFFSET;

        // Renders the day on the Calendar
        drawOutlineRect(window, DAY_X, DAY_Y, DAY_SIZE - 1, DAY_SIZE - 1, sf::Color::White, DAY_BORDER, sf::Color::Black);

        drawText(window, *_pFont, (int) (DAY_X + 5), (int) (DAY_Y + 5), false, std::to_string(i + 1), 16, sf::Color::Black);

        int eventCount = 0;
        for (size_t j = 0; j < _items.size(); j++) {
            // Renders each individual calendar item that falls on the day
            CalendarItem* pItem = _items.at(j);
            if (pItem->getDate().dateEquals(Date(_currentMonth.getYear(), _currentMonth.getMonth(), i))) {
                drawRect(window, DAY_X + 6, DAY_Y + 30 + 20 * (float) eventCount, DAY_SIZE - 12 - DAY_BORDER * 2, 17, sf::Color(150, 150, 150));

                drawText(window, *_pFont, (int) (DAY_X + 10), DAY_Y + 32 + 20 * (float) eventCount, false, pItem->getDisplayName(), 10, sf::Color::Black);

                eventCount++;
            }
        }

        column++;
        if (column == 7) {
            column = 0;
            row++;
        }
    }

    _pMenu->setWindowSize(window.getSize().x, window.getSize().y);
    _pMenu->draw(window);
}

void Calendar::handleMouseClick(sf::Event& event) {
    const float DAY_SIZE = 105;
    const float X_OFFSET = (float) _windowWidth / 3 * 2 - DAY_SIZE * 3.5f;
    const float Y_OFFSET = 75;

    // Handles the mouse clicking the next month button
    if (event.mouseButton.x > X_OFFSET + DAY_SIZE * 3.5f + 160 && event.mouseButton.x < X_OFFSET + DAY_SIZE * 3.5f + 160 + 30 &&
            event.mouseButton.y > 22 && event.mouseButton.y < 22 + 30) {
        if (_currentMonth.getMonth() > 10) {
            _currentMonth = Month(_currentMonth.getYear() + 1, 0);
        } else {
            _currentMonth = Month(_currentMonth.getYear(), _currentMonth.getMonth() + 1);
        }
    }

    // Handles the mouse clicking the previous month button
    if (event.mouseButton.x > X_OFFSET + DAY_SIZE * 3.5f - 160 - 30 && event.mouseButton.x < X_OFFSET + DAY_SIZE * 3.5f - 160 &&
            event.mouseButton.y > 22 && event.mouseButton.y < 22 + 30) {
        if (_currentMonth.getMonth() < 1) {
            _currentMonth = Month(_currentMonth.getYear() - 1, 11);
        } else {
            _currentMonth = Month(_currentMonth.getYear(), _currentMonth.getMonth() - 1);
        }
    }

    // Handles the mouse clicking the new event button
    if (event.mouseButton.x > _windowWidth / 3 + 15 && event.mouseButton.x < _windowWidth / 3 + 15 + 30 &&
            event.mouseButton.y > 15 && event.mouseButton.y < 15 + 30) {
        _pMenu = new MenuCreateEvent(this);
    }

    // Handles if the user clicks on an event to delete it
    int row = 0;
    int column = _currentMonth.getDayOfWeek();
    for (short unsigned int i = 0; i < _currentMonth.getDayCount(); i++) {
        const float DAY_X = (float) column * DAY_SIZE + X_OFFSET;
        const float DAY_Y = (float) row * DAY_SIZE + Y_OFFSET;

        int eventCount = 0;
        for (size_t j = 0; j < _items.size(); j++) {
            CalendarItem* pItem = _items.at(j);
            // Removes the event that is clicked
            if (pItem->getDate().dateEquals(Date(_currentMonth.getYear(), _currentMonth.getMonth(), i))) {
                if (event.mouseButton.x > DAY_X + 6 && event.mouseButton.x < DAY_X + DAY_SIZE - 6 && event.mouseButton.y > DAY_Y + 30 + 20 * (float) eventCount && event.mouseButton.y < DAY_Y + 30 + 20 * (float) eventCount + 17) {
                    this->removeItem(pItem);
                }

                eventCount++;
            }
        }

        column++;
        if (column == 7) {
            column = 0;
            row++;
        }
    }

    _pMenu->handleMouseClick(event);
}

void Calendar::handleMouseMove(State& state, sf::Event& event) {
    const float DAY_SIZE = 105;
    const float X_OFFSET = (float) _windowWidth / 3 * 2 - DAY_SIZE * 3.5f;
    const float Y_OFFSET = 75;

    _backButtonHovered = false;
    _nextButtonHovered = false;
    _createButtonHovered = false;

    // Handles if the mouse hovers of the next button
    if (event.mouseMove.x > X_OFFSET + DAY_SIZE * 3.5f + 160 && event.mouseMove.x < X_OFFSET + DAY_SIZE * 3.5f + 160 + 30 &&
            event.mouseMove.y > 22 && event.mouseMove.y < 22 + 30) {
        state.cursorType = sf::Cursor::Hand;
        _nextButtonHovered = true;
    }

    // Handles if the mouse hovers of the previous button
    if (event.mouseMove.x > X_OFFSET + DAY_SIZE * 3.5f - 160 - 30 && event.mouseMove.x < X_OFFSET + DAY_SIZE * 3.5f - 160 &&
            event.mouseMove.y > 22 && event.mouseMove.y < 22 + 30) {
        state.cursorType = sf::Cursor::Hand;
        _backButtonHovered = true;
    }

    // Handles if the mouse hovers of the create button
    if (event.mouseMove.x > _windowWidth / 3 + 15 && event.mouseMove.x < _windowWidth / 3 + 15 + 30 &&
            event.mouseMove.y > 15 && event.mouseMove.y < 15 + 30) {
        state.cursorType = sf::Cursor::Hand;
        _createButtonHovered = true;
    }

    // Handles if the mouse hovers over an event
    int row = 0;
    int column = _currentMonth.getDayOfWeek();
    for (short unsigned int i = 0; i < _currentMonth.getDayCount(); i++) {
        const float DAY_X = (float) column * DAY_SIZE + X_OFFSET;
        const float DAY_Y = (float) row * DAY_SIZE + Y_OFFSET;

        int eventCount = 0;
        for (size_t j = 0; j < _items.size(); j++) {
            CalendarItem* pItem = _items.at(j);
            if (pItem->getDate().dateEquals(Date(_currentMonth.getYear(), _currentMonth.getMonth(), i))) {
                if (event.mouseMove.x > DAY_X + 6 && event.mouseMove.x < DAY_X + DAY_SIZE - 6 && event.mouseMove.y > DAY_Y + 30 + 20 * (float) eventCount && event.mouseMove.y < DAY_Y + 30 + 20 * (float) eventCount + 17) {
                    state.cursorType = sf::Cursor::Hand;
                }

                eventCount++;
            }
        }

        column++;
        if (column == 7) {
            column = 0;
            row++;
        }
    }

    _pMenu->handleMouseMove(state, event);
}

void Calendar::handleTextEnter(sf::Event& event) {
    _pMenu->handleTextEnter(event);
}

void Calendar::setWindowSize(const int WIDTH, const int HEIGHT) {
    _windowWidth = WIDTH;
    _windowHeight = HEIGHT;
}

void Calendar::setDisplayed(const Month MONTH) {
    _currentMonth = MONTH;
}

void Calendar::addItem(CalendarItem* const ITEM) {
    _items.push_back(ITEM);
    saveToFile();
}

void Calendar::removeItem(CalendarItem* const ITEM) {
    for (size_t i = 0; i < _items.size(); i++) {
        if (_items.at(i) == ITEM) {
            _items.erase(_items.begin() + i);
        }
    }
    saveToFile();
}

void Calendar::resetMenu() {
    _pMenu = new MenuBlank(this);
}

void Calendar::loadFromFile() {
    std::ifstream stream("skeduleSave");
    if (!stream.is_open()) {
        return;
    }

    // File Format:
    // YEAR MONTH DAY EVENT_NAME
    // Event name can be a string with spaces, the other fields are field separated
    while (!stream.eof()) {
        unsigned int year;
        unsigned short int month;
        unsigned short int day;

        stream >> year >> month >> day;

        stream.get();

        std::string name;
        std::getline(stream, name);

        _items.push_back(new Event(name, Date(year, month, day)));

        stream.peek();
    }
}

void Calendar::saveToFile() {
    std::ofstream stream("skeduleSave");
    for (size_t i = 0; i < _items.size(); i++) {
        _items.at(i)->saveToFile(stream);
    }
}
