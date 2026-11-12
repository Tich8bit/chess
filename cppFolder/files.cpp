#include "files.h"
#include "player.h"
#include "coach.h"
#include "specialization.h"
#include "tournament.h"
#include "tournamentSystem.h"
#include "trainingSession.h"
#include "matchResult.h"
#include "exceptions/exception.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <array>
#include <algorithm>

void StorageManager::saveState(const std::string& filename, const ChessClub& club) {
    std::ofstream ofs(filename);
    if (!ofs.is_open()) throw InvalidOperationException("не удалось открыть файл для сохранения");
    savePlayers(ofs, club);
    saveEvents(ofs, club);
    saveMatches(ofs, club);
}

void StorageManager::savePlayers(std::ofstream& ofs, const ChessClub& club) {
    const auto& players = club.getPlayers();
    ofs << players.size() << "\n";
    for (const auto& p : players) {
        auto firstName  = std::string(p->getFirstName());
        auto lastName   = std::string(p->getLastName());
        auto middleName = std::string(p->getMiddleName());

        if (auto coach = std::dynamic_pointer_cast<Coach>(p)) {
            int specInt = static_cast<int>(coach->getSpecialization().getType());
            ofs << PREFIX_COACH << " " << coach->getId() << " " << std::quoted(lastName) << " "
                << std::quoted(firstName) << " " << std::quoted(middleName) << " "
                << p->getRatings().getClassical() << " " << p->getRatings().getRapid() << " "
                << p->getRatings().getBlitz() << " " << p->getWins() << " " << p->getDraws() << " "
                << p->getLosses() << " " << coach->getExperienceYears() << " "
                << specInt << " " << coach->getQualificationLevel() << "\n";
        } else {
            ofs << PREFIX_PLAYER << " " << p->getId() << " " << std::quoted(lastName) << " "
                << std::quoted(firstName) << " " << std::quoted(middleName) << " "
                << p->getRatings().getClassical() << " " << p->getRatings().getRapid() << " "
                << p->getRatings().getBlitz() << " " << p->getWins() << " " << p->getDraws() << " "
                << p->getLosses() << "\n";
        }
    }
}

void StorageManager::saveEvents(std::ofstream& ofs, const ChessClub& club) {
    const auto& events = club.getEvents();
    ofs << events.size() << "\n";
    for (const auto& e : events) {
        if (auto t = std::dynamic_pointer_cast<Tournament>(e)) {
            auto title = std::string(t->getTitle());
            ofs << PREFIX_TOURNAMENT << " " << t->getId() << " " << std::quoted(title) << " "
                << static_cast<int>(t->getTimeControl()) << " " << t->getSystem()->getTypeId() << " "
                << t->getMaxPlayers() << "\n";
        } else if (auto ts = std::dynamic_pointer_cast<TrainingSession>(e)) {
            auto title = std::string(ts->getTitle());
            auto topic = std::string(ts->getTopic());
            int coachId = -1;
            if (auto coach = ts->getCoach()) coachId = coach->getId();
            ofs << PREFIX_TRAINING << " " << ts->getId() << " " << std::quoted(title) << " "
                << std::quoted(topic) << " " << ts->getDurationMinutes() << " " << coachId << "\n";
        }
    }
}

void StorageManager::saveMatches(std::ofstream& ofs, const ChessClub& club) {
    const auto& matches = club.getMatches();
    ofs << matches.size() << "\n";
    for (const auto& m : matches) {
        ofs << PREFIX_MATCH << " " << m->getId() << " " << m->getWhitePlayer()->getId() << " "
            << m->getBlackPlayer()->getId() << " " << std::quoted(m->getDate().toString()) << " "
            << static_cast<int>(m->getResult().getResult()) << "\n";
    }
}

void StorageManager::loadState(const std::string& filename, ChessClub& club) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) throw InvalidOperationException("не удалось открыть файл для загрузки");

    int playersCount = 0;
    ifs >> playersCount;
    for (int i = 0; i < playersCount; ++i) {
        std::string prefix; ifs >> prefix;
        if (prefix == PREFIX_PLAYER) loadPlayer(ifs, club);
        else if (prefix == PREFIX_COACH) loadCoach(ifs, club);
        else throw InvalidDataException("неверный префикс участника: " + prefix);
    }

    int eventsCount = 0;
    ifs >> eventsCount;
    for (int i = 0; i < eventsCount; ++i) {
        std::string prefix; ifs >> prefix;
        if (prefix == PREFIX_TOURNAMENT) loadTournament(ifs, club);
        else if (prefix == PREFIX_TRAINING) loadTraining(ifs, club);
        else throw InvalidDataException("неверный префикс события: " + prefix);
    }

    int matchesCount = 0;
    ifs >> matchesCount;
    for (int i = 0; i < matchesCount; ++i) loadMatch(ifs, club);
}

void StorageManager::loadPlayer(std::ifstream& ifs, ChessClub& club) {
    int id, classical, rapid, blitz, wins, draws, losses;
    std::string lastName, firstName, middleName;
    if (!(ifs >> id >> std::quoted(lastName) >> std::quoted(firstName) >> std::quoted(middleName)
              >> classical >> rapid >> blitz >> wins >> draws >> losses)) {
        throw InvalidDataException("ошибка чтения данных игрока");
    }
    club.addPlayer(std::make_shared<Player>(id, firstName, lastName, middleName,
        Ratings(classical, rapid, blitz), wins, draws, losses));
}

