#include <iostream>
#include <memory>
#include <locale>
#include <Windows.h>

#include "basefunction.h"
#include "constants.h"
#include "ratings.h"
#include "player.h"
#include "coach.h"
#include "tournament.h"
#include "trainingSession.h"
#include "match.h"
#include "chessClub.h"
#include "collection.h"
#include "algs.h"
#include "analytics.h"
#include "files.h"
#include "exceptions/exception.h"

using namespace std;

void printMenu() {
    cout << "_________________________________________\n";
    cout << "|          ШАХМАТНЫЙ КЛУБ               |\n";
    cout << "|_______________________________________|\n";
    cout << "|1.  Показать участников                |\n";
    cout << "|2.  Показать события                   |\n";
    cout << "|3.  Показать партии                    |\n";
    cout << "|4.  Добавить игрока                    |\n";
    cout << "|5.  Добавить тренера                   |\n";
    cout << "|6.  Добавить турнир                    |\n";
    cout << "|7.  Добавить тренировку                |\n";
    cout << "|8.  Создать партию                     |\n";
    cout << "|_______________________________________|\n";
    cout << "|9.  Сохранить в файл                   |\n";
    cout << "|10. Загрузить из файла                 |\n";
    cout << "|11. Сформировать отчёт                 |\n";
    cout << "|_______________________________________|\n";
    cout << "|12. Поиск игрока по имени              |\n";
    cout << "|13. Группировка по роли                |\n";
    cout << "|14. Топ-N по метрике                   |\n";
    cout << "|15. Уникальные события                 |\n";
    cout << "|16. Кол-во с рейтингом > N             |\n";
    cout << "|17. Min/Max по метрике                 |\n";
    cout << "|18. Сумма рейтингов                    |\n";
    cout << "|19. Сортировка по 2 критериям          |\n";
    cout << "|_______________________________________|\n";
    cout << "|0. Выход                               |\n";
    cout << "|_______________________________________|\n";
}

void createTestClub(ChessClub& club) {
    auto p1 = make_shared<Player>("Иван", "Иванов", "Иванович",
        Ratings(1200, 1250, 1300), 5, 2, 3);
    auto p2 = make_shared<Player>("Пётр", "Петров", "Петрович",
        Ratings(1800, 1750, 1700), 10, 4, 6);
    auto c1 = make_shared<Coach>("Тимофей", "Тренеров", "Тимофеевич",
        Ratings(2000, 1950, 1900), 15, 5, 10, 25, "Дебюты", 4);

    club += p1;
    club += p2;
    club += c1;

    auto t1 = make_shared<Tournament>("Чемпионат клуба", 9,
        Tournament::TimeControl::Classic,
        Tournament::TournamentSystem::RoundRobin, 12);
    *t1 += p1;
    *t1 += p2;
    club += t1;

    auto training = make_shared<TrainingSession>("Дебютная подготовка",
        "Испанская партия", 90, c1);
    *training += p1;
    club += training;

    club.createMatch(p1, p2, "01.11.2026");

    cout << "Тестовая система создана:\n";
    cout << "  Игроков: " << club.getPlayerCount() << '\n';
    cout << "  Событий: " << club.getEventCount() << '\n';
    cout << "  Партий: " << club.getMatchCount() << '\n';
}

void demoAddPlayer(ChessClub& club) {
    string firstName  = inputString("Имя: ");
    string lastName   = inputString("Фамилия: ");
    string middleName = inputString("Отчество: ");
    int classical = inputNumber<int>("Рейтинг классика: ", 0, 3000);
    int rapid     = inputNumber<int>("Рейтинг рапид: ", 0, 3000);
    int blitz     = inputNumber<int>("Рейтинг блиц: ", 0, 3000);
    int wins      = inputNumber<int>("Победы: ", 0, 10000);
    int draws     = inputNumber<int>("Ничьи: ", 0, 10000);
    int losses    = inputNumber<int>("Поражения: ", 0, 10000);

    auto player = make_shared<Player>(firstName, lastName, middleName,
        Ratings(classical, rapid, blitz), wins, draws, losses);
    club += player;
    cout << "Успешно добавлен игрок: " << player->getFullName() << "\n";
}

