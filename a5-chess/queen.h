#ifndef _QUEEN_
#define _QUEEN_
#include "piece.h"
#include "cell.h"
#include <string>
#include <vector>

class Queen: public Piece{
    public:
    Queen(std::string name, int number);
    void detectNextPos(std::vector<std::vector<Cell*>>& board) override;
};

#endif
