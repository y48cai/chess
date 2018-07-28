#include "move.h"
#include "textdisplay.h"
#include "tools.h"
#include <vector>
#include <string>
#include "piece.h"
#include "king.h"
#include "knight.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "pawn.h"
#include "graphics.h"
#include "player.h"
#include <iostream>

using namespace std;

class Graphics;

//private methods
void Move::detectNextPos(Piece* piece){
    piece->detectNextPos(board);
}

void Move::clearNextPos(Piece* piece){
    //for piece
    piece->clearNextPos();
    //for cells
    for (int i=0; i<8; ++i){
        for (int j=0; j<8; ++j){
            string name=piece->getName();
            int num=piece->getNumber();
            board[i][j]->deleteOther(name,num);
        }
    }
}

void Move::othersRecalculate(Cell* cell){
    for (int i=0; i<cell->othersLen();++i){
        string other=cell->otherAt(i);  
        if (other[0]>'a' && other[0]<'z'){
            clearNextPos(black[stoi(other.substr(1))]);
            detectNextPos(black[stoi(other.substr(1))]);
        }else{
            clearNextPos(white[stoi(other.substr(1))]); 
            detectNextPos(white[stoi(other.substr(1))]);
        }
    }
}


void Move::setPiece(Piece* piece, Cell* cell){
    //on Cell
    cell->setCurrent(piece->getName(),piece->getNumber());
    //on piece
    piece->setPos(cell->getPos());
    piece->pushHistoryPos(cell->getPos());//record history
    //detectNextPos for piece
    detectNextPos(piece);
    //let others of cell recalculate nextPos
    othersRecalculate(cell);

    //graphics
    string name=piece->getName();
    Location loc=to_Location(cell->getPos());
    int numColour;
    if (whatColour(name)=="white"){
        numColour=0;
    }else{
        numColour=1;
    }
    g->notify(loc.row,loc.col,name,numColour);

}

void Move::unsetPiece(Piece* piece, Cell* cell){
    Location loc=to_Location(cell->getPos());
    //graphics
    int numColour;
    if ((loc.row%2==0 && loc.col%2==0)||(loc.row%2==1 && loc.col%2==1)){
        numColour=3;
    }else{
        numColour=2;
    }
    g->notify(loc.row,loc.col,piece->getName(),numColour);

   //on Cell
    cell->unsetCurrent();
    //on piece
    piece->setPos("");
    clearNextPos(piece);
    //let others of cell recalculate nextPos
    othersRecalculate(cell);
}

void Move::move(Cell* cell1, Cell* cell2, Piece* piece){
    vector<string> newhistory;//record history
    newhistory.push_back(cell1->getCurrent());
    newhistory.push_back("");
    if (cell2->getCurrent()!=""){//if cell2 i    set("R","h1");s occupied
        newhistory.pop_back(); 
        newhistory.push_back(cell2->getCurrent());
        unset(cell2->getPos());
    }
    unsetPiece(piece,cell1);
    setPiece(piece,cell2);
    piece->stepsIncrement();
    history.push_back(newhistory);
}

void Move::upgrade(Piece* piece,Cell* cell, string type){
    int whiteNum=static_cast<int>(white.size());
    int blackNum=static_cast<int>(black.size());
    if (type=="N"){
        Piece* p=new Knight{type,whiteNum};
        white.push_back(p);
        move(cell,cell,p);
        p->stepsDecrement();
    }else if (type=="Q"){
        Piece* p=new Queen{type,whiteNum};
        white.push_back(p);
        move(cell,cell,p);
        p->stepsDecrement();
    }else if (type=="R"){
        Piece* p=new Rook{type,whiteNum};
        white.push_back(p);
        move(cell,cell,p);
        p->stepsDecrement();
    }else if (type=="B"){
        Piece* p=new Bishop{type,whiteNum};
        white.push_back(p);
        move(cell,cell,p);
        p->stepsDecrement();
    }else if (type=="n"){
        Piece* p=new Knight{type,blackNum};
        black.push_back(p);
        move(cell,cell,p);
        p->stepsDecrement();
    }else if (type=="q"){
        Piece* p=new Queen{type,blackNum};
        black.push_back(p);
        move(cell,cell,p);
        p->stepsDecrement();
    }else if (type=="r"){
        Piece* p=new Rook{type,blackNum};
        black.push_back(p);
        move(cell,cell,p);
        p->stepsDecrement();
    }else if (type=="b"){
        Piece* p=new Bishop{type,blackNum};
        black.push_back(p);
        move(cell,cell,p);
        p->stepsDecrement();
    }
}

