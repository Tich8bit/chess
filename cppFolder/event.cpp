#include "event.h"
#include "exceptions/exception.h"

Event::Event(int id, std::string_view title) : _id(id), _title(title) {
    if (id <= 0) throw InvalidDataException("ID события > 0");
    if (title.empty()) throw InvalidDataException("название не пустое");
}

int Event::getId() const { return _id; }
std::string_view Event::getTitle() const { return _title; }
std::string Event::getType() const { return "Событие"; }
double Event::calculateMetric() const { return 0.0; }
std::string Event::getMetricName() const { return "Метрика"; }
void Event::printInfo(std::ostream& os) const { os << "\n  ID: " << _id; }

std::ostream& operator<<(std::ostream& os, const Event& e) {
    os << "[" << e.getType() << "] " << e._title << " | ID: " << e._id;
    e.printInfo(os);
    return os;
}