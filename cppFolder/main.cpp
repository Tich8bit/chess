#include <iostream>
#include <memory>
#include <locale>
#include <Windows.h>
#include <sstream>

#include "basefunction.h"
#include "ratings.h"
#include "player.h"
#include "coach.h"
#include "specialization.h"
#include "tournament.h"
#include "trainingSession.h"
#include "match.h"
#include "chessClub.h"
#include "files.h"
#include "analytics.h"
#include "exceptions/exception.h"

using namespace std;

DateTime inputDateTime() {
    while (true) {
        string str = inputString("Дата (ДД.ММ.ГГГГ ЧЧ:ММ:СС): ");
        int d, m, y, h = 0, min = 0, s = 0;
        char dot1, dot2;
        stringstream ss(str);
        if (ss >> d >> dot1 >> m >> dot2 >> y && dot1 == '.' && dot2 == '.') {
            if (ss >> h) {
                char c1, c2;
                if (!(ss >> c1 >> min >> c2 >> s) || c1 != ':' || c2 != ':') { cout << "Ошибка времени\n"; continue; }
            }
            try { return DateTime(d, m, y, h, min, s); }
            catch (const ChessException& e) { cout << e.what() << "\n"; }
        } else cout << "Ошибка формата\n";
    }
}

void createTestSystem(ChessClub& club) {
    club = ChessClub("Гамбит");
    auto p1 = make_shared<Player>(1, "Иван", "Иванов", "Иванович", Ratings(1200, 1250, 1300), 5, 2, 3);
    auto p2 = make_shared<Player>(2, "Пётр", "Петров", "Петрович", Ratings(1800, 1750, 1700), 10, 4, 6);
    auto c1 = make_shared<Coach>(3, "Тимофей", "Тренеров", "Тимофеевич", Ratings(2000, 1950, 1900), 15, 5, 10, 25, Specialization(Specialization::Type::Openings), 4);
    club += p1; club += p2; club += c1;
    
    auto sys = make_shared<RoundRobinSystem>(1, true);
    auto t1 = make_shared<Tournament>(1, "Чемпионат", Tournament::TimeControl::Classic, sys, 12);
    *t1 += p1; *t1 += p2;
    club += t1;
    
    auto m1 = make_shared<Match>(1, p1, p2, DateTime(1, 11, 2026, 14, 30, 0));
    *t1 += m1; club.addMatch(m1);
    
    club += make_shared<TrainingSession>(2, "Дебюты", "Испанская", 90, c1);
    cout << "Тестовая система создана.\n";
}

void demoAddPlayer(ChessClub& club) {
    int id = inputNumber<int>("ID: ", 1, 99999);
    string fn = inputString("Имя: "), ln = inputString("Фамилия: "), mn = inputString("Отчество: ");
    int cl = inputNumber<int>("Классика: ", 0, 3000), rp = inputNumber<int>("Рапид: ", 0, 3000), bl = inputNumber<int>("Блиц: ", 0, 3000);
    int w = inputNumber<int>("Победы: ", 0, 10000), d = inputNumber<int>("Ничьи: ", 0, 10000), l = inputNumber<int>("Поражения: ", 0, 10000);
    club += make_shared<Player>(id, fn, ln, mn, Ratings(cl, rp, bl), w, d, l);
    cout << "Игрок добавлен.\n";
}

void demoAddCoach(ChessClub& club) {
    int id = inputNumber<int>("ID: ", 1, 99999);
    string fn = inputString("Имя: "), ln = inputString("Фамилия: "), mn = inputString("Отчество: ");
    int cl = inputNumber<int>("Классика: ", 0, 3000), rp = inputNumber<int>("Рапид: ", 0, 3000), bl = inputNumber<int>("Блиц: ", 0, 3000);
    int w = inputNumber<int>("Победы: ", 0, 10000), d = inputNumber<int>("Ничьи: ", 0, 10000), l = inputNumber<int>("Поражения: ", 0, 10000);
    int exp = inputNumber<int>("Стаж: ", 0, 80);
    cout << "1.Дебюты 2.Миттельшпиль 3.Эндшпиль 4.Тактика 5.Общая\n";
    int sc = inputNumber<int>("Спец: ", 1, 5);
    int q = inputNumber<int>("Квалификация: ", 1, 5);
    club += make_shared<Coach>(id, fn, ln, mn, Ratings(cl, rp, bl), w, d, l, exp, Specialization(Specialization::intToType(sc)), q);
    cout << "Тренер добавлен.\n";
}

