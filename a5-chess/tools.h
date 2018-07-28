#ifndef _TOOLS_
#define _TOOLS_
#include <string>

struct Location{
    int row;
    int col;
};

Location to_Location(std::string pos);

std::string to_Position(Location loc);

std::string to_Position(int row, int col);

bool ifPosExists(std::string pos);

std::string whatColour(std::string pieceName);

struct Invalid{
    std::string msg;
};

bool validPiece(std::string piece);

#endif
