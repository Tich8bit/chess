#pragma once

#include "chessException.h"

class RelationException : public ChessException {
public:
    explicit RelationException(const std::string& message)
        : ChessException("Нарушение связи: " + message) {}
};