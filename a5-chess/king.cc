#include "king.h"
#include "cell.h"
#include <vector>
#include <string>
#include <iostream>
#include "piece.h"
#include "tools.h"
using namespace std;

King::King(string name, int number):Piece(name,number){}

void King::detectNextPos(vector<vector<Cell*>>& board){
    Location currLoc=to_Location(getPos());
    //generate candidate pos
    string pos1=to_Position(currLoc.row-1,currLoc.col-1);
    string pos2=to_Position(currLoc.row-1,currLoc.col);
    string pos3=to_Position(currLoc.row-1,currLoc.col+1);
    string pos4=to_Position(currLoc.row,currLoc.col-1);
    string pos5=to_Position(currLoc.row,currLoc.col+1);
    string pos6=to_Position(currLoc.row+1,currLoc.col-1);
    string pos7=to_Position(currLoc.row+1,currLoc.col);
    string pos8=to_Position(currLoc.row+1,currLoc.col+1);
    string arr[8]={pos1,pos2,pos3,pos4,pos5,pos6,pos7,pos8}; 
    for (int i=0; i<8; ++i){
        string pos=arr[i];
        if (ifPosExists(pos)){
            bool validNextPos=true;
            Location loc=to_Location(pos);
            Cell* cell=board[loc.row][loc.col];
            if (cell->getCurrent() !="" && whatColour(cell->getCurrent())==whatColour(getName())){
                cell->addOther(getName(),getNumber());
                validNextPos=false;
            }

            if (validNextPos==true){
                cell->addOther(getName(),getNumber());
                this->addNextPos(pos);
            }
        }
    }
}












