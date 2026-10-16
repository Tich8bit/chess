#pragma once

#include "player.h"
#include <memory>
#include <string>
#include <string_view>
#include <iostream>

class Match {
public:
    enum class Result { NotPlayed = -1, Draw = 0, WhiteWin = 1, BlackWin = 2 };

    Match(const std::shared_ptr<Player>& whitePlayer,
          const std::shared_ptr<Player>& blackPlayer,
          std::string_view date);

    const std::shared_ptr<Player>& getWhitePlayer() const;
    const std::shared_ptr<Player>& getBlackPlayer() const;
    std::string_view getDate() const;
    Result getResult() const;

    void setResult(Result res);
    void play(Result res);

    void printMatchInformation() const;
    double calculateMetric() const;

    friend bool operator==(const Match& a, const Match& b) {
        return a._whitePlayer == b._whitePlayer
            && a._blackPlayer == b._blackPlayer
            && a._date == b._date;
    }

    friend std::ostream& operator<<(std::ostream& os, const Match& m) {
        os << "Дата: " << m._date
           << " | " << m._whitePlayer->getFullName() << " (Белые) vs "
           << m._blackPlayer->getFullName() << " (Черные) | Результат: ";
        switch (m._result) {
            case Match::Result::NotPlayed: os << "Не сыграна"; break;
            case Match::Result::Draw:      os << "Ничья 0.5 - 0.5"; break;
            case Match::Result::WhiteWin:  os << "Победа белых 1 - 0"; break;
            case Match::Result::BlackWin:  os << "Победа черных 0 - 1"; break;
        }
        return os;
    }

private:
    std::shared_ptr<Player> _whitePlayer;
    std::shared_ptr<Player> _blackPlayer;
    std::string _date;
    Result _result;
};