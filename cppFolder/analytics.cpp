#include "analytics.h"
#include "player.h"
#include "coach.h"
#include <algorithm>
#include <numeric>

std::map<std::string, std::vector<std::shared_ptr<Member>>, std::less<>>
ClubAnalytics::groupPlayersByRole(const ChessClub& club) {
    std::map<std::string, std::vector<std::shared_ptr<Member>>, std::less<>> groups;
    for (const auto& p : club.getPlayers()) {
        groups[p->getRole()].push_back(p);
    }
    return groups;
}

std::set<std::string, std::less<>>
ClubAnalytics::getUniqueEventTitles(const ChessClub& club) {
    std::set<std::string, std::less<>> titles;
    for (const auto& e : club.getEvents()) {
        titles.emplace(e->getTitle());
    }
    return titles;
}

std::vector<std::shared_ptr<Member>>
ClubAnalytics::findTopNByMetric(const ChessClub& club, size_t n) {
    std::vector<std::shared_ptr<Member>> sorted;
    for (const auto& p : club.getPlayers()) {
        sorted.push_back(p);
    }

    std::sort(sorted.begin(), sorted.end(),
        [](const std::shared_ptr<Member>& a, const std::shared_ptr<Member>& b) {
            return a->calculateMetric() > b->calculateMetric();
        });

    if (sorted.size() > n) sorted.resize(n);
    return sorted;
}

std::pair<std::shared_ptr<Member>, std::shared_ptr<Member>>
ClubAnalytics::findMinMaxMetric(const ChessClub& club) {
    if (club.getPlayers().empty()) return {nullptr, nullptr};

    auto [minIt, maxIt] = std::minmax_element(
        club.getPlayers().begin(), club.getPlayers().end(),
        [](const std::shared_ptr<Member>& a, const std::shared_ptr<Member>& b) {
            return a->calculateMetric() < b->calculateMetric();
        });

    return {*minIt, *maxIt};
}

size_t ClubAnalytics::countPlayersWithRatingAbove(const ChessClub& club, int minRating) {
    return std::count_if(club.getPlayers().begin(), club.getPlayers().end(),
        [minRating](const std::shared_ptr<Member>& p) {
            return p->getRatings().getMax() > minRating;
        });
}

std::vector<std::shared_ptr<Member>>
ClubAnalytics::filterPlayersByRole(const ChessClub& club, const std::string& role) {
    std::vector<std::shared_ptr<Member>> result;
    std::copy_if(club.getPlayers().begin(), club.getPlayers().end(),
        std::back_inserter(result),
        [&role](const std::shared_ptr<Member>& p) {
            return p->getRole() == role;
        });
    return result;
}

int ClubAnalytics::sumRatings(const ChessClub& club) {
    return std::accumulate(club.getPlayers().begin(), club.getPlayers().end(), 0,
        [](int acc, const std::shared_ptr<Member>& p) {
            return acc + p->getRatings().getMax();
        });
}

std::vector<std::shared_ptr<Member>>
ClubAnalytics::sortByTwoCriteria(const ChessClub& club) {
    std::vector<std::shared_ptr<Member>> sorted;
    for (const auto& p : club.getPlayers()) {
        sorted.push_back(p);
    }

    std::sort(sorted.begin(), sorted.end(),
        [](const std::shared_ptr<Member>& a, const std::shared_ptr<Member>& b) {
            if (a->getRatings().getMax() != b->getRatings().getMax()) {
                return a->getRatings().getMax() > b->getRatings().getMax();
            }
            return a->getGamesPlayed() > b->getGamesPlayed();
        });
    return sorted;
}