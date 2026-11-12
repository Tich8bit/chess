#pragma once

#include <string>
#include <string_view>
#include <memory>
#include <iostream>
#include "collection.h"
#include "player.h"
#include "event.h"
#include "match.h"
#include "dateTime.h"

class ChessClub {
public:
    explicit ChessClub(std::string_view name);

    std::string_view getName() const;
    size_t getPlayerCount() const;
    size_t getEventCount() const;
    size_t getMatchCount() const;

    const Collection<Player>& getPlayers() const;
    const Collection<Event>& getEvents() const;
    const Collection<Match>& getMatches() const;

    void addPlayer(std::shared_ptr<Player> player);
    bool removePlayer(std::shared_ptr<Player> player);

    void addEvent(std::shared_ptr<Event> event);
    bool removeEvent(std::shared_ptr<Event> event);

    void addMatch(std::shared_ptr<Match> match);
    bool removeMatch(std::shared_ptr<Match> match);

    std::shared_ptr<Player> findPlayerById(int id) const;
    std::shared_ptr<Player> findPlayerByName(std::string_view namePart) const;
    std::shared_ptr<Event> findEventById(int id) const;

    // Изменено: принимает DateTime вместо std::string_view
    void createMatch(int id,
                     std::shared_ptr<Player> white,
                     std::shared_ptr<Player> black,
                     const DateTime& date);

    void printAllPlayers() const;
    void printAllEvents() const;
    void printAllMatches() const;

    ChessClub& operator+=(std::shared_ptr<Player> player);
    ChessClub& operator+=(std::shared_ptr<Event> event);
    ChessClub& operator+=(std::shared_ptr<Match> match);

    friend std::ostream& operator<<(std::ostream& os, const ChessClub& club);

private:
    std::string _clubName;
    Collection<Player> _players;
    Collection<Event> _events;
    Collection<Match> _matches;
};