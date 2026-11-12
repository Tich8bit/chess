#include "member.h"
#include "exceptions/exception.h"

Member::Member(int id, std::string_view firstName, std::string_view lastName, std::string_view middleName, const Ratings& ratings, int wins, int draws, int losses)
    : _id(id), _firstName(firstName), _lastName(lastName), _middleName(middleName),
      _ratings(ratings), _wins(wins), _draws(draws), _losses(losses) {
    if (id <= 0) throw InvalidDataException("ID > 0");
    if (firstName.empty() || lastName.empty()) throw InvalidDataException("имя/фамилия пустые");
}

int Member::getId() const { return _id; }
std::string_view Member::getFirstName() const { return _firstName; }
std::string_view Member::getLastName() const { return _lastName; }
std::string_view Member::getMiddleName() const { return _middleName; }

std::string Member::getFullName() const {
    std::string res(_lastName);
    if (!_firstName.empty()) { res += " "; res += _firstName; }
    if (!_middleName.empty()) { res += " "; res += _middleName; }
    return res;
}

const Ratings& Member::getRatings() const { return _ratings; }
int Member::getWins() const { return _wins; }
int Member::getDraws() const { return _draws; }
int Member::getLosses() const { return _losses; }
int Member::getGamesPlayed() const { return _wins + _draws + _losses; }

double Member::getScore() const {
    int games = getGamesPlayed();
    if (games == 0) return 0.0;
    return (_wins + 0.5 * _draws) / games;
}

std::ostream& operator<<(std::ostream& os, const Member& m) {
    os << "[" << m.getRole() << "] " << m.getFullName() << " | ID: " << m._id << " | Метрика: " << m.calculateMetric();
    m.printInfo(os);
    return os;
}