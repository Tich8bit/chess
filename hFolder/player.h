#pragma once

#include <string>
#include <string_view>
#include <iostream>
#include "ratings.h"

class Player {
public:
    Player(int id,
           std::string_view firstName,
           std::string_view lastName,
           std::string_view middleName,
           const Ratings& ratings,
           int wins,
           int draws,
           int losses);

    virtual ~Player() = default;

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

    void setFirstName(std::string_view newFirstName);
    void setLastName(std::string_view newLastName);
    void setMiddleName(std::string_view newMiddleName);
    void setRatings(const Ratings& newRatings);
    void setWins(int newWins);
    void setDraws(int newDraws);
    void setLosses(int newLosses);

    virtual std::string getRole() const;
    virtual double calculateMetric() const;
    virtual std::string getMetricName() const;
    virtual void printInfo(std::ostream& os) const;

    friend std::ostream& operator<<(std::ostream& os, const Player& p);

private:
    int _id;
    std::string _firstName;
    std::string _lastName;
    std::string _middleName;
    Ratings _ratings;
    int _wins;
    int _draws;
    int _losses;
};