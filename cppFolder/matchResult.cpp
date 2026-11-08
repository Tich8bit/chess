#include "matchResult.h"

MatchResult::MatchResult() : _result(Result::NotPlayed) {}

MatchResult::MatchResult(Result result) : _result(result) {}

MatchResult::Result MatchResult::getResult() const { return _result; }

void MatchResult::setResult(Result newResult) { _result = newResult; }

bool MatchResult::isPlayed() const { return _result != Result::NotPlayed; }

double MatchResult::getWhiteScore() const {
    if (_result == Result::WhiteWin) return 1.0;
    if (_result == Result::Draw)     return 0.5;
    return 0.0;
}

double MatchResult::getBlackScore() const {
    if (_result == Result::BlackWin) return 1.0;
    if (_result == Result::Draw)     return 0.5;
    return 0.0;
}

std::string MatchResult::toString() const {
    return toString(_result);
}

std::string MatchResult::toString(Result result) {
    switch (result) {
        case Result::NotPlayed: return "не сыграна";
        case Result::Draw:      return "ничья";
        case Result::WhiteWin:  return "победа белых";
        case Result::BlackWin:  return "победа чёрных";
    }
    return "неизвестно";
}

std::ostream& operator<<(std::ostream& os, const MatchResult& res) {
    os << res.toString();
    return os;
}

bool operator==(const MatchResult& a, const MatchResult& b) {
    return a._result == b._result;
}