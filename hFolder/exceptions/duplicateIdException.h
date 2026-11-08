#pragma once
#include "chessException.h"

class DuplicateIdException : public ChessException {
public:
    explicit DuplicateIdException(const std::string& message)
        : ChessException("Дубликат: " + message) {}
};