void demoAddCoach(ChessClub& club) {
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
    string spec   = inputString("Специализация: ");
    int qual      = inputNumber<int>("Квалификация (1-5): ", 1, 5);

    auto coach = make_shared<Coach>(firstName, lastName, middleName,
        Ratings(classical, rapid, blitz), wins, draws, losses,
        exp, spec, qual);
    club += coach;
    cout << "Успешно добавлен тренер: " << coach->getFullName() << "\n";
}

void demoAddTournament(ChessClub& club) {
    string title = inputString("Название турнира: ");
    int rounds = inputNumber<int>("Туров: ", 1, 30);
    int tc = inputNumber<int>("Контроль (0-Блиц,1-Рапид,2-Классика): ", 0, 2);
    int sys = inputNumber<int>("Система (0-Круговая,1-Швейцарская): ", 0, 1);
    int maxP = inputNumber<int>("Макс. участников: ", 2, 200);

    auto tournament = make_shared<Tournament>(title, rounds,
        static_cast<Tournament::TimeControl>(tc),
        static_cast<Tournament::TournamentSystem>(sys), maxP);
    club += tournament;
    cout << "Успешно добавлен турнир: " << title << "\n";
}

void demoAddTraining(ChessClub& club) {
    string title  = inputString("Название тренировки: ");
    string topic  = inputString("Тема: ");
    int duration  = inputNumber<int>("Длительность (мин): ", 10, 300);
    int coachId   = inputNumber<int>("ID тренера (-1 если нет): ", -1, 100000);

    shared_ptr<Coach> coach = nullptr;
    if (coachId != -1) {
        auto found = club.findPlayerById(coachId);
        if (!found) {
            cout << "Тренер с ID " << coachId << " не найден.\n";
            return;
        }
        coach = dynamic_pointer_cast<Coach>(found);
        if (!coach) {
            cout << "Участник ID " << coachId << " не является тренером.\n";
            return;
        }
    }

    auto training = make_shared<TrainingSession>(title, topic, duration, coach);
    club += training;
    cout << "Успешно добавлена тренировка: " << title << "\n";
}

void demoCreateMatch(ChessClub& club) {
    club.printAllPlayers();

    int whiteId = inputNumber<int>("ID белого игрока: ", 1, 100000);
    int blackId = inputNumber<int>("ID чёрного игрока: ", 1, 100000);
    string date = inputString("Дата (дд.мм.гггг): ");

    auto white = club.findPlayerById(whiteId);
    auto black = club.findPlayerById(blackId);

    if (!white) {
        cout << "Игрок с ID " << whiteId << " не найден.\n";
        return;
    }
    if (!black) {
        cout << "Игрок с ID " << blackId << " не найден.\n";
        return;
    }

    club.createMatch(white, black, date);
    cout << "Успешно создана партия.\n";
}

void demoFindPlayerByName(const ChessClub& club) {
    string namePart = inputString("Часть имени для поиска: ");
    auto found = club.findPlayerByName(namePart);
    if (found) {
        cout << "Найден: " << *found << "\n";
    } else {
        cout << "Игрок не найден.\n";
    }
}

void demoGroupByRole(const ChessClub& club) {
    auto groups = ClubAnalytics::groupPlayersByRole(club);
    for (const auto& [role, list] : groups) {
        cout << role << ": " << list.size() << " чел.\n";
        for (const auto& p : list) {
            cout << "    - " << p->getFullName() << '\n';
        }
    }
}

void demoTopNByMetric(const ChessClub& club) {
    int n = inputNumber<int>("Сколько топ-игроков вывести: ", 1, 100);
    auto top = ClubAnalytics::findTopNByMetric(club, static_cast<size_t>(n));
    for (size_t i = 0; i < top.size(); ++i) {
        cout << "  " << (i + 1) << ". " << top[i]->getFullName()
             << " | Метрика: " << top[i]->calculateMetric()
             << " (" << top[i]->getMetricName() << ")\n";
    }
}

