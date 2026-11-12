#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <set>
#include <locale>
#include <algorithm>
#include <numeric>
#include <Windows.h>

#include "basefunction.h"
#include "constants.h"
#include "ratings.h"
#include "player.h"
#include "coach.h"
#include "specialization.h"
#include "tournament.h"
#include "tournamentSystem.h"
#include "trainingSession.h"
#include "matchResult.h"
#include "match.h"
#include "dateTime.h"
#include "chessClub.h"
#include "collection.h"
#include "algs.h"
#include "analytics.h"
#include "files.h"
#include "exceptions/exception.h"

using namespace std;

DateTime inputDateTime() {
    while (true) {
        std::string str = inputString("Введите дату (ДД.ММ.ГГГГ) и время (ЧЧ:ММ:СС через пробел): ");
        int d, m, y, h = 0, min = 0, s = 0;
        char dot1, dot2;
        std::stringstream ss(str);
        
        if (ss >> d >> dot1 >> m >> dot2 >> y && dot1 == '.' && dot2 == '.') {
            if (ss >> h) {
                char colon1, colon2;
                if (!(ss >> colon1 >> min >> colon2 >> s) || colon1 != ':' || colon2 != ':') {
                    cout << "Неверный формат времени. Используйте ЧЧ:ММ:СС\n";
                    continue;
                }
            }
            try {
                return DateTime(d, m, y, h, min, s);
            } catch (const ChessException& e) {
                cout << "Ошибка: " << e.what() << "\n";
            }
        } else {
            cout << "Неверный формат. Используйте ДД.ММ.ГГГГ\n";
        }
    }
}

int chooseStartMode() {
    cout << "_________________________________________\n";
    cout << "|         Выберите режим запуска        |\n";
    cout << "|_______________________________________|\n";
    cout << "|1. Создать тестовую систему            |\n";
    cout << "|2. Загрузить систему из файла          |\n";
    cout << "|0. Выход                               |\n";
    cout << "|_______________________________________|\n";
    int choice = -1;
    while (choice < 0 || choice > 2) {
        choice = inputNumber<int>("Ваш выбор: ", 0, 2);
        if (choice < 0 || choice > 2) cout << "Неверный пункт. Попробуйте снова.\n";
    }
    return choice;
}

void printMenu() {
    cout << "_________________________________________\n";
    cout << "|          Управление клубом            |\n";
    cout << "|_______________________________________|\n";
    cout << "|             ДОБАВЛЕНИЕ                |\n";
    cout << "|1.  Добавить игрока                    |\n";
    cout << "|2.  Добавить тренера                   |\n";
    cout << "|3.  Добавить турнир                    |\n";
    cout << "|4.  Добавить тренировку                |\n";
    cout << "|5.  Создать партию                     |\n";
    cout << "|_______________________________________|\n";
    cout << "|             СВЯЗЫВАНИЕ                |\n";
    cout << "|6.  Записать игрока на тренировку      |\n";
    cout << "|7.  Записать игрока в турнир           |\n";
    cout << "|8.  Ввести результат партии            |\n";
    cout << "|_______________________________________|\n";
    cout << "|          ПРОСМОТР И ОТКРЕПЛЕНИЕ       |\n";
    cout << "|9.  Показать участников                |\n";
    cout << "|10. Показать события                   |\n";
    cout << "|11. Показать партии                    |\n";
    cout << "|12. Таблица турнира                    |\n";
    cout << "|13. Открепить игрока от тренировки     |\n";
    cout << "|14. Открепить игрока от турнира        |\n";
    cout << "|15. Удалить участника (игрок/тренер)   |\n";
    cout << "|16. Удалить событие (турнир/тренировка)|\n";
    cout << "|17. Удалить партию                     |\n";
    cout << "|_______________________________________|\n";
    cout << "|             ФАЙЛЫ И STL               |\n";
    cout << "|18. Сохранить в файл                   |\n";
    cout << "|19. Сформировать отчёт                 |\n";
    cout << "|20. Аналитика (STL)                    |\n";
    cout << "|_______________________________________|\n";
    cout << "|0. Выход                               |\n";
    cout << "|_______________________________________|\n";
}

