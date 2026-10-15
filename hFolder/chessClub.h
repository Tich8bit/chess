#pragma once

#include "player.h"
#include "match.h"
#include <vector>
#include <string>
#include <string_view>
#include <iostream>

class ChessClub {
public:
    explicit ChessClub(std::string_view name);

    std::string_view getName() const;
    int getPlayerCount() const;
    int getMatchCount() const;

    void addPlayer(const Player& player);
    void removePlayer(int playerId);

    Player* findPlayerById(int searchId);
    const Player* findPlayerById(int searchId) const;

    void createMatch(int id1, int id2, std::string_view date);

    void showAllPlayers(std::ostream& os) const;
    void showAllMatches(std::ostream& os) const;

    void inputPlayerAndAdd();
    void inputMatchAndAdd();

private:
    std::string _clubName;
    std::vector<Player> _players;
    std::vector<Match> _matches;
};