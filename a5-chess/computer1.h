#ifndef _COMP1_
#define _COMP1_
#include "player.h"
#include <string>
class Move;
class Cell;
class Piece;

class Computer1: public Player{
    public:
    Computer1(std::string colour, Move* m);
    void move(std::string pos1="", std::string pos2="", std::string piece="") override;
    void generateMove(std::vector<Piece*>& white, std::vector<Piece*>& black, std::vector<std::vector<Cell*>>& board) override;
};

#endif

