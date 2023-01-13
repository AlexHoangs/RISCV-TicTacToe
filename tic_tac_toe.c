#include <stdbool.h>
#include <stddef.h>  // for NULL (if you need it)
#include <stdint.h>

#define INT_ENABLE ((uint32_t*) 0x40000000)
#define INT_PENDING ((uint32_t*) 0x40000004)

#define MTIME_LOW ((uint32_t*) 0x40000008)
#define MTIME_HIGH ((uint32_t*) 0x4000000C)
#define MTIMECMP_LOW ((uint32_t*) 0x40000010)
#define MTIMECMP_HIGH ((uint32_t*) 0x40000014)
#define PERIOD 50000

#define CONTROLLER ((uint32_t*) 0x40000018)
#define LEFT 0x1
#define UP 0x2
#define DOWN 0x4
#define RIGHT 0x8

#define VIDEO_MEMORY ((char*) 0x500FE800)
#define VIDEO_NUM_ROWS 36
#define VIDEO_NUM_COLS 64

int winCoord_R[9] = {5,7,9,5,7,9,5,7,9};
int winCoord_C[9] = {2,2,2,4,4,4,6,6,6};
int cursorCoord_R[9] = {4,5,6,4, 5 ,6,4,5,6};
int cursorCoord_C[9] = {1,1,1,2, 2 ,2,3,3,3};
char current[9] = "Current: ";
char player1[9] = "Player 1";
char player2[9] = "Player 2";
char neither[15] = "Neither Player";
char winnerstatus[16] = "The winner is: ";
char board[3] = "012";
int currentPlayer = 1;
bool noWinner = true;
bool endLoop = true;
int winner = 0;
int numTurns = 0;

// coords to check (5,2) (5,4) (5,6)
//                 (7,2) (7,4) (7,6)
//                 (9,2) (9,4) (9,6)

void checkWinner(void)
{
    //check if all spaces are filled out
    if (numTurns >= 9) 
        {
            winner = -1;
        }

    // check if X vertical wins
    if ((VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[0]) + winCoord_C[0]] == 'X' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[1]) + winCoord_C[1]] == 'X' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[2]) + winCoord_C[2]] == 'X') ||
        (VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[3]) + winCoord_C[3]] == 'X' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[4]) + winCoord_C[4]] == 'X' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[5]) + winCoord_C[5]] == 'X') ||
        (VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[6]) + winCoord_C[6]] == 'X' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[7]) + winCoord_C[7]] == 'X' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[8]) + winCoord_C[8]] == 'X'))
        {
            winner = 1;
        }
    

    // check if O vertical wins
    if ((VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[0]) + winCoord_C[0]] == 'O' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[1]) + winCoord_C[1]] == 'O' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[2]) + winCoord_C[2]] == 'O') ||
        (VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[3]) + winCoord_C[3]] == 'O' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[4]) + winCoord_C[4]] == 'O' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[5]) + winCoord_C[5]] == 'O') ||
        (VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[6]) + winCoord_C[6]] == 'O' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[7]) + winCoord_C[7]] == 'O' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[8]) + winCoord_C[8]] == 'O'))
        {
            winner = 2;
        }

    // check if X horizontal wins
    if ((VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[0]) + winCoord_C[0]] == 'X' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[3]) + winCoord_C[3]] == 'X' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[6]) + winCoord_C[6]] == 'X') ||
        (VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[1]) + winCoord_C[1]] == 'X' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[4]) + winCoord_C[4]] == 'X' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[7]) + winCoord_C[7]] == 'X') ||
        (VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[2]) + winCoord_C[2]] == 'X' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[5]) + winCoord_C[5]] == 'X' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[8]) + winCoord_C[8]] == 'X'))
        {
            winner = 1;
        }

    // check if O horizontal wins
    if ((VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[0]) + winCoord_C[0]] == 'O' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[3]) + winCoord_C[3]] == 'O' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[6]) + winCoord_C[6]] == 'O') ||
        (VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[1]) + winCoord_C[1]] == 'O' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[4]) + winCoord_C[4]] == 'O' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[7]) + winCoord_C[7]] == 'O') ||
        (VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[2]) + winCoord_C[2]] == 'O' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[5]) + winCoord_C[5]] == 'O' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[8]) + winCoord_C[8]] == 'O'))
        {
            winner = 2;
        }
    // check if X diagonal wins
    if ((VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[0]) + winCoord_C[0]] == 'X' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[4]) + winCoord_C[4]] == 'X' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[8]) + winCoord_C[8]] == 'X') ||
        (VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[2]) + winCoord_C[2]] == 'X' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[4]) + winCoord_C[4]] == 'X' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[6]) + winCoord_C[6]] == 'X'))
        {
            winner = 1;
        }

    // check if O diagonal wins
    if ((VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[0]) + winCoord_C[0]] == 'O' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[4]) + winCoord_C[4]] == 'O' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[8]) + winCoord_C[8]] == 'O') ||
        (VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[2]) + winCoord_C[2]] == 'O' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[4]) + winCoord_C[4]] == 'O' &&
        VIDEO_MEMORY[VIDEO_NUM_COLS*(winCoord_R[6]) + winCoord_C[6]] == 'O'))
        {
            winner = 2;
        }
}