void StorageManager::loadCoach(std::ifstream& ifs, ChessClub& club) {
    int id, classical, rapid, blitz, wins, draws, losses, experienceYears, specInt, qualificationLevel;
    std::string lastName, firstName, middleName;
    if (!(ifs >> id >> std::quoted(lastName) >> std::quoted(firstName) >> std::quoted(middleName)
              >> classical >> rapid >> blitz >> wins >> draws >> losses
              >> experienceYears >> specInt >> qualificationLevel)) {
        throw InvalidDataException("ошибка чтения данных тренера");
    }
    club.addPlayer(std::make_shared<Coach>(id, firstName, lastName, middleName,
        Ratings(classical, rapid, blitz), wins, draws, losses,
        experienceYears, Specialization(static_cast<Specialization::Type>(specInt)), qualificationLevel));
}

void StorageManager::loadTournament(std::ifstream& ifs, ChessClub& club) {
    int id, tc, sysId, maxPlayers;
    std::string title;
    if (!(ifs >> id >> std::quoted(title) >> tc >> sysId >> maxPlayers)) {
        throw InvalidDataException("ошибка чтения турнира");
    }
    auto system = TournamentSystem::createFromId(sysId);
    club.addEvent(std::make_shared<Tournament>(id, title,
        static_cast<Tournament::TimeControl>(tc), system, maxPlayers));
}

void StorageManager::loadTraining(std::ifstream& ifs, ChessClub& club) {
    int id, durationMinutes, coachId;
    std::string title, topic;
    if (!(ifs >> id >> std::quoted(title) >> std::quoted(topic) >> durationMinutes >> coachId)) {
        throw InvalidDataException("ошибка чтения тренировки");
    }
    std::shared_ptr<Coach> coach = nullptr;
    if (coachId != -1) {
        auto found = club.findPlayerById(coachId);
        if (!found) throw RelationException("тренер не найден");
        coach = std::dynamic_pointer_cast<Coach>(found);
        if (!coach) throw RelationException("участник не является тренером");
    }
    club.addEvent(std::make_shared<TrainingSession>(id, title, topic, durationMinutes, coach));
}

void StorageManager::loadMatch(std::ifstream& ifs, ChessClub& club) {
    std::string prefix, dateStr;
    int id, whiteId, blackId, resultInt;
    
    if (!(ifs >> prefix >> id >> whiteId >> blackId >> std::quoted(dateStr) >> resultInt)) {
        throw InvalidDataException("ошибка чтения партии");
    }
    if (prefix != PREFIX_MATCH) throw InvalidDataException("неверный префикс партии");

    int d, m, y, h = 0, min = 0, s = 0;
    char dot1, dot2;
    std::stringstream ss(dateStr);
    DateTime date;
    if (ss >> d >> dot1 >> m >> dot2 >> y) {
        if (ss >> h) {
            char colon1, colon2;
            ss >> colon1 >> min >> colon2 >> s;
        }
        date = DateTime(d, m, y, h, min, s);
    } else {
        throw InvalidDataException("неверный формат даты в файле: " + dateStr);
    }

    auto white = club.findPlayerById(whiteId);
    auto black = club.findPlayerById(blackId);
    if (!white || !black) throw RelationException("игрок не найден");
    
    auto match = std::make_shared<Match>(id, white, black, date);
    match->setResult(static_cast<MatchResult::Result>(resultInt));
    club.addMatch(match);
}

void StorageManager::generateReport(const std::string& reportFilename, const ChessClub& club) {
    std::ofstream ofs(reportFilename);
    if (!ofs.is_open()) throw InvalidOperationException("не удалось открыть файл для отчёта");
    ofs << "ОТЧЁТ О СОСТОЯНИИ ШАХМАТНОГО КЛУБА\n==================================\n\n";
    reportPlayers(ofs, club.getPlayers());
    reportEvents(ofs, club.getEvents());
    reportMatches(ofs, club.getMatches());
}

void StorageManager::reportPlayers(std::ofstream& ofs, const Collection<Player>& players) {
    ofs << "УЧАСТНИКИ (" << players.size() << "):\n";
    for (const auto& p : players) {
        ofs << "  - [" << p->getRole() << "] " << p->getFullName() << " | ID: " << p->getId() << "\n";
    }
    ofs << "\n";
}

void StorageManager::reportEvents(std::ofstream& ofs, const Collection<Event>& events) {
    ofs << "СОБЫТИЯ (" << events.size() << "):\n";
    for (const auto& e : events) {
        ofs << "  - [" << e->getType() << "] " << e->getTitle() << " | ID: " << e->getId() << "\n";
    }
    ofs << "\n";
}

void StorageManager::reportMatches(std::ofstream& ofs, const Collection<Match>& matches) {
    ofs << "ПАРТИИ (" << matches.size() << "):\n";
    for (const auto& m : matches) {
        ofs << "  - " << m->getWhitePlayer()->getFullName() << " vs " << m->getBlackPlayer()->getFullName() << " | Дата: " << m->getDate() << "\n";
    }
    ofs << "\n";
}

void StorageManager::logAction(const std::string& logFilename, const std::string& action) {
    std::ofstream ofs(logFilename, std::ios::app);
    if (!ofs.is_open()) throw InvalidOperationException("не удалось открыть лог-файл");
    std::time_t now = std::time(nullptr);
    std::tm timeInfo;
    localtime_s(&timeInfo, &now);
    std::array<char, 100> buf{};
    std::strftime(buf.data(), buf.size(), "%Y-%m-%d %H:%M:%S", &timeInfo);
    ofs << "[" << buf.data() << "] " << action << "\n";
}