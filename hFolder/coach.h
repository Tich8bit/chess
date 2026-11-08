#pragma once

#include "player.h"
#include "specialization.h"

class Coach : public Player {
public:
    Coach(int id,
          std::string_view firstName,
          std::string_view lastName,
          std::string_view middleName,
          const Ratings& ratings,
          int wins,
          int draws,
          int losses,
          int experienceYears,
          const Specialization& specialization,
          int qualificationLevel);

    int getExperienceYears() const;
    const Specialization& getSpecialization() const;
    int getQualificationLevel() const;

    void setExperienceYears(int newExperienceYears);
    void setSpecialization(const Specialization& newSpecialization);
    void setQualificationLevel(int newQualificationLevel);

    std::string getRole() const override;
    double calculateMetric() const override;
    std::string getMetricName() const override;
    void printInfo(std::ostream& os) const override;

private:
    int _experienceYears;
    Specialization _specialization;
    int _qualificationLevel;
};