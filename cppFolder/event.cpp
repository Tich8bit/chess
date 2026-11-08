#include "event.h"
#include "exceptions/exception.h"

Event::Event(int id, std::string_view title)
    : _id(id), _title(title) {
    if (id <= 0) {
        throw InvalidDataException("ID должен быть положительным числом");
    }
    if (title.empty()) {
        throw InvalidDataException("название события не может быть пустым");
    }
}

int Event::getId() const { return _id; }
std::string_view Event::getTitle() const { return _title; }

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