#ifndef WIDGET_H
#define WIDGET_H

#include "State.h"

#include <SFML/Graphics.hpp>

class Widget {
public:
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual void handleMouseClick(sf::Event& event) = 0;
    virtual void handleMouseMove(State& state, sf::Event& event) = 0;
private:
    float _x;
    float _y;
};

#endif
