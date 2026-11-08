#include "tournament.h"
#include "player.h"
#include "exceptions/exception.h"

Tournament::Tournament(std::string_view title,
                       int roundsCount,
                       TimeControl timeControl,
                       TournamentSystem system,
                       int maxPlayers)
    : Event(title),
      _roundsCount(roundsCount),
      _timeControl(timeControl),
      _system(system),
      _maxPlayers(maxPlayers) {
    if (roundsCount < 1 || roundsCount > 30) {
        throw LimitExceededException("количество туров должно быть от 1 до 30");
    }
    if (maxPlayers < 2 || maxPlayers > 200) {
        throw LimitExceededException("количество участников должно быть от 2 до 200");
    }
}

int Tournament::getRoundsCount() const { return _roundsCount; }
Tournament::TimeControl Tournament::getTimeControl() const { return _timeControl; }
Tournament::TournamentSystem Tournament::getSystem() const { return _system; }
int Tournament::getMaxPlayers() const { return _maxPlayers; }
const Collection<Player>& Tournament::getPlayers() const { return _players; }

void Tournament::setRoundsCount(int newRoundsCount) {
    if (newRoundsCount < 1 || newRoundsCount > 30) {
        throw LimitExceededException("количество туров должно быть от 1 до 30");
    }
    _roundsCount = newRoundsCount;
}

void Tournament::setTimeControl(TimeControl newTimeControl) { _timeControl = newTimeControl; }
void Tournament::setSystem(TournamentSystem newSystem) { _system = newSystem; }

void Tournament::setMaxPlayers(int newMaxPlayers) {
    if (newMaxPlayers < 2 || newMaxPlayers > 200) {
        throw LimitExceededException("количество участников должно быть от 2 до 200");
    }
    _maxPlayers = newMaxPlayers;
}

std::string Tournament::getType() const { return "Турнир"; }

double Tournament::calculateMetric() const {
    double coef = 1.0;
    if (_timeControl == TimeControl::Rapid) coef = 1.5;
    else if (_timeControl == TimeControl::Classic) coef = 2.0;
    return _roundsCount * coef;
}

std::string Tournament::getMetricName() const { return "Игровая нагрузка"; }

void Tournament::printInfo(std::ostream& os) const {
    Event::printInfo(os);
    os << "\n  Туров: " << _roundsCount
       << "\n  Контроль: " << timeControlToString(_timeControl)
       << "\n  Система: " << systemToString(_system)
       << "\n  Участников: " << _players.size() << "/" << _maxPlayers;
}

Tournament& Tournament::operator+=(std::shared_ptr<Player> player) {
    if (!player) {
        throw InvalidDataException("пустой указатель на игрока");
    }
    if (_players.size() >= static_cast<size_t>(_maxPlayers)) {
        throw LimitExceededException("турнир заполнен (макс. " + std::to_string(_maxPlayers) + ")");
    }
    if (auto existing = _players.find([&player](const std::shared_ptr<Player>& p) {
        return p == player;
    })) {
        throw DuplicateIdException("игрок " + player->getFullName() + " уже участвует в турнире");
    }
    _players.add(player);
    return *this;
}

Tournament& Tournament::operator-=(std::shared_ptr<Player> player) {
    if (!player) {
        throw InvalidDataException("пустой указатель на игрока");
    }
    if (size_t removed = _players.removeIf([&player](const std::shared_ptr<Player>& p) {
        return p == player;
    }); removed == 0) {
        throw ObjectNotFoundException("игрок " + player->getFullName() + " не участвует в турнире");
    }
    return *this;
}

std::string Tournament::timeControlToString(TimeControl tc) {
    switch (tc) {
        case TimeControl::Blitz:   return "Блиц";
        case TimeControl::Rapid:   return "Рапид";
        case TimeControl::Classic: return "Классика";
    }
    return "Неизвестно";
}

std::string Tournament::systemToString(TournamentSystem sys) {
    switch (sys) {
        case TournamentSystem::RoundRobin: return "Круговая";
        case TournamentSystem::Swiss:      return "Швейцарская";
    }
    return "Неизвестно";
}