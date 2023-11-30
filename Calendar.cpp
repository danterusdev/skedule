#include "Calendar.h"
#include "MenuBlank.h"
#include "MenuCreateEvent.h"
#include "DrawUtil.h"

#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

Calendar::Calendar() : _currentMonth(0, 0) {
    resetMenu();

    _font = new sf::Font();
    _font->loadFromFile("assets/Roboto-Regular.ttf");
}

void Calendar::draw(sf::RenderWindow& window) const {
    const float DAY_SIZE = 105;
    const float X_OFFSET = (float) window.getSize().x / 3 * 2 - DAY_SIZE * 3.5f;
    const float Y_OFFSET = 75;

    const float DAY_BORDER = 1;

    std::ostringstream stringStream;
    stringStream << _currentMonth.toString() << " " << _currentMonth.getYear();

    drawRect(window, window.getSize().x / 3 + 15, 15, 30, 30, sf::Color(100, 100, 100));

    drawRect(window, X_OFFSET + DAY_SIZE * 3.5f - 160 - 30, 22, 30, 30, sf::Color(100, 100, 100)); // previous button
    drawRect(window, X_OFFSET + DAY_SIZE * 3.5f + 160, 22, 30, 30, sf::Color(100, 100, 100)); // next button

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
            if (item->getTime().dateEquals(Date(_currentMonth.getYear(), _currentMonth.getMonth(), i))) {
                drawRect(window, DAY_X + 6, DAY_Y + 30 + 20 * (float) eventCount, DAY_SIZE - 12 - DAY_BORDER * 2, 17, sf::Color::Red);

                drawText(window, *_font, (int) (DAY_X + 10), DAY_Y + 30.5 + 20 * (float) eventCount, false, item->getDisplayName(), 12, sf::Color::Black);

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

    _menu->handleMouseClick(event);
}

void Calendar::handleMouseMove(State& state, sf::Event& event) {
    const float DAY_SIZE = 105;
    const float X_OFFSET = (float) _windowWidth / 3 * 2 - DAY_SIZE * 3.5f;

    if (event.mouseMove.x > X_OFFSET + DAY_SIZE * 3.5f + 160 && event.mouseMove.x < X_OFFSET + DAY_SIZE * 3.5f + 160 + 30 &&
            event.mouseMove.y > 22 && event.mouseMove.y < 22 + 30) {
        state.cursorType = sf::Cursor::Hand;
    }

    if (event.mouseMove.x > X_OFFSET + DAY_SIZE * 3.5f - 160 - 30 && event.mouseMove.x < X_OFFSET + DAY_SIZE * 3.5f - 160 &&
            event.mouseMove.y > 22 && event.mouseMove.y < 22 + 30) {
        state.cursorType = sf::Cursor::Hand;
    }

    if (event.mouseMove.x > _windowWidth / 3 + 15 && event.mouseMove.x < _windowWidth / 3 + 15 + 30 &&
            event.mouseMove.y > 15 && event.mouseMove.y < 15 + 30) {
        state.cursorType = sf::Cursor::Hand;
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
}

void Calendar::resetMenu() {
    _menu = new MenuBlank(this);
}
