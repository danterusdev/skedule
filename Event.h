#ifndef EVENT_H
#define EVENT_H

#include "CalendarItem.h"

#include <string>

/**
 * Implementation of the abstract CalendarItem for an Event
 */
class Event : public CalendarItem {
public:
    /**
     * Costructs an event with a specific name and Date
     */
    Event(const std::string NAME, const Date DATE);

    std::string getDisplayName() const override;

    void saveToFile(std::ofstream& stream) const override;
private:
    std::string _name;
};

#endif