bool Move::dangerousFor(Cell* cell,string colour){
    for (int i=0; i<cell->othersLen(); ++i){
        string name=cell->otherAt(i);
        if (whatColour(name)=="white" && colour=="black"){
            Piece* piece=white[stoi(name.substr(1))];
            for(int j=0; j<piece->nextPosLen();++j){
                if (piece->nextPosAt(j)==cell->getPos()){
                    return true;
                }
            }
        }else if (whatColour(name)=="black" && colour=="white"){
            Piece* piece=black[stoi(name.substr(1))];
            for(int j=0; j<piece->nextPosLen();++j){
                if (piece->nextPosAt(j)==cell->getPos()){
                    return true;
                }
            }
        }
    }
    return false;
}


bool Move::availableMoves(string colour){
    if (ifIncheck(colour)){//if colour is also in check
        //for white colour
        if (colour=="white"){
            for (int i=0; i<static_cast<int>(white.size()); ++i){
                if (white[i]->getPos()!="" && white[i]->nextPosLen()!=0){
                    for (int j=0; j<white[i]->nextPosLen();++j){
                         try{
                            move(colour,white[i]->getPos(),white[i]->nextPosAt(j));
                            undo();
                            return true;
                         }catch(...){
                         }
                    }
                }
            }
            return false;
        }else{//for black colour
            for (int i=0; i<static_cast<int>(black.size()); ++i){
                if (black[i]->getPos()!="" && black[i]->nextPosLen()!=0){
                    for (int j=0; j<black[i]->nextPosLen();++j){
                         try{
                            move(colour,black[i]->getPos(),black[i]->nextPosAt(j));
                            undo();   
                            return true;
                         }catch(...){
                         }
                    }
                }
            }
            return false;
        }
    }
    if (colour=="white"){
        for (int i=0; i<static_cast<int>(white.size()); ++i){
            if (white[i]->getPos()!="" && white[i]->nextPosLen()!=0){
                return true;
            }
        }
    }else if (colour=="black"){
        for (int i=0; i<static_cast<int>(black.size()); ++i){
            if (black[i]->getPos()!="" && black[i]->nextPosLen()!=0){
                return true;
            }
        }
    }
    return false;
}











//public methods:
Move::Move(TextDisplay* td, Graphics* g):td{td},g{g}{}

Move::~Move(){
    for (int i=0; i<8; ++i){
        for(int j=0; j<8; ++j){
            delete board[i][j];
        }
    }
    if (! white.empty()){
        for (size_t i=0; i<white.size(); ++i){
            delete white[i];
        }
    }
    if (! black.empty()){
        for (size_t i=0; i<black.size();++i){
            delete black[i];
        }
    }
}

void Move::BoardSetUp(){
    for (int i=0; i<8; ++i){
        vector<Cell*> row;
        for (int j=0; j<8; ++j){
            Cell* cell= new Cell{to_Position(i,j)};
            row.push_back(cell);
        }
        board.push_back(row);
    }
}

void Move::clearBoard(){
    for (int i=0; i<8; ++i){//clear all pieces on board
        for (int j=0; j<8; ++j){

            //graphics
            int numColour;
            if ((i%2==0 && j%2==0)||(i%2==1 && j%2==1)){
                numColour=3;
            }else{
                numColour=2;
            }
            if (board[i][j]->getCurrent()!=""){
                g->notify(i,j,board[i][j]->getCurrent().substr(0,1),numColour);
            }

            board[i][j]->clearCell();
            td->notify(board[i][j]);
        }
    }
    if (! white.empty()){//clear all pieces in white player
        for (size_t i=0; i<white.size(); ++i){
            delete white[i];
        }
        white.clear();
    }
    if (! black.empty()){//clear all pieces in black player
        for (size_t i=0; i<black.size();++i){
            delete black[i];
        }
        black.clear();
    }

    //clear history
    history.clear();
}

void Move::set(string name, string pos){
    if (! ifPosExists(pos)){
        throw Invalid{pos + " is not a valid position!"};
    }
    Location loc=to_Location(pos);
    if (board[loc.row][loc.col]->getCurrent()!=""){
        throw Invalid{pos +" is occupied!"};
    }
    if (!(name.length()==1 && validPiece(name))){
        throw Invalid{name + "is not a valid piece!"};
    }
    if (whatColour(name)=="white"){
        int number=static_cast<int>(white.size());
        if (name=="K"){
            Piece* piece=new King{name,number};
            white.push_back(piece);
        }else if (name=="N"){
            Piece* piece=new Knight{name,number};
            white.push_back(piece);
        }else if (name=="Q"){
            Piece* piece=new Queen{name,number};
            white.push_back(piece);
         }else if (name=="R"){
            Piece* piece=new Rook{name,number};
            white.push_back(piece);
        }else if (name=="B"){
            Piece* piece=new Bishop{name,number};
            white.push_back(piece);
        }else if (name=="P"){
            Piece* piece=new Pawn{name,number};
            white.push_back(piece);
        }
        setPiece(white[number],board[loc.row][loc.col]);

    }else{
        int number=static_cast<int>(black.size());
        if (name=="k"){
            Piece* piece=new King{name,number};
            black.push_back(piece);
        }else if (name=="n"){
            Piece* piece=new Knight{name,number};
            black.push_back(piece);
        }else if (name=="q"){
            Piece* piece=new Queen{name,number};
            black.push_back(piece);
        }else if (name=="r"){
            Piece* piece=new Rook{name,number};
            black.push_back(piece);
        }else if (name=="b"){
            Piece* piece=new Bishop{name,number};
            black.push_back(piece);
        }else if (name=="p"){
            Piece* piece=new Pawn{name,number};
            black.push_back(piece);
        }
        setPiece(black[number],board[loc.row][loc.col]);
    }
    //notify display
    td->notify(board[loc.row][loc.col]);
}

