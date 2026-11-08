#include "specialization.h"

Specialization::Specialization()
    : _type(Type::General) {}

Specialization::Specialization(Type type)
    : _type(type) {}

Specialization::Type Specialization::getType() const { return _type; }

std::string Specialization::toString() const {
    return typeToString(_type);
}

std::string Specialization::typeToString(Type type) {
    switch (type) {
        case Type::Openings:   return "Дебюты";
        case Type::Middlegame: return "Миттельшпиль";
        case Type::Endgame:    return "Эндшпиль";
        case Type::Tactics:    return "Тактика";
        case Type::General:    return "Общая подготовка";
    }
    return "Неизвестно";
}

Specialization::Type Specialization::intToType(int value) {
    switch (value) {
        case 1: return Type::Openings;
        case 2: return Type::Middlegame;
        case 3: return Type::Endgame;
        case 4: return Type::Tactics;
        case 5: return Type::General;
        default: return Type::General;
    }
}

std::ostream& operator<<(std::ostream& os, const Specialization& spec) {
    os << spec.toString();
    return os;
}