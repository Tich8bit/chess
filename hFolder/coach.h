#pragma once

#include "player.h"

class Coach : public Player {
public:
    Coach(std::string_view firstName,
          std::string_view lastName,
          std::string_view middleName,
          const Ratings& ratings,
          int wins,
          int draws,
          int losses,
          int experienceYears,
          std::string_view specialization,
          int qualificationLevel);

    int getExperienceYears() const;
    std::string_view getSpecialization() const;
    int getQualificationLevel() const;

    void setExperienceYears(int newExperienceYears);
    void setSpecialization(std::string_view newSpecialization);
    void setQualificationLevel(int newQualificationLevel);

    std::string getRole() const override;
    double calculateMetric() const override;
    std::string getMetricName() const override;
    void printInfo(std::ostream& os) const override;

private:
    int _experienceYears;
    std::string _specialization;
    int _qualificationLevel;
};