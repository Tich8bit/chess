#include "chessClub.h"
#include "exceptions/exception.h"

ChessClub::ChessClub(std::string_view name) : _clubName(name) {}
std::string_view ChessClub::getName() const { return _clubName; }
size_t ChessClub::getPlayerCount() const { return _players.size(); }
size_t ChessClub::getEventCount() const { return _events.size(); }
size_t ChessClub::getMatchCount() const { return _matches.size(); }
const Collection<Member>& ChessClub::getPlayers() const { return _players; }
const Collection<Event>& ChessClub::getEvents() const { return _events; }
const Collection<Match>& ChessClub::getMatches() const { return _matches; }

void ChessClub::addPlayer(std::shared_ptr<Member> player) { _players.add(player); }
void ChessClub::addEvent(std::shared_ptr<Event> event) { _events.add(event); }
void ChessClub::addMatch(std::shared_ptr<Match> match) { _matches.add(match); }

std::shared_ptr<Member> ChessClub::findPlayerById(int id) const {
    return _players.find([id](const std::shared_ptr<Member>& p) { return p->getId() == id; });
}

std::shared_ptr<Event> ChessClub::findEventById(int id) const {
    return _events.find([id](const std::shared_ptr<Event>& e) { return e->getId() == id; });
}

void ChessClub::createMatch(int id, std::shared_ptr<Player> white, std::shared_ptr<Player> black, const DateTime& date) {
    _matches.add(std::make_shared<Match>(id, white, black, date));
}

void ChessClub::printAllPlayers() const { std::cout << "\nУчастники:\n"; _players.print(); }
void ChessClub::printAllEvents() const { std::cout << "\nСобытия:\n"; _events.print(); }
void ChessClub::printAllMatches() const { std::cout << "\nМатчи:\n"; _matches.print(); }

ChessClub& ChessClub::operator+=(std::shared_ptr<Member> player) { addPlayer(player); return *this; }
ChessClub& ChessClub::operator+=(std::shared_ptr<Event> event) { addEvent(event); return *this; }
ChessClub& ChessClub::operator+=(std::shared_ptr<Match> match) { addMatch(match); return *this; }