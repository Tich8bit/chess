#pragma once

#include <map>
#include <set>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include "chessClub.h"

class ClubAnalytics {
public:
    static std::map<std::string, std::vector<std::shared_ptr<Player>>, std::less<>>
    groupPlayersByRole(const ChessClub& club);

    static std::set<std::string, std::less<>>
    getUniqueEventTitles(const ChessClub& club);

    static std::vector<std::shared_ptr<Player>>
    findTopNByMetric(const ChessClub& club, size_t n);

    static std::pair<std::shared_ptr<Player>, std::shared_ptr<Player>>
    findMinMaxMetric(const ChessClub& club);

    static size_t
    countPlayersWithRatingAbove(const ChessClub& club, int minRating);

    static std::vector<std::shared_ptr<Player>>
    filterPlayersByRole(const ChessClub& club, const std::string& role);

    static int
    sumRatings(const ChessClub& club);

    static std::vector<std::shared_ptr<Player>>
    sortByTwoCriteria(const ChessClub& club);
};