// UMBC - CMSC 341 - Fall 2024 - Proj1
#include "snakes.h"
using namespace std;
/*class Tester{
public:

};*/
int main(){
    cout << "Creating a 5x5 board with a default number of snakes and ladders:" << endl << endl;
    Snakes game(16);
    //game.makeRandomBoard(25, 5);
    game.dumpBoard();
    Snakes games;
    games = game;
   games.dumpBoard();
    cout << "Player 1 gets a 3, and player 2 gets a 6:" << endl << endl;
    games.play(6);// player 1
    games.play(6);// player 2
    games.dumpBoard();
    games.play(6);
    games.play(6);
    games.play(6);
    cout << "** COPY BOARD" << endl;
    games.dumpBoard();
    cout << "**ORIGINAL BOARD" << endl;
    game.dumpBoard();
    // game.rollDice();
    // game.rollDice();
    // game.rollDice();
   
    return 0;
}
