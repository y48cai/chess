#include "human.h"
#include "player.h"
#include "move.h"
#include "tools.h"
#include <string>
using namespace std;

Human::Human(string colour, Move* m):Player(colour,m){}

void Human::move(string pos1, string pos2, string piece){
    if (pos1==""){
        throw Invalid{"human"};
    }
    try{
        m->move(getColour(),pos1,pos2,piece);
    }catch(Invalid& in){
        throw in;
    }
}
