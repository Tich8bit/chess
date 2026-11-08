#include "ratings.h"
#include "exceptions/exception.h"

Ratings::Ratings(int classical, int rapid, int blitz)
    : _classical(classical), _rapid(rapid), _blitz(blitz) {
    if (classical < 0 || classical > 3000 ||
        rapid < 0 || rapid > 3000 ||
        blitz < 0 || blitz > 3000) {
        throw LimitExceededException("рейтинг должен быть от 0 до 3000");
    }
}

int Ratings::getClassical() const { return _classical; }
int Ratings::getRapid() const { return _rapid; }
int Ratings::getBlitz() const { return _blitz; }

int Ratings::getMax() const {
    int maxVal = _classical;
    if (_rapid > maxVal) maxVal = _rapid;
    if (_blitz > maxVal) maxVal = _blitz;
    return maxVal;
}

void Ratings::setClassical(int newClassical) {
    if (newClassical < 0 || newClassical > 3000) {
        throw LimitExceededException("рейтинг должен быть от 0 до 3000");
    }
    _classical = newClassical;
}

void Ratings::setRapid(int newRapid) {
    if (newRapid < 0 || newRapid > 3000) {
        throw LimitExceededException("рейтинг должен быть от 0 до 3000");
    }
    _rapid = newRapid;
}

void Ratings::setBlitz(int newBlitz) {
    if (newBlitz < 0 || newBlitz > 3000) {
        throw LimitExceededException("рейтинг должен быть от 0 до 3000");
    }
    _blitz = newBlitz;
}

std::ostream& operator<<(std::ostream& os, const Ratings& r) {
    os << "Классика: " << r._classical
       << " | Рапид: " << r._rapid
       << " | Блиц: " << r._blitz;
    return os;
}