#pragma once
#include "chessException.h"

class LimitExceededException : public ChessException {
public:
    explicit LimitExceededException(const std::string& message)
        : ChessException("Превышен лимит: " + message) {}
};