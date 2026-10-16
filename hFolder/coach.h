#pragma once

#include "member.h"

class Coach : public Member {
public:
    Coach(int id, std::string_view fullName, int birthYear,
          int experienceYears, int studentsCount, std::string_view specialization);

    int getExperienceYears() const;
    int getStudentsCount() const;
    std::string_view getSpecialization() const;

    void setExperienceYears(int newExperienceYears);
    void setStudentsCount(int newStudentsCount);
    void setSpecialization(std::string_view newSpecialization);

    std::string_view getRole() const override;
    double calculateMetric() const override;
    std::string_view getMetricName() const override;
    void printMemberInformation() const override;

private:
    int _experienceYears;
    int _studentsCount;
    std::string _specialization;
};