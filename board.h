#pragma once
#include "definitions.h"
#include "colors.h"
/**
 * Initializes the board according to the official scrabble rules.
 *
 * @returns None
 */
void initializeBoard(Letter board[16][16])
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            board[i][j].c = ' ';
        }
    }
    for (int i = 1; i < 16; i++)
    {
        char a = i + 96;
        char b = i + 64;
        board[0][i].c = a;
        board[i][0].c = b;
    }
    board[1][1].c = '!';
    board[1][8].c = '!';
    board[1][15].c = '!';
    board[8][1].c = '!';
    board[8][15].c = '!';
    board[15][1].c = '!';
    board[15][8].c = '!';
    board[15][15].c = '!';
    int x, y;
    for (x = 2, y = 2; x < 15; x++, y++)
    {
        board[x][y].c = '*';
        board[x][16 - y].c = '*';
    }
    board[2][6].c = '3';
    board[2][10].c = '3';
    board[6][2].c = '3';
    board[6][6].c = '3';
    board[6][10].c = '3';
    board[6][14].c = '3';
    board[10][2].c = '3';
    board[10][6].c = '3';
    board[10][10].c = '3';
    board[10][14].c = '3';
    board[14][6].c = '3';
    board[14][10].c = '3';

    board[1][4].c = '2';
    board[1][12].c = '2';
    board[3][7].c = '2';
    board[3][9].c = '2';
    board[4][1].c = '2';
    board[4][8].c = '2';
    board[4][15].c = '2';
    board[7][3].c = '2';
    board[7][7].c = '2';
    board[7][9].c = '2';
    board[7][13].c = '2';
    board[8][4].c = '2';
    board[8][12].c = '2';
    board[9][3].c = '2';
    board[9][7].c = '2';
    board[9][9].c = '2';
    board[9][13].c = '2';
    board[12][1].c = '2';
    board[12][8].c = '2';
    board[12][15].c = '2';
    board[13][7].c = '2';
    board[13][9].c = '2';
    board[15][4].c = '2';
    board[15][12].c = '2';
}
/**
 * Displays the board.
 *
 * @returns None
 */
void displayBoard(Letter board[16][16])
{
    for (int i = 0; i < 16; i++)
    {
        printf("\t\t");
        for (int j = 0; j < 16; j++)
        {
            if (i == 0 && j == 0)
            {
                printf("     ");
                continue;
            }
            green();
            if (i == 0 || j == 0)
            {
                red();
                printf(" |");

                printf("%c", board[i][j].c);

                printf("| ");
                reset();
                continue;
            }

            printf(" |");
            reset();
            if (board[i][j].c == '!')
                magenta();
            else if (board[i][j].c == '*')
                yellow();
            else if (board[i][j].c == '2')
                cyan();
            else if (board[i][j].c == '3')
                blue();
            printf("%c", board[i][j].c);
            green();
            printf("| ");
            reset();
        }
        green();
        printf("\n\t\t-------------------------------------------------------------------------------\n");
        reset();
    }
}
/**
 * Initializes the tile bag according to the official scrabble rules.
 *
 * @returns None
 */
void initializeTileBag(Letter TileBag[100], int NumTiles)
{
    NumTiles = 100;
    for (int i = 0; i < 9; i++)
    {
        TileBag[i].c = 'A';
        TileBag[i].points = 1;
    }
    TileBag[9].c = 'B';
    TileBag[9].points = 3;
    TileBag[10].c = 'B';
    TileBag[10].points = 3;
    TileBag[11].c = 'C';
    TileBag[11].points = 3;
    TileBag[12].c = 'C';
    TileBag[12].points = 3;
    TileBag[13].c = 'D';
    TileBag[13].points = 2;
    TileBag[14].c = 'D';
    TileBag[14].points = 2;
    TileBag[15].c = 'D';
    TileBag[15].points = 2;
    TileBag[16].c = 'D';
    TileBag[16].points = 2;
    for (int i = 17; i < 26; i++)
    {
        TileBag[i].c = 'I';
        TileBag[i].points = 1;
    }
    TileBag[26].c = 'J';
    TileBag[26].points = 8;
    TileBag[27].c = 'K';
    TileBag[27].points = 5;
    for (int i = 28; i < 40; i++)
    {
        TileBag[i].c = 'E';
        TileBag[i].points = 1;
    }
    TileBag[40].c = 'F';
    TileBag[40].points = 4;
    TileBag[41].c = 'F';
    TileBag[41].points = 4;
    TileBag[42].c = 'G';
    TileBag[42].points = 2;
    TileBag[43].c = 'G';
    TileBag[43].points = 2;
    TileBag[44].c = 'G';
    TileBag[44].points = 2;
    TileBag[45].c = 'H';
    TileBag[45].points = 4;
    TileBag[46].c = 'H';
    TileBag[46].points = 4;
    for (int i = 47; i < 51; i++)
    {
        TileBag[i].c = 'L';
        TileBag[i].points = 1;
    }
    TileBag[51].c = 'M';
    TileBag[51].points = 3;
    TileBag[52].c = 'M';
    TileBag[52].points = 3;
    for (int i = 53; i < 59; i++)
    {
        TileBag[i].c = 'N';
        TileBag[i].points = 1;
    }
    for (int i = 59; i < 67; i++)
    {
        TileBag[i].c = 'O';
        TileBag[i].points = 1;
    }
    TileBag[67].c = 'P';
    TileBag[67].points = 3;
    TileBag[68].c = 'P';
    TileBag[68].points = 3;
    TileBag[69].c = 'Q';
    TileBag[69].points = 10;
    for (int i = 70; i < 76; i++)
    {
        TileBag[i].c = 'R';
        TileBag[i].points = 1;
    }
    for (int i = 76; i < 80; i++)
    {
        TileBag[i].c = 'S';
        TileBag[i].points = 1;
    }
    for (int i = 80; i < 86; i++)
    {
        TileBag[i].c = 'T';
        TileBag[i].points = 1;
    }
    for (int i = 86; i < 90; i++)
    {
        TileBag[i].c = 'U';
        TileBag[i].points = 1;
    }
    TileBag[90].c = 'V';
    TileBag[90].points = 4;
    TileBag[91].c = 'V';
    TileBag[91].points = 4;
    TileBag[92].c = 'W';
    TileBag[92].points = 4;
    TileBag[93].c = 'W';
    TileBag[93].points = 4;
    TileBag[94].c = 'X';
    TileBag[94].points = 8;
    TileBag[95].c = 'Y';
    TileBag[95].points = 4;
    TileBag[96].c = 'Y';
    TileBag[96].points = 4;
    TileBag[97].c = 'Z';
    TileBag[97].points = 10;
    TileBag[98].c = 'A';
    TileBag[98].points = 1;
    TileBag[99].c = 'O';
    TileBag[99].points = 1;
}