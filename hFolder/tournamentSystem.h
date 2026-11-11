#pragma once

#include <string>
#include <memory>

class TournamentSystem {
public:
    virtual ~TournamentSystem() = default;
    virtual std::string getName() const = 0;
    virtual int getTypeId() const = 0;
    virtual int calculateOptimalRounds(int maxPlayers) const = 0;
    virtual void validateRules(int maxPlayers) const = 0;

    static std::shared_ptr<TournamentSystem> createFromId(int id);
};

class RoundRobinSystem : public TournamentSystem {
public:
    RoundRobinSystem(int circlesCount = 1, bool alternateColors = true);

    std::string getName() const override;
    int getTypeId() const override;
    int calculateOptimalRounds(int maxPlayers) const override;
    void validateRules(int maxPlayers) const override;

    int getCirclesCount() const;
    void setCirclesCount(int newCirclesCount);
    bool getAlternateColors() const;
    void setAlternateColors(bool value);

private:
    int _circlesCount;
    bool _alternateColors;
};

class SwissSystem : public TournamentSystem {
public:
    SwissSystem(int roundsCount = 5, bool avoidRematches = true);

    std::string getName() const override;
    int getTypeId() const override;
    int calculateOptimalRounds(int maxPlayers) const override;
    void validateRules(int maxPlayers) const override;

    int getRoundsCount() const;
    void setRoundsCount(int newRoundsCount);
    bool getAvoidRematches() const;
    void setAvoidRematches(bool value);

private:
    int _roundsCount;
    bool _avoidRematches;
};

class KnockoutSystem : public TournamentSystem {
public:
    KnockoutSystem(bool hasThirdPlaceMatch = false);

    std::string getName() const override;
    int getTypeId() const override;
    int calculateOptimalRounds(int maxPlayers) const override;
    void validateRules(int maxPlayers) const override;

    bool getHasThirdPlaceMatch() const;
    void setHasThirdPlaceMatch(bool value);

private:
    bool _hasThirdPlaceMatch;
};