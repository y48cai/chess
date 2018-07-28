#include "rook.h"
#include "cell.h"
#include <vector>
#include <string>
#include <iostream>
#include "piece.h"
#include "tools.h"
using namespace std;

Rook::Rook(string name, int number):Piece(name,number){}

void Rook::detectNextPos(vector<vector<Cell*>>& board){
    Location currLoc=to_Location(getPos());

    //E direction
    for (int row=currLoc.row, col=currLoc.col+1; col<8; ++col){
        Cell* cell=board[row][col];
        if (cell->getCurrent()!=""){
            if (whatColour(cell->getCurrent())==whatColour(getName())){
                cell->addOther(getName(),getNumber());
                break;
            }else{
                cell->addOther(getName(),getNumber());
                this->addNextPos(cell->getPos());
                break;
            }
        }else{
            cell->addOther(getName(),getNumber());
            this->addNextPos(cell->getPos());
        }
    }


    //S direction
    for (int row=currLoc.row-1, col=currLoc.col; row>=0; --row){
        Cell* cell=board[row][col];
        if (cell->getCurrent()!=""){
            if (whatColour(cell->getCurrent())==whatColour(getName())){
                cell->addOther(getName(),getNumber());
                break;
            }else{
                cell->addOther(getName(),getNumber());
                this->addNextPos(cell->getPos());
                break;
            }
        }else{
            cell->addOther(getName(),getNumber());
            this->addNextPos(cell->getPos());
        }
    }

    //W direction
    for (int row=currLoc.row, col=currLoc.col-1; col>=0; --col){
        Cell* cell=board[row][col];
        if (cell->getCurrent()!=""){
            if (whatColour(cell->getCurrent())==whatColour(getName())){
                cell->addOther(getName(),getNumber());
                break;
            }else{
                cell->addOther(getName(),getNumber());
                this->addNextPos(cell->getPos());
                break;
            }
        }else{
            cell->addOther(getName(),getNumber());
            this->addNextPos(cell->getPos());
        }
    }

    //N direction
    for (int row=currLoc.row+1, col=currLoc.col; row<8; ++row){
        Cell* cell=board[row][col];
        if (cell->getCurrent()!=""){
            if (whatColour(cell->getCurrent())==whatColour(getName())){
                cell->addOther(getName(),getNumber());
                break;
            }else{
                cell->addOther(getName(),getNumber());
                this->addNextPos(cell->getPos());
                break;
            }
        }else{
            cell->addOther(getName(),getNumber());
            this->addNextPos(cell->getPos());
        }
    }
}





