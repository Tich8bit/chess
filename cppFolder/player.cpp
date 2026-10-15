#include "player.h"
#include <iomanip>
#include <limits>

int Player::_nextId = 1;
const int Player::MIN_RATING = 0;
const int Player::MAX_RATING = 3000;
const int Player::CURRENT_YEAR = 2026;

Player::Player(std::string_view name,
               int birthYear,
               int rating,
               std::string_view category)
    : _id(_nextId++),
      _name(name),
      _birthYear(birthYear),
      _category(category) {
    setRating(rating);
}

int Player::getId() const { return _id; }
std::string_view Player::getName() const { return _name; }
int Player::getBirthYear() const { return _birthYear; }
int Player::getRating() const { return _rating; }
std::string_view Player::getCategory() const { return _category; }

int Player::getAge() const {
    return CURRENT_YEAR - _birthYear;
}

void Player::setName(std::string_view newName) {
    if (newName.empty()) {
        std::cerr << "[Ошибка] Имя не может быть пустым.\n";
        return;
    }
    _name = newName;
}

void Player::setRating(int newRating) {
    if (newRating < MIN_RATING || newRating > MAX_RATING) {
        std::cerr << "[Ошибка] Рейтинг должен быть в диапазоне ["
                  << MIN_RATING << "; " << MAX_RATING
                  << "]. Получено: " << newRating << "\n";
        return;
    }
    _rating = newRating;
}

void Player::setCategory(std::string_view newCategory) {
    _category = newCategory;
}

void Player::inputPlayer() {
    std::cout << "Введите имя игрока: ";
    std::getline(std::cin, _name);

    std::cout << "Введите год рождения: ";
    std::cin >> _birthYear;

    int newRating;
    std::cout << "Введите рейтинг: ";
    std::cin >> newRating;
    setRating(newRating);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Введите категорию: ";
    std::getline(std::cin, _category);
}

void Player::printInfo(std::ostream& os) const {
    os << "ID: " << std::setw(3) << _id
       << " | Имя: " << std::setw(20) << std::left << _name
       << " | Возраст: " << std::setw(3) << getAge()
       << " | Рейтинг: " << std::setw(5) << _rating
       << " | Категория: " << _category;
}

bool Player::equals(const Player& other) const {
    return _id == other._id;
}