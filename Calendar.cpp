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

    _font = new sf::Font();
    _font->loadFromFile("assets/Roboto-Regular.ttf");

    _back = new sf::Texture();
    _back->loadFromFile("assets/back.png");
    _back->setSmooth(true);

    _forward = new sf::Texture();
    _forward->loadFromFile("assets/forward.png");
    _forward->setSmooth(true);

    _create = new sf::Texture();
    _create->loadFromFile("assets/create.png");
    _create->setSmooth(true);

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

    if (_createButtonHovered) {
        drawOutlineRect(window, window.getSize().x / 3 + 15, 15, 30, 30, sf::Color(100, 100, 100), 2, sf::Color(80, 80, 80));
    } else {
        drawRect(window, window.getSize().x / 3 + 15, 15, 30, 30, sf::Color(100, 100, 100));
    }
    sf::RectangleShape createButton;
    createButton.setPosition(window.getSize().x / 3 + 20, 20);
    createButton.setSize(sf::Vector2f(20, 20));
    createButton.setTexture(_create);
    window.draw(createButton);

    if (_backButtonHovered) {
        drawOutlineRect(window, X_OFFSET + DAY_SIZE * 3.5f - 160 - 30, 22, 30, 30, sf::Color(100, 100, 100), 2, sf::Color(80, 80, 80));
    } else {
        drawRect(window, X_OFFSET + DAY_SIZE * 3.5f - 160 - 30, 22, 30, 30, sf::Color(100, 100, 100));
    }
    sf::RectangleShape backButton;
    backButton.setPosition(X_OFFSET + DAY_SIZE * 3.5f - 160 - 25, 27);
    backButton.setSize(sf::Vector2f(20, 20));
    backButton.setTexture(_back);
    window.draw(backButton);

    if (_nextButtonHovered) {
        drawOutlineRect(window, X_OFFSET + DAY_SIZE * 3.5f + 160, 22, 30, 30, sf::Color(100, 100, 100), 2, sf::Color(80, 80, 80));
    } else {
        drawRect(window, X_OFFSET + DAY_SIZE * 3.5f + 160, 22, 30, 30, sf::Color(100, 100, 100));
    }
    sf::RectangleShape forwardButton;
    forwardButton.setPosition(X_OFFSET + DAY_SIZE * 3.5f + 165, 27);
    forwardButton.setSize(sf::Vector2f(20, 20));
    forwardButton.setTexture(_forward);
    window.draw(forwardButton);

    drawText(window, *_font, (int) (X_OFFSET + DAY_SIZE * 3.5f), 17, true, stringStream.str(), 32, sf::Color::Black);

    int row = 0;
    int column = _currentMonth.getDayOfWeek();
    for (short unsigned int i = 0; i < _currentMonth.getDayCount(); i++) {
        const float DAY_X = (float) column * DAY_SIZE + X_OFFSET;
        const float DAY_Y = (float) row * DAY_SIZE + Y_OFFSET;

        drawOutlineRect(window, DAY_X, DAY_Y, DAY_SIZE - 1, DAY_SIZE - 1, sf::Color::White, DAY_BORDER, sf::Color::Black);

        drawText(window, *_font, (int) (DAY_X + 5), (int) (DAY_Y + 5), false, std::to_string(i + 1), 16, sf::Color::Black);

        int eventCount = 0;
        for (size_t j = 0; j < _items.size(); j++) {
            CalendarItem* item = _items.at(j);
            if (item->getDate().dateEquals(Date(_currentMonth.getYear(), _currentMonth.getMonth(), i))) {
                drawRect(window, DAY_X + 6, DAY_Y + 30 + 20 * (float) eventCount, DAY_SIZE - 12 - DAY_BORDER * 2, 17, sf::Color(150, 150, 150));

                drawText(window, *_font, (int) (DAY_X + 10), DAY_Y + 32 + 20 * (float) eventCount, false, item->getDisplayName(), 10, sf::Color::Black);

                eventCount++;
            }
        }

        column++;
        if (column == 7) {
            column = 0;
            row++;
        }
    }

    _menu->setWindowSize(window.getSize().x, window.getSize().y);
    _menu->draw(window);
}

