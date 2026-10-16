#include "player.h"

Player::Player(int id, std::string_view fullName, int birthYear, int rating)
    : Member(id, fullName, birthYear),
      _rating(rating) {}

int Player::getRating() const { return _rating; }

void Player::setRating(int newRating) { _rating = newRating; }

std::string_view Player::getRole() const { return "Игрок"; }

double Player::calculateMetric() const { return static_cast<double>(_rating); }

std::string_view Player::getMetricName() const { return "Рейтинг Эло"; }

void Player::printMemberInformation() const {
    std::cout << *this << " | Рейтинг: " << _rating << "\n";
}