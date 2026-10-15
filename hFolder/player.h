#pragma once

#include <string>
#include <string_view>
#include <iostream>

class Player {
public:
    Player(std::string_view name,
           int birthYear,
           int rating,
           std::string_view category);

    int getId() const;
    std::string_view getName() const;
    int getBirthYear() const;
    int getRating() const;
    std::string_view getCategory() const;
    int getAge() const;

    void setName(std::string_view newName);
    void setRating(int newRating);
    void setCategory(std::string_view newCategory);

    void inputPlayer();
    void printInfo(std::ostream& os) const;
    bool equals(const Player& other) const;

private:
    static int _nextId;
    static const int MIN_RATING;
    static const int MAX_RATING;
    static const int CURRENT_YEAR;

    int _id;
    std::string _name;
    int _birthYear;
    int _rating;
    std::string _category;
};