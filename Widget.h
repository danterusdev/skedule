#ifndef WIDGET_H
#define WIDGET_H

#include "State.h"

#include <SFML/Graphics.hpp>

/**
 * Represents a renderable widget
 */
class Widget {
public:
    /**
     * Draws the widget to the given window
     *
     * @param window the window to draw to
     */
    virtual void draw(sf::RenderWindow& window) const = 0;

    /**
     * Handles a mouse click over the widget
     *
     * @param event the mouse click button and location
     */
    virtual void handleMouseClick(sf::Event& event) = 0;

    /**
     * Handles a key pressed
     *
     * @param event the key pressed and state
     */
    virtual void handleTextEnter(sf::Event& event) = 0;

    /**
     * Handles when the mouse is moved
     *
     * @param state the current state (contains cursor state)
     * @param event the new mouse location
     */
    virtual void handleMouseMove(State& state, sf::Event& event) = 0;
};

#endif
