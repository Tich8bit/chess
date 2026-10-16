#pragma once

#include "member.h"

class Player : public Member {
public:
    Player(int id, std::string_view fullName, int birthYear, int rating);

    int getRating() const;
    void setRating(int newRating);

    std::string_view getRole() const override;
    double calculateMetric() const override;
    std::string_view getMetricName() const override;
    void printMemberInformation() const override;

    friend int getPlayerRating(const Player& p) { return p._rating; }
    friend bool isExperienced(const Player& p) { return p.getAge() >= 40 && p._rating >= 1500; }

private:
    int _rating;
};