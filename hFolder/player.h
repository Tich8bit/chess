#pragma once
#include "member.h"
#include "specialization.h"

class Player : public Member {
public:
    Player(int id, std::string_view firstName, std::string_view lastName, std::string_view middleName, const Ratings& ratings, int wins, int draws, int losses);
    std::string getRole() const override;
    double calculateMetric() const override;
    std::string getMetricName() const override;
    void printInfo(std::ostream& os) const override;
    void applyTrainingEffect(const Specialization& spec);
};