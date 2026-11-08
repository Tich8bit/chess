#include "player.h"
#include "exceptions/exception.h"

Player::Player(std::string_view firstName,
               std::string_view lastName,
               std::string_view middleName,
               const Ratings& ratings,
               int wins,
               int draws,
               int losses)
    : _id(-1),
      _firstName(firstName),
      _lastName(lastName),
      _middleName(middleName),
      _ratings(ratings),
      _wins(wins),
      _draws(draws),
      _losses(losses) {
    if (firstName.empty()) {
        throw InvalidDataException("имя не может быть пустым");
    }
    if (lastName.empty()) {
        throw InvalidDataException("фамилия не может быть пустой");
    }
    if (wins < 0 || draws < 0 || losses < 0) {
        throw InvalidDataException("статистика не может быть отрицательной");
    }
}

int Player::getId() const { return _id; }
std::string_view Player::getFirstName() const { return _firstName; }
std::string_view Player::getLastName() const { return _lastName; }
std::string_view Player::getMiddleName() const { return _middleName; }

std::string Player::getFullName() const {
    std::string result(_lastName);
    if (!_firstName.empty()) {
        result += " ";
        result += _firstName;
    }
    if (!_middleName.empty()) {
        result += " ";
        result += _middleName;
    }
    return result;
}

const Ratings& Player::getRatings() const { return _ratings; }
int Player::getWins() const { return _wins; }
int Player::getDraws() const { return _draws; }
int Player::getLosses() const { return _losses; }
int Player::getGamesPlayed() const { return _wins + _draws + _losses; }

double Player::getScore() const {
    int games = getGamesPlayed();
    if (games == 0) return 0.0;
    return (_wins + 0.5 * _draws) / games;
}

void Player::setId(int newId) { _id = newId; }

void Player::setFirstName(std::string_view newFirstName) {
    if (newFirstName.empty()) {
        throw InvalidDataException("имя не может быть пустым");
    }
    _firstName = newFirstName;
}

void Player::setLastName(std::string_view newLastName) {
    if (newLastName.empty()) {
        throw InvalidDataException("фамилия не может быть пустой");
    }
    _lastName = newLastName;
}

void Player::setMiddleName(std::string_view newMiddleName) { _middleName = newMiddleName; }
void Player::setRatings(const Ratings& newRatings) { _ratings = newRatings; }

void Player::setWins(int newWins) {
    if (newWins < 0) throw InvalidDataException("победы не могут быть отрицательными");
    _wins = newWins;
}

void Player::setDraws(int newDraws) {
    if (newDraws < 0) throw InvalidDataException("ничьи не могут быть отрицательными");
    _draws = newDraws;
}

void Player::setLosses(int newLosses) {
    if (newLosses < 0) throw InvalidDataException("поражения не могут быть отрицательными");
    _losses = newLosses;
}

std::string Player::getRole() const { return "Игрок"; }
double Player::calculateMetric() const { return static_cast<double>(_ratings.getMax()); }
std::string Player::getMetricName() const { return "Максимальный рейтинг"; }

void Player::printInfo(std::ostream& os) const {
    os << "\n  Рейтинги: " << _ratings
       << "\n  В/Н/П: " << _wins << "/" << _draws << "/" << _losses
       << "\n  Очки: " << getScore();
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
    os << "[" << p.getRole() << "] "
       << p.getFullName()
       << " | ID: " << p._id
       << " | Метрика: " << p.calculateMetric()
       << " (" << p.getMetricName() << ")";
    p.printInfo(os);
    return os;
}