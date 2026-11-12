#pragma once

#include <memory>
#include <string>
#include <iostream>
#include "matchResult.h"
#include "dateTime.h"

class Player;

class Match {
public:
    Match(int id,
          std::shared_ptr<Player> whitePlayer,
          std::shared_ptr<Player> blackPlayer,
          const DateTime& date);

    int getId() const;
    std::shared_ptr<Player> getWhitePlayer() const;
    std::shared_ptr<Player> getBlackPlayer() const;
    const DateTime& getDate() const;
    MatchResult getResult() const;

    void setDate(const DateTime& newDate);
    void setResult(MatchResult::Result newResult);
    void play(MatchResult::Result newResult);

    double calculateMetric() const;

    friend std::ostream& operator<<(std::ostream& os, const Match& m);
    friend bool operator==(const Match& a, const Match& b);

private:
    int _id;
    std::shared_ptr<Player> _whitePlayer;
    std::shared_ptr<Player> _blackPlayer;
    DateTime _date;
    MatchResult _result;
};