void printAnalyticsMenu() {
    cout << "_________________________________________\n";
    cout << "|          АНАЛИТИКА (STL)              |\n";
    cout << "|_______________________________________|\n";
    cout << "|1.  Поиск игрока по имени              |\n";
    cout << "|2.  Группировка по роли                |\n";
    cout << "|3.  Топ-N по метрике                   |\n";
    cout << "|4.  Уникальные события                 |\n";
    cout << "|5.  Кол-во с рейтингом > N             |\n";
    cout << "|6.  Min/Max по метрике                 |\n";
    cout << "|7.  Сумма рейтингов                    |\n";
    cout << "|8.  Сортировка по 2 критериям          |\n";
    cout << "|_______________________________________|\n";
    cout << "|0.  Назад в главное меню               |\n";
    cout << "|_______________________________________|\n";
}

void createTestSystem(ChessClub& club) {
    club = ChessClub("Шахматный клуб \"Гамбит\"");
    auto p1 = make_shared<Player>(1, "Иван", "Иванов", "Иванович", Ratings(1200, 1250, 1300), 5, 2, 3);
    auto p2 = make_shared<Player>(2, "Пётр", "Петров", "Петрович", Ratings(1800, 1750, 1700), 10, 4, 6);
    auto c1 = make_shared<Coach>(3, "Тимофей", "Тренеров", "Тимофеевич", Ratings(2000, 1950, 1900), 15, 5, 10, 25, Specialization(Specialization::Type::Openings), 4);
    
    club += p1; club += p2; club += c1;

    auto sys = make_shared<RoundRobinSystem>(1, true);
    auto t1 = make_shared<Tournament>(1, "Чемпионат клуба", Tournament::TimeControl::Classic, sys, 12);
    *t1 += p1; *t1 += p2;
    
    auto m1 = make_shared<Match>(1, p1, p2, DateTime(1, 11, 2026, 14, 30, 0));
    *t1 += m1;
    
    club += t1;
    club.addMatch(m1);

    auto training = make_shared<TrainingSession>(2, "Дебютная подготовка", "Испанская партия", 90, c1);
    *training += p1;
    club += training;

    cout << "Тестовая система создана.\n";
}

void printCurrentState(const ChessClub& club) {
    cout << "\n--- ТЕКУЩЕЕ СОСТОЯНИЕ ---\n";
    club.printAllPlayers();
    club.printAllEvents();
    club.printAllMatches();
    cout << "--------------------------------\n";
}

void demoAddPlayer(ChessClub& club) {
    cout << "=== Добавление игрока ===\n";
    int id = inputNumber<int>("ID игрока: ", 1, 100000);
    string firstName  = inputString("Имя: ");
    string lastName   = inputString("Фамилия: ");
    string middleName = inputString("Отчество: ");
    int classical = inputNumber<int>("Рейтинг классика: ", 0, 3000);
    int rapid     = inputNumber<int>("Рейтинг рапид: ", 0, 3000);
    int blitz     = inputNumber<int>("Рейтинг блиц: ", 0, 3000);
    int wins      = inputNumber<int>("Победы: ", 0, 10000);
    int draws     = inputNumber<int>("Ничьи: ", 0, 10000);
    int losses    = inputNumber<int>("Поражения: ", 0, 10000);
    club += make_shared<Player>(id, firstName, lastName, middleName, Ratings(classical, rapid, blitz), wins, draws, losses);
    cout << "Игрок добавлен.\n";
}

void demoAddCoach(ChessClub& club) {
    cout << "=== Добавление тренера ===\n";
    int id = inputNumber<int>("ID тренера: ", 1, 100000);
    string firstName  = inputString("Имя: ");
    string lastName   = inputString("Фамилия: ");
    string middleName = inputString("Отчество: ");
    int classical = inputNumber<int>("Рейтинг классика: ", 0, 3000);
    int rapid     = inputNumber<int>("Рейтинг рапид: ", 0, 3000);
    int blitz     = inputNumber<int>("Рейтинг блиц: ", 0, 3000);
    int wins      = inputNumber<int>("Победы: ", 0, 10000);
    int draws     = inputNumber<int>("Ничьи: ", 0, 10000);
    int losses    = inputNumber<int>("Поражения: ", 0, 10000);
    int exp       = inputNumber<int>("Стаж (лет): ", 0, 80);
    cout << "1. Дебюты\n2. Миттельшпиль\n3. Эндшпиль\n4. Тактика\n5. Общая подготовка\n";
    int specChoice = inputNumber<int>("Специализация: ", 1, 5);
    Specialization spec(Specialization::intToType(specChoice));
    int qual = inputNumber<int>("Квалификация (1-5): ", 1, 5);
    club += make_shared<Coach>(id, firstName, lastName, middleName, Ratings(classical, rapid, blitz), wins, draws, losses, exp, spec, qual);
    cout << "Тренер добавлен.\n";
}

