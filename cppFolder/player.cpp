#include "player.h"
#include "exceptions/exception.h"

Player::Player(int id, std::string_view fullName, int birthYear, int rating)
    : Member(id, fullName, birthYear), _rating(1000) {
    setRating(rating);
}

int Player::getRating() const { return _rating; }

void Player::setRating(int newRating) {
    if (newRating < 0 || newRating > 3000) {
        throw LimitExceededException("Рейтинг должен быть от 0 до 3000. Получено: " + std::to_string(newRating));
    }
    _rating = newRating;
}

std::string_view Player::getRole() const { return "Игрок"; }

double Player::calculateMetric() const { return static_cast<double>(_rating); }

std::string_view Player::getMetricName() const { return "Рейтинг Эло"; }

void Player::printMemberInformation() const {
    std::cout << *this << " | Рейтинг: " << _rating << "\n";
}