// UMBC - CMSC 341 - Fall 2024 - Proj1
#include "snakes.h"
using namespace std;

class Tester{
    public:
        //this tests the values of boards with the size 16
        // this function will be used to test validBoard and the nonPerfectSquareBoard
        bool validBoardTester(const Snakes& board);
        //This tests boards that should be empty
        // this function will be used on emptyBoard and invalidSizeBoard
        bool emptyBoardTester(const Snakes& board);
        //This function tests the reStart function
        // the test calls play two times to move the player pointers,
        // then call restart and test if the players are reset
        bool validReStartTest(Snakes& board);
        //This function tests if reStart is called on an empty board
        //If an empty board is passed, no changes should be made.
        bool errorReStartTest(Snakes& board);
        //This function tests different cases of the play function
        // This function tests if a player lands on a normal space, snake and a ladder
        bool playTest(Snakes& board);
        //This function tests when one of the pieces reaches the end 
        //using the play function
        bool playLastSpaceTest(Snakes& board);
        //This function tests the defaultBoard function
        //An empty board is passed in and turned into a default board, then tested
        bool defaultBoardTest(Snakes& board);

        //this tests error cases for randomBoard
        //tests if the boardSize is lower than 9 and if the amount of snakes is invalid
        bool errorCaseRandomBoardTest(Snakes& board);
        //this function tests a normal case for the randomBoard function
        //tests the attributes in the randomBoard
        bool normalCaseRandomBoardTest(Snakes& board);
        //this function tests the normal case for overloaded assignment operator
        //the function compares an original valid board with a copied board
        bool normalOverloadedTest(Snakes& copy, Snakes& original);
        //this function tests the edge cases for the overloaded assignmnet operator
        //the function compares an empty board and a copied version of the empty board
        bool edgeOverloadedTest(Snakes& copy, Snakes& original);
        //this function tests the clear function
        //this function clears a default board and tests if it is cleared
        bool clearTest(Snakes&board);
};
   

