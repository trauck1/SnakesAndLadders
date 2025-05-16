// UMBC - CMSC 341 - Fall 2024 - Proj1
#include "snakes.h"
Snakes::Snakes(){ 
    m_start = nullptr;
    m_player1 = nullptr;
    m_player2 = nullptr;
    m_playerTurn = NOGAME;
}
Snakes::~Snakes(){
    clear();
}
void Snakes::clear(){
    m_player1 = nullptr;
    m_player2 = nullptr;
    m_playerTurn = NOGAME;
    Cell *temp = m_start;
    //deletes each position on the board
    while(m_start != nullptr){
        temp = m_start->m_next;
        delete m_start;
        m_start = temp;
    }
    m_start = nullptr;
}
const Snakes & Snakes::operator=(const Snakes & rhs){
    clear();
    //if the rhs board is occupied
    if(rhs.m_start != nullptr){
        Cell *temp = rhs.m_start;
        Cell * cellData = temp;
        m_playerTurn = rhs.m_playerTurn;
        int counter = 1;
        Cell * prev = m_start;
        //creates the board
        while(temp != nullptr){
            cellData = new Cell;
            if(counter == 1){
                m_start = cellData;
                prev = m_start;
            }
            cellData->setID(counter);
            prev->setNext(cellData);
            temp = temp->m_next;
            prev = prev->m_next;
            counter++;
        }
        Cell *original = rhs.m_start;
        Cell *copy = m_start;
        //sets the snakes and ladders
        while(original != nullptr){
            //sets the snakes
            if(original->getSouth() != nullptr){
                int snakeValue = original->getSouth()->getID();
                Cell *snakeMaker = m_start;
                for(int i = 1; i <snakeValue;i++){
                    snakeMaker = snakeMaker->m_next;
                }
                copy->setSouth(snakeMaker);
            }
            //sets the ladders
            else if(original->getNorth()){
                int ladderValue = original->getNorth()->getID();
                Cell *ladderMaker = m_start;
                for(int i = 1; i < ladderValue; i++){
                    ladderMaker = ladderMaker->m_next;
                }
                copy->setNorth(ladderMaker);
            }
            original = original->m_next;
            copy = copy->m_next;

        }
        m_player1 = m_start;
        m_player2 = m_start;
    //if the rhs board is empty
    }else{
        m_start = nullptr;
        m_player1 = nullptr;
        m_player2 = nullptr;
        m_playerTurn = NOGAME;
    }
    return *this;
}


