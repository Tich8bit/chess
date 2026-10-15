#include <iostream>
#include "chessClub.h"

int main() {
    setlocale(LC_ALL, "Russian");

    ChessClub club("Гамбит");

    Player p1("Иванов И.И.", 2005, 1200, "Юниор");
    Player p2("Петров П.П.", 1980, 1800, "Взрослый");
    Player p3("Сидоров С.С.", 1955, 2100, "Ветеран");
    Player p4("Кузнецов К.К.", 2010, 900, "Ребенок");

    club.addPlayer(p1);
    club.addPlayer(p2);
    club.addPlayer(p3);
    club.addPlayer(p4);

    club.showAllPlayers(std::cout);

    club.createMatch(1, 2, "12.10.2026");
    club.createMatch(3, 4, "12.10.2026");
    club.createMatch(1, 1, "13.10.2026");

    club.showAllMatches(std::cout);

    std::cout << "\n=== Демонстрация ограничений ===\n";
    p2.setRating(-500);
    p2.setRating(5000);
    p2.setRating(1850);
    std::cout << "Новый рейтинг Петрова: " << p2.getRating() << "\n";

    std::cout << "\nИгроков в клубе: " << club.getPlayerCount() << "\n";
    std::cout << "Партий в истории: " << club.getMatchCount() << "\n";

    club.removePlayer(999);

    return 0;
}