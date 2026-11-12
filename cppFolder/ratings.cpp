#include "ratings.h"
#include "exceptions/exception.h"
#include <algorithm>

Ratings::Ratings(int classical, int rapid, int blitz)
    : _classical(classical), _rapid(rapid), _blitz(blitz) {
    if (classical < 0 || classical > 3000 || rapid < 0 || rapid > 3000 || blitz < 0 || blitz > 3000)
        throw LimitExceededException("рейтинг от 0 до 3000");
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

std::ostream& operator<<(std::ostream& os, const Ratings& r) {
    os << "Классика: " << r._classical << " | Рапид: " << r._rapid << " | Блиц: " << r._blitz;
    return os;
}