#pragma once
#include <string>
#include <iostream>

class Event {
public:
    Event(int id, std::string_view title);
    virtual ~Event() = default;
    int getId() const;
    std::string_view getTitle() const;
    virtual std::string getType() const;
    virtual double calculateMetric() const;
    virtual std::string getMetricName() const;
    virtual void printInfo(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const Event& e);
protected:
    int _id;
    std::string _title;
};