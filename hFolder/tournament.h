#pragma once

#include "event.h"
#include "collection.h"

class Player;

class Tournament : public Event {
public:
    enum class TimeControl { Blitz, Rapid, Classic };
    enum class TournamentSystem { RoundRobin, Swiss };

    Tournament(std::string_view title,
               int roundsCount,
               TimeControl timeControl,
               TournamentSystem system,
               int maxPlayers);

    int getRoundsCount() const;
    TimeControl getTimeControl() const;
    TournamentSystem getSystem() const;
    int getMaxPlayers() const;
    const Collection<Player>& getPlayers() const;

    void setRoundsCount(int newRoundsCount);
    void setTimeControl(TimeControl newTimeControl);
    void setSystem(TournamentSystem newSystem);
    void setMaxPlayers(int newMaxPlayers);

    std::string getType() const override;
    double calculateMetric() const override;
    std::string getMetricName() const override;
    void printInfo(std::ostream& os) const override;

    Tournament& operator+=(std::shared_ptr<Player> player);
    Tournament& operator-=(std::shared_ptr<Player> player);

    static std::string timeControlToString(TimeControl tc);
    static std::string systemToString(TournamentSystem sys);

private:
    int _roundsCount;
    TimeControl _timeControl;
    TournamentSystem _system;
    int _maxPlayers;
    Collection<Player> _players;
};