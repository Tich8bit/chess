#pragma once

#include "event.h"
#include "collection.h"
#include "player.h"
#include "match.h"
#include "tournamentSystem.h"
#include <string>
#include <string_view>
#include <memory>
#include <iostream>
#include <vector>

struct Standing {
    std::shared_ptr<Player> player;
    int wins;
    int draws;
    int losses;
    double points;
};

class Tournament : public Event {
public:
    enum class TimeControl { Blitz, Rapid, Classic };

    Tournament(int id,
               std::string_view title,
               TimeControl timeControl,
               std::shared_ptr<TournamentSystem> system,
               int maxPlayers);

    TimeControl getTimeControl() const;
    std::shared_ptr<TournamentSystem> getSystem() const;
    int getMaxPlayers() const;
    const Collection<Player>& getParticipants() const;
    const Collection<Match>& getMatches() const;

    void setTimeControl(TimeControl newTimeControl);
    void setSystem(std::shared_ptr<TournamentSystem> newSystem);
    void setMaxPlayers(int newMaxPlayers);

    std::string getType() const override;
    double calculateMetric() const override;
    std::string getMetricName() const override;
    void printInfo(std::ostream& os) const override;

    Tournament& operator+=(std::shared_ptr<Player> player);
    Tournament& operator-=(std::shared_ptr<Player> player);
    Tournament& operator+=(std::shared_ptr<Match> match);

    std::vector<Standing> getStandings(bool useHeadToHead) const;

    static std::string timeControlToString(TimeControl tc);

private:
    TimeControl _timeControl;
    std::shared_ptr<TournamentSystem> _system;
    int _maxPlayers;
    Collection<Player> _participants;
    Collection<Match> _matches;
};