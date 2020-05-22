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
    #define SYMBOL_VERTICAL_LINE_SINGLE "\u2502"
    #define SYMBOL_CROSS "\u253C"
    #define SYMBOL_VERTICAL_LINE "\u2551"
    #define SYMBOL_UPPER_LEFT_EDGE "\u2554"
    #define UPPER_BORDER_T "\u2566"
    #define VERTICAL_LINE "\u2550\u2550\u2550"
    #define SINGLE_VERTICAL_LINE "\u2551"
    #define SYMBOL_UPPER_RIGHT_EDGE "\u2557"
    #define SYMBOL_LOWER_LEFT_EDGE "\u255A"
    #define SYMBOL_LOWER_RIGHT_EDGE "\u255D"
    #define SYMBOL_T_ROTATED_RIGHT_SECOND "\u255F"
    #define SYMBOL_T_ROTATED_RIGHT "\u2560"
    #define SYMBOL_T_ROTATED_LEFT "\u2563"
    #define SYMBOL_T_ROTATED_LEFT_SECOND "\u2562"
    #define SYMBOL_T_SECOND_TYPE "\u2564"
    #define SYMBOL_T_ROTATED_SECOND "\u2567"
    #define LOWER_BORDER_T "\u2569"
    #define HORIZONTAL_LINE_SINGLE "\u2500\u2500\u2500"  //unicode ima isti kod za ova dva karaktera?
    #define HORIZONTAL_LINE "\u2550\u2550\u2550"

#else
    #define CLEAR "cls"
    //extended ascii
    #define SYMBOL_VERTICAL_LINE_SINGLE "%c", 179
    #define SYMBOL_T_ROTATED_LEFT_SECOND "%c", 182
    #define SYMBOL_T_ROTATED_LEFT "%c", 185
    #define SYMBOL_VERTICAL_LINE "%c", 186
    #define SYMBOL_LOWER_RIGHT_EDGE "%c", 188
    #define SYMBOL_UPPER_RIGHT_EDGE "%c", 187
    #define SINGLE_VERTICAL_LINE "%c", 186
    #define HORIZONTAL_LINE_SINGLE "%c%c%c", 196, 196, 196
    #define SYMBOL_CROSS "%c", 197
    #define SYMBOL_T_ROTATED_RIGHT_SECOND "%c", 199
    #define SYMBOL_LOWER_LEFT_EDGE "%c", 200
    #define SYMBOL_UPPER_LEFT_EDGE "%c", 201
    #define LOWER_BORDER_T "%c", 202
    #define UPPER_BORDER_T "%c", 203
    #define HORIZONTAL_LINE "%c%c%c", 205, 205, 205
    #define SYMBOL_T_ROTATED_RIGHT "%c", 204
    #define SYMBOL_HORIZONTAL_LINE 205
    #define SYMBOL_T_ROTATED_SECOND "%c", 207
    #define SYMBOL_T_SECOND_TYPE "%c", 209

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

#define ROWS            10  // Number of rows    (ROWS <= 12)
#define COLS            10  // Number of columns (COLS <= 58)

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
void updateCell (cell board[][COLS], coordinates);

int tryEveryDirection(cell playersBoard[][COLS], coordinates *target, int *number_of_tested_shots);
#endif
