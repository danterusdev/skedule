#ifndef MENU_CREATE_EVENT_H
#define MENU_CREATE_EVENT_H

#include "Menu.h"
#include "Widget.h"

/**
 * A menu that is displayed when the user is creating
 * a new event
 */
class MenuCreateEvent : public Menu {
public:
    /** 
     * Constructs the menu for the calendar
     *
     * @param P_CALENDAR the calendar parent
     */
    MenuCreateEvent(Calendar* const P_CALENDAR);

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
