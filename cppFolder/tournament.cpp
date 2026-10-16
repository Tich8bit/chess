#include "tournament.h"

Tournament::Tournament(int id, std::string_view title,
                       int roundsCount,
                       TimeControl timeControl,
                       System system,
                       int playerCount)
    : Event(id, title),
      _roundsCount(roundsCount),
      _timeControl(timeControl),
      _system(system),
      _playerCount(playerCount) {}

int Tournament::getRoundsCount() const { return _roundsCount; }
Tournament::TimeControl Tournament::getTimeControl() const { return _timeControl; }
Tournament::System Tournament::getSystem() const { return _system; }
int Tournament::getPlayerCount() const { return _playerCount; }

void Tournament::setRoundsCount(int newRoundsCount) { _roundsCount = newRoundsCount; }
void Tournament::setTimeControl(TimeControl newTimeControl) { _timeControl = newTimeControl; }
void Tournament::setSystem(System newSystem) { _system = newSystem; }
void Tournament::setPlayerCount(int newPlayerCount) { _playerCount = newPlayerCount; }

std::string_view Tournament::getType() const { return "Турнир"; }

double Tournament::calculateMetric() const {
    double coef = 1.0;
    if (_timeControl == TimeControl::Rapid) coef = 1.5;
    else if (_timeControl == TimeControl::Classic) coef = 2.0;
    return _roundsCount * coef;
}

std::string_view Tournament::getMetricName() const { return "Игровая нагрузка"; }

void Tournament::printEventInformation() const {
    std::cout << *this
              << " | Туров: " << _roundsCount
              << " | Контроль: " << timeControlToString(_timeControl)
              << " | Система: " << systemToString(_system)
              << " | Участников: " << _playerCount
              << "\n";
}

std::string_view Tournament::timeControlToString(TimeControl tc) {
    switch (tc) {
        case TimeControl::Blitz:   return "Блиц";
        case TimeControl::Rapid:   return "Рапид";
        case TimeControl::Classic: return "Классика";
    }
    return "Неизвестно";
}

std::string_view Tournament::systemToString(System sys) {
    switch (sys) {
        case System::RoundRobin: return "Круговая";
        case System::Swiss:      return "Швейцарская";
    }
    return "Неизвестно";
}