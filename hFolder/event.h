#pragma once

#include <string>
#include <string_view>
#include <iostream>

class Event {
public:
    Event(std::string_view title);
    virtual ~Event() = default;

    int getId() const;
    std::string_view getTitle() const;

    void setId(int newId);
    void setTitle(std::string_view newTitle);

    virtual std::string getType() const;
    virtual double calculateMetric() const;
    virtual std::string getMetricName() const;
    virtual void printInfo(std::ostream& os) const;

    friend std::ostream& operator<<(std::ostream& os, const Event& e);

private:
    int _id;
    std::string _title;
};