int main(){
    int testsPassed = 0;
    const int totalTests = 14;
    Snakes validBoard(16);
    Snakes invalidSizeBoard(8);
    Snakes nonPerfectSquareBoard(18);
    Snakes emptyBoard;
    Snakes validBoardCopy;
    validBoardCopy = validBoard;
    Snakes emptyBoardCopy;
    emptyBoardCopy = emptyBoard;
    Tester tester;
    if(tester.validBoardTester(validBoard) == true){
        testsPassed++;
        cout << "Test passed for defaultBoard!" << endl;
    }else{
        cout <<"Test has failed for defaultBoard." << endl;
    }
    if(tester.validBoardTester(nonPerfectSquareBoard) == true){
        testsPassed++;
        cout << "Test passed for nonPerfectSquareBoard!" << endl;
    }else{
        cout <<"Test has failed for nonPerfectSquareBoard." << endl;
    }
    if(tester.emptyBoardTester(emptyBoard) == true){
        testsPassed++;
        cout << "Test passed for emptyBoard!" << endl;
    }else{
        cout <<"Test has failed for emptyBoard." << endl;
    }
    if(tester.emptyBoardTester(invalidSizeBoard) == true){
        testsPassed++;
        cout << "Test passed for invalidSizeBoard!" << endl;
    }else{
        cout <<"Test has failed for invalidSizeBoard." << endl;
    }
    if(tester.validReStartTest(validBoard) == true){
         testsPassed++;
        cout << "Test passed for valid reStart!" << endl;
    }else{
        cout << "Test failed for valid reStart." << endl;
    }
    if(tester.errorReStartTest(emptyBoard) == true){
         testsPassed++;
        cout << "Test passed for error reStart!" << endl;
    }else{
        cout << "Test failed for error reStart." << endl;
    }
    if(tester.playTest(validBoard) == true){
         testsPassed++;
        cout << "Test passed for play!" << endl;
    }else{
        cout << "Test failed for play." << endl;
    }
    if(tester.playLastSpaceTest(validBoard) == true){
         testsPassed++;
        cout << "Test passed for last space in play!" << endl;
    }else{
        cout << "Test failed for last space in play." << endl;
    }
    if(tester.defaultBoardTest(emptyBoard) == true){
         testsPassed++;
        cout << "Test passed for default board!" << endl;
    }else{
        cout << "Test failed for default board." << endl;
    }
    if(tester.errorCaseRandomBoardTest(emptyBoard) == true){
         testsPassed++;
        cout << "Test passed for error cases in random board!" << endl;
    }else{
        cout << "Test failed for error cases in random board." << endl;
    }
    if(tester.normalCaseRandomBoardTest(emptyBoard) == true){
         testsPassed++;
        cout << "Test passed for normal cases in random board!" << endl;
    }else{
        cout << "Test failed for normal cases in random board." << endl;
    }
    if(tester.normalOverloadedTest(validBoardCopy, validBoard) == true){
         testsPassed++;
        cout << "Test passed for normal overloaded constructor!" << endl;
    }else{
        cout << "Test failed for normal overloaded constructor." << endl;
    }
    if(tester.edgeOverloadedTest(emptyBoardCopy, emptyBoard) == true){
         testsPassed++;
        cout << "Test passed for edge overloaded constructor!" << endl;
    }else{
        cout << "Test failed for edge overloaded constructor." << endl;
    }
    if(tester.clearTest(validBoard) == true){
         testsPassed++;
        cout << "Test passed for clear!" << endl;
    }else{
        cout << "Test failed for clear." << endl;
    }
    if(testsPassed == totalTests){
        cout << "All tests passed!" << endl;
    }else{
        cout << "Not all tests passed" << endl;
    }
    return 0;
}
 bool Tester::validBoardTester(const Snakes& board){
        if(board.m_start != nullptr && board.m_playerTurn == PLAYER1TURN
        && board.m_player1 == board.m_start && board.m_player2 == board.m_start){
            int counter = 0;
            int snakeLadderCounter = 0;
            Cell* temp = board.m_start;
            while(temp != nullptr){
                if(temp->m_south != nullptr || temp->m_north != nullptr){
                    snakeLadderCounter++;
                }
                counter++;
                temp = temp->m_next;
            }
            if(counter == 16 && snakeLadderCounter == 4){
                return true;
            }
        }
        return false;
    }
    bool Tester::emptyBoardTester(const Snakes& board){
        if(board.m_start == nullptr && board.m_player1 == nullptr 
        && board.m_player2 == nullptr && board.m_playerTurn == NOGAME){
            return true;
        }
        return false;
    }

    bool Tester::validReStartTest(Snakes& board){
        bool validMove = false;
        bool validReset = false;
        board.play(1);
        board.play(1);
        //tests to see if the pieces have moved from the first space and are still on the board
        if(board.m_player1 != board.m_start && board.m_player2 != board.m_start
        && board.m_player1 != nullptr && board.m_player2 != nullptr){
            validMove = true;
        }
        board.reStart();
        //tests to see if the players are reset
        if(board.m_player1 == board.m_start && board.m_player2 == board.m_start 
        && board.m_playerTurn == PLAYER1TURN){
            validReset = true;
        }
        if(validReset && validMove){
            return true;
        }
        return false;
    }
    
    bool Tester::errorReStartTest(Snakes& board){
        bool emptyBoard = false;
        bool noChanges = false;
        if(board.m_start == nullptr && 
        board.m_playerTurn == NOGAME &&
        board.m_player1 == nullptr &&
        board.m_player2 == nullptr){
            emptyBoard = true;
        }
        board.reStart();
        if(board.m_start == nullptr && 
        board.m_playerTurn == NOGAME &&
        board.m_player1 == nullptr &&
        board.m_player2 == nullptr){
            noChanges = true;
        }
        if(emptyBoard && noChanges){
            return true;
        }
        return false;
    }

    bool Tester::playTest(Snakes& board){
        bool validLadder = false;
        bool validSnake = false;
        bool validMove = false;
        //This moves player1 onto a ladder to space 5
        board.play(1);
        //This moves player1 onto a ladder to space 4
        board.play(5);
        if(board.m_player1->getID() == 5){
            validLadder = true;
        }
        if(board.m_player2->getID() == 4){
            validSnake = true;
        }
        //This moves player 1 to space 7
        board.play(2);
        if(board.m_player1->getID() == 7){
            validMove = true;
        }
        if(validMove && validLadder && validSnake){
            return true;
        }
        return false;
    }

    bool Tester::playLastSpaceTest(Snakes& board){
        //resets the board
        board.reStart();
        //moves player 1 and 2 to position 5
        board.play(1);
        board.play(1);
        //moves player1 and 2 to position 13
        board.play(5);
        board.play(5);
        //should move both players to the end position and return false
        bool playerOneEnd = board.play(6);
        bool playerTwoEnd = board.play(6);
        if(!playerOneEnd && !playerTwoEnd){
            return true;
        }
        return false;
    }

    bool Tester::defaultBoardTest(Snakes& board){
        bool emptyBoard = false;
        if(board.m_start == nullptr && 
        board.m_playerTurn == NOGAME &&
        board.m_player1 == nullptr &&
        board.m_player2 == nullptr){
            emptyBoard = true;
        }
        //creates a default board with 25 spaces
        board.makeDefaultBoard(25);
        if(board.m_start != nullptr && board.m_playerTurn == PLAYER1TURN
        && board.m_player1 == board.m_start && board.m_player2 == board.m_start){
            int counter = 0;
            int snakeLadderCounter = 0;
            Cell* temp = board.m_start;
            while(temp != nullptr){
                if(temp->m_south != nullptr || temp->m_north != nullptr){
                    snakeLadderCounter++;
                }
                counter++;
                temp = temp->m_next;
            }
            if(counter == 25 && snakeLadderCounter == 6 && emptyBoard){
                return true;
            }
        }

        //sets the board back to empty
        board.clear();
        return false;
    }
    bool Tester::errorCaseRandomBoardTest(Snakes& board){
        bool invalidBoardSize = false;
        //for testing when the amount of snakes and ladders is above or below the mac
        bool tooLow = false;
        bool tooHigh = false;
        int snakeLadderCounter = 0;
        const int boardSize = 25;
        int minSnakeLadder = 2;
        int maxSnakeLadder = (boardSize / 2) - 2;
        //There should be no changes made to this board
        //invalid board size
        board.makeRandomBoard(8, 2);
         if(board.m_start == nullptr && board.m_player1 == nullptr 
        && board.m_player2 == nullptr && board.m_playerTurn == NOGAME){
            invalidBoardSize = true;
        }
        //snakes and ladder amount below min
        board.makeRandomBoard(25, 0);
        Cell *lowTemp = board.m_start;
        int counter = 0;
        while(lowTemp != nullptr){
            counter++;
            if(lowTemp->m_south != nullptr || lowTemp->m_north != nullptr){
                snakeLadderCounter++;
            }
            lowTemp = lowTemp->m_next;
        }
        if(snakeLadderCounter == minSnakeLadder && counter == boardSize){
            tooLow = true;
        }
        //snakes and ladders amount above max
        board.makeRandomBoard(25, 100);
        Cell *highTemp = board.m_start;
        counter = 0;
        snakeLadderCounter = 0;
        while(highTemp != nullptr){
            counter++;
            if(highTemp->m_south != nullptr || highTemp->m_north != nullptr){
                snakeLadderCounter++;
            }
            highTemp = highTemp->m_next;
        }
        if(snakeLadderCounter == maxSnakeLadder && counter == boardSize){
            tooHigh = true;
        }
        if(tooHigh && tooLow && invalidBoardSize){
            return true;
        }
        return false;
    }

    bool Tester::normalCaseRandomBoardTest(Snakes& board){
        board.clear();
        const int boardSize = 25;
        const int snakeLadderAmount = 4;
        board.makeRandomBoard(25, 4);
        if(board.m_start != nullptr &&
        board.m_playerTurn == PLAYER1TURN &&
        board.m_player1 == board.m_start &&
        board.m_player2 == board.m_start){
            Cell *temp = board.m_start;
            int counter = 0;
            int snakeLadderCounter = 0;
            while(temp != nullptr){
                counter++;
                if(temp->m_south != nullptr || temp->m_north != nullptr){
                snakeLadderCounter++;
                }
                temp = temp->m_next;
            }
            if(counter == boardSize && snakeLadderCounter == snakeLadderAmount){
                board.clear();
                return true;
            }
        }
        board.clear();
        return false;
    }

    bool Tester::normalOverloadedTest(Snakes& copy, Snakes& original){
        int copySize = 0;
        int originalSize = 0;
        int locationID;
        original.reStart();
        copy.reStart();
        Cell * copyTemp = copy.m_start;
        Cell * originalTemp = original.m_start;
        while(copyTemp != nullptr){
            originalTemp = original.m_start;
            if(copyTemp->m_south != nullptr){
                locationID = copyTemp->getID();
                for(int i = 1; i < locationID; i++){
                    originalTemp = originalTemp->m_next;
                }
                if(originalTemp->m_south == nullptr){
                    return false;
                }else{
                    if(originalTemp->m_south->getID() != copyTemp->m_south->getID()){
                        return false;
                    }
                }
            }else if(copyTemp->m_north != nullptr){
                locationID = copyTemp->getID();
                for(int i = 1; i < locationID; i++){
                    originalTemp = originalTemp->m_next;
                }
                if(originalTemp->m_north == nullptr){
                    return false;
                }else{
                    if(originalTemp->m_north->getID() != copyTemp->m_north->getID()){
                        return false;
                    }
                }
            }
            copySize++;
            copyTemp = copyTemp->m_next;
        }
        return true;
    }
    bool Tester::edgeOverloadedTest(Snakes& copy, Snakes& original){
        if(copy.m_start == original.m_start &&
        copy.m_playerTurn == original. m_playerTurn &&
        copy.m_player1 == original.m_player1 &&
        copy.m_player2 == original.m_player2){
            return true;
        }
        return false;
    }

    bool Tester::clearTest(Snakes&board){
        bool fullBoard = false;
        bool clearedBoard = false;
        if(board.m_start != nullptr &&
        board.m_player1 == board.m_start && 
        board.m_player1 == board.m_start &&
        board.m_playerTurn != NOGAME){
            fullBoard = true;
        }
        board.clear();
        if(board.m_start == nullptr &&
        board.m_player1 == nullptr &&
        board.m_player2 == nullptr &&
        board.m_playerTurn == NOGAME){
            clearedBoard = true;
        }
        if(fullBoard == true && clearedBoard == true){
            return true;
        }
        return false;
    }