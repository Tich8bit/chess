#include "match.h"
#include "player.h"
#include "exceptions/exception.h"

Match::Match(int id, std::shared_ptr<Player> whitePlayer, std::shared_ptr<Player> blackPlayer, const DateTime& date)
    : _id(id), _whitePlayer(whitePlayer), _blackPlayer(blackPlayer), _date(date), _result(MatchResult::Result::NotPlayed) {
    if (id <= 0) throw InvalidDataException("ID партии > 0");
    if (!whitePlayer || !blackPlayer) throw InvalidDataException("пустые игроки");
}

int Match::getId() const { return _id; }
std::shared_ptr<Player> Match::getWhitePlayer() const { return _whitePlayer; }
std::shared_ptr<Player> Match::getBlackPlayer() const { return _blackPlayer; }
const DateTime& Match::getDate() const { return _date; }
MatchResult Match::getResult() const { return _result; }
void Match::setResult(MatchResult::Result newResult) { _result.setResult(newResult); }

std::ostream& operator<<(std::ostream& os, const Match& m) {
    os << "ID: " << m._id << " | " << m._date << " | " << m._whitePlayer->getFullName() << " vs " << m._blackPlayer->getFullName() << " | " << m._result;
    return os;
}