void Move::unset(string pos){        
    if (! ifPosExists(pos)){
        throw Invalid{pos + " is not a valid position!"};
    }
    Location loc=to_Location(pos); 
    string pieceName=board[loc.row][loc.col]->getCurrent();          
    if (pieceName==""){return;}

    if (whatColour(pieceName)=="white"){
        unsetPiece(white[stoi(pieceName.substr(1))],board[loc.row][loc.col]);
    }else{
        unsetPiece(black[stoi(pieceName.substr(1))],board[loc.row][loc.col]);
    }
    td->notify(board[loc.row][loc.col]);
   //notify display
}

void Move::move(string colour, string pos1, string pos2, string piece){
    //check if pos1 and pos are valid pos
    if (! (ifPosExists(pos1) && ifPosExists(pos2))){
        throw Invalid{"Invalid position!"};
    }

    Location loc1=to_Location(pos1);
    Location loc2=to_Location(pos2);    
    //check if pos1 has a piece of colour
    string pieceName=board[loc1.row][loc1.col]->getCurrent();
    if (pieceName==""){
        throw Invalid{pos1 + " is empty!"};
    }else if (whatColour(pieceName)!=colour){
        throw Invalid{"Cannot move piece that is not yours!"};
    }

    //for en passant
    if (pieceName[0]=='p' && loc1.row==3 && loc2.row==2 && (loc2.col==loc1.col-1 || loc2.col==loc1.col+1) && board[loc2.row][loc2.col]->getCurrent()==""){
        string targetPiece=board[loc1.row][loc2.col]->getCurrent();
        if (targetPiece!="" && targetPiece[0]=='P' &&
                targetPiece==history[static_cast<int>(history.size())-1][0]){
            if (white[stoi(targetPiece.substr(1))]->getSteps()==1){
                vector<string> newhistory;
                newhistory.push_back(board[loc1.row][loc2.col]->getCurrent());
                newhistory.push_back(targetPiece);
                history.push_back(newhistory);
                unsetPiece(white[stoi(targetPiece.substr(1))],board[loc1.row][loc2.col]);
                unsetPiece(black[stoi(pieceName.substr(1))],board[loc1.row][loc1.col]);
                setPiece(black[stoi(pieceName.substr(1))],board[loc2.row][loc2.col]);
                black[stoi(pieceName.substr(1))]->stepsIncrement();
                td->notify(board[loc1.row][loc1.col]);
                td->notify(board[loc2.row][loc2.col]);
                td->notify(board[loc1.row][loc2.col]);
                //check if the game is over
                if (colour=="white" && (!availableMoves("black"))){
                    if (ifIncheck("black")){
                        result="white";
                        whiteScore++;
                    }else{
                        result="stalemate";
                        whiteScore+=0.5;
                        blackScore+=0.5;
                    }
                }else if (colour=="black" && (!availableMoves("white"))){
                    if (ifIncheck("white")){
                        result="black";
                        blackScore++;
                    }else{
                        result="stalemate";
                        whiteScore+=0.5;
                        blackScore+=0.5;
                    }
                }

                return;
            }
        }
    }
    if (pieceName[0]=='P' && loc1.row==4 && loc2.row==5 && (loc2.col==loc1.col-1 || loc2.col==loc1.col+1) && board[loc2.row][loc2.col]->getCurrent()==""){
        string targetPiece=board[loc1.row][loc2.col]->getCurrent();
        if (targetPiece!="" && targetPiece[0]=='p' &&
                targetPiece==history[static_cast<int>(history.size())-1][0]){
            if (black[stoi(targetPiece.substr(1))]->getSteps()==1){
                vector<string> newhistory;
                newhistory.push_back(board[loc1.row][loc2.col]->getCurrent());
                newhistory.push_back(targetPiece);
                history.push_back(newhistory);
                unsetPiece(black[stoi(targetPiece.substr(1))],board[loc1.row][loc2.col]);
                unsetPiece(white[stoi(pieceName.substr(1))],board[loc1.row][loc1.col]);
                setPiece(white[stoi(pieceName.substr(1))],board[loc2.row][loc2.col]);
                white[stoi(pieceName.substr(1))]->stepsIncrement();
                td->notify(board[loc1.row][loc1.col]);
                td->notify(board[loc2.row][loc2.col]);
                td->notify(board[loc1.row][loc2.col]);
                //check if the game is over
                if (colour=="white" && (!availableMoves("black"))){
                    if (ifIncheck("black")){
                        result="white";
                        whiteScore++;
                    }else{
                        result="stalemate";
                        whiteScore+=0.5;
                        blackScore+=0.5;
                    }
                }else if (colour=="black" && (!availableMoves("white"))){
                    if (ifIncheck("white")){
                        result="black";
                        blackScore++;
                    }else{
                        result="stalemate";
                        whiteScore+=0.5;
                        blackScore+=0.5;
                    }
                }

                return;
            }
        }
    }

    //for castling
    if (pieceName[0]=='K' && loc2.row==loc1.row && (loc2.col==loc1.col-2 || loc2.col==loc1.col+2) && loc1.row==0 && loc1.col==4){//for white King
        if (white[(stoi(pieceName.substr(1)))]->getSteps()==0){//check if king moved
            if (loc2.col==loc1.col-2){//to the left
                if (board[0][0]->getCurrent()[0]=='R' && (white[stoi(board[0][0]->getCurrent().substr(1))])->getSteps()==0){//check if left rook moved
                    bool piecesBetween=false;
                    for (int i=1; i<4;++i){
                        if (board[0][i]->getCurrent()!=""){
                            piecesBetween=true;
                            break;
                        }
                    }
                    if (piecesBetween==false){//check if there is any pieces between king and rook
                        //check if would be in check in these position
                        if (!dangerousFor(board[0][4],"white")){
                            if (!dangerousFor(board[0][3],"white")){
                                if (!dangerousFor(board[0][2],"white")){
                                    //record history
                                    vector<string> newhistory1;//for rook
                                    vector<string> newhistory2;//for king
                                    newhistory1.push_back(board[0][0]->getCurrent());
                                    newhistory1.push_back("");
                                    history.push_back(newhistory1);
                                    newhistory2.push_back(pieceName);
                                    newhistory2.push_back("");
                                    history.push_back(newhistory2);
                                    //move the king
                                    unsetPiece(white[stoi(pieceName.substr(1))],board[0][4]);
                                    setPiece(white[stoi(pieceName.substr(1))],board[0][2]);
                                    white[stoi(pieceName.substr(1))]->stepsIncrement();
                                    td->notify(board[0][4]);
                                    td->notify(board[0][2]);
                                    //move the rook
                                    int rookNo=stoi(board[0][0]->getCurrent().substr(1));
                                    unsetPiece(white[rookNo],board[0][0]);
                                    setPiece(white[rookNo],board[0][3]);
                                    white[rookNo]->stepsIncrement();
                                    td->notify(board[0][0]);
                                    td->notify(board[0][3]);
                                    //check if the game is over
                                    if (colour=="white" && (!availableMoves("black"))){
                                        if (ifIncheck("black")){
                                            result="white";
                                            whiteScore++;
                                        }else{
                                            result="stalemate";
                                            whiteScore+=0.5;
                                            blackScore+=0.5;
                                        }
                                    }else if (colour=="black" && (!availableMoves("white"))){
                                        if (ifIncheck("white")){
                                            result="black";
                                            blackScore++;
                                        }else{
                                            result="stalemate";
                                            whiteScore+=0.5;
                                            blackScore+=0.5;
                                        }
                                    }
                                   return;
                                }
                            }
                        }
                    }
                }
            }else{//to the right
                if (board[0][7]->getCurrent()[0]=='R' && (white[stoi(board[0][7]->getCurrent().substr(1))])->getSteps()==0){//check if left rook moved
                    bool piecesBetween=false;
                    for (int i=5; i<7;++i){
                        if (board[0][i]->getCurrent()!=""){
                            piecesBetween=true;
                            break;
                        }
                    }
                    if (piecesBetween==false){//check if there is any pieces between king and rook
                        //check if would be in check in these position
                        if (!dangerousFor(board[0][4],"white")){
                            if (!dangerousFor(board[0][5],"white")){
                                if (!dangerousFor(board[0][6],"white")){
                                    //record history
                                    vector<string> newhistory1;//for rook
                                    vector<string> newhistory2;//for king
                                    newhistory1.push_back(board[0][7]->getCurrent());
                                    newhistory1.push_back("");
                                    history.push_back(newhistory1);
                                    newhistory2.push_back(pieceName);
                                    newhistory2.push_back("");
                                    history.push_back(newhistory2);
                                    //move the king
                                    unsetPiece(white[stoi(pieceName.substr(1))],board[0][4]);
                                    setPiece(white[stoi(pieceName.substr(1))],board[0][6]);
                                    white[stoi(pieceName.substr(1))]->stepsIncrement();
                                    td->notify(board[0][4]);
                                    td->notify(board[0][6]);
                                    //move the rook
                                    int rookNo=stoi(board[0][7]->getCurrent().substr(1));
                                    unsetPiece(white[rookNo],board[0][7]);
                                    setPiece(white[rookNo],board[0][5]);
                                    white[rookNo]->stepsIncrement();
                                    td->notify(board[0][7]);
                                    td->notify(board[0][5]);
                                    //check if the game is over
                                    if (colour=="white" && (!availableMoves("black"))){
                                        if (ifIncheck("black")){
                                            result="white";
                                            whiteScore++;
                                        }else{
                                            result="stalemate";
                                            whiteScore+=0.5;
                                            blackScore+=0.5;
                                        }
                                    }else if (colour=="black" && (!availableMoves("white"))){
                                        if (ifIncheck("white")){
                                            result="black";
                                            blackScore++;
                                        }else{
                                            result="stalemate";
                                            whiteScore+=0.5;
                                            blackScore+=0.5;
                                        }
                                    }
                                   return;
                                }
                            }
                        }
                    }
                }

            }
        }
    }

    if (pieceName[0]=='k' && loc2.row==loc1.row && (loc2.col==loc1.col-2 || loc2.col==loc1.col+2) && loc1.row==7 && loc1.col==4){//for black King
        if (black[(stoi(pieceName.substr(1)))]->getSteps()==0){//check if king moved
            if (loc2.col==loc1.col-2){//to the left
                if (board[7][0]->getCurrent()[0]=='r' && (black[stoi(board[7][0]->getCurrent().substr(1))])->getSteps()==0){//check if left rook moved
                    bool piecesBetween=false;
                    for (int i=1; i<4;++i){
                        if (board[7][i]->getCurrent()!=""){
                            piecesBetween=true;
                            break;
                        }
                    }
                    if (piecesBetween==false){//check if there is any pieces between king and rook
                        //check if would be in check in these position
                        if (!dangerousFor(board[7][4],"black")){
                            if (!dangerousFor(board[7][3],"black")){
                                if (!dangerousFor(board[7][2],"black")){
                                    //record history
                                    vector<string> newhistory1;//for rook
                                    vector<string> newhistory2;//for king
                                    newhistory1.push_back(board[7][0]->getCurrent());
                                    newhistory1.push_back("");
                                    history.push_back(newhistory1);
                                    newhistory2.push_back(pieceName);
                                    newhistory2.push_back("");
                                    history.push_back(newhistory2);
                                    //move the king
                                    unsetPiece(black[stoi(pieceName.substr(1))],board[7][4]);
                                    setPiece(black[stoi(pieceName.substr(1))],board[7][2]);
                                    black[stoi(pieceName.substr(1))]->stepsIncrement();
                                    td->notify(board[7][4]);
                                    td->notify(board[7][2]);
                                    //move the rook
                                    int rookNo=stoi(board[7][0]->getCurrent().substr(1));
                                    unsetPiece(black[rookNo],board[7][0]);
                                    setPiece(black[rookNo],board[7][3]);
                                    black[rookNo]->stepsIncrement();
                                    td->notify(board[7][0]);
                                    td->notify(board[7][3]);
                                    //check if the game is over
                                    if (colour=="white" && (!availableMoves("black"))){
                                        if (ifIncheck("black")){
                                            result="white";
                                            whiteScore++;
                                        }else{
                                            result="stalemate";
                                            whiteScore+=0.5;
                                            blackScore+=0.5;
                                        }
                                    }else if (colour=="black" && (!availableMoves("white"))){
                                        if (ifIncheck("white")){
                                            result="black";
                                            blackScore++;
                                        }else{
                                            result="stalemate";
                                            whiteScore+=0.5;
                                            blackScore+=0.5;
                                        }
                                    }
                                   return;
                                }
                            }
                        }
                    }
                }
            }else{//to the right
                if (board[7][7]->getCurrent()[0]=='r' && (black[stoi(board[7][7]->getCurrent().substr(1))])->getSteps()==0){//check if left rook moved
                    bool piecesBetween=false;
                    for (int i=5; i<7;++i){
                        if (board[7][i]->getCurrent()!=""){
                            piecesBetween=true;
                            break;
                        }
                    }
                    if (piecesBetween==false){//check if there is any pieces between king and rook
                        //check if would be in check in these position
                        if (!dangerousFor(board[7][4],"black")){
                            if (!dangerousFor(board[7][5],"black")){
                                if (!dangerousFor(board[7][6],"black")){
                                    //record history
                                    vector<string> newhistory1;//for rook
                                    vector<string> newhistory2;//for king
                                    newhistory1.push_back(board[7][7]->getCurrent());
                                    newhistory1.push_back("");
                                    history.push_back(newhistory1);
                                    newhistory2.push_back(pieceName);
                                    newhistory2.push_back("");
                                    history.push_back(newhistory2);
                                    //move the king
                                    unsetPiece(black[stoi(pieceName.substr(1))],board[7][4]);
                                    setPiece(black[stoi(pieceName.substr(1))],board[7][6]);
                                    black[stoi(pieceName.substr(1))]->stepsIncrement();
                                    td->notify(board[7][4]);
                                    td->notify(board[7][6]);
                                    //move the rook
                                    int rookNo=stoi(board[7][7]->getCurrent().substr(1));
                                    unsetPiece(black[rookNo],board[7][7]);
                                    setPiece(black[rookNo],board[7][5]);
                                    black[rookNo]->stepsIncrement();
                                    td->notify(board[7][7]);
                                    td->notify(board[7][5]);
                                    //check if the game is over
                                    if (colour=="white" && (!availableMoves("black"))){
                                        if (ifIncheck("black")){
                                            result="white";
                                            whiteScore++;
                                        }else{
                                            result="stalemate";
                                            whiteScore+=0.5;
                                            blackScore+=0.5;
                                        }
                                    }else if (colour=="black" && (!availableMoves("white"))){
                                        if (ifIncheck("white")){
                                            result="black";
                                            blackScore++;
                                        }else{
                                            result="stalemate";
                                            whiteScore+=0.5;
                                            blackScore+=0.5;
                                        }
                                    }
                                   return;
                                }
                            }
                        }
                    }
                }

            }
        }
    }


    //check if that piece can move to pos2
    int pieceNo=stoi(pieceName.substr(1));
    bool canMove=false;
    if (colour=="white"){           
        for (int i=0; i<white[pieceNo]->nextPosLen();++i){
            if ( white[pieceNo]->nextPosAt(i)==pos2){ 
                canMove=true;
                break;
            }
        }
        if (canMove){
            if (pieceName[0]=='P' && loc2.row==7){//check if needs upgrade
                if (piece==""){
                    throw Invalid{"upgrade"};
                }else if (!validPiece(piece) || piece=="K" || piece=="P" || whatColour(piece)!="white"){
                    throw Invalid{piece + " is not a valid type"};
                }
            }
            if (pieceName[0]=='K' && dangerousFor(board[loc2.row][loc2.col],"white")){
                throw Invalid{"Illegal as it puts your king in check!"};
            }
            move(board[loc1.row][loc1.col],board[loc2.row][loc2.col],white[pieceNo]);
            if (ifIncheck("white")){
                    undo();
                    throw Invalid{"Illegal! in check!"};
            }
            td->notify(board[loc1.row][loc1.col]);
            td->notify(board[loc2.row][loc2.col]);
        }
    }else{
        for (int i=0; i<black[pieceNo]->nextPosLen();++i){
            if ( black[pieceNo]->nextPosAt(i)==pos2){
                canMove=true;
                break;
            }
        }
        if (canMove){
            if (pieceName[0]=='p' && loc2.row==0){
                if (piece==""){//check if needs upgrade
                    throw Invalid{"upgrade"};
                }else if (!validPiece(piece) || piece=="k" || piece=="p" || whatColour(piece)!="black"){
                    throw Invalid{piece + " is not a valid type"};
                }
            }
            if (pieceName[0]=='k' && dangerousFor(board[loc2.row][loc2.col],"black")){
                throw Invalid{"Illegal as it puts your king in check!"};
            }
            move(board[loc1.row][loc1.col],board[loc2.row][loc2.col],black[pieceNo]);
            if (ifIncheck("black")){
                    undo();
                    throw Invalid{"Illegal! in check!"};
            }
            td->notify(board[loc1.row][loc1.col]);
            td->notify(board[loc2.row][loc2.col]);
        }
    }
    if (!canMove){
        throw Invalid{"Illegal Move!"};
    }
    //if that piece is a pawn and needs an upgrade
    if (piece !="" && pieceName[0]=='P' && loc2.row==7){//white
            upgrade(white[pieceNo],board[loc2.row][loc2.col],piece);
            td->notify(board[loc2.row][loc2.col]);
    }else if (piece!="" && pieceName[0]=='p' && loc2.row==0){//black
            upgrade(black[pieceNo],board[loc2.row][loc2.col],piece);
            td->notify(board[loc2.row][loc2.col]);
    }

    //check if the game is over
    if (colour=="white" && (!availableMoves("black"))){
        if (ifIncheck("black")){
            result="white";
            whiteScore++;
        }else{
            result="stalemate";
            whiteScore+=0.5;
            blackScore+=0.5;
        }
    }else if (colour=="black" && (!availableMoves("white"))){
        if (ifIncheck("white")){
            result="black";
            blackScore++;
        }else{
            result="stalemate";
            whiteScore+=0.5;
            blackScore+=0.5;
        }
    }

}



