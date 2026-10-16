#pragma once

#include "event.h"

class Tournament : public Event {
public:
    enum class TimeControl { Blitz, Rapid, Classic };
    enum class System { RoundRobin, Swiss };

    Tournament(int id, std::string_view title,
               int roundsCount,
               TimeControl timeControl,
               System system,
               int playerCount);

    int getRoundsCount() const;
    TimeControl getTimeControl() const;
    System getSystem() const;
    int getPlayerCount() const;

    void setRoundsCount(int newRoundsCount);
    void setTimeControl(TimeControl newTimeControl);
    void setSystem(System newSystem);
    void setPlayerCount(int newPlayerCount);

    std::string_view getType() const override;
    double calculateMetric() const override;
    std::string_view getMetricName() const override;
    void printEventInformation() const override;

    static std::string_view timeControlToString(TimeControl tc);
    static std::string_view systemToString(System sys);

private:
    int _roundsCount;
    TimeControl _timeControl;
    System _system;
    int _playerCount;
};