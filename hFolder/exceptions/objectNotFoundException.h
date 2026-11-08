#pragma once
#include "chessException.h"

class ObjectNotFoundException : public ChessException {
public:
    explicit ObjectNotFoundException(const std::string& message)
        : ChessException("Не найдено: " + message) {}
};