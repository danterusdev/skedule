#ifndef MENU_BLANK_H
#define MENU_BLANK_H

#include "Menu.h"
#include "Widget.h"

class MenuBlank : public Menu {
public:
    MenuBlank(Calendar* const CALENDAR) : Menu(CALENDAR) {};

    void draw(sf::RenderWindow& window) const override;
    void handleMouseClick(sf::Event& event) override;
    void handleMouseMove(State& state, sf::Event& event) override;
    void handleTextEnter(sf::Event& event) override;
    void setWindowSize(const int X, const int Y) override;
};

#endif
