#pragma once

#include <fstream>
#include <string>
#include "chessClub.h"
#include "collection.h"
#include "member.h"
#include "event.h"

class StorageManager {
public:
    static void saveState(const std::string& filename, const ChessClub& club);
    static void loadState(const std::string& filename, ChessClub& club);
    static void logAction(const std::string& logFilename, const std::string& action);
    static void generateReport(const std::string& reportFilename, const ChessClub& club);

private:
    static void saveMembers(std::ofstream& ofs, const ChessClub& club);
    static void savePlayers(std::ofstream& ofs, const ChessClub& club);
    static void saveCoaches(std::ofstream& ofs, const ChessClub& club);

    static void saveEvents(std::ofstream& ofs, const ChessClub& club);
    static void saveTournaments(std::ofstream& ofs, const ChessClub& club);
    static void saveTrainings(std::ofstream& ofs, const ChessClub& club);
    static void saveMasterClasses(std::ofstream& ofs, const ChessClub& club);

    static void saveMatches(std::ofstream& ofs, const ChessClub& club);

    static void loadMembers(std::ifstream& ifs, ChessClub& club);
    static void loadPlayer(std::ifstream& ifs, ChessClub& club);
    static void loadCoach(std::ifstream& ifs, ChessClub& club);

    static void loadEvents(std::ifstream& ifs, ChessClub& club);
    static void loadTournament(std::ifstream& ifs, ChessClub& club);
    static void loadTraining(std::ifstream& ifs, ChessClub& club);
    static void loadMasterClass(std::ifstream& ifs, ChessClub& club);

    static void loadMatches(std::ifstream& ifs, ChessClub& club);

    static void reportMembers(std::ofstream& ofs, const ChessClub& club);
    static void reportEvents(std::ofstream& ofs, const ChessClub& club);

    static constexpr const char* PREFIX_PLAYER = "PLR";
    static constexpr const char* PREFIX_COACH  = "CHC";
    static constexpr const char* PREFIX_EVENT_TOUR = "TRN";
    static constexpr const char* PREFIX_EVENT_TRAIN = "TNG";
    static constexpr const char* PREFIX_EVENT_MASTER = "MST";
    static constexpr const char* PREFIX_MATCH = "MTC";
};