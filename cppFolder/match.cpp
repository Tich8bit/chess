#include "match.h"
#include "player.h"
#include "tournament.h"
#include "exceptions/exception.h"

Match::Match(std::shared_ptr<Player> whitePlayer,
             std::shared_ptr<Player> blackPlayer,
             std::string_view date)
    : _id(-1),
      _whitePlayer(whitePlayer),
      _blackPlayer(blackPlayer),
      _date(date),
      _result(Result::NotPlayed) {
    if (!whitePlayer || !blackPlayer) {
        throw InvalidDataException("игроки не могут быть пустыми");
    }
    if (whitePlayer == blackPlayer) {
        throw InvalidOperationException("игрок не может играть сам с собой");
    }
    if (date.empty()) {
        throw InvalidDataException("дата партии не может быть пустой");
    }
}

int Match::getId() const { return _id; }
std::shared_ptr<Player> Match::getWhitePlayer() const { return _whitePlayer; }
std::shared_ptr<Player> Match::getBlackPlayer() const { return _blackPlayer; }
std::string_view Match::getDate() const { return _date; }
Match::Result Match::getResult() const { return _result; }
std::shared_ptr<Tournament> Match::getTournament() const { return _tournament.lock(); }

void Match::setId(int newId) { _id = newId; }

void Match::setDate(std::string_view newDate) {
    if (newDate.empty()) {
        throw InvalidDataException("дата партии не может быть пустой");
    }
    _date = newDate;
}

void Match::setResult(Result newResult) { _result = newResult; }

void Match::play(Result newResult) {
    if (newResult == Result::NotPlayed) {
        throw InvalidOperationException("нельзя записать результат 'не сыграна'");
    }
    _result = newResult;
}

void Match::setTournament(std::shared_ptr<Tournament> newTournament) {
    _tournament = newTournament;
}

double Match::calculateMetric() const {
    return _result == Result::NotPlayed ? 0.0 : 1.0;
}

bool operator==(const Match& a, const Match& b) {
    return a._whitePlayer == b._whitePlayer
        && a._blackPlayer == b._blackPlayer
        && a._date == b._date;
}

std::ostream& operator<<(std::ostream& os, const Match& m) {
    os << "Дата: " << m._date
       << " | " << m._whitePlayer->getFullName() << " (белые) vs "
       << m._blackPlayer->getFullName() << " (чёрные) | Результат: ";
    switch (m._result) {
        case Match::Result::NotPlayed: os << "не сыграна"; break;
        case Match::Result::Draw:      os << "ничья"; break;
        case Match::Result::WhiteWin:  os << "победа белых"; break;
        case Match::Result::BlackWin:  os << "победа чёрных"; break;
    }
    return os;
}