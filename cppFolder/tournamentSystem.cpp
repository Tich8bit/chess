#include "tournamentSystem.h"
#include "exceptions/exception.h"

RoundRobinSystem::RoundRobinSystem(int circlesCount, bool alternateColors) : _circlesCount(circlesCount), _alternateColors(alternateColors) {}
std::string RoundRobinSystem::getName() const { return "Круговая"; }
int RoundRobinSystem::getTypeId() const { return 0; }
int RoundRobinSystem::calculateOptimalRounds(int maxPlayers) const { return (maxPlayers > 1 ? maxPlayers - 1 : 1) * _circlesCount; }
void RoundRobinSystem::validateRules(int maxPlayers) const { if (maxPlayers < 3) throw InvalidDataException("минимум 3 игрока"); }

SwissSystem::SwissSystem(int roundsCount, bool avoidRematches) : _roundsCount(roundsCount), _avoidRematches(avoidRematches) {}
std::string SwissSystem::getName() const { return "Швейцарская"; }
int SwissSystem::getTypeId() const { return 1; }
int SwissSystem::calculateOptimalRounds(int maxPlayers) const { return _roundsCount; }
void SwissSystem::validateRules(int maxPlayers) const { if (maxPlayers < 3) throw InvalidDataException("минимум 3 игрока"); }

KnockoutSystem::KnockoutSystem(bool hasThirdPlaceMatch) : _hasThirdPlaceMatch(hasThirdPlaceMatch) {}
std::string KnockoutSystem::getName() const { return "На выбывание"; }
int KnockoutSystem::getTypeId() const { return 2; }
int KnockoutSystem::calculateOptimalRounds(int maxPlayers) const { int r = 0, t = maxPlayers; while (t > 1) { t /= 2; r++; } return r; }
void KnockoutSystem::validateRules(int maxPlayers) const { if ((maxPlayers & (maxPlayers - 1)) != 0) throw InvalidDataException("нужно 2, 4, 8, 16..."); }

std::shared_ptr<TournamentSystem> TournamentSystem::createFromId(int id) {
    if (id == 0) return std::make_shared<RoundRobinSystem>();
    if (id == 1) return std::make_shared<SwissSystem>();
    if (id == 2) return std::make_shared<KnockoutSystem>();
    throw InvalidDataException("Неизвестная система");
}