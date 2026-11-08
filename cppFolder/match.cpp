#include "match.h"
#include "exceptions/exception.h"

Match::Match(const std::shared_ptr<Player>& whitePlayer,
             const std::shared_ptr<Player>& blackPlayer,
             std::string_view date)
    : _whitePlayer(whitePlayer),
      _blackPlayer(blackPlayer),
      _date(date),
      _result(Result::NotPlayed) {
    if (whitePlayer == blackPlayer) {
        throw InvalidOperationException("Игрок не может играть сам с собой");
    }
    if (date.empty()) {
        throw InvalidDataException("Дата партии не может быть пустой");
    }
}

const std::shared_ptr<Player>& Match::getWhitePlayer() const { return _whitePlayer; }
const std::shared_ptr<Player>& Match::getBlackPlayer() const { return _blackPlayer; }
std::string_view Match::getDate() const { return _date; }
Match::Result Match::getResult() const { return _result; }

void Match::setResult(Result res) { _result = res; }

void Match::play(Result res) {
    if (res == Result::NotPlayed) {
        throw InvalidOperationException("Нельзя записать результат 'не сыграна'");
    }
    _result = res;
}

void Match::printMatchInformation() const { std::cout << *this << "\n"; }

double Match::calculateMetric() const {
    if (_result == Result::NotPlayed) return 0.0;
    return 1.0;
}