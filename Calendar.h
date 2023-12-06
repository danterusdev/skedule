#ifndef CALENDAR_H
#define CALENDAR_H

#include "CalendarItem.h"
#include "Menu.h"
#include "Month.h"
#include "Widget.h"

#include <vector>

#include <SFML/Graphics.hpp>

class Menu;

/**
 * Represents a calendar that stores events as well as how to
 * render those events
 */
class Calendar : public Widget {
public:
    /**
     * Constructs a calendar with an invalid current month and no events
     */
    Calendar();

    /**
     * Draws the calendar to the screen
     *
     * @param window the window to draw to
     */
    void draw(sf::RenderWindow& window) const override;

    /**
     * Handles what happens if the mouse is clicked
     *
     * @param event data about where the mouse was clicked and what button
     */
    void handleMouseClick(sf::Event& event) override;

    /**
     * Handles what happens if a key is pressed
     *
     * @param event data about what key was pressed
     */
    void handleTextEnter(sf::Event& event) override;

    /**
     * Handles what happens if the mouse is moved
     *
     * @param event data about where the mouse was moved
     */
    void handleMouseMove(State& state, sf::Event& event) override;

    /**
     * Specifies a month to show as the currently active displayed month
     *
     * @param MONTH the month to displace
     */
    void setDisplayed(const Month MONTH);

    /**
     * Adds an item to the list of items in the calendar
     *
     * @param P_ITEM the item to add
     */
    void addItem(CalendarItem* const P_ITEM);

    /**
     * Removes the item from the list of items in the calendar
     *
     * @param P_ITEM the item to remove
     */
    void removeItem(CalendarItem* const P_ITEM);

    /**
     * Updates the internally stored window size, which is used for rendering purposes
     *
     * @param WIDTH the new width of the window
     * @param HEIGHT the new height of the window
     */
    void setWindowSize(const int WIDTH, const int HEIGHT);

    /**
     * Sets the currently displayed menu to the left to a blank menu
     */
    void resetMenu();

    /**
     * Reads from the event save file and stores the events inside
     * the internal vector of events
     */
    void loadFromFile();

    /**
     * Writes the current events to the current save file,
     * called after a modification is made
     */
    void saveToFile();
private:
    Month _currentMonth;
    std::vector<CalendarItem*> _items;

    int _windowWidth;
    int _windowHeight;
    Menu* _pMenu;
    sf::Font* _pFont;

    sf::Texture* _pCreate;
    sf::Texture* _pBack;
    sf::Texture* _pForward;

    bool _backButtonHovered;
    bool _nextButtonHovered;
    bool _createButtonHovered;
};

#endif
