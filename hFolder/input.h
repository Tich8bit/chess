#pragma once

#include <string>
#include <iostream>
#include <limits>

inline std::string inputString(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

template <typename T>
T inputNumber(const std::string& prompt, T minValue, T maxValue) {
    T value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= minValue && value <= maxValue) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Некорректный ввод. Повторите попытку.\n";
    }
}