void demoAddTournament(ChessClub& club) {
    cout << "=== Добавление турнира ===\n";
    int id = inputNumber<int>("ID турнира: ", 1, 100000);
    string title = inputString("Название турнира: ");
    int tc = inputNumber<int>("Контроль (0-Блиц,1-Рапид,2-Классика): ", 0, 2);
    
    cout << "Система (0-Круговая, 1-Швейцарская, 2-На выбывание): ";
    int sysChoice = inputNumber<int>("", 0, 2);
    int maxP = inputNumber<int>("Макс. участников: ", 2, 200);
    shared_ptr<TournamentSystem> system;

    if (sysChoice == 0) {
        int circles = inputNumber<int>("Количество кругов (1 или 2): ", 1, 2);
        int altColors = inputNumber<int>("Чередовать цвета? (1-да, 0-нет): ", 0, 1);
        system = make_shared<RoundRobinSystem>(circles, altColors == 1);
    } else if (sysChoice == 1) {
        int rounds = inputNumber<int>("Количество туров: ", 3, 30);
        int avoid = inputNumber<int>("Исключать повторные встречи? (1-да, 0-нет): ", 0, 1);
        system = make_shared<SwissSystem>(rounds, avoid == 1);
    } else {
        int thirdPlace = inputNumber<int>("Играть матч за 3-е место? (1-да, 0-нет): ", 0, 1);
        system = make_shared<KnockoutSystem>(thirdPlace == 1);
    }

    try {
        system->validateRules(maxP);
        auto tournament = make_shared<Tournament>(id, title, static_cast<Tournament::TimeControl>(tc), system, maxP);
        club += tournament;
        cout << "Турнир добавлен.\n";
    } catch (const ChessException& e) {
        cout << "Ошибка: " << e.what() << "\n";
    }
}

void demoAddTraining(ChessClub& club) {
    cout << "=== Добавление тренировки ===\n";
    int id = inputNumber<int>("ID тренировки: ", 1, 100000);
    string title  = inputString("Название тренировки: ");
    string topic  = inputString("Тема: ");
    int duration  = inputNumber<int>("Длительность (мин): ", 10, 300);
    int coachId   = inputNumber<int>("ID тренера (-1 если нет): ", -1, 100000);
    shared_ptr<Coach> coach = nullptr;
    if (coachId != -1) {
        auto found = club.findPlayerById(coachId);
        if (!found) { cout << "Тренер не найден.\n"; return; }
        coach = dynamic_pointer_cast<Coach>(found);
        if (!coach) { cout << "Участник не является тренером.\n"; return; }
    }
    club += make_shared<TrainingSession>(id, title, topic, duration, coach);
    cout << "Тренировка добавлена.\n";
}

void demoCreateMatch(ChessClub& club) {
    cout << "=== Создание партии ===\n";
    int isTournament = inputNumber<int>("Партия в турнире? (1-да, 0-нет): ", 0, 1);
    if (isTournament == 0) {
        club.printAllPlayers();
        int id = inputNumber<int>("ID партии: ", 1, 100000);
        int whiteId = inputNumber<int>("ID белого: ", 1, 100000);
        int blackId = inputNumber<int>("ID чёрного: ", 1, 100000);
        DateTime date = inputDateTime();
        auto white = club.findPlayerById(whiteId);
        auto black = club.findPlayerById(blackId);
        if (!white || !black) { cout << "Игрок не найден.\n"; return; }
        club.createMatch(id, white, black, date);
        cout << "Партия создана.\n";
    } else {
        for (const auto& e : club.getEvents()) {
            if (auto t = dynamic_pointer_cast<Tournament>(e)) t->printInfo(cout);
        }
        int tourId = inputNumber<int>("ID турнира: ", 1, 100000);
        auto tournament = dynamic_pointer_cast<Tournament>(club.findEventById(tourId));
        if (!tournament) { cout << "Турнир не найден.\n"; return; }
        cout << "Участники:\n";
        for (const auto& p : tournament->getParticipants()) cout << " [" << p->getId() << "] " << p->getFullName() << "\n";
        int id = inputNumber<int>("ID партии: ", 1, 100000);
        int whiteId = inputNumber<int>("ID белого: ", 1, 100000);
        int blackId = inputNumber<int>("ID чёрного: ", 1, 100000);
        DateTime date = inputDateTime();
        auto white = tournament->getParticipants().find([whiteId](const std::shared_ptr<Player>& p) { return p->getId() == whiteId; });
        auto black = tournament->getParticipants().find([blackId](const std::shared_ptr<Player>& p) { return p->getId() == blackId; });
        if (!white || !black) { cout << "Игрок не заявлен в турнире.\n"; return; }
        auto match = make_shared<Match>(id, white, black, date);
        try {
            *tournament += match;
            club.addMatch(match);
            cout << "Партия создана.\n";
        } catch (const ChessException& e) { cout << "Ошибка: " << e.what() << "\n"; }
    }
}

