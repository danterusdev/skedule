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
    stream << _date.getYear() << " " <<
        _date.getMonth() << " " <<
        _date.getDay() << " " <<
        _name << std::endl;
}
