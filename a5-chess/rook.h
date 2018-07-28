#ifndef _ROOK_
#define _ROOK_
#include "piece.h"
#include "cell.h"
#include <string>
#include <vector>

class Rook: public Piece{
    public:
    Rook(std::string name,int number);
    void detectNextPos(std::vector<std::vector<Cell*>>& board) override;
};

#endif
