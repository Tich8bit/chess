#pragma once
#include <iostream>

class MatchResult {
public:
    enum class Result { NotPlayed = -1, Draw = 0, WhiteWin = 1, BlackWin = 2 };
    MatchResult();
    MatchResult(Result result);
    Result getResult() const;
    void setResult(Result newResult);
    bool isPlayed() const;
    double getWhiteScore() const;
    double getBlackScore() const;
    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& os, const MatchResult& res);
private:
    Result _result;
};