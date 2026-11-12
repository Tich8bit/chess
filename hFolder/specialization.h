#pragma once
#include <string>
#include <iostream>

class Specialization {
public:
    enum class Type { Openings, Middlegame, Endgame, Tactics, General };
    enum class RatingType { Classical, Rapid, Blitz, All };

    Specialization();
    Specialization(Type type);
    Type getType() const;
    RatingType getTargetRating() const;
    std::string toString() const;
    static Type intToType(int value);
    friend std::ostream& operator<<(std::ostream& os, const Specialization& spec);
private:
    Type _type;
};