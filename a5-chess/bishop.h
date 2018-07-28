#ifndef _BISHOP_
#define _BISHOP_
#include "piece.h"
#include "cell.h"
#include <string>
#include <vector>

class Bishop: public Piece{
    public:
    Bishop(std::string name,int number);
    void detectNextPos(std::vector<std::vector<Cell*>>& board) override;
};

#endif
