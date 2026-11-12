#include "match.h"
#include "player.h"
#include "exceptions/exception.h"

Match::Match(int id, std::shared_ptr<Player> whitePlayer, std::shared_ptr<Player> blackPlayer, const DateTime& date)
    : _id(id), _whitePlayer(whitePlayer), _blackPlayer(blackPlayer), _date(date), _result(MatchResult::Result::NotPlayed) {
    if (id <= 0) throw InvalidDataException("ID должен быть положительным");
    if (!whitePlayer || !blackPlayer) throw InvalidDataException("игроки не могут быть пустыми");
    if (whitePlayer == blackPlayer) throw InvalidOperationException("игрок не может играть сам с собой");
}

int Match::getId() const { return _id; }
std::shared_ptr<Player> Match::getWhitePlayer() const { return _whitePlayer; }
std::shared_ptr<Player> Match::getBlackPlayer() const { return _blackPlayer; }
const DateTime& Match::getDate() const { return _date; }
MatchResult Match::getResult() const { return _result; }

void Match::setDate(const DateTime& newDate) { _date = newDate; }

void Match::setResult(MatchResult::Result newResult) { _result.setResult(newResult); }

void Match::play(MatchResult::Result newResult) {
    if (newResult == MatchResult::Result::NotPlayed) {
        throw InvalidOperationException("нельзя записать результат 'не сыграна'");
    }
    _result.setResult(newResult);
}

double Match::calculateMetric() const { return _result.isPlayed() ? 1.0 : 0.0; }

bool operator==(const Match& a, const Match& b) {
    return a._whitePlayer == b._whitePlayer && a._blackPlayer == b._blackPlayer && a._date == b._date;
}

std::ostream& operator<<(std::ostream& os, const Match& m) {
    os << "ID: " << m._id << " | Дата: " << m._date
       << " | " << m._whitePlayer->getFullName() << " (белые) vs "
       << m._blackPlayer->getFullName() << " (чёрные) | Результат: " << m._result;
    return os;
}