#pragma once
#include "chessException.h"

class InvalidOperationException : public ChessException {
public:
    explicit InvalidOperationException(const std::string& message)
        : ChessException("Недопустимая операция: " + message) {}
};