void demoEnrollPlayerToTraining(ChessClub& club) {
    cout << "=== Запись на тренировку ===\n";
    club.printAllEvents();
    int eventId = inputNumber<int>("ID тренировки: ", 1, 100000);
    auto training = dynamic_pointer_cast<TrainingSession>(club.findEventById(eventId));
    if (!training) { cout << "Не найдено.\n"; return; }
    club.printAllPlayers();
    int playerId = inputNumber<int>("ID игрока: ", 1, 100000);
    auto player = club.findPlayerById(playerId);
    if (!player) { cout << "Игрок не найден.\n"; return; }
    try {
        *training += player;
        cout << "Успешно записан.\n";
    } catch (const ChessException& e) { cout << "Ошибка: " << e.what() << "\n"; }
}

void demoEnrollPlayerToTournament(ChessClub& club) {
    cout << "=== Запись в турнир ===\n";
    for (const auto& e : club.getEvents()) {
        if (auto t = dynamic_pointer_cast<Tournament>(e)) t->printInfo(cout);
    }
    int tourId = inputNumber<int>("ID турнира: ", 1, 100000);
    auto tournament = dynamic_pointer_cast<Tournament>(club.findEventById(tourId));
    if (!tournament) { cout << "Не найдено.\n"; return; }
    club.printAllPlayers();
    int playerId = inputNumber<int>("ID игрока: ", 1, 100000);
    auto player = club.findPlayerById(playerId);
    if (!player) { cout << "Игрок не найден.\n"; return; }
    try {
        *tournament += player;
        cout << "Успешно заявлен.\n";
    } catch (const ChessException& e) { cout << "Ошибка: " << e.what() << "\n"; }
}

void demoEnterMatchResult(ChessClub& club) {
    cout << "=== Ввод результата партии ===\n";
    club.printAllMatches();
    int id = inputNumber<int>("ID партии: ", 1, 100000);
    auto match = club.getMatches().find([id](const std::shared_ptr<Match>& m) { return m->getId() == id; });
    if (!match) { cout << "Партия не найдена.\n"; return; }
    cout << "1. Победа белых\n2. Победа чёрных\n3. Ничья\n";
    int res = inputNumber<int>("Результат: ", 1, 3);
    MatchResult::Result result;
    if (res == 1) result = MatchResult::Result::WhiteWin;
    else if (res == 2) result = MatchResult::Result::BlackWin;
    else result = MatchResult::Result::Draw;
    match->setResult(result);
    cout << "Результат сохранен.\n";
}

void demoShowStandings(const ChessClub& club) {
    cout << "=== Таблица турнира ===\n";
    for (const auto& e : club.getEvents()) {
        if (auto t = dynamic_pointer_cast<Tournament>(e)) t->printInfo(cout);
    }
    int tourId = inputNumber<int>("ID турнира: ", 1, 100000);
    auto tournament = dynamic_pointer_cast<Tournament>(club.findEventById(tourId));
    if (!tournament) { cout << "Турнир не найден.\n"; return; }
    
    auto standings = tournament->getStandings(true);
    cout << "\nМесто | Игрок | Очки | В | Н | П\n";
    cout << "--------------------------------\n";
    for (size_t i = 0; i < standings.size(); ++i) {
        const auto& s = standings[i];
        cout << i+1 << ". " << s.player->getFullName() << " | " 
             << s.points << " | " << s.wins << " | " << s.draws << " | " << s.losses << "\n";
    }
}

