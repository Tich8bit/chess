#include "coach.h"
#include "exceptions/exception.h"

Coach::Coach(int id, std::string_view firstName, std::string_view lastName, std::string_view middleName, const Ratings& ratings, int wins, int draws, int losses, int experienceYears, const Specialization& specialization, int qualificationLevel)
    : Member(id, firstName, lastName, middleName, ratings, wins, draws, losses),
      _experienceYears(experienceYears), _specialization(specialization), _qualificationLevel(qualificationLevel) {
    if (experienceYears < 0 || experienceYears > 80) throw LimitExceededException("стаж 0-80");
}

int Coach::getExperienceYears() const { return _experienceYears; }
const Specialization& Coach::getSpecialization() const { return _specialization; }
int Coach::getQualificationLevel() const { return _qualificationLevel; }
std::string Coach::getRole() const { return "Тренер"; }

double Coach::calculateMetric() const {
    return _experienceYears * 3.0 + _qualificationLevel * 10.0 + static_cast<double>(_ratings.getMax());
}

std::string Coach::getMetricName() const { return "Тренерский вклад"; }

void Coach::printInfo(std::ostream& os) const {
    os << "\n  Рейтинги: " << _ratings << "\n  Стаж: " << _experienceYears << "\n  Квалификация: " << _qualificationLevel << "\n  Специализация: " << _specialization;
}