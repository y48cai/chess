#include "knight.h"
#include "cell.h"
#include "piece.h"
#include "tools.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

Knight::Knight(string name, int number):Piece(name,number){}

void Knight::detectNextPos(vector<vector<Cell*>>& board){
    vector<string> pos;
    Location currLoc=to_Location(getPos());
    pos.push_back(to_Position(currLoc.row+1,currLoc.col+2));
    pos.push_back(to_Position(currLoc.row+1,currLoc.col-2));
    pos.push_back(to_Position(currLoc.row-1,currLoc.col+2));
    pos.push_back(to_Position(currLoc.row-1,currLoc.col-2));
    pos.push_back(to_Position(currLoc.row+2,currLoc.col+1));
    pos.push_back(to_Position(currLoc.row+2,currLoc.col-1));
    pos.push_back(to_Position(currLoc.row-2,currLoc.col+1));
    pos.push_back(to_Position(currLoc.row-2,currLoc.col-1));
    for (auto &p :pos){
        if (ifPosExists(p)){
            bool validNextPos=true;
            Location loc=to_Location(p);
            Cell* cell=board[loc.row][loc.col];
            if (cell->getCurrent() !="" && whatColour(cell->getCurrent())==whatColour(getName())){       
                cell->addOther(getName(),getNumber());
                validNextPos=false;
            }

            if (validNextPos==true){
                cell->addOther(getName(),getNumber());
                this->addNextPos(p);
            }
        }
    }
}
           
