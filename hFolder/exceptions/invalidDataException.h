#pragma once
#include "chessException.h"

class InvalidDataException : public ChessException {
public:
    explicit InvalidDataException(const std::string& message)
        : ChessException("Ошибка данных: " + message) {}
};