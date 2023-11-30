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
    bool _eventNameFieldSelected;
    std::string _name;
};

#endif