void Move::undo(){
    if (static_cast<int>(history.size())==0){
        throw Invalid{"Already back to initial state!"};
    }
    vector<string> lastMove=history[static_cast<int>(history.size())-1];
    history.pop_back();

    if (lastMove[0][0]=='K'){
        string pos1=white[stoi(lastMove[0].substr(1))]->lastHistoryPos();
        white[stoi(lastMove[0].substr(1))]->popHistoryPos();
        Location loc1=to_Location(pos1);
        if (white[stoi(lastMove[0].substr(1))]->historyPosLen()!=0){
            string pos0=white[stoi(lastMove[0].substr(1))]->lastHistoryPos();
            white[stoi(lastMove[0].substr(1))]->popHistoryPos();
            Location loc0=to_Location(pos0);
            if (loc0.col==loc1.col-2 || loc0.col==loc1.col+2){//castling
                //move the king back to former position
                unsetPiece(white[stoi(lastMove[0].substr(1))], board[loc1.row][loc1.col]);
                setPiece(white[stoi(lastMove[0].substr(1))],board[loc0.row][loc0.col]);
                white[stoi(lastMove[0].substr(1))]->stepsDecrement();
                td->notify(board[loc1.row][loc1.col]);
                td->notify(board[loc0.row][loc0.col]);
                //move the rook back to former position
                undo();
                return;
            }
            white[stoi(lastMove[0].substr(1))]->pushHistoryPos(pos0);
            white[stoi(lastMove[0].substr(1))]->pushHistoryPos(pos1);
        }else{
            white[stoi(lastMove[0].substr(1))]->pushHistoryPos(pos1);
        }
    }else if (lastMove[0][0]=='k'){
        string pos1=black[stoi(lastMove[0].substr(1))]->lastHistoryPos();
        black[stoi(lastMove[0].substr(1))]->popHistoryPos();
        Location loc1=to_Location(pos1);
        if (black[stoi(lastMove[0].substr(1))]->historyPosLen()!=0){
            string pos0=black[stoi(lastMove[0].substr(1))]->lastHistoryPos();
            black[stoi(lastMove[0].substr(1))]->popHistoryPos();
            Location loc0=to_Location(pos0);
            if (loc0.col==loc1.col-2 || loc0.col==loc1.col+2){//castling
                //move the king back to former position
                unsetPiece(black[stoi(lastMove[0].substr(1))], board[loc1.row][loc1.col]);
                setPiece(black[stoi(lastMove[0].substr(1))],board[loc0.row][loc0.col]);
                black[stoi(lastMove[0].substr(1))]->stepsDecrement();
                td->notify(board[loc1.row][loc1.col]);
                td->notify(board[loc0.row][loc0.col]);
                //move the rook back to former position
                undo();
                return;
            }
            black[stoi(lastMove[0].substr(1))]->pushHistoryPos(pos0);
            black[stoi(lastMove[0].substr(1))]->pushHistoryPos(pos1);
         }else{
            black[stoi(lastMove[0].substr(1))]->pushHistoryPos(pos1);
        } 
    }

    if (whatColour(lastMove[0])=="white"){
        string pos1=white[stoi(lastMove[0].substr(1))]->lastHistoryPos();
        white[stoi(lastMove[0].substr(1))]->popHistoryPos();
        Location loc1=to_Location(pos1);
        if (white[stoi(lastMove[0].substr(1))]->historyPosLen()!=0){
            string pos0=white[stoi(lastMove[0].substr(1))]->lastHistoryPos();
            white[stoi(lastMove[0].substr(1))]->popHistoryPos();
            Location loc0=to_Location(pos0);
            unsetPiece(white[stoi(lastMove[0].substr(1))], board[loc1.row][loc1.col]);
            setPiece(white[stoi(lastMove[0].substr(1))],board[loc0.row][loc0.col]);
            white[stoi(lastMove[0].substr(1))]->stepsDecrement();
            td->notify(board[loc1.row][loc1.col]);
            td->notify(board[loc0.row][loc0.col]);
        }else{
            unsetPiece(white[stoi(lastMove[0].substr(1))], board[loc1.row][loc1.col]);
            td->notify(board[loc1.row][loc1.col]);
        }
    }else{
        string pos1=black[stoi(lastMove[0].substr(1))]->lastHistoryPos();
        black[stoi(lastMove[0].substr(1))]->popHistoryPos();
            Location loc1=to_Location(pos1);
        if (black[stoi(lastMove[0].substr(1))]->historyPosLen()!=0){
            string pos0=black[stoi(lastMove[0].substr(1))]->lastHistoryPos();
            black[stoi(lastMove[0].substr(1))]->popHistoryPos();
            Location loc0=to_Location(pos0);
            unsetPiece(black[stoi(lastMove[0].substr(1))], board[loc1.row][loc1.col]);
            setPiece(black[stoi(lastMove[0].substr(1))],board[loc0.row][loc0.col]);
            black[stoi(lastMove[0].substr(1))]->stepsDecrement();
            td->notify(board[loc1.row][loc1.col]);
            td->notify(board[loc0.row][loc0.col]);
        }else{
            unsetPiece(white[stoi(lastMove[0].substr(1))], board[loc1.row][loc1.col]);
            td->notify(board[loc1.row][loc1.col]);
        }
    }

    if (lastMove[1]!=""){//a piece had been captured or upgrade in this move 
        if (whatColour(lastMove[1])=="white"){
            string pos0=white[stoi(lastMove[1].substr(1))]->lastHistoryPos();
            white[stoi(lastMove[1].substr(1))]->popHistoryPos();
            Location loc0=to_Location(pos0);
            setPiece(white[stoi(lastMove[1].substr(1))],board[loc0.row][loc0.col]);
            td->notify(board[loc0.row][loc0.col]);
        }else{
            string pos0=black[stoi(lastMove[1].substr(1))]->lastHistoryPos();
            black[stoi(lastMove[1].substr(1))]->popHistoryPos();
            Location loc0=to_Location(pos0);
            setPiece(black[stoi(lastMove[1].substr(1))],board[loc0.row][loc0.col]);
            td->notify(board[loc0.row][loc0.col]);
        }
    }
}


