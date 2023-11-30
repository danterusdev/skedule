#include "Event.h"

Event::Event(const std::string NAME, const Time TIME) : CalendarItem(TIME) {
    this->_name = NAME;
}

std::string Event::getDisplayName() const {
    return _name;
}
