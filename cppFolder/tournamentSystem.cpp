#include "tournamentSystem.h"
#include "exceptions/exception.h"

RoundRobinSystem::RoundRobinSystem(int circlesCount, bool alternateColors)
    : _circlesCount(circlesCount), _alternateColors(alternateColors) {
    if (_circlesCount < 1) throw InvalidDataException("количество кругов должно быть больше 0");
}

std::string RoundRobinSystem::getName() const { return "Круговая"; }
int RoundRobinSystem::getTypeId() const { return 0; }

int RoundRobinSystem::calculateOptimalRounds(int maxPlayers) const {
    return (maxPlayers > 1 ? (maxPlayers - 1) : 1) * _circlesCount;
}

void RoundRobinSystem::validateRules(int maxPlayers) const {
    if (maxPlayers < 3) throw InvalidDataException("для круговой системы нужно минимум 3 игрока");
}

int RoundRobinSystem::getCirclesCount() const { return _circlesCount; }
void RoundRobinSystem::setCirclesCount(int newCirclesCount) {
    if (newCirclesCount < 1) throw InvalidDataException("количество кругов должно быть больше 0");
    _circlesCount = newCirclesCount;
}
bool RoundRobinSystem::getAlternateColors() const { return _alternateColors; }
void RoundRobinSystem::setAlternateColors(bool value) { _alternateColors = value; }

SwissSystem::SwissSystem(int roundsCount, bool avoidRematches)
    : _roundsCount(roundsCount), _avoidRematches(avoidRematches) {
    if (_roundsCount < 3) throw InvalidDataException("для швейцарской системы нужно хотя бы 3 тура");
}

std::string SwissSystem::getName() const { return "Швейцарская"; }
int SwissSystem::getTypeId() const { return 1; }

int SwissSystem::calculateOptimalRounds(int maxPlayers) const { return _roundsCount; }

void SwissSystem::validateRules(int maxPlayers) const {
    if (maxPlayers < 3) throw InvalidDataException("для швейцарской системы нужно минимум 3 игрока");
    if (_roundsCount > maxPlayers - 1) throw InvalidDataException("слишком много туров для швейцарской системы");
}

int SwissSystem::getRoundsCount() const { return _roundsCount; }
void SwissSystem::setRoundsCount(int newRoundsCount) {
    if (newRoundsCount < 3) throw InvalidDataException("нужно хотя бы 3 тура");
    _roundsCount = newRoundsCount;
}
bool SwissSystem::getAvoidRematches() const { return _avoidRematches; }
void SwissSystem::setAvoidRematches(bool value) { _avoidRematches = value; }

KnockoutSystem::KnockoutSystem(bool hasThirdPlaceMatch) : _hasThirdPlaceMatch(hasThirdPlaceMatch) {}

std::string KnockoutSystem::getName() const { return "На выбывание"; }
int KnockoutSystem::getTypeId() const { return 2; }

int KnockoutSystem::calculateOptimalRounds(int maxPlayers) const {
    int rounds = 0, temp = maxPlayers;
    while (temp > 1) { temp /= 2; rounds++; }
    return rounds;
}

void KnockoutSystem::validateRules(int maxPlayers) const {
    if ((maxPlayers & (maxPlayers - 1)) != 0) {
        throw InvalidDataException("число участников должно быть кратно степени двойки (2, 4, 8, 16, 32...)");
    }
}

bool KnockoutSystem::getHasThirdPlaceMatch() const { return _hasThirdPlaceMatch; }
void KnockoutSystem::setHasThirdPlaceMatch(bool value) { _hasThirdPlaceMatch = value; }

std::shared_ptr<TournamentSystem> TournamentSystem::createFromId(int id) {
    if (id == 0) return std::make_shared<RoundRobinSystem>();
    if (id == 1) return std::make_shared<SwissSystem>();
    if (id == 2) return std::make_shared<KnockoutSystem>();
    throw InvalidDataException("Неизвестный ID системы турнира");
}