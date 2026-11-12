#pragma once
#include "collection.h"
#include "member.h"
#include "event.h"
#include "match.h"

class ChessClub {
public:
    explicit ChessClub(std::string_view name);
    std::string_view getName() const;
    size_t getPlayerCount() const;
    size_t getEventCount() const;
    size_t getMatchCount() const;
    const Collection<Member>& getPlayers() const;
    const Collection<Event>& getEvents() const;
    const Collection<Match>& getMatches() const;

    void addPlayer(std::shared_ptr<Member> player);
    void addEvent(std::shared_ptr<Event> event);
    void addMatch(std::shared_ptr<Match> match);
    
    std::shared_ptr<Member> findPlayerById(int id) const;
    std::shared_ptr<Event> findEventById(int id) const;
    void createMatch(int id, std::shared_ptr<Player> white, std::shared_ptr<Player> black, const DateTime& date);

    void printAllPlayers() const;
    void printAllEvents() const;
    void printAllMatches() const;
    ChessClub& operator+=(std::shared_ptr<Member> player);
    ChessClub& operator+=(std::shared_ptr<Event> event);
    ChessClub& operator+=(std::shared_ptr<Match> match);
private:
    std::string _clubName;
    Collection<Member> _players;
    Collection<Event> _events;
    Collection<Match> _matches;
};