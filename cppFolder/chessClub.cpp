#include "chessClub.h"
#include "exceptions/exception.h"

ChessClub::ChessClub(std::string_view name)
    : _clubName(name),
      _nextPlayerId(1),
      _nextEventId(1),
      _nextMatchId(1) {
    if (name.empty()) {
        throw InvalidDataException("название клуба не может быть пустым");
    }
}

std::string_view ChessClub::getName() const { return _clubName; }
size_t ChessClub::getPlayerCount() const { return _players.size(); }
size_t ChessClub::getEventCount() const { return _events.size(); }
size_t ChessClub::getMatchCount() const { return _matches.size(); }

const Collection<Player>& ChessClub::getPlayers() const { return _players; }
const Collection<Event>& ChessClub::getEvents() const { return _events; }
const Collection<Match>& ChessClub::getMatches() const { return _matches; }

void ChessClub::addPlayer(std::shared_ptr<Player> player) {
    if (!player) {
        throw InvalidDataException("пустой указатель на игрока");
    }
    player->setId(_nextPlayerId++);
    _players.add(player);
}

void ChessClub::addPlayerWithId(std::shared_ptr<Player> player, int id) {
    if (!player) {
        throw InvalidDataException("пустой указатель на игрока");
    }
    player->setId(id);
    _players.add(player);
    if (id >= _nextPlayerId) {
        _nextPlayerId = id + 1;
    }
}

bool ChessClub::removePlayer(std::shared_ptr<Player> player) {
    if (!player) {
        throw InvalidDataException("пустой указатель на игрока");
    }
    if (size_t removed = _players.removeIf([&player](const std::shared_ptr<Player>& p) {
        return p == player;
    }); removed == 0) {
        throw ObjectNotFoundException("игрок " + player->getFullName() + " не найден");
    }
    return true;
}

void ChessClub::addEvent(std::shared_ptr<Event> event) {
    if (!event) {
        throw InvalidDataException("пустой указатель на событие");
    }
    event->setId(_nextEventId++);
    _events.add(event);
}

void ChessClub::addEventWithId(std::shared_ptr<Event> event, int id) {
    if (!event) {
        throw InvalidDataException("пустой указатель на событие");
    }
    event->setId(id);
    _events.add(event);
    if (id >= _nextEventId) {
        _nextEventId = id + 1;
    }
}

bool ChessClub::removeEvent(std::shared_ptr<Event> event) {
    if (!event) {
        throw InvalidDataException("пустой указатель на событие");
    }
    if (size_t removed = _events.removeIf([&event](const std::shared_ptr<Event>& e) {
        return e == event;
    }); removed == 0) {
        throw ObjectNotFoundException("событие \"" + std::string(event->getTitle()) + "\" не найдено");
    }
    return true;
}

void ChessClub::addMatch(std::shared_ptr<Match> match) {
    if (!match) {
        throw InvalidDataException("пустой указатель на партию");
    }
    match->setId(_nextMatchId++);
    _matches.add(match);
}

void ChessClub::addMatchWithId(std::shared_ptr<Match> match, int id) {
    if (!match) {
        throw InvalidDataException("пустой указатель на партию");
    }
    match->setId(id);
    _matches.add(match);
    if (id >= _nextMatchId) {
        _nextMatchId = id + 1;
    }
}

bool ChessClub::removeMatch(std::shared_ptr<Match> match) {
    if (!match) {
        throw InvalidDataException("пустой указатель на партию");
    }
    if (size_t removed = _matches.removeIf([&match](const std::shared_ptr<Match>& m) {
        return m == match;
    }); removed == 0) {
        throw ObjectNotFoundException("партия не найдена");
    }
    return true;
}

std::shared_ptr<Player> ChessClub::findPlayerById(int id) const {
    return _players.find([id](const std::shared_ptr<Player>& p) {
        return p->getId() == id;
    });
}

std::shared_ptr<Player> ChessClub::findPlayerByName(std::string_view namePart) const {
    return _players.find([namePart](const std::shared_ptr<Player>& p) {
        return p->getFullName().find(namePart) != std::string::npos;
    });
}

std::shared_ptr<Event> ChessClub::findEventById(int id) const {
    return _events.find([id](const std::shared_ptr<Event>& e) {
        return e->getId() == id;
    });
}

void ChessClub::createMatch(std::shared_ptr<Player> white,
                            std::shared_ptr<Player> black,
                            std::string_view date) {
    auto match = std::make_shared<Match>(white, black, date);
    addMatch(match);
}

void ChessClub::printAllPlayers() const {
    std::cout << "\n=== Участники клуба \"" << _clubName << "\" ===\n";
    _players.print();
}

void ChessClub::printAllEvents() const {
    std::cout << "\n=== События клуба ===\n";
    _events.print();
}

void ChessClub::printAllMatches() const {
    std::cout << "\n=== История партий ===\n";
    _matches.print();
}

ChessClub& ChessClub::operator+=(std::shared_ptr<Player> player) {
    addPlayer(player);
    return *this;
}

ChessClub& ChessClub::operator+=(std::shared_ptr<Event> event) {
    addEvent(event);
    return *this;
}

ChessClub& ChessClub::operator+=(std::shared_ptr<Match> match) {
    addMatch(match);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const ChessClub& club) {
    os << "Клуб: " << club._clubName
       << " | Игроков: " << club._players.size()
       << " | Событий: " << club._events.size()
       << " | Партий: " << club._matches.size();
    return os;
}