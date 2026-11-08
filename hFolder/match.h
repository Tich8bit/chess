#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <iostream>
#include "collection.h"
#include "matchResult.h"

class Player;
class Tournament;

class Match {
public:
    Match(int id,
          std::shared_ptr<Player> whitePlayer,
          std::shared_ptr<Player> blackPlayer,
          std::string_view date);

    int getId() const;
    std::shared_ptr<Player> getWhitePlayer() const;
    std::shared_ptr<Player> getBlackPlayer() const;
    std::string_view getDate() const;
    MatchResult getResult() const;
    std::shared_ptr<Tournament> getTournament() const;

    void setDate(std::string_view newDate);
    void setResult(MatchResult::Result newResult);
    void play(MatchResult::Result newResult);
    void setTournament(std::shared_ptr<Tournament> newTournament);

    double calculateMetric() const;

    friend std::ostream& operator<<(std::ostream& os, const Match& m);
    friend bool operator==(const Match& a, const Match& b);

private:
    int _id;
    std::shared_ptr<Player> _whitePlayer;
    std::shared_ptr<Player> _blackPlayer;
    std::string _date;
    MatchResult _result;
    std::weak_ptr<Tournament> _tournament;
};