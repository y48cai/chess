#include "queen.h"
#include "cell.h"
#include "piece.h"
#include "tools.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

Queen::Queen(string name, int number):Piece(name,number){}

void Queen::detectNextPos(std::vector<std::vector<Cell*>>& board){
    Location currLoc=to_Location(getPos());

    //NE direction
    for (int row=currLoc.row+1, col=currLoc.col+1; row<8 && col<8; ++row,++col){
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

    //SE direction
    for (int row=currLoc.row-1, col=currLoc.col+1; row>=0 && col<8; --row, ++col){
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

    //SW direction
    for (int row=currLoc.row-1, col=currLoc.col-1; row>=0 && col>=0; --row,--col){
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

    //NW direction
    for (int row=currLoc.row+1, col=currLoc.col-1; row<8 && col>=0; ++row,--col){
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

