#include "storageManager.h"
#include "exceptions/exception.h"
#include "player.h"
#include "coach.h"
#include "tournament.h"
#include "trainingSession.h"
#include "masterClass.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <array>
#include <algorithm>

void StorageManager::saveState(const std::string& filename, const ChessClub& club) {
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        throw InvalidOperationException("Не удалось открыть файл для сохранения: " + filename);
    }

    saveMembers(ofs, club);
    saveEvents(ofs, club);
    saveMatches(ofs, club);
}

void StorageManager::saveMembers(std::ofstream& ofs, const ChessClub& club) {
    ofs << club.getMembers().size() << "\n";
    savePlayers(ofs, club);
    saveCoaches(ofs, club);
}

void StorageManager::savePlayers(std::ofstream& ofs, const ChessClub& club) {
    const auto& members = club.getMembers();
    for (int i = 0; i < members.size(); ++i) {
        auto m = members.getShared(i);
        if (auto p = std::dynamic_pointer_cast<Player>(m)) {
            std::string name = std::string(p->getFullName()); // Конвертация string_view в string
            ofs << PREFIX_PLAYER << " " << p->getId() << " " 
                << std::quoted(name) << " " << p->getBirthYear() << " " 
                << p->getRating() << "\n";
        }
    }
}

void StorageManager::saveCoaches(std::ofstream& ofs, const ChessClub& club) {
    const auto& members = club.getMembers();
    for (int i = 0; i < members.size(); ++i) {
        auto m = members.getShared(i);
        if (auto c = std::dynamic_pointer_cast<Coach>(m)) {
            std::string name = std::string(c->getFullName());
            std::string spec = std::string(c->getSpecialization());
            ofs << PREFIX_COACH << " " << c->getId() << " " 
                << std::quoted(name) << " " << c->getBirthYear() << " "
                << c->getExperienceYears() << " " << c->getStudentsCount() << " " 
                << std::quoted(spec) << "\n";
        }
    }
}

void StorageManager::saveEvents(std::ofstream& ofs, const ChessClub& club) {
    ofs << club.getEvents().size() << "\n";
    saveTournaments(ofs, club);
    saveTrainings(ofs, club);
    saveMasterClasses(ofs, club);
}

void StorageManager::saveTournaments(std::ofstream& ofs, const ChessClub& club) {
    const auto& events = club.getEvents();
    for (int i = 0; i < events.size(); ++i) {
        auto e = events.getShared(i);
        if (auto t = std::dynamic_pointer_cast<Tournament>(e)) {
            std::string title = std::string(t->getTitle());
            ofs << PREFIX_EVENT_TOUR << " " << t->getId() << " " 
                << std::quoted(title) << " " << t->getRoundsCount() << " "
                << static_cast<int>(t->getTimeControl()) << " " 
                << static_cast<int>(t->getSystem()) << " " 
                << t->getPlayerCount() << "\n";
        }
    }
}

void StorageManager::saveTrainings(std::ofstream& ofs, const ChessClub& club) {
    const auto& events = club.getEvents();
    for (int i = 0; i < events.size(); ++i) {
        auto e = events.getShared(i);
        if (auto ts = std::dynamic_pointer_cast<TrainingSession>(e)) {
            std::string title = std::string(ts->getTitle());
            std::string topic = std::string(ts->getTopic());
            std::string coach = std::string(ts->getCoachName());
            ofs << PREFIX_EVENT_TRAIN << " " << ts->getId() << " " 
                << std::quoted(title) << " " << std::quoted(topic) << " " 
                << std::quoted(coach) << " " << static_cast<int>(ts->getLevel()) << " " 
                << ts->getDurationMinutes() << "\n";
        }
    }
}

