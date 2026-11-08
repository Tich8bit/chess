#pragma once

#include <string>
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
    static std::string toString(Result result);

    friend std::ostream& operator<<(std::ostream& os, const MatchResult& res);
    friend bool operator==(const MatchResult& a, const MatchResult& b);

private:
    Result _result;
};