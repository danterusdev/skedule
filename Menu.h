#ifndef MENU_H
#define MENU_H

#include "Calendar.h"
#include "Widget.h"

class Calendar;

class Menu : public Widget {
public:
    Menu(Calendar* const CALENDAR);

    virtual void setWindowSize(const int X, const int Y) = 0;
protected:
    sf::Font* _font;
    int _windowWidth;
    int _windowHeight;
    Calendar* _parent;
};

#endif
