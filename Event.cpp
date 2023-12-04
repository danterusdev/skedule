#include "Event.h"

Event::Event(const std::string NAME, const Date DATE) : CalendarItem(DATE) {
    this->_name = NAME;
}

std::string Event::getDisplayName() const {
    return _name;
}
