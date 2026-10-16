#include "member.h"
#include "constants.h"

Member::Member(int id, std::string_view fullName, int birthYear)
    : _id(id),
      _fullName(fullName),
      _birthYear(birthYear) {}

Member::~Member() {}

int Member::getId() const { return _id; }
std::string_view Member::getFullName() const { return _fullName; }
int Member::getBirthYear() const { return _birthYear; }

int Member::getAge() const { return CURRENT_YEAR - _birthYear; }

Member::Category Member::getCategory() const {
    int age = getAge();
    if (age < 14) return Category::Child;
    if (age < 20) return Category::Junior;
    if (age < 60) return Category::Adult;
    return Category::Veteran;
}

void Member::setFullName(std::string_view newFullName) { _fullName = newFullName; }

double Member::calculateMetric() const { return 0.0; }
std::string_view Member::getMetricName() const { return "Метрика"; }

void Member::printMemberInformation() const {
    std::cout << *this << "\n";
}

std::string_view Member::categoryToString(Category c) {
    switch (c) {
        case Category::Child:   return "Ребенок";
        case Category::Junior:  return "Юниор";
        case Category::Adult:   return "Взрослый";
        case Category::Veteran: return "Ветеран";
    }
    return "Неизвестно";
}