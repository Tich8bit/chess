#include "coach.h"
#include "exceptions/exception.h"

Coach::Coach(int id,
             std::string_view firstName,
             std::string_view lastName,
             std::string_view middleName,
             const Ratings& ratings,
             int wins,
             int draws,
             int losses,
             int experienceYears,
             const Specialization& specialization,
             int qualificationLevel)
    : Player(id, firstName, lastName, middleName, ratings, wins, draws, losses),
      _experienceYears(experienceYears),
      _specialization(specialization),
      _qualificationLevel(qualificationLevel) {
    if (experienceYears < 0 || experienceYears > 80) {
        throw LimitExceededException("стаж должен быть от 0 до 80 лет");
    }
    if (qualificationLevel < 1 || qualificationLevel > 5) {
        throw LimitExceededException("квалификация должна быть от 1 до 5");
    }
}

int Coach::getExperienceYears() const { return _experienceYears; }
const Specialization& Coach::getSpecialization() const { return _specialization; }
int Coach::getQualificationLevel() const { return _qualificationLevel; }

void Coach::setExperienceYears(int newExperienceYears) {
    if (newExperienceYears < 0 || newExperienceYears > 80) {
        throw LimitExceededException("стаж должен быть от 0 до 80 лет");
    }
    _experienceYears = newExperienceYears;
}

void Coach::setSpecialization(const Specialization& newSpecialization) {
    _specialization = newSpecialization;
}

void Coach::setQualificationLevel(int newQualificationLevel) {
    if (newQualificationLevel < 1 || newQualificationLevel > 5) {
        throw LimitExceededException("квалификация должна быть от 1 до 5");
    }
    _qualificationLevel = newQualificationLevel;
}

std::string Coach::getRole() const { return "Тренер"; }

double Coach::calculateMetric() const {
    return _experienceYears * 3.0
         + _qualificationLevel * 10.0
         + static_cast<double>(getRatings().getMax());
}

std::string Coach::getMetricName() const { return "Тренерский вклад"; }

void Coach::printInfo(std::ostream& os) const {
    Player::printInfo(os);
    os << "\n  Стаж: " << _experienceYears << " лет"
       << "\n  Квалификация: " << _qualificationLevel
       << "\n  Специализация: " << _specialization;
}