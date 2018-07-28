#ifndef _HUMAN_
#define _HUMAN_
#include "player.h"
#include <string>

class Move;

class Human: public Player{
    public:
    Human(std::string colour, Move* m);
    void move(std::string pos1="", std::string pos2="", std::string piece="") override;
};

#endif
