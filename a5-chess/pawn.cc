#include "pawn.h"
#include "cell.h"
#include <vector>
#include <string>
#include <iostream>
#include "piece.h"
#include "tools.h"
using namespace std;

Pawn::Pawn(string name, int number):Piece(name,number){}

void Pawn::detectNextPos(vector<vector<Cell*>>& board){
    Location currLoc=to_Location(getPos());

    if (whatColour(getName())=="white"){//white pawn
        //currLoc cannot be the last line
        if (currLoc.row==7){return;}

        //first step can be 2 steps forward
        if (getSteps()==0 && currLoc.row==1 ){
            Cell* cell=board[currLoc.row+2][currLoc.col];
            Cell* cell_btw =board[currLoc.row+1][currLoc.col];
            if (cell_btw->getCurrent()==""){
                if (cell->getCurrent()!=""){
                    cell->addOther(getName(),getNumber());
                }else{
                    cell->addOther(getName(),getNumber());
                    this->addNextPos(cell->getPos());
                } 
            }
        }

        //middle cell a step forward
        Cell* cell1=board[currLoc.row+1][currLoc.col]; 
        if (cell1->getCurrent()!=""){
            cell1->addOther(getName(),getNumber());
        }else{
            cell1->addOther(getName(),getNumber());
            this->addNextPos(cell1->getPos());
        }

        //left cell a step forward
        if (currLoc.col!=0){
            Cell* cell2=board[currLoc.row+1][currLoc.col-1];
            if (cell2->getCurrent()!="" && whatColour(cell2->getCurrent())=="black"){
                cell2->addOther(getName(),getNumber());
                this->addNextPos(cell2->getPos());
            }else{
                cell2->addOther(getName(),getNumber());
            }
        }

        //right cell a step forward
        if (currLoc.col!=7){
            Cell* cell3=board[currLoc.row+1][currLoc.col+1];
            if (cell3->getCurrent()!="" && whatColour(cell3->getCurrent())=="black"){
                cell3->addOther(getName(),getNumber());
                this->addNextPos(cell3->getPos());
            }else{
            cell3->addOther(getName(),getNumber());
            }
        }

    }else if (whatColour(getName())=="black"){//black pawn
        //currLoc cannot be the first line
        if (currLoc.row==0){return;}

        //first step can be 2 steps forward
        if (getSteps()==0 && currLoc.row==6 ){
            Cell* cell=board[currLoc.row-2][currLoc.col];
            Cell* cell_btw=board[currLoc.row-1][currLoc.col];
            if (cell_btw->getCurrent()==""){
                if (cell->getCurrent()!=""){
                    cell->addOther(getName(),getNumber());
                }else{
                    cell->addOther(getName(),getNumber());
                    this->addNextPos(cell->getPos());
                }
            }
        }

        //middle cell a step forward
        Cell* cell1=board[currLoc.row-1][currLoc.col];
        if (cell1->getCurrent()!=""){
            cell1->addOther(getName(),getNumber());
        }else{
            cell1->addOther(getName(),getNumber());
            this->addNextPos(cell1->getPos());
        }

        //left cell a step forward
        if (currLoc.col !=0){
            Cell* cell2=board[currLoc.row-1][currLoc.col-1];
            if (cell2->getCurrent()!="" && whatColour(cell2->getCurrent())=="white"){
                cell2->addOther(getName(),getNumber());
                this->addNextPos(cell2->getPos());
            }else{
                cell2->addOther(getName(),getNumber());
            }
       }

        //right cell a step forward
        if (currLoc.col!=7){
            Cell* cell3=board[currLoc.row-1][currLoc.col+1];
            if (cell3->getCurrent()!="" && whatColour(cell3->getCurrent())=="white"){
                cell3->addOther(getName(),getNumber());
                this->addNextPos(cell3->getPos());
            }else{
               cell3->addOther(getName(),getNumber());
            }
        }
    }
}

