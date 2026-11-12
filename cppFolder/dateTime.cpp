#include "dateTime.h"
#include "exceptions/exception.h"
#include <iomanip>
#include <sstream>

DateTime::DateTime() : _day(1), _month(1), _year(2026), _hour(0), _minute(0), _second(0) {}

DateTime::DateTime(int day, int month, int year, int hour, int minute, int second) {
    if (year < 1900 || year > 2100 || month < 1 || month > 12 || hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59)
        throw InvalidDataException("неверная дата/время");
    int maxDays = getDaysInMonth(month, year);
    if (day < 1 || day > maxDays) throw InvalidDataException("неверный день");
    _day = day; _month = month; _year = year; _hour = hour; _minute = minute; _second = second;
}

bool DateTime::isLeapYear(int year) const { return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0); }
int DateTime::getDaysInMonth(int month, int year) const {
    if (month == 2) return isLeapYear(year) ? 29 : 28;
    if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
    return 31;
}

std::string DateTime::toString() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << _day << "." << std::setw(2) << _month << "." << _year
        << " " << std::setw(2) << _hour << ":" << std::setw(2) << _minute << ":" << std::setw(2) << _second;
    return oss.str();
}

bool DateTime::operator<(const DateTime& other) const {
    if (_year != other._year) return _year < other._year;
    if (_month != other._month) return _month < other._month;
    if (_day != other._day) return _day < other._day;
    return _hour < other._hour;
}

std::ostream& operator<<(std::ostream& os, const DateTime& dt) { os << dt.toString(); return os; }