int Snakes::rollDice(){
    m_dice.init(1,6);
    int randomRoll = m_dice.getRandNum();
    return randomRoll;
}
Snakes::Snakes(int boardSize){
    m_start = nullptr;
    makeDefaultBoard(boardSize);

}
bool Snakes::makeDefaultBoard(int boardSize){
    if(m_start == nullptr){
        m_playerTurn = PLAYER1TURN;
        int sqrtOfBoardSize;
        int snakeOrLadderTurn = 0; 
        // alternates between adding snakes and ladders
        //snakes and ladders are 3 nodes long
        int defaultDifference = 3;
        m_start = nullptr;
        //if the boardSize isn't valid, creates an empty board
        if(boardSize < 9){
            m_start = nullptr;
            m_player1 = nullptr;
            m_player2 = nullptr;
            m_playerTurn = NOGAME;
            return false;
        }else{
            //if the boardSize isn't a perfect square
            //set the boardSize to the closest perfect square
            sqrtOfBoardSize = sqrt(boardSize);
            boardSize = (sqrtOfBoardSize*sqrtOfBoardSize);
            
        }
        //creates the board without the snakes and ladders
        for(int i = 1; i <= boardSize; i++){
            Cell *node = new Cell;
            //sets the id, but pointers are set to default values temporarily
            node->setID(boardSize + 1 -i);
            node->setNext(nullptr);
            node->setSouth(nullptr);
            node->setNorth(nullptr);
            if(m_start == nullptr){
                m_start = node;
            }else{
                node->m_next = m_start;
                m_start = node;
            }
        }
        //adds the snakes and ladders
        Cell *temp = m_start;
        //doesn't iterate the first or last space on the board because 
        //no ladders or snakes can be placed there
        for(int i = 2; i < boardSize; i++){
            if((i % 4) == 3){ //every 4 is a ladder or snake
                    if(snakeOrLadderTurn % 2 == 0){//creates ladder
                        Cell *ladderEnd = temp;
                        if((i + defaultDifference) < boardSize){
                            for(int x = 0; x < defaultDifference; x++){
                                ladderEnd = ladderEnd->m_next;
                            }
                            if(ladderEnd->getID() < boardSize || ladderEnd->getID() >= 1){
                                temp->setNorth(ladderEnd);
                            }
                        }

                    }else{//creates snake
                        Cell *snakeEnd = m_start;
                        int snakeEndLocation = i - defaultDifference;
                        for(int x = 1; x < snakeEndLocation; x++){
                            snakeEnd = snakeEnd->m_next;
                        }
                        if(snakeEnd->getID() < boardSize || snakeEnd->getID() >= 1){
                            temp->setSouth(snakeEnd);
                        }
                }
                snakeOrLadderTurn++;
            }
            temp = temp->m_next;
        }
        m_player1 = m_start;
        m_player2 = m_start;
        return true;
    }
    //returns false if no board is made
    return false;
}
void Snakes::makeRandomBoard(int boardSize, int numSnakesLadders){
    clear();
    //random id of start of ladder and head of snake
    int randomStart = 0;
    int randomHead = 0;
    int sqrtOfBoardSize;
    int snakeOrLadderTurn = 0;
    //the board can't be smaller than 9
    if(boardSize >= 9){
        m_playerTurn = PLAYER1TURN;
        //makes sure the board size is a perfect square
        sqrtOfBoardSize = sqrt(boardSize);
        boardSize = (sqrtOfBoardSize*sqrtOfBoardSize);
        //makes sure the number of Snakes and ladders is in the allowed range
        if (numSnakesLadders < 2){
        numSnakesLadders = 2;
    }else if(numSnakesLadders > ((boardSize / 2) - 2)){
        numSnakesLadders = ((boardSize / 2) - 2);
    }
        //creates an empty board without the snakes and ladders
        for(int i = 1; i <= boardSize; i++){
            Cell *node = new Cell;
            node->setID(boardSize + 1 -i);
            node->setNext(nullptr);
            node->setSouth(nullptr);
            node->setNorth(nullptr);
            if(m_start == nullptr){
                m_start = node;
            }else{
                node->m_next = m_start;
                m_start = node;
        }
    }
    m_player1 = m_start;
    m_player2 = m_start;
    //add the snakes and ladders to the board
    for(int i = 0; i < numSnakesLadders; i++){
        if(i % 2 == 0){//makes a ladder
            bool validLadder = false;
            bool validDistance = false;
            //tries different ladder positions until it finds a valid one
            while(validLadder == false || validDistance == false){
                Cell *startOfLadder = m_start;
                //Uses the random class to get a randomized position on the board
                m_dice.init(2, boardSize - 2);
                m_dice.setSeed(random_device{}());
                randomStart = m_dice.getRandNum();
                //puts the start of the ladder at the correct id
                for(int i = 1; i < randomStart; i++){
                    startOfLadder = startOfLadder->m_next;
                }
                //checks if the start of the ladder is already the start of a snake or ladder
                if(startOfLadder->getNorth() != 0
                || startOfLadder->getSouth() != 0
                || startOfLadder->getID() <= 1 
                || startOfLadder->getID() >= (boardSize -2)){
                    validLadder = false;
                }else{
                    Cell *startChecker = m_start;
                    validLadder = true;
                    //checks if the startOfLadder is the end of any snakes or ladders
                    for(int i = 1; i <= boardSize; i++){
                        if(startChecker->getNorth() == startOfLadder 
                        || startChecker->getSouth() == startOfLadder){
                            validLadder = false;
                        }
                        startChecker = startChecker->m_next;
                    }
                }
                m_dice.init(randomStart, boardSize - 1);
                m_dice.setSeed(random_device{}());
                int randomEnd = m_dice.getRandNum();
                Cell *endOfLadder = m_start;
                for(int i = 0; i < randomEnd; i++){
                    endOfLadder = endOfLadder->m_next;
                }
                //validates the endOfLadder
                if(endOfLadder->getNorth() == nullptr 
                && endOfLadder->getSouth() == nullptr 
                && endOfLadder->getID() > 2
                && endOfLadder->getID() < (boardSize - 1)){
                    validDistance = true;
                    Cell *endChecker = m_start;
                    for(int i = 1; i <= boardSize; i++){
                        if(endChecker->getNorth() == endOfLadder 
                        || endChecker->getSouth() == endOfLadder){
                            validDistance = false;
                        }
                        endChecker = endChecker->m_next;
                }
            }
            //if the starting and ending position on the ladder is valid, create the ladder
            if(validLadder == true && validDistance == true){
                startOfLadder->setNorth(endOfLadder);
            }
            }
        }else{//makes a snake
            bool validHead = false;
            bool validTail = false;
            while(validHead == false || validTail == false){
                Cell *snakeHead = m_start;
                m_dice.init(3, boardSize - 1);
                m_dice.setSeed(random_device{}());
                randomHead = m_dice.getRandNum();
                for(int i = 0; i < randomHead; i++){
                    snakeHead = snakeHead->m_next;
                    }
                //validate the snakeHead
                if(snakeHead->getNorth() != 0
                || snakeHead->getSouth() != 0
                || snakeHead->getID() <= 2
                || snakeHead->getID() >= (boardSize - 1)){
                    validHead = false;
                }else{
                    validHead = true;
                    Cell *headChecker = m_start;
                    for(int i = 1; i <= boardSize; i++){
                        if(headChecker->getSouth() == snakeHead 
                        || headChecker->getNorth() == snakeHead){
                            validHead = false;
                        }
                        headChecker = headChecker->m_next;
                    }
                }
                 m_dice.init(2, randomHead - 1);
                m_dice.setSeed(random_device{}());
                int randomTail = m_dice.getRandNum();
                Cell *tailOfSnake = m_start;
                for(int i = 0; i < randomTail; i++){
                    tailOfSnake = tailOfSnake->m_next;
                }
                //validates the tail of the snake
                if(tailOfSnake->getSouth() == nullptr
                && tailOfSnake->getNorth() == nullptr
                && tailOfSnake->getID() > 1
                && tailOfSnake->getID() < (boardSize - 2)){
                    validTail = true;
                    Cell *tailChecker = m_start;
                    for(int i = 0; i < boardSize; i++){
                        if(tailChecker->getNorth() == tailOfSnake 
                        || tailChecker->getSouth() == tailOfSnake){
                            validTail = false;
                        }
                        tailChecker = tailChecker->m_next;
                    }
                }
                //if the head and tail are valid, create the snake
                if(validHead == true && validTail == true){
                    snakeHead->setSouth(tailOfSnake);
                }
            }

        }
    }
    }
}


