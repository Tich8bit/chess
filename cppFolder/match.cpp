#include "match.h"

Match::Match(const Player& whitePlayer,
             const Player& blackPlayer,
             std::string_view date)
    : _whitePlayer(whitePlayer),
      _blackPlayer(blackPlayer),
      _date(date),
      _result(Result::NotPlayed) {
    if (whitePlayer.equals(blackPlayer)) {
        std::cerr << "[Ошибка] Игрок не может играть сам с собой.\n";
    }
}

const Player& Match::getWhitePlayer() const { return _whitePlayer; }
const Player& Match::getBlackPlayer() const { return _blackPlayer; }
std::string_view Match::getDate() const { return _date; }
Match::Result Match::getResult() const { return _result; }

void Match::setResult(Result res) {
    _result = res;
}

void Match::play(Result res) {
    if (res == Result::NotPlayed) {
        std::cerr << "[Ошибка] Нельзя записать результат 'не сыграна'.\n";
        return;
    }
    _result = res;
}

void Match::printInfo(std::ostream& os) const {
    os << "Дата: " << _date
       << " | " << _whitePlayer.getName() << " (Белые) vs "
       << _blackPlayer.getName() << " (Черные) | Результат: ";
    switch (_result) {
        case Result::NotPlayed: os << "Не сыграна"; break;
        case Result::Draw:      os << "Ничья 0.5 - 0.5"; break;
        case Result::WhiteWin:  os << "Победа белых 1 - 0"; break;
        case Result::BlackWin:  os << "Победа черных 0 - 1"; break;
    }
}

bool Match::equals(const Match& other) const {
    return _whitePlayer.equals(other._whitePlayer)
        && _blackPlayer.equals(other._blackPlayer)
        && _date == other._date;
}