void demoUnenrollFromTraining(ChessClub& club) {
    cout << "=== Открепление от тренировки ===\n";
    club.printAllEvents();
    int eventId = inputNumber<int>("ID тренировки: ", 1, 100000);
    auto training = dynamic_pointer_cast<TrainingSession>(club.findEventById(eventId));
    if (!training) { cout << "Не найдено.\n"; return; }
    
    for (const auto& p : training->getParticipants()) {
        cout << " [" << p->getId() << "] " << p->getFullName() << "\n";
    }
    int playerId = inputNumber<int>("ID игрока: ", 1, 100000);
    auto player = club.findPlayerById(playerId);
    if (!player) { cout << "Игрок не найден.\n"; return; }
    
    try {
        *training -= player;
        cout << "Игрок откреплен от тренировки.\n";
    } catch (const ChessException& e) { cout << "Ошибка: " << e.what() << "\n"; }
}

void demoUnenrollFromTournament(ChessClub& club) {
    cout << "=== Открепление от турнира ===\n";
    for (const auto& e : club.getEvents()) {
        if (auto t = dynamic_pointer_cast<Tournament>(e)) t->printInfo(cout);
    }
    int tourId = inputNumber<int>("ID турнира: ", 1, 100000);
    auto tournament = dynamic_pointer_cast<Tournament>(club.findEventById(tourId));
    if (!tournament) { cout << "Не найдено.\n"; return; }
    
    for (const auto& p : tournament->getParticipants()) {
        cout << " [" << p->getId() << "] " << p->getFullName() << "\n";
    }
    int playerId = inputNumber<int>("ID игрока: ", 1, 100000);
    auto player = club.findPlayerById(playerId);
    if (!player) { cout << "Игрок не найден.\n"; return; }
    
    try {
        *tournament -= player;
        cout << "Игрок откреплен от турнира.\n";
    } catch (const ChessException& e) { cout << "Ошибка: " << e.what() << "\n"; }
}

void demoDeletePlayer(ChessClub& club) {
    cout << "=== Удаление участника ===\n";
    club.printAllPlayers();
    int id = inputNumber<int>("ID участника: ", 1, 100000);
    auto player = club.findPlayerById(id);
    if (!player) { cout << "Не найден.\n"; return; }
    try {
        club.removePlayer(player);
        cout << "Участник удален.\n";
    } catch (const ChessException& e) { cout << "Ошибка: " << e.what() << "\n"; }
}

void demoDeleteEvent(ChessClub& club) {
    cout << "=== Удаление события ===\n";
    club.printAllEvents();
    int id = inputNumber<int>("ID события: ", 1, 100000);
    auto event = club.findEventById(id);
    if (!event) { cout << "Не найдено.\n"; return; }
    try {
        club.removeEvent(event);
        cout << "Событие удалено.\n";
    } catch (const ChessException& e) { cout << "Ошибка: " << e.what() << "\n"; }
}

void demoDeleteMatch(ChessClub& club) {
    cout << "=== Удаление партии ===\n";
    club.printAllMatches();
    int id = inputNumber<int>("ID партии: ", 1, 100000);
    auto match = club.getMatches().find([id](const std::shared_ptr<Match>& m) { return m->getId() == id; });
    if (!match) { cout << "Не найдена.\n"; return; }
    try {
        club.removeMatch(match);
        cout << "Партия удалена.\n";
    } catch (const ChessException& e) { cout << "Ошибка: " << e.what() << "\n"; }
}

void demoSaveState(const string& filename, const string& logFilename, const ChessClub& club) {
    StorageManager::saveState(filename, club);
    StorageManager::logAction(logFilename, "Сохранение");
    cout << "Сохранено в " << filename << "\n";
}

void demoGenerateReport(const string& reportFilename, const string& logFilename, const ChessClub& club) {
    StorageManager::generateReport(reportFilename, club);
    StorageManager::logAction(logFilename, "Отчёт");
    cout << "Отчёт сформирован в " << reportFilename << "\n";
}

