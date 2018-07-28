#include <iostream>
#include "move.h"
#include "player.h"
#include "human.h"
#include "computer1.h"
#include "textdisplay.h"
#include "graphics.h"
#include "tools.h"
using namespace std;

int main(){
    //set up essential elements
    Graphics* g=new Graphics{};
    TextDisplay* td= new TextDisplay{};
    Move* m=new Move{td,g};
    m->BoardSetUp();//set up board
    Player* white=nullptr;
    Player* black=nullptr;
    bool ifStart=false;//whether a game is started.
    bool ifRunning=false;//whether a game is currently running
    string whosTurn="white";

    string command;
    //read in commands
    while(cin>>command){

        if (command=="game" && ifRunning==false){

            //check if inputs are illegal
            string whitePlayer,blackPlayer;
            cin>>whitePlayer>>blackPlayer;
            if (whitePlayer != "human" && whitePlayer !="computer[1]"){
                cout<<whitePlayer<<" is not a valid player type!"<<endl;
                continue;
            }
            if (blackPlayer != "human" && blackPlayer !="computer[1]"){
                cout<<blackPlayer<<" is not a valid player type!"<<endl;
                continue;
            }

            //starts a new game
            delete white;
            delete black;
            ifStart=true;
            whosTurn="white";
            m->start();
            cout<<*td<<endl;
            //white player
            if (whitePlayer=="human"){
                white=new Human{"white",m};
            }else if (whitePlayer=="computer[1]"){
                white=new Computer1{"white",m};
            }else if (whitePlayer=="computer[2]"){

            }else if (whitePlayer=="computer[3]"){

            }else{

            }
            //black player
            if (blackPlayer=="human"){
                black=new Human{"black",m};
            }else if (blackPlayer=="computer[1]"){
                black=new Computer1{"black",m};
            }else if (blackPlayer=="computer[2]"){

            }else if (blackPlayer=="computer[3]"){

            }else{

            }
            continue;

        }else if (command=="resign" && ifStart==true){
            ifRunning=false;
            ifStart=false;
            if (whosTurn=="white"){
                m->whiteResign();
                cout<<"Black wins!"<<endl;
            }else{
                m->blackResign();
                cout<<"White wins!"<<endl;
            }
            continue;

        }else if (command=="move" && ifStart==true){
            string pos1,pos2,piece;
            if (whosTurn=="white"){
                try{
                    white->move();
                }catch(...){
                    cin>>pos1>>pos2;
                    try{
                        white->move(pos1,pos2);
                    }catch(Invalid& in){
                        if (in.msg=="upgrade"){
                            cin>>piece;
                            try{
                                white->move(pos1,pos2,piece);
                            }catch(Invalid& in){
                                cout<<in.msg<<endl;
                                continue;
                            }
                        }else{
                            cout<<in.msg<<endl;
                            continue;
                        }
                    }
                }
            }else{
                try{
                    black->move();
                }catch(...){
                    cin>>pos1>>pos2;
                    try{
                        black->move(pos1,pos2);
                    }catch(Invalid& in){
                        if (in.msg=="upgrade"){
                            cin>>piece;
                            try{
                                black->move(pos1,pos2,piece);
                            }catch(Invalid& in){
                                cout<<in.msg<<endl;
                                continue;
                            }
                        }else{
                            cout<<in.msg<<endl;
                            continue;
                        }
                    }
                }
            }
            cout<<*td<<endl;
            //check if the game is over
            string result=m->getResult();
            if (result !=""){
                ifStart=false;
                ifRunning=false;
                if (result=="white"){
                    cout<<"Checkmate! White wins!"<<endl;
                    continue;
                }else if (result=="black"){
                    cout<<"Checkmate! Black wins!"<<endl;
                    continue;
                }else{
                    cout<<"Stalemate!"<<endl;
                    continue;
                }
            }

            ifRunning=true;
            if (whosTurn=="white"){
                whosTurn="black";
                if (m->ifIncheck(whosTurn)){
                    cout<<"Black is in check."<<endl;
                }
            }else{
                whosTurn="white";
                if (m->ifIncheck(whosTurn)){
                    cout<<"White is in check."<<endl;
                }
            }
            continue;

        }else if (command=="setup" && ifStart==true && ifRunning==false){
            m->clearBoard();
            cout<<*td<<endl;
            string keyword;
            while(cin>>keyword){
                if (keyword!= "+" && keyword!="-" && keyword!="=" && keyword!="done"){
                    cout<<keyword<<" is not a legal set up operation."<<endl;
                    continue;
                }else if (keyword=="+"){
                    string piece,pos;
                    cin>>piece>>pos;
                    try{
                        m->set(piece,pos);
                        cout<<*td<<endl;
                    }catch(Invalid& in){
                        cout<<in.msg<<endl;
                        continue;
                    }
                    continue;
                }else if (keyword=="-"){
                    string pos;
                    cin>>pos;
                    try{
                        m->unset(pos);
                        cout<<*td<<endl;
                    }catch(Invalid& in){
                        cout<<in.msg<<endl;
                        continue;
                    }
                    continue;
                }else if (keyword=="="){
                    string colour;
                    cin>>colour;
                    if (colour=="white"){
                        whosTurn="white";
                    }else if (colour=="black"){
                        whosTurn="black";
                    }else{
                        cout<<colour<<" is not a valid colour."<<endl;
                    }
                    continue;
                }else if (keyword=="done"){
                    try{
                        m->setUpCheck();
                        break;
                    }catch(Invalid& in){
                        cout<<in.msg<<endl;
                    }
                    continue;
                }
            }
            continue;

        }else if (command=="undo" && ifRunning==true){
            try{
                m->undo();
                cout<<*td<<endl;
                if (whosTurn=="white"){
                    whosTurn="black";
                }else{
                    whosTurn="white";
                }
            }catch(Invalid& in){
                cout<<in.msg<<endl;
            }
            continue;
        }else{
            cout<<"Illegal Command"<<endl;
            continue;
        }

    }
    //print the score
    cout<<"Final Score: "<<endl;
    cout<<"White: "<<(white?white->getScore():0)<<endl;
    cout<<"Black: "<<(black?black->getScore():0)<<endl;

    //delete heap memory
    delete white;
    delete black;
    delete td;
    delete m;
    delete g;

}

