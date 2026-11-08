#include "event.h"
#include "exceptions/exception.h"

Event::Event(int id, std::string_view title)
    : _id(id), _title(title) {
    if (title.empty()) {
        throw InvalidDataException("Название события не может быть пустым");
    }
}

Event::~Event() {}

int Event::getId() const { return _id; }
std::string_view Event::getTitle() const { return _title; }

void Event::setTitle(std::string_view newTitle) {
    if (newTitle.empty()) {
        throw InvalidDataException("Название события не может быть пустым");
    }
    _title = newTitle;
}

std::string_view Event::getType() const { return "Событие"; }
double Event::calculateMetric() const { return 0.0; }
std::string_view Event::getMetricName() const { return "Метрика"; }

void Event::printEventInformation() const { std::cout << *this << "\n"; }