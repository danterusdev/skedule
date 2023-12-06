#ifndef MENU_BLANK_H
#define MENU_BLANK_H

#include "Menu.h"
#include "Widget.h"

/**
 * A menu with no buttons, represents when
 * there are no interactions for the menu
 */
class MenuBlank : public Menu {
public:
    /**
     * Constructs a Blank menu for the current Calendar
     *
     * @param P_CALENDAR the calendar parent
     */
    MenuBlank(Calendar* const P_CALENDAR) : Menu(P_CALENDAR) {};

    void draw(sf::RenderWindow& window) const override;
    void handleMouseClick(sf::Event& event) override;
    void handleMouseMove(State& state, sf::Event& event) override;
    void handleTextEnter(sf::Event& event) override;
    void setWindowSize(const int X, const int Y) override;
};

#endif