string Move::getResult(){
    return result;
}


float Move::getWhiteScore(){
    return whiteScore;
}


float Move::getBlackScore(){
    return blackScore;
}


void Move::start(){
    result="";
    clearBoard();
    set("N","b1");
    set("B","c1");
    set("Q","d1");
    set("K","e1");
    set("N","g1");
    set("n","b8");
    set("b","c8");
    set("q","d8");
    set("k","e8");
    set("n","g8");

    for (int i=0; i<8;++i){
        set("P",to_Position(1,i));
        set("p",to_Position(6,i));
    }
    set("B","f1");
    set("r","h8");
    set("r","a8");
    set("R","a1");
    set("R","h1"); 
    set("b","f8");


}


bool Move::ifIncheck(string colour){
    if (colour=="white"){
        for(int i=0; i<static_cast<int>(white.size());++i){
            if (white[i]->getName()=="K"){
                if (ifPosExists(white[i]->getPos())){
                    Location loc=to_Location(white[i]->getPos());
                    return dangerousFor(board[loc.row][loc.col],"white");
                }
            }
        }
    }
    else if(colour=="black"){
        for(int i=0; i<static_cast<int>(black.size());++i){
            if (black[i]->getName()=="k"){
                if (ifPosExists(black[i]->getPos())){
                    Location loc=to_Location(black[i]->getPos());
                    return dangerousFor(board[loc.row][loc.col],"black");
                }
            }
        }
    }
    return false;
}


