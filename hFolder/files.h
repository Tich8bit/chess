#pragma once

#include <fstream>
#include <string>
#include "chessClub.h"
#include "collection.h"

class StorageManager {
public:
    static void saveState(const std::string& filename, const ChessClub& club);
    static void loadState(const std::string& filename, ChessClub& club);
    static void logAction(const std::string& logFilename, const std::string& action);
    static void generateReport(const std::string& reportFilename, const ChessClub& club);

private:
    static void savePlayers(std::ofstream& ofs, const ChessClub& club);
    static void saveEvents(std::ofstream& ofs, const ChessClub& club);
    static void saveMatches(std::ofstream& ofs, const ChessClub& club);

    static void loadPlayer(std::ifstream& ifs, ChessClub& club);
    static void loadCoach(std::ifstream& ifs, ChessClub& club);
    static void loadTournament(std::ifstream& ifs, ChessClub& club);
    static void loadTraining(std::ifstream& ifs, ChessClub& club);
    static void loadMatch(std::ifstream& ifs, ChessClub& club);

    static void reportPlayers(std::ofstream& ofs, const Collection<Player>& players);
    static void reportEvents(std::ofstream& ofs, const Collection<Event>& events);
    static void reportMatches(std::ofstream& ofs, const Collection<Match>& matches);

    static constexpr const char* PREFIX_PLAYER     = "PLR";
    static constexpr const char* PREFIX_COACH      = "CHC";
    static constexpr const char* PREFIX_TOURNAMENT = "TRN";
    static constexpr const char* PREFIX_TRAINING   = "TNG";
    static constexpr const char* PREFIX_MATCH      = "MTC";
};