#include "specialization.h"

Specialization::Specialization() : _type(Type::General) {}
Specialization::Specialization(Type type) : _type(type) {}

Specialization::Type Specialization::getType() const { return _type; }

Specialization::RatingType Specialization::getTargetRating() const {
    switch (_type) {
        case Type::Openings:   return RatingType::Classical;
        case Type::Middlegame: return RatingType::Rapid;
        case Type::Endgame:    return RatingType::Classical;
        case Type::Tactics:    return RatingType::Blitz;
        case Type::General:    return RatingType::All;
    }
    return RatingType::All;
}

std::string Specialization::toString() const {
    switch (_type) {
        case Type::Openings: return "Дебюты";
        case Type::Middlegame: return "Миттельшпиль";
        case Type::Endgame: return "Эндшпиль";
        case Type::Tactics: return "Тактика";
        case Type::General: return "Общая подготовка";
    }
    return "Неизвестно";
}

Specialization::Type Specialization::intToType(int value) {
    switch (value) {
        case 1: return Type::Openings;
        case 2: return Type::Middlegame;
        case 3: return Type::Endgame;
        case 4: return Type::Tactics;
        default: return Type::General;
    }
}

std::ostream& operator<<(std::ostream& os, const Specialization& spec) {
    os << spec.toString();
    return os;
}