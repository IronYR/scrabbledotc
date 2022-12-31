#pragma once
#include <stdio.h>
#define BOARD_SIZE 16
#define TILE_BAG_SIZE 100
#define USER_TILES_SIZE 7

enum DIRECTION
{
    down = 0,

    right = 1
};

typedef struct
{
    int x;
    int y;
    enum DIRECTION dire;
    char word[50];
} Word;

typedef struct
{
    char c;
    int points;
    int lm;
    int wm;
} Letter;

typedef struct
{
    Letter tiles[USER_TILES_SIZE];
    int ptr;
    char name[20];
    int total_points;
    int skip;
} Player;

Letter board[BOARD_SIZE][BOARD_SIZE];
Letter TileBag[TILE_BAG_SIZE];
int NumTiles = TILE_BAG_SIZE;

static FILE *fp;

Letter CurrentWord[16];
int cwPtr = 0;
Letter CurrentSubWord[16];
int cswPtr = 0;

int TotalPoints;

bool exists;

Player playerArr[4];

Letter OldBoard[BOARD_SIZE][BOARD_SIZE];

int tempTileptr;
Letter tempTileArray[USER_TILES_SIZE];
