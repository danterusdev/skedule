#ifndef CALENDAR_H
#define CALENDAR_H

#include "CalendarItem.h"
#include "Month.h"
#include "Widget.h"

#include <vector>

#include <SFML/Graphics.hpp>

class Calendar : public Widget {
public:
    Calendar();

    virtual void draw(sf::RenderWindow& window) const override;
    virtual void handleMouseClick(sf::Event& event) override;
    virtual void handleMouseMove(State& state, sf::Event& event) override;

    void setDisplayed(const Month MONTH);
    void addItem(CalendarItem* const ITEM);
    void setWindowSize(const int WIDTH, const int HEIGHT);
private:
    Month _currentMonth;
    std::vector<CalendarItem*> _items;
    int _windowWidth;
    int _windowHeight;
};

#endif