void updateCursor(int opt, int winner)
{
    if (winner == -1) 
    {
        for (int i = 0; i < 15; i++) { // prints out "the winner is"
            VIDEO_MEMORY[i] = winnerstatus[i];
        }
        for (int i = 15; i < 30; i++) { // neither
                VIDEO_MEMORY[i] = neither[i - 15];
            }
    }

    else if (winner != 0) 
    {
        for (int i = 0; i < 15; i++) { // prints out "the winner is"
            VIDEO_MEMORY[i] = winnerstatus[i];
        }
        if (winner == 1) {
            for (int i = 15; i < 24; i++) { // player 1
                VIDEO_MEMORY[i] = player1[i - 15];
            }
        }
        if (winner == 2) {
            for (int i = 15; i < 24; i++) { // player 1
                VIDEO_MEMORY[i] = player2[i - 15];
            }
        }
    }

    else 
    {
        for (int i = 0; i < 9; i++) { // prints out "current"
            VIDEO_MEMORY[i] = current[i];
    }

        if (currentPlayer == 1) 
            { // prints out player
            for (int i = 9; i < 18; i++) { // player 1
            VIDEO_MEMORY[i] = player1[i - 9];
            }
    } 
        else {
            for (int i = 9; i < 18; i++) { // player 2
            VIDEO_MEMORY[i] = player2[i - 9];
            }
        }
    }

    switch(opt)
    {
        case 0: // right
            if(cursorCoord_C[7] != 7) { // right boundaries
                for(int i = 0; i < 9; i++) { // replace old cursair with blanks
                    if (VIDEO_MEMORY[VIDEO_NUM_COLS*(cursorCoord_R[i]) + cursorCoord_C[i]] == 'X'
                        || VIDEO_MEMORY[VIDEO_NUM_COLS*(cursorCoord_R[i]) + cursorCoord_C[i]] == 'O') {
                        cursorCoord_C[i] += 2; // add to move to right
                        continue;
                    }
                    VIDEO_MEMORY[VIDEO_NUM_COLS*(cursorCoord_R[i]) + cursorCoord_C[i]] = ' ';
                    cursorCoord_C[i] += 2; // add to move to right
                }
            }
            break;
        case 1: // left
            if(cursorCoord_C[0] != 1) { // left boundaries
                for(int i = 0; i < 9; i++) { // replace old cursair with blanks
                    if (VIDEO_MEMORY[VIDEO_NUM_COLS*(cursorCoord_R[i]) + cursorCoord_C[i]] == 'X'
                        || VIDEO_MEMORY[VIDEO_NUM_COLS*(cursorCoord_R[i]) + cursorCoord_C[i]] == 'O') {
                        cursorCoord_C[i] -= 2; // add to move to left
                        continue;
                    }
                    VIDEO_MEMORY[VIDEO_NUM_COLS*(cursorCoord_R[i]) + cursorCoord_C[i]] = ' ';
                    cursorCoord_C[i] -= 2; // subtract to move left
                }
            }
            break;
        case 2: // down
            if(cursorCoord_R[0] != 8) { // down boundaries
                for(int i = 0; i < 9; i++) { // replace old cursair with blanks
                    if (VIDEO_MEMORY[VIDEO_NUM_COLS*(cursorCoord_R[i]) + cursorCoord_C[i]] == 'X'
                        || VIDEO_MEMORY[VIDEO_NUM_COLS*(cursorCoord_R[i]) + cursorCoord_C[i]] == 'O') {
                            cursorCoord_R[i] += 2; // add to move to right
                            continue;
                        }
                    VIDEO_MEMORY[VIDEO_NUM_COLS*(cursorCoord_R[i]) + cursorCoord_C[i]] = ' ';
                    cursorCoord_R[i] += 2; // add to move to right
                } 
            }
            break;
        case 3: // up
            if(cursorCoord_R[0] != 4) { // up boundaries
                for(int i = 0; i < 9; i++) { // replace old cursair with blanks
                    if (VIDEO_MEMORY[VIDEO_NUM_COLS*(cursorCoord_R[i]) + cursorCoord_C[i]] == 'X'
                        || VIDEO_MEMORY[VIDEO_NUM_COLS*(cursorCoord_R[i]) + cursorCoord_C[i]] == 'O') {
                            cursorCoord_R[i] -= 2; // add to move to left
                            continue;
                        }
                    VIDEO_MEMORY[VIDEO_NUM_COLS*(cursorCoord_R[i]) + cursorCoord_C[i]] = ' ';
                    cursorCoord_R[i] -= 2; // subtract to move left
                }
            }
            break;
    }

    for(int i = 0; i < 9; i++) { // print out cursor
        if (i == 4) 
            continue;
        else if (i == 1 || i == 7) { // prints out "|" of cursor
            VIDEO_MEMORY[VIDEO_NUM_COLS*(cursorCoord_R[i]) + cursorCoord_C[i]] = '|';
        }
        else // prints out top and bottom of cursor
            VIDEO_MEMORY[VIDEO_NUM_COLS*(cursorCoord_R[i]) + cursorCoord_C[i]] = '-';
    }
}

