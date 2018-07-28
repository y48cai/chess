#include "computer1.h"
#include "player.h"
#include "move.h"
#include "piece.h"
#include "tools.h"
#include "cell.h"
#include <string>
#include <stdlib.h>
using namespace std;

Computer1::Computer1(string colour, Move* m): Player(colour,m){}

void Computer1::move(string pos1, string pos2, string piece){
    m->move(this);
}

void Computer1::generateMove(std::vector<Piece*>& white, std::vector<Piece*>& black, std::vector<std::vector<Cell*>>& board){
    if (getColour()=="white"){
        int size=static_cast<int>(white.size());
        for(int i=rand()%size; i<size; ++i){
            if (white[i]->getPos()!="" && white[i]->nextPosLen()!=0){
                for (int j=0; j<white[i]->nextPosLen(); ++j){
                    try{
                        m->move("white",white[i]->getPos(),white[i]->nextPosAt(j));
                        return;
                    }catch(Invalid& in){
                        if (in.msg=="upgrade"){
                            try{
                                m->move("white",white[i]->getPos(),white[i]->nextPosAt(j),"Q");
                            }catch(...){
                            }
                        }
                    }
                }
            }
            if (i==size-1){i=0;}
        }
    }else{
        int size=static_cast<int>(black.size());
        for(int i=rand()%size; i<size; ++i){
            if (black[i]->getPos()!="" && black[i]->nextPosLen()!=0){
                for (int j=0; j<black[i]->nextPosLen(); ++j){
                    try{
                        m->move("black",black[i]->getPos(),black[i]->nextPosAt(j));
                        return;
                    }catch(Invalid& in){
                        if (in.msg=="upgrade"){
                            try{
                                m->move("black",black[i]->getPos(),black[i]->nextPosAt(j),"q");
                            }catch(...){
                            }
                        }
                    }
                }
            }
            if (i==size-1){i=0;}
        }
    }

}


