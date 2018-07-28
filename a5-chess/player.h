#ifndef _PLAYER_
#define _PLAYER_
#include "move.h"
#include <string>
class Piece;
class Cell;

class Player{
    protected:
    std::string colour;
    Move* m;
    public:
    Player(std::string colour, Move* m);
    virtual void move(std::string pos1="", std::string pos2="", std::string piece=""){};
    virtual void generateMove(std::vector<Piece*>& white, std::vector<Piece*>& black, std::vector<std::vector<Cell*>>& board){};
    virtual ~Player()=0;
    std::string getColour();
    float getScore();
};

#endif

