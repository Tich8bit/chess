#pragma once

#include <string>
#include <string_view>
#include <iostream>
#include <compare>

class Event {
public:
    Event(int id, std::string_view title);
    virtual ~Event();

    int getId() const;
    std::string_view getTitle() const;

    void setTitle(std::string_view newTitle);

    virtual std::string_view getType() const;
    virtual double calculateMetric() const;
    virtual std::string_view getMetricName() const;
    virtual void printEventInformation() const;

    friend bool operator==(const Event& a, const Event& b) {
        return a._id == b._id;
    }

    friend std::strong_ordering operator<=>(const Event& a, const Event& b) {
        if (a.calculateMetric() < b.calculateMetric()) return std::strong_ordering::less;
        if (a.calculateMetric() > b.calculateMetric()) return std::strong_ordering::greater;
        return std::strong_ordering::equal;
    }

    friend std::ostream& operator<<(std::ostream& os, const Event& e) {
        os << "ID: " << e._id
           << " | Тип: " << e.getType()
           << " | Название: " << e._title
           << " | " << e.getMetricName() << ": " << e.calculateMetric();
        return os;
    }

protected:
    int _id;
    std::string _title;
};