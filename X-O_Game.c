#include <stdio.h>
#include <stdbool.h>
#include <conio.h>

enum Player{Null, X, O};

struct cell{
    int number;
    enum Player player;
};

struct cell gameCells[9];
enum Player player1, player2;

void startNewGame();
void initGameCells();
void readPlayer1Letter();
void readNextMove(int currentPlayerNo);
bool isValidCellNo(int cellNo);
enum Player getGameWinner();
void printGameResult(enum Player winner);
void printGameCells();




void startNewGame(){

    initGameCells();            // Clear all game cells and the ex-chosen player letters  
    readPlayer1Letter();        // Determine player 1 letter "X/O" (and hence player 2 letter) 

    //enum Player currentPlayer = player1;
    int currentPlayerNo = 1;
    enum Player winner = Null;
    int noOfPlayedTurns = 0;
    
    while(winner == Null && noOfPlayedTurns < 9){
        system("cls");
        printGameCells();
        readNextMove(currentPlayerNo);   // Read next move of the current player

        winner = getGameWinner();       // Check if one of the players has won (i.e. completed a row, a cloumn, or a diagonal)
                                        // If not, winner will be "Null"4
        
        currentPlayerNo = (currentPlayerNo == 1) ? 2 : 1;     // Swap the players turn
        noOfPlayedTurns++;
    }

    printGameResult(winner);            // Print the game winner, or announce a tie if there is not 
}



// Clear all game cells and the ex-chosen player sides  
void initGameCells(){

    // Set both player sides to Null
    player1 = Null;
    player2 = Null;

    // Clear all game cells to Null
    for(int i=0; i<9; i++){
        gameCells[i].number = i+1;
        gameCells[i].player = Null;
    }
}



// Determine player 1 letter "X/O" (and hence player 2 letter) before the game starts
void readPlayer1Letter(){
    
    printf("\n              PLayer 1: Choose your letter (x/o)?    ");

    char player1Letter, trash[100];
    scanf("%c", &player1Letter);
    fgets(trash, 100, stdin);       // reads the extra new line character (/n) that is left from calling the above scanf()
                                    // or any possible residue strings

    if(player1Letter == 'x' || player1Letter == 'X'){
        player2 = O;
        player1 = X;
        printf("\n            Player 1: %c\n", (player1==X) ? 'X':'O');
        printf("            Player 2: %c\n", (player2==O) ? 'O':'X');
    }
    else if(player1Letter == 'o' || player1Letter == 'O'){
        player1 = O;
        player2 = X;
        printf("\n            Player 1: %c\n", (player1==X) ? 'X':'O');
        printf("            Player 2: %c\n", (player2==O) ? 'O':'X');
        printf("_________________________________________________________");
    }
    else{
        printf("Invalid Input! Please enter either (X/O) or (x/o):    " );
        readPlayer1Letter(player1, player2); //Recall it self agian to re-determine player 1 side again 
    }
}



// Reads the cell no in which the current player wants to place his letter 
void readNextMove(int currentPlayerNo){

    printf("\n__________________Player %d__________________\n", currentPlayerNo);
    printf("Enter the cell no to put your letter in:      ");

    int cellNo;
    scanf("%d", &cellNo);

    while(!isValidCellNo(cellNo)){
        printf("The cell no you entered is invalid!\n");
        printf("Either the cell is not empty, or the number is out of the accepted range (1-9)\n\n");
        printf("Re-enter the cell no to put your letter in:      ");
        scanf("%d", &cellNo);
    }

    gameCells[cellNo-1].player = (currentPlayerNo == 1) ? player1 : player2 ;
    //printGameCells();
}



// Check if the chosen cell is both valid (1-9) and empty
bool isValidCellNo(int cellNo){
    if(cellNo < 1 || cellNo > 9)            return false;
    if(gameCells[cellNo-1].player != Null)  return false;

    return true;
}



// Check if one of the players has won (i.e. completed a row, a cloumn, or a diagonal) or not
// If there is a winner, it returns "X" or "O" as an enum Player value
// If not, it will return "Null"
enum Player getGameWinner(){

    for(int i=0; i<=2; i++){
        if( gameCells[i].player != Null
            && gameCells[i].player == gameCells[i+3].player
            && gameCells[i].player == gameCells[i+6].player )
        {
            return gameCells[i].player;
        }
    }

    for(int i=0; i<=6; i+=3){
        if( gameCells[i].player != Null
            && gameCells[i].player == gameCells[i+1].player
            && gameCells[i].player == gameCells[i+2].player )
        {
            return gameCells[i].player;
        }
    }

    if( gameCells[0].player != Null
        && gameCells[0].player == gameCells[4].player
        && gameCells[0].player == gameCells[8].player )
    {
        return gameCells[0].player;
    }

    if( gameCells[2].player != Null
        && gameCells[2].player == gameCells[4].player
        && gameCells[2].player == gameCells[6].player )
    {
        return gameCells[2].player;
    }

    return Null;
}



// Print the game winner, or announce a tie if there is not 
void printGameResult(enum Player winner){
    printGameCells();
    printf("\n\n_________________________ Game End! __________________________\n\n");
    if(winner == Null){
        printf("                     There is a TIE \n");
    }
    else if(winner == player1){
        printf("                     WINNER : PLAYER 1 \n");
        printf("                     Congratulations! :) \n");
    }
    else if(winner == player2){
        printf("                     WINNER : PLAYER 2  \n");
        printf("                     Congratulations! :) \n");
    }
    printf("\n\n______________________________________________________________\n\n");
}



// Print the current game status visually as a matrix 
void printGameCells(){

    printf("\n");
    printf("        -------------------------\n");

    for(int i=0; i<3; i++){
        printf("        ");
        for(int j=0; j<3; j++){
            char c;
            if(gameCells[(3*i+j)].player == Null)   c = ' ';
            else if(gameCells[(3*i+j)].player == X)   c = 'X';
            else if(gameCells[(3*i+j)].player == O)   c = 'O';
            printf("|   %c   ", c);
        }
        printf("|\n");
        printf("        -------------------------\n");
    }
}




int main(){

    startNewGame();
}