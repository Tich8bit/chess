#include "chessClub.h"

ChessClub::ChessClub(std::string_view name) : _clubName(name) {}

std::string_view ChessClub::getName() const { return _clubName; }
int ChessClub::getMemberCount() const { return _members.size(); }
int ChessClub::getMatchCount() const { return _matches.size(); }
int ChessClub::getEventCount() const { return _events.size(); }

void ChessClub::addMember(const std::shared_ptr<Member>& member) {
    if (!member) {
        std::cerr << "[Ошибка] Пустой указатель на участника.\n";
        return;
    }
    for (int i = 0; i < _members.size(); ++i) {
        if (auto existing = _members.getShared(i)) {
            if (*existing == *member) {
                std::cerr << "[Ошибка] Участник с ID " << member->getId()
                          << " уже существует.\n";
                return;
            }
        }
    }
    _members.add(member);
}

bool ChessClub::removeMemberAt(int index) {
    return _members.removeAt(index);
}

std::shared_ptr<Member> ChessClub::findMemberById(int searchId) const {
    return _members.findShared([searchId](const Member& m) {
        return m.getId() == searchId;
    });
}

std::shared_ptr<Player> ChessClub::findPlayerById(int searchId) const {
    return std::dynamic_pointer_cast<Player>(findMemberById(searchId));
}

void ChessClub::createMatch(int id1, int id2, std::string_view date) {
    auto p1 = findPlayerById(id1);
    auto p2 = findPlayerById(id2);

    if (!p1) { std::cerr << "[Ошибка] Игрок с ID " << id1 << " не найден.\n"; return; }
    if (!p2) { std::cerr << "[Ошибка] Игрок с ID " << id2 << " не найден.\n"; return; }

    _matches.add(Match(p1, p2, date));
}

void ChessClub::addEvent(const std::shared_ptr<Event>& event) {
    if (!event) {
        std::cerr << "[Ошибка] Пустой указатель на событие.\n";
        return;
    }
    for (int i = 0; i < _events.size(); ++i) {
        if (auto e = _events.get(i)) {
            if (*e == *event) {
                std::cerr << "[Ошибка] Событие с ID " << event->getId()
                          << " уже существует.\n";
                return;
            }
        }
    }
    _events.add(event);
}

bool ChessClub::removeEventAt(int index) {
    return _events.removeAt(index);
}

std::shared_ptr<Event> ChessClub::findEventById(int searchId) const {
    return _events.findShared([searchId](const Event& e) {
        return e.getId() == searchId;
    });
}

void ChessClub::printAllMembers() const {
    std::cout << "\n=== Участники клуба \"" << _clubName << "\" ===\n";
    if (_members.isEmpty()) { std::cout << "Список пуст.\n"; return; }
    for (int i = 0; i < _members.size(); ++i) {
        if (auto m = _members.get(i)) m->printMemberInformation();
    }
}

void ChessClub::printAllMatches() const {
    std::cout << "\n=== История партий ===\n";
    if (_matches.isEmpty()) { std::cout << "Партий не сыграно.\n"; return; }
    _matches.print(std::cout);
}

void ChessClub::printAllEvents() const {
    std::cout << "\n=== События клуба ===\n";
    if (_events.isEmpty()) { std::cout << "Событий нет.\n"; return; }
    for (int i = 0; i < _events.size(); ++i) {
        if (auto e = _events.get(i)) e->printEventInformation();
    }
}

void ChessClub::printAllMetrics() const {
    std::cout << "\n=== Метрики событий ===\n";
    for (int i = 0; i < _events.size(); ++i) {
        if (auto e = _events.get(i)) {
            std::cout << e->getType() << " \"" << e->getTitle() << "\" -> "
                      << e->getMetricName() << ": " << e->calculateMetric() << "\n";
        }
    }
}

ChessClub& ChessClub::operator+=(const std::shared_ptr<Member>& member) {
    addMember(member);
    return *this;
}

ChessClub& ChessClub::operator-=(const std::shared_ptr<Member>& member) {
    if (!member) return *this;
    for (int i = 0; i < _members.size(); ++i) {
        if (auto cur = _members.getShared(i)) {
            if (cur->getId() == member->getId()) {
                _members.removeAt(i);
                return *this;
            }
        }
    }
    return *this;
}

ChessClub& ChessClub::operator+=(const std::shared_ptr<Event>& event) {
    addEvent(event);
    return *this;
}

ChessClub& ChessClub::operator-=(const std::shared_ptr<Event>& event) {
    if (!event) return *this;
    for (int i = 0; i < _events.size(); ++i) {
        if (auto cur = _events.get(i)) {
            if (cur->getId() == event->getId()) {
                _events.removeAt(i);
                return *this;
            }
        }
    }
    return *this;
}