void StorageManager::saveMasterClasses(std::ofstream& ofs, const ChessClub& club) {
    const auto& events = club.getEvents();
    for (int i = 0; i < events.size(); ++i) {
        auto e = events.getShared(i);
        if (auto mc = std::dynamic_pointer_cast<MasterClass>(e)) {
            std::string title = std::string(mc->getTitle());
            std::string guest = std::string(mc->getGuestName());
            ofs << PREFIX_EVENT_MASTER << " " << mc->getId() << " " 
                << std::quoted(title) << " " << std::quoted(guest) << " " 
                << static_cast<int>(mc->getGuestTitle()) << " " 
                << mc->getAudienceCount() << " " << mc->getDurationMinutes() << "\n";
        }
    }
}

void StorageManager::saveMatches(std::ofstream& ofs, const ChessClub& club) {
    const auto& matches = club.getMatches();
    ofs << matches.size() << "\n";

    for (int i = 0; i < matches.size(); ++i) {
        auto m = matches.get(i);
        if (!m) continue;
        std::string date = std::string(m->getDate());
        
        ofs << PREFIX_MATCH << " " 
            << m->getWhitePlayer()->getId() << " " 
            << m->getBlackPlayer()->getId() << " " 
            << std::quoted(date) << " " 
            << static_cast<int>(m->getResult()) << "\n";
    }
}

void StorageManager::loadState(const std::string& filename, ChessClub& club) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        throw InvalidOperationException("Не удалось открыть файл для загрузки: " + filename);
    }

    loadMembers(ifs, club);
    loadEvents(ifs, club);
    loadMatches(ifs, club);
}

void StorageManager::loadMembers(std::ifstream& ifs, ChessClub& club) {
    int count = 0;
    if (!(ifs >> count)) throw InvalidDataException("Ошибка чтения количества участников");

    for (int i = 0; i < count; ++i) {
        std::string prefix;
        if (!(ifs >> prefix)) throw InvalidDataException("Ошибка чтения префикса участника");

        if (prefix == PREFIX_PLAYER) {
            loadPlayer(ifs, club);
        } else if (prefix == PREFIX_COACH) {
            loadCoach(ifs, club);
        } else {
            throw InvalidDataException("Неизвестный тип участника: " + prefix);
        }
    }
}

void StorageManager::loadPlayer(std::ifstream& ifs, ChessClub& club) {
    int id, year, rating;
    std::string name;

    if (!(ifs >> id >> std::quoted(name) >> year >> rating)) {
        throw InvalidDataException("Ошибка чтения данных игрока");
    }
    club.addMember(std::make_shared<Player>(id, name, year, rating));
}

void StorageManager::loadCoach(std::ifstream& ifs, ChessClub& club) {
    int id, year, exp, students;
    std::string name, spec;

    if (!(ifs >> id >> std::quoted(name) >> year >> exp >> students >> std::quoted(spec))) {
        throw InvalidDataException("Ошибка чтения данных тренера");
    }
    club.addMember(std::make_shared<Coach>(id, name, year, exp, students, spec));
}

void StorageManager::loadEvents(std::ifstream& ifs, ChessClub& club) {
    int count = 0;
    if (!(ifs >> count)) throw InvalidDataException("Ошибка чтения количества событий");

    for (int i = 0; i < count; ++i) {
        std::string prefix;
        if (!(ifs >> prefix)) throw InvalidDataException("Ошибка чтения префикса события");

        if (prefix == PREFIX_EVENT_TOUR) {
            loadTournament(ifs, club);
        } else if (prefix == PREFIX_EVENT_TRAIN) {
            loadTraining(ifs, club);
        } else if (prefix == PREFIX_EVENT_MASTER) {
            loadMasterClass(ifs, club);
        } else {
            throw InvalidDataException("Неизвестный тип события: " + prefix);
        }
    }
}

void StorageManager::loadTournament(std::ifstream& ifs, ChessClub& club) {
    int id, rounds, tc, sys, players;
    std::string title;

    if (!(ifs >> id >> std::quoted(title) >> rounds >> tc >> sys >> players)) {
        throw InvalidDataException("Ошибка чтения параметров турнира");
    }
    club.addEvent(std::make_shared<Tournament>(id, title, rounds, 
        static_cast<Tournament::TimeControl>(tc), 
        static_cast<Tournament::System>(sys), players));
}

