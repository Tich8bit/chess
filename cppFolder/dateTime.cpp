#include "dateTime.h"
#include "exceptions/exception.h"
#include <iomanip>
#include <sstream>

DateTime::DateTime() 
    : _day(1), _month(1), _year(2026), _hour(0), _minute(0), _second(0) {}

DateTime::DateTime(int day, int month, int year, int hour, int minute, int second) {
    setDateTime(day, month, year, hour, minute, second);
}

int DateTime::getDay() const { return _day; }
int DateTime::getMonth() const { return _month; }
int DateTime::getYear() const { return _year; }
int DateTime::getHour() const { return _hour; }
int DateTime::getMinute() const { return _minute; }
int DateTime::getSecond() const { return _second; }

bool DateTime::isLeapYear(int year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int DateTime::getDaysInMonth(int month, int year) const {
    if (month == 2) return isLeapYear(year) ? 29 : 28;
    if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
    return 31;
}

void DateTime::setDateTime(int day, int month, int year, int hour, int minute, int second) {
    if (year < 1900 || year > 2100) {
        throw InvalidDataException("год должен быть в диапазоне от 1900 до 2100");
    }
    if (month < 1 || month > 12) {
        throw InvalidDataException("месяц должен быть от 1 до 12");
    }
    
    int maxDays = getDaysInMonth(month, year);
    if (day < 1 || day > maxDays) {
        throw InvalidDataException("некорректный день для указанного месяца и года");
    }
    
    if (hour < 0 || hour > 23) throw InvalidDataException("часы должны быть от 0 до 23");
    if (minute < 0 || minute > 59) throw InvalidDataException("минуты должны быть от 0 до 59");
    if (second < 0 || second > 59) throw InvalidDataException("секунды должны быть от 0 до 59");
    
    _day = day;
    _month = month;
    _year = year;
    _hour = hour;
    _minute = minute;
    _second = second;
}

std::string DateTime::toString() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << _day << "."
        << std::setfill('0') << std::setw(2) << _month << "."
        << _year << " "
        << std::setfill('0') << std::setw(2) << _hour << ":"
        << std::setfill('0') << std::setw(2) << _minute << ":"
        << std::setfill('0') << std::setw(2) << _second;
    return oss.str();
}

bool DateTime::operator<(const DateTime& other) const {
    if (_year != other._year) return _year < other._year;
    if (_month != other._month) return _month < other._month;
    if (_day != other._day) return _day < other._day;
    if (_hour != other._hour) return _hour < other._hour;
    if (_minute != other._minute) return _minute < other._minute;
    return _second < other._second;
}

bool DateTime::operator==(const DateTime& other) const {
    return _year == other._year && _month == other._month && _day == other._day &&
           _hour == other._hour && _minute == other._minute && _second == other._second;
}

std::ostream& operator<<(std::ostream& os, const DateTime& dt) {
    os << dt.toString();
    return os;
}