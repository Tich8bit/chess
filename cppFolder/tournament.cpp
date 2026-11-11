#include "tournament.h"
#include "exceptions/exception.h"
#include <algorithm>
#include <map>

Tournament::Tournament(int id, std::string_view title, TimeControl timeControl,
                       std::shared_ptr<TournamentSystem> system, int maxPlayers)
    : Event(id, title), _timeControl(timeControl), _system(system), _maxPlayers(maxPlayers) {
    
    if (maxPlayers < 2 || maxPlayers > 200) throw LimitExceededException("количество участников должно быть от 2 до 200");
    if (!_system) throw InvalidDataException("система турнира не задана");

    _system->validateRules(_maxPlayers);
}

Tournament::TimeControl Tournament::getTimeControl() const { return _timeControl; }
std::shared_ptr<TournamentSystem> Tournament::getSystem() const { return _system; }
int Tournament::getMaxPlayers() const { return _maxPlayers; }
const Collection<Player>& Tournament::getParticipants() const { return _participants; }
const Collection<Match>& Tournament::getMatches() const { return _matches; }

void Tournament::setTimeControl(TimeControl newTimeControl) { _timeControl = newTimeControl; }

void Tournament::setSystem(std::shared_ptr<TournamentSystem> newSystem) {
    if (!newSystem) throw InvalidDataException("система не задана");
    newSystem->validateRules(_maxPlayers);
    _system = newSystem;
}

void Tournament::setMaxPlayers(int newMaxPlayers) {
    if (newMaxPlayers < 2 || newMaxPlayers > 200) throw LimitExceededException("количество участников от 2 до 200");
    _system->validateRules(newMaxPlayers);
    _maxPlayers = newMaxPlayers;
}

std::string Tournament::getType() const { return "Турнир"; }

double Tournament::calculateMetric() const {
    double coef = 1.0;
    if (_timeControl == TimeControl::Rapid) coef = 1.5;
    else if (_timeControl == TimeControl::Classic) coef = 2.0;
    return _system->calculateOptimalRounds(_maxPlayers) * coef;
}

std::string Tournament::getMetricName() const { return "Игровая нагрузка"; }

void Tournament::printInfo(std::ostream& os) const {
    Event::printInfo(os);
    os << "\n  Контроль: " << timeControlToString(_timeControl)
       << "\n  Система: " << _system->getName()
       << "\n  Участников: " << _participants.size() << "/" << _maxPlayers
       << "\n  Матчей: " << _matches.size();
}

Tournament& Tournament::operator+=(std::shared_ptr<Player> player) {
    if (!player) throw InvalidDataException("пустой указатель на игрока");
    if (_participants.size() >= static_cast<size_t>(_maxPlayers)) throw LimitExceededException("турнир заполнен");
    if (_participants.find([&player](const std::shared_ptr<Player>& p) { return p == player; })) {
        throw DuplicateIdException("игрок уже участвует в турнире");
    }
    _participants.add(player);
    return *this;
}

Tournament& Tournament::operator-=(std::shared_ptr<Player> player) {
    if (!player) throw InvalidDataException("пустой указатель на игрока");
    if (size_t removed = _participants.removeIf([&player](const std::shared_ptr<Player>& p) { return p == player; }); removed == 0) {
        throw ObjectNotFoundException("игрок не участвует в турнире");
    }
    return *this;
}

Tournament& Tournament::operator+=(std::shared_ptr<Match> match) {
    if (!match) throw InvalidDataException("пустой указатель на матч");
    if (!_participants.find([&match](const std::shared_ptr<Player>& p) { return p == match->getWhitePlayer(); })) {
        throw RelationException("белый игрок не заявлен в турнире");
    }
    if (!_participants.find([&match](const std::shared_ptr<Player>& p) { return p == match->getBlackPlayer(); })) {
        throw RelationException("чёрный игрок не заявлен в турнире");
    }
    _matches.add(match);
    return *this;
}

std::vector<Standing> Tournament::getStandings(bool useHeadToHead) const {
    std::map<std::shared_ptr<Player>, Standing> table;
    
    for (const auto& p : _participants) {
        table[p] = {p, 0, 0, 0, 0.0};
    }

    for (const auto& m : _matches) {
        auto result = m->getResult();
        if (!result.isPlayed()) continue;

        auto white = m->getWhitePlayer();
        auto black = m->getBlackPlayer();

        double wScore = result.getWhiteScore();
        double bScore = result.getBlackScore();

        table[white].points += wScore;
        table[black].points += bScore;

        if (result.getResult() == MatchResult::Result::WhiteWin) {
            table[white].wins++; table[black].losses++;
        } else if (result.getResult() == MatchResult::Result::BlackWin) {
            table[black].wins++; table[white].losses++;
        } else if (result.getResult() == MatchResult::Result::Draw) {
            table[white].draws++; table[black].draws++;
        }
    }

    std::vector<Standing> standings;
    for (const auto& [p, s] : table) standings.push_back(s);

    std::sort(standings.begin(), standings.end(), [this, useHeadToHead](const Standing& a, const Standing& b) {
        if (a.points != b.points) return a.points > b.points;
        
        if (useHeadToHead) {
            auto m = _matches.find([&a, &b](const std::shared_ptr<Match>& match) {
                return (match->getWhitePlayer() == a.player && match->getBlackPlayer() == b.player) ||
                       (match->getWhitePlayer() == b.player && match->getBlackPlayer() == a.player);
            });
            if (m) {
                auto res = m->getResult();
                if (res.isPlayed()) {
                    if (m->getWhitePlayer() == a.player) return res.getWhiteScore() > res.getBlackScore();
                    else return res.getBlackScore() > res.getWhiteScore();
                }
            }
        }
        return a.player->getRatings().getMax() > b.player->getRatings().getMax();
    });

    return standings;
}

std::string Tournament::timeControlToString(TimeControl tc) {
    switch (tc) {
        case TimeControl::Blitz:   return "Блиц";
        case TimeControl::Rapid:   return "Рапид";
        case TimeControl::Classic: return "Классика";
    }
    return "Неизвестно";
}