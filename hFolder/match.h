#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <iostream>
#include "collection.h"

class Player;
class Tournament;

class Match {
public:
    enum class Result { NotPlayed = -1, Draw = 0, WhiteWin = 1, BlackWin = 2 };

    Match(int id,
          std::shared_ptr<Player> whitePlayer,
          std::shared_ptr<Player> blackPlayer,
          std::string_view date);

    int getId() const;
    std::shared_ptr<Player> getWhitePlayer() const;
    std::shared_ptr<Player> getBlackPlayer() const;
    std::string_view getDate() const;
    Result getResult() const;
    std::shared_ptr<Tournament> getTournament() const;

    void setDate(std::string_view newDate);
    void setResult(Result newResult);
    void play(Result newResult);
    void setTournament(std::shared_ptr<Tournament> newTournament);

    double calculateMetric() const;

    friend std::ostream& operator<<(std::ostream& os, const Match& m);
    friend bool operator==(const Match& a, const Match& b);

private:
    int _id;
    std::shared_ptr<Player> _whitePlayer;
    std::shared_ptr<Player> _blackPlayer;
    std::string _date;
    Result _result;
    std::weak_ptr<Tournament> _tournament;
};