void runAnalyticsMenu(const ChessClub& club) {
    int choice = -1;
    do {
        printAnalyticsMenu();
        try {
            choice = inputNumber<int>("Выберите пункт: ", 0, 8);
            switch (choice) {
                case 1: {
                    string namePart = inputString("Часть имени: ");
                    auto found = club.findPlayerByName(namePart);
                    if (found) cout << "Найден: " << *found << "\n";
                    else cout << "Не найден.\n";
                    break;
                }
                case 2: {
                    auto groups = ClubAnalytics::groupPlayersByRole(club);
                    for (const auto& [role, list] : groups) {
                        cout << role << ": " << list.size() << " чел.\n";
                        for (const auto& p : list) cout << "    - " << p->getFullName() << '\n';
                    }
                    break;
                }
                case 3: {
                    int n = inputNumber<int>("Топ-N: ", 1, 100);
                    auto top = ClubAnalytics::findTopNByMetric(club, static_cast<size_t>(n));
                    for (size_t i = 0; i < top.size(); ++i) {
                        cout << "  " << (i + 1) << ". " << top[i]->getFullName() << " | Метрика: " << top[i]->calculateMetric() << "\n";
                    }
                    break;
                }
                case 4: {
                    auto titles = ClubAnalytics::getUniqueEventTitles(club);
                    cout << "Событий: " << titles.size() << '\n';
                    for (const auto& t : titles) cout << "  - " << t << '\n';
                    break;
                }
                case 5: {
                    int minRating = inputNumber<int>("Мин. рейтинг: ", 0, 3000);
                    size_t count = ClubAnalytics::countPlayersWithRatingAbove(club, minRating);
                    cout << "Найдено: " << count << '\n';
                    break;
                }
                case 6: {
                    auto [minP, maxP] = ClubAnalytics::findMinMaxMetric(club);
                    if (minP) cout << "Min: " << minP->getFullName() << "\n";
                    if (maxP) cout << "Max: " << maxP->getFullName() << "\n";
                    break;
                }
                case 7: {
                    int total = ClubAnalytics::sumRatings(club);
                    cout << "Сумма: " << total << '\n';
                    break;
                }
                case 8: {
                    auto sorted = ClubAnalytics::sortByTwoCriteria(club);
                    for (const auto& p : sorted) {
                        cout << p->getFullName() << " | Рейтинг: " << p->getRatings().getMax() << " | Партий: " << p->getGamesPlayed() << '\n';
                    }
                    break;
                }
                case 0: break;
                default: cout << "Неверный пункт.\n"; break;
            }
        } catch (const ChessException& e) {
            cout << "ОШИБКА: " << e.what() << '\n';
        }
    } while (choice != 0);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");

    string filename       = "club.txt";
    string reportFilename = "report.txt";
    string logFilename    = "journal.log";

    ChessClub club("Шахматный клуб \"Гамбит\"");

    int startMode = chooseStartMode();
    if (startMode == 0) return 0;

    if (startMode == 1) {
        try { createTestSystem(club); } 
        catch (const ChessException& e) { cout << "ОШИБКА: " << e.what() << '\n'; }
    } else {
        try {
            StorageManager::loadState(filename, club);
            cout << "Загружено из " << filename << "\n";
        } catch (const ChessException& e) {
            cout << "ОШИБКА загрузки: " << e.what() << "\nСоздана тестовая.\n";
            try { createTestSystem(club); } 
            catch (const ChessException& ex) { cout << "ОШИБКА: " << ex.what() << '\n'; }
        }
    }

    int choice = -1;
    do {
        printMenu();
        try {
            choice = inputNumber<int>("Выберите пункт: ", 0, 20);
            switch (choice) {
                case 1:  demoAddPlayer(club); break;
                case 2:  demoAddCoach(club); break;
                case 3:  demoAddTournament(club); break;
                case 4:  demoAddTraining(club); break;
                case 5:  demoCreateMatch(club); break;
                case 6:  demoEnrollPlayerToTraining(club); break;
                case 7:  demoEnrollPlayerToTournament(club); break;
                case 8:  demoEnterMatchResult(club); break;
                case 9:  printCurrentState(club); break;
                case 10: club.printAllEvents(); break;
                case 11: club.printAllMatches(); break;
                case 12: demoShowStandings(club); break;
                case 13: demoUnenrollFromTraining(club); break;
                case 14: demoUnenrollFromTournament(club); break;
                case 15: demoDeletePlayer(club); break;
                case 16: demoDeleteEvent(club); break;
                case 17: demoDeleteMatch(club); break;
                case 18: demoSaveState(filename, logFilename, club); break;
                case 19: demoGenerateReport(reportFilename, logFilename, club); break;
                case 20: runAnalyticsMenu(club); break;
                case 0:  cout << "Выход.\n"; break;
                default: cout << "Неверный пункт.\n"; break;
            }
        } catch (const ChessException& e) { cout << "ОШИБКА: " << e.what() << '\n'; }
    } while (choice != 0);

    return 0;
}