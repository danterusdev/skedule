#ifndef CALENDAR_H
#define CALENDAR_H

#include "CalendarItem.h"
#include "Menu.h"
#include "Month.h"
#include "Widget.h"

#include <vector>

#include <SFML/Graphics.hpp>

class Menu;

class Calendar : public Widget {
public:
    Calendar();

    void draw(sf::RenderWindow& window) const override;
    void handleMouseClick(sf::Event& event) override;
    void handleTextEnter(sf::Event& event) override;
    void handleMouseMove(State& state, sf::Event& event) override;

    void setDisplayed(const Month MONTH);
    void addItem(CalendarItem* const ITEM);
    void removeItem(CalendarItem* const ITEM);
    void setWindowSize(const int WIDTH, const int HEIGHT);

    void resetMenu();
private:
    Month _currentMonth;
    std::vector<CalendarItem*> _items;
    int _windowWidth;
    int _windowHeight;
    Menu* _menu;
    sf::Font* _font;
};

#endif