bool Snakes::play(int dice){
    int iterator = 0;
    //checks if the dice amount is in range
    if(dice > 6){
        dice = 6;
    }else if(dice < 1){
        dice = 1;
    }
    //player 1 move
    if(m_playerTurn == PLAYER1TURN){
        //moves the player the correct amount of moves or until it reaches the end
        while(iterator != dice && m_player1->m_next != nullptr){
            m_player1 = m_player1->m_next;
            iterator++;
        }
        //if the player reaches the end
        if(m_player1->m_next == nullptr){
            return false;
        }else{
            //if the player lands on a snake or ladder
            if(m_player1->getSouth() != nullptr){
                m_player1 = m_player1->getSouth();
            }else if(m_player1->getNorth() != nullptr){
                m_player1 = m_player1->getNorth();
            }
        }
        m_playerTurn++;
        return true;
    //player two
    }else if(m_playerTurn == PLAYER2TURN){
        while(iterator != dice && m_player2->m_next != nullptr){
            m_player2 = m_player2->m_next;
            iterator++;
        }
        //if the player reaches the end
        if(m_player2->m_next == nullptr){
            return false;
        }else{
            //if the player lands on a snake or ladder
            if(m_player2->getSouth() != nullptr){
                m_player2 = m_player2->getSouth();
            }else if(m_player2->getNorth() != nullptr){
                m_player2 = m_player2->getNorth();
            }
        }
        m_playerTurn--;
        return true;
    }
    return true;
}
void Snakes::reStart(){ 
    //if the board isn't empty, set the players back to the beginning and
    //reset the turns
    if(m_start != nullptr){
        m_player1 = m_start;
        m_player2 = m_start;
        m_playerTurn = PLAYER1TURN;
    }
}
void Snakes::dumpBoard(){
    if (m_start != nullptr){
        int ladderCode, snakeCode;
        Cell *temp = m_start;
        cout << "START => ";
        while(temp != nullptr){
            cout << temp->m_cellID;

            if (temp == m_player1) cout << " (Player 1)";
            if (temp == m_player2) cout << " (Player 2)";
            if (temp->m_north != nullptr) ladderCode = temp->m_north->m_cellID;
            else ladderCode = -1;
            if (temp->m_south != nullptr) snakeCode = temp->m_south->m_cellID;
            else snakeCode = -1;
            if (ladderCode != -1 || snakeCode != -1){
                cout << " (";
                if (ladderCode != -1) cout << "\033[1;32mLadder to: " << ladderCode << "\033[0m";// green text
                if (snakeCode != -1) cout << "\033[1;31mSnake to: " << snakeCode << "\033[0m";//red text
                cout << ")";
            }
            cout << " => ";
            temp = temp->m_next;
        }
        cout << "END" << endl;
    }
}
