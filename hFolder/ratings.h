#pragma once
#include <iostream>

class Ratings {
public:
    Ratings(int classical, int rapid, int blitz);
    int getClassical() const;
    int getRapid() const;
    int getBlitz() const;
    int getMax() const;
    friend std::ostream& operator<<(std::ostream& os, const Ratings& r);
private:
    int _classical;
    int _rapid;
    int _blitz;
};