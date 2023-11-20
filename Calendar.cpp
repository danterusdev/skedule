#include "Calendar.h"

#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

Calendar::Calendar() : _currentMonth(0, 0) {
}

void Calendar::draw(sf::RenderWindow& window) const {
    sf::Font font;
    font.loadFromFile("assets/Roboto-Regular.ttf");

    const float DAY_SIZE = 105;
    const float X_OFFSET = (float) window.getSize().x / 2 - DAY_SIZE * 3.5f;
    const float Y_OFFSET = 75;

    const float DAY_BORDER = 1;

    std::ostringstream stringStream;
    stringStream << _currentMonth.toString() << " " << _currentMonth.getYear();

    sf::RectangleShape previousButton;
    previousButton.setPosition(X_OFFSET + DAY_SIZE * 3.5f - 160 - 30, 22);
    previousButton.setSize(sf::Vector2f(30, 30));
    previousButton.setFillColor(sf::Color(100, 100, 100));
    window.draw(previousButton);

    sf::RectangleShape nextButton;
    nextButton.setPosition(X_OFFSET + DAY_SIZE * 3.5f + 160, 22);
    nextButton.setSize(sf::Vector2f(30, 30));
    nextButton.setFillColor(sf::Color(100, 100, 100));
    window.draw(nextButton);

    sf::Text title;
    title.setFont(font);
    title.setString(stringStream.str());
    title.setCharacterSize(32);
    title.setFillColor(sf::Color::Black);
    title.setPosition((int) (X_OFFSET + DAY_SIZE * 3.5f - title.getLocalBounds().width / 2), 17);
    window.draw(title);

    int row = 0;
    int column = _currentMonth.getDayOfWeek();
    for (short unsigned int i = 0; i < _currentMonth.getDayCount(); i++) {
        const float DAY_X = (float) column * DAY_SIZE + X_OFFSET;
        const float DAY_Y = (float) row * DAY_SIZE + Y_OFFSET;

        sf::RectangleShape shape;
        shape.setFillColor(sf::Color::White);
        shape.setPosition(DAY_X, DAY_Y);
        shape.setSize(sf::Vector2f(DAY_SIZE - 1, DAY_SIZE - 1));
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(DAY_BORDER);
        window.draw(shape);

        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(i + 1));
        text.setCharacterSize(16);
        text.setFillColor(sf::Color::Black);
        text.setPosition((int) (DAY_X + 5), (int) (DAY_Y + 5));
        window.draw(text);

        int eventCount = 0;
        for (size_t j = 0; j < _items.size(); j++) {
            CalendarItem item = _items.at(j);
            if (item.getTime().dateEquals(Date(_currentMonth.getYear(), _currentMonth.getMonth(), i))) {
                sf::RectangleShape itemRect;
                itemRect.setFillColor(sf::Color::Red);
                itemRect.setPosition(DAY_X + 6, DAY_Y + 30 + 20 * (float) eventCount);
                itemRect.setSize(sf::Vector2f(DAY_SIZE - 12 - DAY_BORDER * 2, 17.5));
                window.draw(itemRect);

                eventCount++;
            }
        }

        column++;
        if (column == 7) {
            column = 0;
            row++;
        }
    }
}

void Calendar::handleMouseClick(sf::Event& event) {
    const float DAY_SIZE = 105;
    const float X_OFFSET = (float) _windowWidth / 2 - DAY_SIZE * 3.5f;

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
}

void Calendar::handleMouseMove(State& state, sf::Event& event) {
    const float DAY_SIZE = 105;
    const float X_OFFSET = (float) _windowWidth / 2 - DAY_SIZE * 3.5f;

    if (event.mouseMove.x > X_OFFSET + DAY_SIZE * 3.5f + 160 && event.mouseMove.x < X_OFFSET + DAY_SIZE * 3.5f + 160 + 30 &&
            event.mouseMove.y > 22 && event.mouseMove.y < 22 + 30) {
        state.cursorType = sf::Cursor::Hand;
    }

    if (event.mouseMove.x > X_OFFSET + DAY_SIZE * 3.5f - 160 - 30 && event.mouseMove.x < X_OFFSET + DAY_SIZE * 3.5f - 160 &&
            event.mouseMove.y > 22 && event.mouseMove.y < 22 + 30) {
        state.cursorType = sf::Cursor::Hand;
    }
}

void Calendar::setWindowSize(const int WIDTH, const int HEIGHT) {
    _windowWidth = WIDTH;
    _windowHeight = HEIGHT;
}

void Calendar::setDisplayed(const Month MONTH) {
    _currentMonth = MONTH;
}

void Calendar::addItem(const CalendarItem ITEM) {
    _items.push_back(ITEM);
}
