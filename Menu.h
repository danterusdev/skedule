#ifndef MENU_H
#define MENU_H

#include "Calendar.h"
#include "Widget.h"

class Calendar;

/**
 * An implementation of Widget for the sidebar menu in this
 * application
 */
class Menu : public Widget {
public:
    /**
     * Constructs a menu for a specific calendar
     *
     * @param P_CALENDAR the calendar parent which opened this menu
     */
    Menu(Calendar* const P_CALENDAR);

    virtual void setWindowSize(const int X, const int Y) = 0;
protected:
    sf::Font* _font;
    int _windowWidth;
    int _windowHeight;
    Calendar* _parent;
};

#endif
