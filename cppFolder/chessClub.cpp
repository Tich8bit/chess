#include "chessClub.h"
#include <limits>

ChessClub::ChessClub(std::string_view name) : _clubName(name) {}

std::string_view ChessClub::getName() const { return _clubName; }
int ChessClub::getPlayerCount() const { return static_cast<int>(_players.size()); }
int ChessClub::getMatchCount() const { return static_cast<int>(_matches.size()); }

void ChessClub::addPlayer(const Player& player) {
    for (const auto& existing : _players) {
        if (existing.equals(player)) {
            std::cerr << "[Ошибка] Игрок с ID " << player.getId()
                      << " уже существует.\n";
            return;
        }
    }
    _players.push_back(player);
}

void ChessClub::removePlayer(int playerId) {
    for (auto it = _players.begin(); it != _players.end(); ++it) {
        if (it->getId() == playerId) {
            _players.erase(it);
            return;
        }
    }
    std::cerr << "[Ошибка] Игрок с ID " << playerId << " не найден.\n";
}

Player* ChessClub::findPlayerById(int searchId) {
    for (auto& p : _players) {
        if (p.getId() == searchId) {
            return &p;
        }
    }
    return nullptr;
}

const Player* ChessClub::findPlayerById(int searchId) const {
    for (const auto& p : _players) {
        if (p.getId() == searchId) {
            return &p;
        }
    }
    return nullptr;
}

void ChessClub::createMatch(int id1, int id2, std::string_view date) {
    Player* p1 = findPlayerById(id1);
    Player* p2 = findPlayerById(id2);

    if (p1 == nullptr) {
        std::cerr << "[Ошибка] Игрок с ID " << id1 << " не найден.\n";
        return;
    }
    if (p2 == nullptr) {
        std::cerr << "[Ошибка] Игрок с ID " << id2 << " не найден.\n";
        return;
    }

    _matches.emplace_back(*p1, *p2, date);
}

void ChessClub::showAllPlayers(std::ostream& os) const {
    os << "\n=== Список игроков клуба \"" << _clubName << "\" ===\n";
    if (_players.empty()) {
        os << "Список пуст.\n";
        return;
    }
    for (const auto& p : _players) {
        p.printInfo(os);
        os << "\n";
    }
}

void ChessClub::showAllMatches(std::ostream& os) const {
    os << "\n=== История партий ===\n";
    if (_matches.empty()) {
        os << "Партий не сыграно.\n";
        return;
    }
    for (const auto& m : _matches) {
        m.printInfo(os);
        os << "\n";
    }
}

void ChessClub::inputPlayerAndAdd() {
    Player p("Placeholder", 2000, 1000, "Новичок");
    p.inputPlayer();
    addPlayer(p);
}

void ChessClub::inputMatchAndAdd() {
    int id1, id2;
    std::string date;

    std::cout << "Введите ID белого игрока: ";
    std::cin >> id1;
    std::cout << "Введите ID черного игрока: ";
    std::cin >> id2;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите дату партии: ";
    std::getline(std::cin, date);

    createMatch(id1, id2, date);
}