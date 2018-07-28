#include "bishop.h"
#include "cell.h"
#include <vector>
#include <string>
#include <iostream>
#include "piece.h"
#include "tools.h"
using namespace std;

Bishop::Bishop(string name, int number):Piece(name,number){}

void Bishop::detectNextPos(vector<vector<Cell*>>& board){
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

}




   