void StorageManager::loadTraining(std::ifstream& ifs, ChessClub& club) {
    int id, level, duration;
    std::string title, topic, coach;

    if (!(ifs >> id >> std::quoted(title) >> std::quoted(topic) >> std::quoted(coach) >> level >> duration)) {
        throw InvalidDataException("Ошибка чтения параметров тренировки");
    }
    club.addEvent(std::make_shared<TrainingSession>(id, title, topic, coach, 
        static_cast<TrainingSession::Level>(level), duration));
}

void StorageManager::loadMasterClass(std::ifstream& ifs, ChessClub& club) {
    int id, titleType, audience, duration;
    std::string title, guest;

    if (!(ifs >> id >> std::quoted(title) >> std::quoted(guest) >> titleType >> audience >> duration)) {
        throw InvalidDataException("Ошибка чтения параметров мастер-класса");
    }
    club.addEvent(std::make_shared<MasterClass>(id, title, guest, 
        static_cast<MasterClass::GuestTitle>(titleType), audience, duration));
}

void StorageManager::loadMatches(std::ifstream& ifs, ChessClub& club) {
    int count = 0;
    if (!(ifs >> count)) throw InvalidDataException("Ошибка чтения количества партий");

    for (int i = 0; i < count; ++i) {
        std::string prefix, date;
        int wId, bId, res;

        if (!(ifs >> prefix >> wId >> bId >> std::quoted(date) >> res)) {
            throw InvalidDataException("Ошибка чтения параметров партии");
        }

        if (prefix == PREFIX_MATCH) {
            auto p1 = club.findPlayerById(wId);
            auto p2 = club.findPlayerById(bId);

            if (!p1) throw ObjectNotFoundException("Игрок с ID " + std::to_string(wId) + " не найден");
            if (!p2) throw ObjectNotFoundException("Игрок с ID " + std::to_string(bId) + " не найден");

            Match m(p1, p2, date);
            m.setResult(static_cast<Match::Result>(res));
            club.getMatches().add(m);
        }
    }
}

void StorageManager::logAction(const std::string& logFilename, const std::string& action) {
    std::ofstream ofs(logFilename, std::ios::app);
    if (!ofs.is_open()) throw InvalidOperationException("Не удалось открыть лог-файл");

    std::time_t now = std::time(nullptr);
    std::tm timeInfo;
    localtime_s(&timeInfo, &now);

    std::array<char, 100> buf{};
    std::strftime(buf.data(), buf.size(), "%Y-%m-%d %H:%M:%S", &timeInfo);

    ofs << "[" << buf.data() << "] " << action << "\n";
}

void StorageManager::generateReport(const std::string& reportFilename, const ChessClub& club) {
    std::ofstream ofs(reportFilename);
    if (!ofs.is_open()) throw InvalidOperationException("Не удалось открыть файл для отчёта");

    ofs << "ОТЧЁТ О СОСТОЯНИИ ШАХМАТНОГО КЛУБА\n";
    ofs << "==================================\n\n";

    reportMembers(ofs, club);
    reportEvents(ofs, club);
}

void StorageManager::reportMembers(std::ofstream& ofs, const ChessClub& club) {
    const auto& members = club.getMembers();
    ofs << "УЧАСТНИКИ (" << members.size() << "):\n";
    for (int i = 0; i < members.size(); ++i) {
        auto m = members.getShared(i);
        if (m) ofs << "  - [" << m->getRole() << "] " << m->getFullName() << "\n";
    }
    ofs << "\n";
}

void StorageManager::reportEvents(std::ofstream& ofs, const ChessClub& club) {
    const auto& events = club.getEvents();
    ofs << "СОБЫТИЯ (" << events.size() << "):\n";
    for (int i = 0; i < events.size(); ++i) {
        auto e = events.get(i);
        if (e) ofs << "  - [" << e->getType() << "] " << e->getTitle() << "\n";
    }
    ofs << "\n";
}