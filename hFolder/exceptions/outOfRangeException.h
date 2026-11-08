#pragma once

#include "chessException.h"

class OutOfRangeException : public ChessException {
public:
    explicit OutOfRangeException(const std::string& message)
        : ChessException("Выход за границы: " + message) {}
};