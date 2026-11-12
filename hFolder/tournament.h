#pragma once
#include "event.h"
#include "collection.h"
#include "member.h"
#include "match.h"
#include "tournamentSystem.h"
#include <vector>

struct Standing {
    std::shared_ptr<Member> player;
    int wins, draws, losses;
    double points;
};

class Tournament : public Event {
public:
    enum class TimeControl { Blitz, Rapid, Classic };
    
    Tournament(int id, std::string_view title, TimeControl timeControl, std::shared_ptr<TournamentSystem> system, int maxPlayers);
    
    TimeControl getTimeControl() const;
    int getMaxPlayers() const;
    const Collection<Member>& getParticipants() const;
    const Collection<Match>& getMatches() const;
    std::shared_ptr<TournamentSystem> getSystem() const;
    
    std::string getType() const override;
    double calculateMetric() const override;
    std::string getMetricName() const override;
    void printInfo(std::ostream& os) const override;
    
    Tournament& operator+=(std::shared_ptr<Member> player);
    Tournament& operator-=(std::shared_ptr<Member> player);
    Tournament& operator+=(std::shared_ptr<Match> match);
    std::vector<Standing> getStandings(bool useHeadToHead) const;

private:
    TimeControl _timeControl;
    std::shared_ptr<TournamentSystem> _system;
    int _maxPlayers;
    Collection<Member> _participants;
    Collection<Match> _matches;
};