#ifndef _KING__
#define _KING_
#include "piece.h"
#include "cell.h"
#include <string>
#include <vector>

class King: public Piece{
    public:
    King(std::string name,int number);
    void detectNextPos(std::vector<std::vector<Cell*>>& board) override;
};

#endif
