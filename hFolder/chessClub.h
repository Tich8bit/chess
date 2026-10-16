#pragma once

#include "member.h"
#include "player.h"
#include "coach.h"
#include "match.h"
#include "event.h"
#include "collection.h"
#include <string>
#include <string_view>
#include <memory>
#include <iostream>

class ChessClub {
public:
    explicit ChessClub(std::string_view name);

    std::string_view getName() const;
    int getMemberCount() const;
    int getMatchCount() const;
    int getEventCount() const;

    void addMember(const std::shared_ptr<Member>& member);
    bool removeMemberAt(int index);
    template <typename Predicate> int removeMembersIf(Predicate pred) {
        return _members.removeIf(pred);
    }
    std::shared_ptr<Member> findMemberById(int searchId) const;
    std::shared_ptr<Player> findPlayerById(int searchId) const;

    void createMatch(int id1, int id2, std::string_view date);

    void addEvent(const std::shared_ptr<Event>& event);
    bool removeEventAt(int index);
    std::shared_ptr<Event> findEventById(int searchId) const;

    void printAllMembers() const;
    void printAllMatches() const;
    void printAllEvents() const;
    void printAllMetrics() const;

    Collection<std::shared_ptr<Member>>& getMembers() { return _members; }
    const Collection<std::shared_ptr<Member>>& getMembers() const { return _members; }
    Collection<Match>& getMatches() { return _matches; }
    const Collection<Match>& getMatches() const { return _matches; }
    Collection<std::shared_ptr<Event>>& getEvents() { return _events; }
    const Collection<std::shared_ptr<Event>>& getEvents() const { return _events; }

    ChessClub& operator+=(const std::shared_ptr<Member>& member);
    ChessClub& operator-=(const std::shared_ptr<Member>& member);
    ChessClub& operator+=(const std::shared_ptr<Event>& event);
    ChessClub& operator-=(const std::shared_ptr<Event>& event);

    friend std::ostream& operator<<(std::ostream& os, const ChessClub& c) {
        os << "Клуб: " << c._clubName
           << " | Участников: " << c._members.size()
           << " | Партий: " << c._matches.size()
           << " | Событий: " << c._events.size();
        return os;
    }

    friend int getTotalClubRating(const ChessClub& c) {
        int total = 0;
        for (int i = 0; i < c._members.size(); ++i) {
            if (auto p = std::dynamic_pointer_cast<Player>(c._members.getShared(i))) {
                total += p->getRating();
            }
        }
        return total;
    }

private:
    std::string _clubName;
    Collection<std::shared_ptr<Member>> _members;
    Collection<Match> _matches;
    Collection<std::shared_ptr<Event>> _events;
};