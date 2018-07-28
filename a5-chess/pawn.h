#ifndef _PAWN_
#define _PAWN_
#include "piece.h"
#include "cell.h"
#include <string>
#include <vector>

class Pawn: public Piece{
    public:
    Pawn(std::string name,int number);
    void detectNextPos(std::vector<std::vector<Cell*>>& board) override;
};

#endif
