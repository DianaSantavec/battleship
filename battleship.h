#ifdef __linux__
    #define CLEAR system("clear")
#else
    #define CLEAR system("cls")
#endif

#ifndef _BATTLESHIP_H_
#define _BATTLESHIP_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define PLAYER_VS_COOP  0
#define PLAYER_V_PLAYER 1

#define PLAYER1         0
#define PLAYER2         1

#define NUM_OF_SHIPS    4   // Number of ship types

#define HORIZONTAL      0
#define VERTICAL        1

#define ROWS            10
#define COLS            10

#define WATER           '~'
#define HIT             'X'
#define MISS            '*'

#define NOSAC_AVIONA    'N'
#define KRSTARICA       'K'
#define RAZARAC         'R'
#define PODMORNICA      'P'

typedef enum {
    FALSE, TRUE
} bool;

typedef struct {
    char symbol;    // Representation of specific type on matrix
    int length;     // Length of specific type
    int ships;      // Number of ships of specific type
} ShipType;

typedef struct {
    int row;
    int column;
} coordinates;

typedef struct {
    char symbol;
    coordinates position;
} cell;

void printBoard(cell board[][COLS], bool);
void initializeBoard(cell board[][COLS]);
void putShipOnBoard(cell boardoard[][COLS], coordinates, int, ShipType);
void randomizeShips(cell board[][COLS], ShipType ship[NUM_OF_SHIPS]);
void manualShips(cell board[][COLS], ShipType ship[NUM_OF_SHIPS]);

bool checkShipPlacement(cell board[][COLS], coordinates, int, int);
coordinates inputCoordinate();
int checkShot(cell board[][COLS], coordinates);

coordinates randomShot(cell playersBoard[][COLS]);
int tryEveryDirection(cell playersBoard[][COLS], coordinates *target, int *number_of_tested_shots);


#endif
