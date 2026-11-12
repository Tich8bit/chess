#pragma once
#include <string>
#include <string_view>
#include <iostream>
#include "ratings.h"

class Member {
public:
    Member(int id, std::string_view firstName, std::string_view lastName, std::string_view middleName, const Ratings& ratings, int wins, int draws, int losses);
    virtual ~Member() = default;

    int getId() const;
    std::string_view getFirstName() const;
    std::string_view getLastName() const;
    std::string_view getMiddleName() const;
    std::string getFullName() const;
    const Ratings& getRatings() const;
    int getWins() const;
    int getDraws() const;
    int getLosses() const;
    int getGamesPlayed() const;
    double getScore() const;

    virtual std::string getRole() const = 0;
    virtual double calculateMetric() const = 0;
    virtual std::string getMetricName() const = 0;
    virtual void printInfo(std::ostream& os) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Member& m);

protected:
    int _id;
    std::string _firstName;
    std::string _lastName;
    std::string _middleName;
    Ratings _ratings;
    int _wins;
    int _draws;
    int _losses;
};