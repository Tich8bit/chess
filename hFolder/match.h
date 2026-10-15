#pragma once

#include "player.h"
#include <string>
#include <string_view>
#include <iostream>

class Match {
public:
    enum class Result {
        NotPlayed = -1,
        Draw = 0,
        WhiteWin = 1,
        BlackWin = 2
    };

    Match(const Player& whitePlayer,
          const Player& blackPlayer,
          std::string_view date);

    const Player& getWhitePlayer() const;
    const Player& getBlackPlayer() const;
    std::string_view getDate() const;
    Result getResult() const;

    void setResult(Result res);
    void play(Result res);
    void printInfo(std::ostream& os) const;
    bool equals(const Match& other) const;

private:
    Player _whitePlayer;
    Player _blackPlayer;
    std::string _date;
    Result _result;
};