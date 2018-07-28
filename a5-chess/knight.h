#ifndef _KNIGHT_
#define _KNIGHT_
#include "piece.h"
#include "cell.h"
#include <string>
#include <vector>

class Knight: public Piece{
    public:
    Knight(std::string name, int number);
    void detectNextPos(std::vector<std::vector<Cell*>>& board) override;
};

#endif
