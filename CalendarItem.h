#ifndef CALENDAR_ITEM_H
#define CALENDAR_ITEM_H

#include "Date.h"

#include <string>

/**
 * Represents an abstract calendar item and provides
 * overridable methods for the implementer to implement
 */
class CalendarItem {
public:
    /**
     * Constructs a new calendar item at a specific time
     *
     * @param TIME the time of the item
     */
    CalendarItem(const Date TIME);

    /**
     * @return the date of the event
     */
    Date getDate() const;

    /**
     * @return the name of the event
     */
    virtual std::string getDisplayName() const = 0;

    /**
     * Writes the event data to the specified save file
     *
     * @param stream the stream to write the event data to
     */
    virtual void saveToFile(std::ofstream& stream) const = 0;
protected:
    Date _date;
};

#endif
