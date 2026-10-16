#pragma once

#include <string>
#include <string_view>
#include <iostream>
#include <compare>

class Member {
public:
    enum class Category { Child, Junior, Adult, Veteran };

    Member(int id, std::string_view fullName, int birthYear);
    virtual ~Member();

    int getId() const;
    std::string_view getFullName() const;
    int getBirthYear() const;
    Category getCategory() const;
    int getAge() const;

    void setFullName(std::string_view newFullName);

    virtual std::string_view getRole() const = 0;
    virtual double calculateMetric() const;
    virtual std::string_view getMetricName() const;
    virtual void printMemberInformation() const;

    static std::string_view categoryToString(Category c);

    friend bool operator==(const Member& a, const Member& b) {
        return a._id == b._id;
    }

    friend std::strong_ordering operator<=>(const Member& a, const Member& b) {
        if (a.calculateMetric() < b.calculateMetric()) return std::strong_ordering::less;
        if (a.calculateMetric() > b.calculateMetric()) return std::strong_ordering::greater;
        return std::strong_ordering::equal;
    }

    friend std::ostream& operator<<(std::ostream& os, const Member& m) {
        os << "ID: " << m._id
           << " | Роль: " << m.getRole()
           << " | Имя: " << m._fullName
           << " | Возраст: " << m.getAge()
           << " | Категория: " << categoryToString(m.getCategory());
        return os;
    }

protected:
    int _id;
    std::string _fullName;
    int _birthYear;
};