void Move::setUpCheck(){
    string msg;//invalid msg
    if (ifIncheck("white")){
        msg=msg+"White King is in check!\n";
    }
    if (ifIncheck("black")){
        msg=msg+"Black King is in check!\n";
    }
    for (int i=0; i<8; ++i){
        if (board[0][i]->getCurrent()[0]=='p' ||
            board[0][i]->getCurrent()[0]=='P'){
            msg=msg+"Pawns in the first row!\n";
        }
        if (board[7][i]->getCurrent()[0]=='p' ||
            board[7][i]->getCurrent()[0]=='P'){
            msg=msg+"Pawns in the last row!\n";
        }
    }
    int numWK=0;
    int numBK=0;
    for (int i=0; i<8;++i){
        for (int j=0; j<8;++j){
            if (board[i][j]->getCurrent()[0]=='k'){
                numBK++;
            }else if (board[i][j]->getCurrent()[0]=='K'){
                numWK++;
            }
        }
    }
    if (numWK!=1){ msg=msg+"There should be one and only one White King.\n";}
    if (numBK!=1){ msg=msg+"There should be one and only one Black King.\n";}

    if (msg!=""){
        throw Invalid{msg};
    }
}

void Move::whiteResign(){
    blackScore++;
}

void Move::blackResign(){
    whiteScore++;
}

void Move::move(Player* computer){
    computer->generateMove(white,black,board);
}