void Calendar::handleMouseClick(sf::Event& event) {
    const float DAY_SIZE = 105;
    const float X_OFFSET = (float) _windowWidth / 3 * 2 - DAY_SIZE * 3.5f;
    const float Y_OFFSET = 75;

    if (event.mouseButton.x > X_OFFSET + DAY_SIZE * 3.5f + 160 && event.mouseButton.x < X_OFFSET + DAY_SIZE * 3.5f + 160 + 30 &&
            event.mouseButton.y > 22 && event.mouseButton.y < 22 + 30) {
        if (_currentMonth.getMonth() > 10) {
            _currentMonth = Month(_currentMonth.getYear() + 1, 0);
        } else {
            _currentMonth = Month(_currentMonth.getYear(), _currentMonth.getMonth() + 1);
        }
    }

    if (event.mouseButton.x > X_OFFSET + DAY_SIZE * 3.5f - 160 - 30 && event.mouseButton.x < X_OFFSET + DAY_SIZE * 3.5f - 160 &&
            event.mouseButton.y > 22 && event.mouseButton.y < 22 + 30) {
        if (_currentMonth.getMonth() < 1) {
            _currentMonth = Month(_currentMonth.getYear() - 1, 11);
        } else {
            _currentMonth = Month(_currentMonth.getYear(), _currentMonth.getMonth() - 1);
        }
    }

    if (event.mouseButton.x > _windowWidth / 3 + 15 && event.mouseButton.x < _windowWidth / 3 + 15 + 30 &&
            event.mouseButton.y > 15 && event.mouseButton.y < 15 + 30) {
        _menu = new MenuCreateEvent(this);
    }

    int row = 0;
    int column = _currentMonth.getDayOfWeek();
    for (short unsigned int i = 0; i < _currentMonth.getDayCount(); i++) {
        const float DAY_X = (float) column * DAY_SIZE + X_OFFSET;
        const float DAY_Y = (float) row * DAY_SIZE + Y_OFFSET;

        int eventCount = 0;
        for (size_t j = 0; j < _items.size(); j++) {
            CalendarItem* item = _items.at(j);
            if (item->getDate().dateEquals(Date(_currentMonth.getYear(), _currentMonth.getMonth(), i))) {
                if (event.mouseButton.x > DAY_X + 6 && event.mouseButton.x < DAY_X + DAY_SIZE - 6 && event.mouseButton.y > DAY_Y + 30 + 20 * (float) eventCount && event.mouseButton.y < DAY_Y + 30 + 20 * (float) eventCount + 17) {
                    this->removeItem(item);
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

    _menu->handleMouseClick(event);
}

void Calendar::handleMouseMove(State& state, sf::Event& event) {
    const float DAY_SIZE = 105;
    const float X_OFFSET = (float) _windowWidth / 3 * 2 - DAY_SIZE * 3.5f;
    const float Y_OFFSET = 75;

    _backButtonHovered = false;
    _nextButtonHovered = false;
    _createButtonHovered = false;

    if (event.mouseMove.x > X_OFFSET + DAY_SIZE * 3.5f + 160 && event.mouseMove.x < X_OFFSET + DAY_SIZE * 3.5f + 160 + 30 &&
            event.mouseMove.y > 22 && event.mouseMove.y < 22 + 30) {
        state.cursorType = sf::Cursor::Hand;
        _nextButtonHovered = true;
    }

    if (event.mouseMove.x > X_OFFSET + DAY_SIZE * 3.5f - 160 - 30 && event.mouseMove.x < X_OFFSET + DAY_SIZE * 3.5f - 160 &&
            event.mouseMove.y > 22 && event.mouseMove.y < 22 + 30) {
        state.cursorType = sf::Cursor::Hand;
        _backButtonHovered = true;
    }

    if (event.mouseMove.x > _windowWidth / 3 + 15 && event.mouseMove.x < _windowWidth / 3 + 15 + 30 &&
            event.mouseMove.y > 15 && event.mouseMove.y < 15 + 30) {
        state.cursorType = sf::Cursor::Hand;
        _createButtonHovered = true;
    }

    int row = 0;
    int column = _currentMonth.getDayOfWeek();
    for (short unsigned int i = 0; i < _currentMonth.getDayCount(); i++) {
        const float DAY_X = (float) column * DAY_SIZE + X_OFFSET;
        const float DAY_Y = (float) row * DAY_SIZE + Y_OFFSET;

        int eventCount = 0;
        for (size_t j = 0; j < _items.size(); j++) {
            CalendarItem* item = _items.at(j);
            if (item->getDate().dateEquals(Date(_currentMonth.getYear(), _currentMonth.getMonth(), i))) {
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

    _menu->handleMouseMove(state, event);
}

void Calendar::handleTextEnter(sf::Event& event) {
    _menu->handleTextEnter(event);
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
    _menu = new MenuBlank(this);
}

void Calendar::loadFromFile() {
    std::ifstream stream("skeduleSave");
    if (!stream.is_open()) {
        return;
    }

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
