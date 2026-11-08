#include "event.h"
#include "exceptions/exception.h"

Event::Event(std::string_view title)
    : _id(-1), _title(title) {
    if (title.empty()) {
        throw InvalidDataException("название события не может быть пустым");
    }
}

int Event::getId() const { return _id; }
std::string_view Event::getTitle() const { return _title; }

void Event::setId(int newId) { _id = newId; }

void Event::setTitle(std::string_view newTitle) {
    if (newTitle.empty()) {
        throw InvalidDataException("название события не может быть пустым");
    }
    _title = newTitle;
}

std::string Event::getType() const { return "Событие"; }
double Event::calculateMetric() const { return 0.0; }
std::string Event::getMetricName() const { return "Метрика"; }

void Event::printInfo(std::ostream& os) const {
    os << "\n  ID: " << _id;
}

std::ostream& operator<<(std::ostream& os, const Event& e) {
    os << "[" << e.getType() << "] " << e._title
       << " | ID: " << e._id
       << " | Метрика: " << e.calculateMetric()
       << " (" << e.getMetricName() << ")";
    e.printInfo(os);
    return os;
}