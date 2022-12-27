#pragma once

enum Direction
{
    DOWN = 0,

    RIGHT = 1
};
enum Multiplier
{
    ONE = 1,
    TWO = 2,
    THREE = 3,
    WTWO = 4,  // for "*"
    WTHREE = 5 // for "!"
};

/// @brief Representation of a word. Has x and y coordinates aswell as direction and the word
typedef struct
{
    int x;
    int y;
    enum Direction dire;
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
    Letter tiles[7];
    int ptr;
    char name[20];
    int total_points;
    int skip;
} Player;