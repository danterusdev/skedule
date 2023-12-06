#include "Event.h"

#include <iostream>
#include <fstream>

Event::Event(const std::string NAME, const Date DATE) : CalendarItem(DATE) {
    this->_name = NAME;
}

std::string Event::getDisplayName() const {
    return _name;
}

void Event::saveToFile(std::ofstream& stream) const {
    // Writes the event in the format:
    //   YEAR MONTH DAY EVENT_NAME
    stream << _date.getYear() << " " <<
        _date.getMonth() << " " <<
        _date.getDay() << " " <<
        _name << std::endl;
}
