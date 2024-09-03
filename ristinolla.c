#include <stdio.h>

void printGrid(char (*currentGrid)[3][3]);
void playerInput(int playerTurn, char (*currentGrid) [3][3]);
int situationCheck(char (*currentGrid) [3][3]);
int checkPoints(int x, int o, char (*currentGrid)[3][3]);


void printGrid(char (*currentGrid)[3][3]) {
//Iterate throught the array and print the items and the grid
    printf("\n  1   2   3\n");
        for (int i = 0; i < 3; i++) {
            printf("%d", i+1);
            for (int j = 0; j < 3; j++){
                printf(" %c ", (*currentGrid)[i][j]);
                // Print horizontal lines.
                    if (j == 0 || j == 1) {
                    printf("|");
                    }      
            }
            // Print vertical lines
            if (i == 0 || i == 1){
                printf("\n ---|---|---");
            }       
            printf("\n");
        }    
}


void playerInput(int playerTurn, char (*currentGrid)[3][3]) {
    // takes the player's input and checks that the input is allowed.
    int x, y;
    int rightAnswer = 0;
    do {
        printf("\nPelaajan %d vuoro. Sijoita merkkisi (X, Y): ", playerTurn);
        scanf("%d, %d", &x, &y);
        if ((*currentGrid)[x - 1][y - 1] != ' ' || x < 1 || x > 3 || y < 1 || y > 3) {
            printf("Väärä syöte. Kokeile uudelleen\n ");
        }
        else {
            rightAnswer = 1;
        }
    } while (rightAnswer == 0);
    (*currentGrid)[x-1][y-1] = (playerTurn == 1) ? 'X' : 'O';
}


int situationCheck(char (*currentGrid)[3][3]) {
    // Function checks if either player has the line required to win
    int rowX = 0;
    int rowO = 0;
    int returnValue = 1;
    //check the horizontal lines
    for (int i = 0; i < 3; i++) {
        rowO = 0;
        rowX = 0;
        for(int j = 0; j < 3; j++) {
            if ((*currentGrid)[i][j] == 'X') {
                rowX++;
            }
            else if ((*currentGrid)[i][j] == 'O') {
                rowO++;
            }
        }
        if (returnValue == 1) {
            returnValue = checkPoints(rowX, rowO, currentGrid);
        }
    }   
    
    // check the vertcal lines
    for (int i = 0; i < 3; i++) {
        rowO = 0;
        rowX = 0;
        for(int j = 0; j < 3; j++) {
            if ((*currentGrid)[j][i] == 'X') {
                rowX++;
            }
            else if ((*currentGrid)[j][i] == 'O') {
                rowO++;
            }
        }
        if (returnValue == 1) {
            returnValue = checkPoints(rowX, rowO, currentGrid);
        }
    }  
    
    // check the first diagonal lines
    int x = 0;
    int y = 0;
    rowO = 0;
    rowX = 0;
    for (int i = 0; i < 3; i++) {
        if ((*currentGrid)[x][y] == 'X') {
            rowX++;
        }
        else if ((*currentGrid)[x][y] == 'O') {
            rowO++;
        }
        x++;
        y++;
        }
        if (returnValue == 1) {
            returnValue = checkPoints(rowX, rowO, currentGrid);
        }
    
    // check the second diagonal line
    x = 0;
    y = 2;
    rowO = 0;
    rowX = 0;
    for (int i = 0; i < 3; i++) {
        if ((*currentGrid)[x][y] == 'X') {
            rowX++;
        }
        else if ((*currentGrid)[x][y] == 'O') {
            rowO++;
        }
        x++;
        y--;
        }
        if (returnValue == 1) {
            returnValue = checkPoints(rowX, rowO, currentGrid);
        } 
    
    //draw check
    int draw = 0;
    for (int i = 0; i<3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((*currentGrid)[j][i] == 'X' || ((*currentGrid)[j][i] == 'O'))
            draw++;
        }
    if (draw == 9) {
        printGrid(currentGrid);
        printf("Tasapeli\n");
        returnValue = 0; 
    }
    }
    return returnValue;
}  


int checkPoints(int x, int o, char (*currentGrid)[3][3]) {
    // Checks the score of the situationCheck function and determines the other player as the winner or continues the game
    if (x == 3) {
        printGrid(currentGrid);
        printf("Pelaaja 1 voitti!\n");
        return 0;
    }
    else if (o == 3) {
        printGrid(currentGrid);
        printf("Pelaaja 2 voitti!\n");
        return 0;
       }
    else {
        return 1;
    }
}


int main() {
    int gameIsOn = 1;
    char grid[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '},{' ', ' ', ' '}};
    int playerTurn = 2;
    while (gameIsOn == 1) {    
        playerTurn = (playerTurn == 1) ? (2) : (1);
        printGrid(&grid);
        playerInput(playerTurn, &grid);
        gameIsOn = situationCheck(&grid);
    }
    int again = 0;
    while (again != 1 || again != 2) {
        printf("Pelataanko uudelleen? Valitse 1, jos haluat aloittaa uuden pelin. Valitse 2, jos haluat lopettaa pelin.\n");
        scanf("%d", &again);
        if (again == 1) {
            main();
        }
        else if (again == 2) {
            break;
        }
        else {
            printf("Väärä syöte.\n");
        }
    }
    return 0;
}