void game(void)
{

    // You'll probably want to use this line at some point.
    // *INT_ENABLE = 0x4;
    
    *INT_ENABLE = 0x4;

    // print current player
    for (int i = 0; i < 9; i++) {
        VIDEO_MEMORY[i] = current[i];
    }

    if (currentPlayer == 1) {
        for (int i = 9; i < 18; i++) {
        VIDEO_MEMORY[i] = player1[i - 9];
        }
    } else {
        for (int i = 9; i < 18; i++) {
        VIDEO_MEMORY[i] = player1[i - 9];
        }
    }

    int a[1] = {194}; // byte that starts toe column labels
    int b[3] = {320, 448, 576}; // bytes that starts labels for each row

    // print columns
    int v = a[0];
    for(int j = 0; j < 3; j++) 
    {
        VIDEO_MEMORY[v] = board[j];
        v += 2;
    }

    // print rows
    for(int i = 0; i < 3; i++)
    {
        int v = b[i];
        for(int j = 0; j < 3; j++) 
        {
            VIDEO_MEMORY[v] = board[i];
            break;
        }
    }

    updateCursor(-1, winner); // load in with the cursor

    // wait for user input and make sure it only moves once with each button
    uint32_t controller = *CONTROLLER;
    int prevPress = 0;
    while(noWinner)
    {
        controller = *CONTROLLER;
        if( !(controller & RIGHT) && !(controller & LEFT) && !(controller & DOWN) && !(controller & UP) ) {
            prevPress = 0;
        }
        if (controller & RIGHT && prevPress == 0)
        {
            updateCursor(0, winner);
            prevPress = 1;
        } else if (controller & LEFT && prevPress == 0)
        {
            updateCursor(1, winner);
            prevPress = 1;
        } else if (controller & DOWN && prevPress == 0)
        {
            updateCursor(2, winner);
            prevPress = 1;
        } else if (controller & UP && prevPress == 0)
        {
            updateCursor(3, winner);
            prevPress = 1;
        } 
    }

    // Update mtimecmp.
    uint32_t prevCmpHigh = *MTIME_HIGH;
    uint32_t prevCmpLow = *MTIME_LOW;
    uint64_t newCompare =
        (((uint64_t) prevCmpHigh) << 32) | prevCmpLow;
    newCompare += PERIOD;
    *MTIMECMP_HIGH = newCompare >> 32;
    *MTIMECMP_LOW = newCompare;

    while(endLoop) {}

    *INT_ENABLE = 0x0;
    // You'll probably want to use this line at some point.
    // *INT_ENABLE = 0x0;
}

void c_interrupt_handler(void)
{
    if (!noWinner)
    {
        *MTIMECMP_HIGH = 0xFFFFFFFF;
        *MTIMECMP_LOW = 0xFFFFFFFF;
        endLoop = false;
    }

    if (VIDEO_MEMORY[VIDEO_NUM_COLS*(cursorCoord_R[4]) + cursorCoord_C[4]] == 'X' ||
        VIDEO_MEMORY[VIDEO_NUM_COLS*(cursorCoord_R[4]) + cursorCoord_C[4]] == 'O') 
        {
          // do nothing if it is X or O already  
        }
    else if (currentPlayer == 1) 
    {

        VIDEO_MEMORY[VIDEO_NUM_COLS*(cursorCoord_R[4]) + cursorCoord_C[4]] = 'X';
        currentPlayer = 2;
        updateCursor(-1, winner);
        numTurns++;
        checkWinner();
        
        if (winner == -1) { // no winner
            updateCursor(-1, winner);
            noWinner = false;
        }
        else if (winner == 1) {
            updateCursor(-1, winner);
            noWinner = false;
        }
        else if (winner == 2) {
            updateCursor(-1, winner);
            noWinner = false;
        }
    }
    else 
    {
        VIDEO_MEMORY[VIDEO_NUM_COLS*(cursorCoord_R[4]) + cursorCoord_C[4]] = 'O';
        currentPlayer = 1;
        updateCursor(-1, winner);
        numTurns++;
        checkWinner();

        if (winner == -1) { // no winner
            updateCursor(-1, winner);
            noWinner = false;
        }
        else if (winner == 1) {
            updateCursor(-1, winner);
            noWinner = false;
        }
        else if (winner == 2) {
            updateCursor(-1, winner);
            noWinner = false;
        }
    }

    *INT_PENDING = 0x4;


    // You'll probably want to use this line at some point.
    // *INT_PENDING = 0x4;


}
