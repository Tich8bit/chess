#include <iostream>
#include <locale>
#include <memory>
#include "constants.h"
#include "member.h"
#include "player.h"
#include "coach.h"
#include "match.h"
#include "event.h"
#include "tournament.h"
#include "trainingSession.h"
#include "masterClass.h"
#include "chessClub.h"
#include "collection.h"
#include "algs.h"
#include "input.h"

using namespace std;

void printMenu() {
    cout << "_________________________________________\n";
    cout << "|          Шахматный клуб               |\n";
    cout << "|_______________________________________|\n";
    cout << "|1.  Все участники                      |\n";
    cout << "|2.  Все партии                         |\n";
    cout << "|3.  Все события                        |\n";
    cout << "|4.  Метрики событий                    |\n";
    cout << "|5.  Добавить игрока                    |\n";
    cout << "|6.  Добавить тренера                   |\n";
    cout << "|7.  Создать партию                     |\n";
    cout << "|8.  Добавить турнир                    |\n";
    cout << "|9.  Добавить тренировку                |\n";
    cout << "|10. Добавить мастер-класс              |\n";
    cout << "|11. Суммарный рейтинг игроков          |\n";
    cout << "|12. Сортировка участников по метрике   |\n";
    cout << "|13. Состояние клуба                    |\n";
    cout << "|_______________________________________|\n";
    cout << "|0.  Выход                              |\n";
    cout << "|_______________________________________|\n";
}

ChessClub createTestClub() {
    ChessClub club("Гамбит");

    club += make_shared<Player>(1, "Иванов И.И.", 2005, 1200);
    club += make_shared<Player>(2, "Петров П.П.", 1980, 1800);
    club += make_shared<Player>(3, "Сидоров С.С.", 1955, 2100);
    club += make_shared<Coach>(4, "Тренеров Т.Т.", 1965, 25, 30, "Дебюты");

    club += make_shared<Tournament>(1, "Чемпионат клуба", 9,
                                    Tournament::TimeControl::Classic,
                                    Tournament::System::RoundRobin, 12);
    club += make_shared<TrainingSession>(2, "Дебютная подготовка",
                                          "Испанская партия",
                                          "Тренеров Т.Т.",
                                          TrainingSession::Level::Intermediate, 90);
    club += make_shared<MasterClass>(3, "Мастер-класс с гроссмейстером",
                                      "Карпов А.Е.",
                                      MasterClass::GuestTitle::GM, 40, 120);

    return club;
}

void demoAllMembers(const ChessClub& club) { club.printAllMembers(); }
void demoAllMatches(const ChessClub& club) { club.printAllMatches(); }
void demoAllEvents(const ChessClub& club) { club.printAllEvents(); }
void demoAllMetrics(const ChessClub& club) { club.printAllMetrics(); }

void demoAddPlayer(ChessClub& club) {
    int id = inputNumber<int>("ID игрока: ", 1, 100000);
    string name = inputString("Имя: ");
    int year = inputNumber<int>("Год рождения: ", 1900, CURRENT_YEAR);
    int rating = inputNumber<int>("Рейтинг: ", 0, 3000);
    club += make_shared<Player>(id, name, year, rating);
}

void demoAddCoach(ChessClub& club) {
    int id = inputNumber<int>("ID тренера: ", 1, 100000);
    string name = inputString("Имя: ");
    int year = inputNumber<int>("Год рождения: ", 1900, CURRENT_YEAR);
    int exp = inputNumber<int>("Стаж (лет): ", 0, 80);
    int students = inputNumber<int>("Учеников: ", 0, 1000);
    string spec = inputString("Специализация: ");
    club += make_shared<Coach>(id, name, year, exp, students, spec);
}

void demoCreateMatch(ChessClub& club) {
    club.printAllMembers();
    int id1 = inputNumber<int>("ID белого: ", 1, 100000);
    int id2 = inputNumber<int>("ID черного: ", 1, 100000);
    string date = inputString("Дата: ");
    club.createMatch(id1, id2, date);
}

void demoAddTournament(ChessClub& club) {
    int id = inputNumber<int>("ID турнира: ", 1, 100000);
    string title = inputString("Название: ");
    int rounds = inputNumber<int>("Туров: ", 1, 30);
    int tc = inputNumber<int>("Контроль (0-Блиц, 1-Рапид, 2-Классика): ", 0, 2);
    int sys = inputNumber<int>("Система (0-Круговая, 1-Швейцарская): ", 0, 1);
    int players = inputNumber<int>("Участников: ", 2, 200);
    club += make_shared<Tournament>(id, title, rounds,
                                    static_cast<Tournament::TimeControl>(tc),
                                    static_cast<Tournament::System>(sys),
                                    players);
}

void demoAddTraining(ChessClub& club) {
    int id = inputNumber<int>("ID тренировки: ", 1, 100000);
    string title = inputString("Название: ");
    string topic = inputString("Тема: ");
    string coach = inputString("Тренер: ");
    int level = inputNumber<int>("Уровень (0-Начин, 1-Средний, 2-Продв): ", 0, 2);
    int duration = inputNumber<int>("Длительность (мин): ", 1, 600);
    club += make_shared<TrainingSession>(id, title, topic, coach,
                                          static_cast<TrainingSession::Level>(level),
                                          duration);
}

void demoAddMasterClass(ChessClub& club) {
    int id = inputNumber<int>("ID мастер-класса: ", 1, 100000);
    string title = inputString("Название: ");
    string guest = inputString("Гость: ");
    int gt = inputNumber<int>("Титул (0-GM, 1-IM, 2-FM): ", 0, 2);
    int audience = inputNumber<int>("Слушателей: ", 1, 1000);
    int duration = inputNumber<int>("Длительность (мин): ", 1, 600);
    club += make_shared<MasterClass>(id, title, guest,
                                      static_cast<MasterClass::GuestTitle>(gt),
                                      audience, duration);
}

void demoTotalRating(const ChessClub& club) {
    cout << "Суммарный рейтинг игроков: " << getTotalClubRating(club) << "\n";
}

void demoSortMembers(ChessClub& club) {
    auto copy = club.getMembers();
    sortBy(copy, [](const shared_ptr<Member>& a, const shared_ptr<Member>& b) {
        return a->calculateMetric() > b->calculateMetric();
    });
    for (int i = 0; i < copy.size(); ++i) {
        if (auto m = copy.get(i)) m->printMemberInformation();
    }
}

void demoClubState(const ChessClub& club) { cout << club << "\n"; }

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    ChessClub club = createTestClub();
    int choice = -1;

    do {
        printMenu();
        choice = inputNumber<int>("Выберите пункт: ", 0, 13);

        switch (choice) {
            case 1:  demoAllMembers(club); break;
            case 2:  demoAllMatches(club); break;
            case 3:  demoAllEvents(club); break;
            case 4:  demoAllMetrics(club); break;
            case 5:  demoAddPlayer(club); break;
            case 6:  demoAddCoach(club); break;
            case 7:  demoCreateMatch(club); break;
            case 8:  demoAddTournament(club); break;
            case 9:  demoAddTraining(club); break;
            case 10: demoAddMasterClass(club); break;
            case 11: demoTotalRating(club); break;
            case 12: demoSortMembers(club); break;
            case 13: demoClubState(club); break;
            case 0:  cout << "Выход.\n"; break;
            default: cout << "Неверный пункт.\n"; break;
        }
    } while (choice != 0);

    return 0;
}