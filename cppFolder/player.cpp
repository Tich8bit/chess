#include "player.h"

Player::Player(int id, std::string_view firstName, std::string_view lastName, std::string_view middleName, const Ratings& ratings, int wins, int draws, int losses)
    : Member(id, firstName, lastName, middleName, ratings, wins, draws, losses) {}

std::string Player::getRole() const { return "Игрок"; }
double Player::calculateMetric() const { return static_cast<double>(_ratings.getMax()); }
std::string Player::getMetricName() const { return "Максимальный рейтинг"; }

void Player::printInfo(std::ostream& os) const {
    os << "\n  Рейтинги: " << _ratings << "\n  В/Н/П: " << _wins << "/" << _draws << "/" << _losses << "\n  Очки: " << getScore();
}

void Player::applyTrainingEffect(const Specialization& spec) {
    auto target = spec.getTargetRating();
    const int boost = 10;
    if (target == Specialization::RatingType::Classical) _ratings = Ratings(_ratings.getClassical() + boost, _ratings.getRapid(), _ratings.getBlitz());
    else if (target == Specialization::RatingType::Rapid) _ratings = Ratings(_ratings.getClassical(), _ratings.getRapid() + boost, _ratings.getBlitz());
    else if (target == Specialization::RatingType::Blitz) _ratings = Ratings(_ratings.getClassical(), _ratings.getRapid(), _ratings.getBlitz() + boost);
    else if (target == Specialization::RatingType::All) _ratings = Ratings(_ratings.getClassical() + boost/2, _ratings.getRapid() + boost/2, _ratings.getBlitz() + boost/2);
}