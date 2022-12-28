#pragma once

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