void demoUniqueEventTitles(const ChessClub& club) {
    auto titles = ClubAnalytics::getUniqueEventTitles(club);
    cout << "Уникальных названий событий: " << titles.size() << '\n';
    for (const auto& t : titles) {
        cout << "  - " << t << '\n';
    }
}

void demoCountPlayersWithRatingAbove(const ChessClub& club) {
    int minRating = inputNumber<int>("Минимальный рейтинг: ", 0, 3000);
    size_t count = ClubAnalytics::countPlayersWithRatingAbove(club, minRating);
    cout << "Участников с рейтингом > " << minRating << ": " << count << '\n';
}

void demoMinMaxMetric(const ChessClub& club) {
    auto [minP, maxP] = ClubAnalytics::findMinMaxMetric(club);
    if (minP) {
        cout << "Min: " << minP->getFullName()
             << " | Метрика: " << minP->calculateMetric() << '\n';
    }
    if (maxP) {
        cout << "Max: " << maxP->getFullName()
             << " | Метрика: " << maxP->calculateMetric() << '\n';
    }
}

void demoSumRatings(const ChessClub& club) {
    int total = ClubAnalytics::sumRatings(club);
    cout << "Суммарный максимальный рейтинг всех участников: " << total << '\n';
}

void demoSortByTwoCriteria(const ChessClub& club) {
    auto sorted = ClubAnalytics::sortByTwoCriteria(club);
    for (const auto& p : sorted) {
        cout << p->getFullName()
             << " | Рейтинг: " << p->getRatings().getMax()
             << " | Партий: " << p->getGamesPlayed() << '\n';
    }
}

void demoSaveState(const string& filename, const string& logFilename, const ChessClub& club) {
    StorageManager::saveState(filename, club);
    StorageManager::logAction(logFilename, "Сохранение в " + filename);
    cout << "Клуб сохранён в файл " << filename << "\n";
}

void demoLoadState(const string& filename, const string& logFilename, ChessClub& club) {
    StorageManager::loadState(filename, club);
    StorageManager::logAction(logFilename, "Загрузка из " + filename);
    cout << "Клуб загружен из файла " << filename << "\n";
}

void demoGenerateReport(const string& reportFilename, const string& logFilename, const ChessClub& club) {
    StorageManager::generateReport(reportFilename, club);
    StorageManager::logAction(logFilename, "Отчёт " + reportFilename);
    cout << "Отчёт сформирован в файле " << reportFilename << "\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");

    string filename       = "club.txt";
    string reportFilename = "report.txt";
    string logFilename    = "journal.log";

    ChessClub club("Шахматный клуб \"Гамбит\"");
    createTestClub(club);

    int choice = -1;

    do {
        printMenu();
        try {
            choice = inputNumber<int>("Выберите пункт меню: ", 0, 19);

            switch (choice) {
                case 1:  club.printAllPlayers(); break;
                case 2:  club.printAllEvents(); break;
                case 3:  club.printAllMatches(); break;
                case 4:  demoAddPlayer(club); break;
                case 5:  demoAddCoach(club); break;
                case 6:  demoAddTournament(club); break;
                case 7:  demoAddTraining(club); break;
                case 8:  demoCreateMatch(club); break;
                case 9:  demoSaveState(filename, logFilename, club); break;
                case 10: demoLoadState(filename, logFilename, club); break;
                case 11: demoGenerateReport(reportFilename, logFilename, club); break;
                case 12: demoFindPlayerByName(club); break;
                case 13: demoGroupByRole(club); break;
                case 14: demoTopNByMetric(club); break;
                case 15: demoUniqueEventTitles(club); break;
                case 16: demoCountPlayersWithRatingAbove(club); break;
                case 17: demoMinMaxMetric(club); break;
                case 18: demoSumRatings(club); break;
                case 19: demoSortByTwoCriteria(club); break;
                case 0:  cout << "Выход.\n"; break;
                default: cout << "Неверный пункт.\n"; break;
            }
        }
        catch (const ChessException& e) { cout << "ОШИБКА: " << e.what() << '\n'; }

    } while (choice != 0);

    return 0;
}