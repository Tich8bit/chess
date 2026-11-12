#pragma once
#include <string>
#include <iostream>

class DateTime {
public:
    DateTime();
    DateTime(int day, int month, int year, int hour = 0, int minute = 0, int second = 0);
    std::string toString() const;
    bool operator<(const DateTime& other) const;
    friend std::ostream& operator<<(std::ostream& os, const DateTime& dt);
private:
    int _day, _month, _year, _hour, _minute, _second;
    bool isLeapYear(int year) const;
    int getDaysInMonth(int month, int year) const;
};