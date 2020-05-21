/* Define header file */

#ifndef BATTLESHIP_H
#define BATTLESHIP_H

/* Standard libraries */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Additional libraries */

#include <time.h>       // Used for generating random numbers
#include <ctype.h>      // Used for user input

/* Check if the program is running on Linux or Windows */

#ifdef __linux__
    #define CLEAR "clear"
    //unicode symbols
    #define SYMBOL_VERTICAL_LINE_SINGLE 2502
    #define SYMBOL_CROSS 253C
    #define SYMBOL_HORIZONTAL_LINE 2550
    #define SYMBOL_VERTICAL_LINE 2551
    #define SYMBOL_UPPER_LEFT_EDGE 2554
    #define SYMBOL_UPPER_RIGHT_EDGE 2557
    #define SYMBOL_LOWER_LEFT_EDGE 255A
    #define SYMBOL_LOWER_RIGHT_EDGE 255D
    #define SYMBOL_T_ROTATED_RIGHT_SECOND 255F
    #define SYMBOL_T_ROTATED_RIGHT 2560
    #define SYMBOL_T_ROTATED_LEFT 2563
    #define SYMBOL_T_ROTATED_LEFT_SECOND 2562
    #define SYMBOL_T_SECOND 2564
    #define SYMBOL_T 2566
    #define SYMBOL_T_ROTATED_SECOND 2567
    #define SYMBOL_T_ROTATED 2569

#else
    #define CLEAR "cls"
    //extended ascii
    #define SYMBOL_VERTICAL_LINE_SINGLE 179
    #define SYMBOL_T_ROTATED_LEFT_SECOND 182
    #define SYMBOL_T_ROTATED_LEFT 185
    #define SYMBOL_VERTICAL_LINE 186
    #define SYMBOL_LOWER_RIGHT_EDGE 188
    #define SYMBOL_UPPER_RIGHT_EDGE 187
    #define SYMBOL_HORIZONTAL_LINE_SINGLE 196
    #define SYMBOL_CROSS 197
    #define SYMBOL_T_ROTATED_RIGHT_SECOND 199
    #define SYMBOL_LOWER_LEFT_EDGE 200
    #define SYMBOL_UPPER_LEFT_EDGE 201
    #define SYMBOL_T_ROTATED 202 
    #define SYMBOL_T 203
    #define SYMBOL_T_ROTATED_RIGHT 204
    #define SYMBOL_HORIZONTAL_LINE 205
    #define SYMBOL_T_ROTATED_SECOND 207
    #define SYMBOL_T_SECOND 209

#endif

/* Game modes */

#define PLAYER_VS_COOP  0   // Player vs Computer mode
#define PLAYER_V_PLAYER 1   // Player vs Player mode

/* Players */

#define PLAYER1         0   // Player one
#define PLAYER2         1   // Player two

/* Number of different types of ships */

#define NUM_OF_SHIPS    4

/* Used for describing rotation of the ship */

#define HORIZONTAL      0   // From the beginning coordinate to the right
#define VERTICAL        1   // From the beginning coordinate down

/* Size of the battle field */

#define ROWS            10  // Number of rows
#define COLS            10  // Number of columns

/* Representation symbols on the board */

#define WATER           '~'
#define HIT             'X'
#define MISS            '*'

#define NOSAC_AVIONA    'N'
#define KRSTARICA       'K'
#define RAZARAC         'R'
#define PODMORNICA      'P'

/* Information about specific ship type */

typedef struct {
    char symbol;    // Representation of specific ship type on board
    int length;     // Length of specific ship type
    int ships;      // Number of ships of specific ship type
} ShipType;

/* Stores coordinates */

typedef struct {
    int x;
    int y;
} coordinates;

/* Stores every cell's current symbol and position on board */

typedef struct {
    char symbol;
    coordinates position;
} cell;

void printBoard(cell board[][COLS], bool);
void initializeBoard(cell board[][COLS]);
void putShipOnBoard(cell boardoard[][COLS], coordinates, int, ShipType);
void randomShips(cell board[][COLS], ShipType ship[NUM_OF_SHIPS]);
void manualShips(cell board[][COLS], ShipType ship[NUM_OF_SHIPS]);

bool checkShipPlacement(cell board[][COLS], coordinates, int, int);
coordinates inputCoordinate();
int checkShot(cell board[][COLS], coordinates);
void updateBoard (cell board[][COLS], coordinates);

int tryEveryDirection(cell playersBoard[][COLS], coordinates *target, int *number_of_tested_shots);
#endif
