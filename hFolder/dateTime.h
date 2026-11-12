#pragma once

#include <string>
#include <iostream>

class DateTime {
public:
    DateTime();
    DateTime(int day, int month, int year, int hour = 0, int minute = 0, int second = 0);

    int getDay() const;
    int getMonth() const;
    int getYear() const;
    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    void setDateTime(int day, int month, int year, int hour, int minute, int second);
    std::string toString() const;

    bool operator<(const DateTime& other) const;
    bool operator==(const DateTime& other) const;

    friend std::ostream& operator<<(std::ostream& os, const DateTime& dt);

private:
    int _day;
    int _month;
    int _year;
    int _hour;
    int _minute;
    int _second;

    bool isLeapYear(int year) const;
    int getDaysInMonth(int month, int year) const;
};