#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

/**
 * Stores an SFML cursor type, used for changing the state 
 * of the cursor through gui interactions
 */
struct State {
    /**
     * The current cursortype of the cursor
     */
    sf::Cursor::Type cursorType;
};

#endif
