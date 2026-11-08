#pragma once

#include <string>
#include <string_view>
#include <iostream>

class Specialization {
public:
    enum class Type {
        Openings,      
        Middlegame,    
        Endgame,       
        Tactics,       
        General        
    };

    Specialization();
    Specialization(Type type);

    Type getType() const;
    std::string toString() const;

    static std::string typeToString(Type type);
    static Type intToType(int value);

    friend std::ostream& operator<<(std::ostream& os, const Specialization& spec);

private:
    Type _type;
};