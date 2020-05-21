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
#else
    #define CLEAR "cls"
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