void demoAddTournament(ChessClub& club) {
    int id = inputNumber<int>("ID турнира: ", 1, 99999);
    string title = inputString("Название: ");
    int tc = inputNumber<int>("Контроль (0-Блиц,1-Рапид,2-Классика): ", 0, 2);
    cout << "Система (0-Круговая, 1-Швейцарская, 2-Плей-офф): ";
    int sc = inputNumber<int>("", 0, 2);
    int maxP = inputNumber<int>("Макс. игроков: ", 2, 200);
    shared_ptr<TournamentSystem> sys;
    if (sc == 0) sys = make_shared<RoundRobinSystem>(1, true);
    else if (sc == 1) sys = make_shared<SwissSystem>(5, true);
    else sys = make_shared<KnockoutSystem>(false);
    try {
        club += make_shared<Tournament>(id, title, static_cast<Tournament::TimeControl>(tc), sys, maxP);
        cout << "Турнир добавлен.\n";
    } catch (const ChessException& e) { cout << e.what() << "\n"; }
}

void demoAddTraining(ChessClub& club) {
    int id = inputNumber<int>("ID тренировки: ", 1, 99999);
    string title = inputString("Название: "), topic = inputString("Тема: ");
    int dur = inputNumber<int>("Длительность: ", 10, 300);
    int cid = inputNumber<int>("ID тренера: ", 1, 99999);
    auto c = dynamic_pointer_cast<Coach>(club.findPlayerById(cid));
    if (c) { club += make_shared<TrainingSession>(id, title, topic, dur, c); cout << "Добавлено.\n"; }
    else cout << "Тренер не найден.\n";
}

void demoCreateMatch(ChessClub& club) {
    int id = inputNumber<int>("ID партии: ", 1, 99999);
    int wId = inputNumber<int>("ID белого: ", 1, 99999);
    int bId = inputNumber<int>("ID чёрного: ", 1, 99999);
    auto w = dynamic_pointer_cast<Player>(club.findPlayerById(wId));
    auto b = dynamic_pointer_cast<Player>(club.findPlayerById(bId));
    if (!w || !b) { cout << "Игроки не найдены.\n"; return; }
    club.createMatch(id, w, b, inputDateTime());
    cout << "Матч создан.\n";
}

void demoShowStandings(const ChessClub& club) {
    int tid = inputNumber<int>("ID турнира: ", 1, 99999);
    auto t = dynamic_pointer_cast<Tournament>(club.findEventById(tid));
    if (!t) { cout << "Нет турнира.\n"; return; }
    auto st = t->getStandings(true);
    for (size_t i = 0; i < st.size(); ++i) cout << i+1 << ". " << st[i].player->getFullName() << " | Очки: " << st[i].points << "\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");

    ChessClub club("Гамбит");
    int mode = inputNumber<int>("1-Тест, 2-Загрузка, 0-Выход: ", 0, 2);
    if (mode == 0) return 0;
    if (mode == 1) createTestSystem(club);
    else { try { StorageManager::loadState("club.txt", club); } catch (...) { createTestSystem(club); } }

    while (true) {
        cout << "\n1.Игрок 2.Тренер 3.Турнир 4.Тренировка 5.Матч 6.Таблица 7.Сохранить 8.Показать 0.Выход\n";
        int c = inputNumber<int>("Действие: ", 0, 8);
        if (c == 0) break;
        try {
            if (c == 1) demoAddPlayer(club);
            else if (c == 2) demoAddCoach(club);
            else if (c == 3) demoAddTournament(club);
            else if (c == 4) demoAddTraining(club);
            else if (c == 5) demoCreateMatch(club);
            else if (c == 6) demoShowStandings(club);
            else if (c == 7) { StorageManager::saveState("club.txt", club); cout << "Сохранено.\n"; }
            else if (c == 8) { club.printAllPlayers(); club.printAllEvents(); club.printAllMatches(); }
        } catch (const ChessException& e) { cout << "ОШИБКА: " << e.what() << "\n"; }
    }
    return 0;
}