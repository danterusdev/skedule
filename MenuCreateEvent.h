#ifndef MENU_CREATE_EVENT_H
#define MENU_CREATE_EVENT_H

#include "Menu.h"
#include "Widget.h"

class MenuCreateEvent : public Menu {
public:
    MenuCreateEvent(Calendar* const CALENDAR);

    void draw(sf::RenderWindow& window) const override;
    void handleMouseClick(sf::Event& event) override;
    void handleTextEnter(sf::Event& event) override;
    void handleMouseMove(State& state, sf::Event& event) override;
    void setWindowSize(const int X, const int Y) override;

    void createEvent();
private:
    sf::Font* _font;

    std::string _name;
    bool _eventNameFieldSelected;
    bool _eventNameFieldHovered;

    unsigned short int _year;
    bool _eventYearFieldSelected;
    bool _eventYearFieldHovered;

    unsigned short int _month;
    bool _eventMonthFieldSelected;
    bool _eventMonthFieldHovered;

    unsigned short int _day;
    bool _eventDayFieldSelected;
    bool _eventDayFieldHovered;

    bool _createButtonHovered;
    bool _creationError;
};

#endif
