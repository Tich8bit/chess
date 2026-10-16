#include "coach.h"

Coach::Coach(int id, std::string_view fullName, int birthYear,
             int experienceYears, int studentsCount, std::string_view specialization)
    : Member(id, fullName, birthYear),
      _experienceYears(experienceYears),
      _studentsCount(studentsCount),
      _specialization(specialization) {}

int Coach::getExperienceYears() const { return _experienceYears; }
int Coach::getStudentsCount() const { return _studentsCount; }
std::string_view Coach::getSpecialization() const { return _specialization; }

void Coach::setExperienceYears(int newExperienceYears) { _experienceYears = newExperienceYears; }
void Coach::setStudentsCount(int newStudentsCount) { _studentsCount = newStudentsCount; }
void Coach::setSpecialization(std::string_view newSpecialization) { _specialization = newSpecialization; }

std::string_view Coach::getRole() const { return "Тренер"; }

double Coach::calculateMetric() const {
    return _experienceYears * 3.0 + _studentsCount * 0.5;
}

std::string_view Coach::getMetricName() const { return "Тренерский вклад"; }

void Coach::printMemberInformation() const {
    std::cout << *this
              << " | Стаж: " << _experienceYears << " лет"
              << " | Учеников: " << _studentsCount
              << " | Специализация: " << _specialization << "\n";
}