#include "player.h"
#include "move.h"
#include <string>
using namespace std;

Player::Player(string colour, Move* m):colour{colour},m{m}{}

Player::~Player(){}

string Player::getColour(){
    return colour;
}

float Player::getScore(){
    float score;
    if (colour=="white"){
        score=m->getWhiteScore();
    }else{
        score=m->getBlackScore();
    }
    return score;
}
