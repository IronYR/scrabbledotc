#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include "definitions.h" // contains type definitions, enums, and macros
#include "colors.h"      // contains the different colors
#include "board.h"       // contains functions related to the board
#include "prototypes.h"  // contains function prototypes
#include "file.h"        // contains functions related to file operations
#include "validation.h"  // contains functions related to word and tile validation

/***********************************************************************************************************************
                                                            MAIN
*************************************************************************************************************************/

/**
 * Plays scrabble with p players.
 *
 * @param p The number of players.
 *
 * @returns 0
 */
int main()
{
    int p;
    printf("\t\t\t\t\tHow many players(2-4) would like to play?\n");
    printf("\t\t\t\t\t\t\t  ");
    scanf_s("%d", &p);
    playScrabble(p);
    declareWinner(p);
    return 0;
}

/************************************************************************************************************************
                                                            PLAY SCRABBLE
***************************************************************************************************************************/

/**
 * Checks if the game is over.
 *
 * @param noPlayers The number of players.
 *
 * @returns 0 if the game is over, 1 otherwise.
 */
int gameOver(int noPlayers)
{
    int total = 0;
    for (int i = 0; i < noPlayers; i++)
    {
        if (playerArr[i].ptr == 0)
        {
            return 0;
        }
        total += playerArr[i].skip;
    }
    if (total == 4)
    {
        return 0;
    }
    return 1;
}

/**
 * Displays the points of each player.
 *
 * @param noPlayers The number of players.
 *
 * @returns None
 */
void displayPoints(int noPlayers)
{

    for (int j = 0; j < noPlayers; j++)
    {
        switch (j)
        {
        case 0:
            red();
            break;
        case 1:
            blue();
            break;
        case 2:
            yellow();
            break;
        case 3:
            green();
            break;
        }
        printf("|[");
        for (int i = 0; i < strlen(playerArr[j].name) - 1; i++)
        {

            printf("%c", playerArr[j].name[i]);
        }
        printf(":  %d points]|\n\n", playerArr[j].total_points);
        reset();
    }
}

/**
 * Initializes the game.
 *
 * @param noPlayers The number of players in the game.
 *
 * @returns None
 */
void initGame(int noPlayers)
{

    printf("\n\n");
    for (int i = 0; i < noPlayers; i++)
    {
        printf("\t\t\t\t\t\tEnter player %d name: \n", i + 1);
        if (i == 0)
        {
            printf("\t\t\t\t\t\t\t  ");
            fgets(playerArr[i].name, 50, stdin);
            fgets(playerArr[i].name, 50, stdin);
        }
        else
        {
            printf("\t\t\t\t\t\t\t  ");
            fgets(playerArr[i].name, 50, stdin);
        }
        printf("\n\n");
    }
    system("CLS");
}

/**
 * Declares the winner of the game.
 *
 * @param player The number of players in the game.
 *
 * @returns None
 */
void declareWinner(int noPlayers)
{
    int max = -1;
    int x = 0;
    for (int i = 0; i < noPlayers; i++)
    {
        if (playerArr[i].total_points > max)
        {
            max = playerArr[i].total_points;
            x = i;
        }
    }
    yellow();
    printf("\t\t\t\t\tTHE WINNER IS: %s", playerArr[x].name);
    displayPoints(noPlayers);
}

/**
 * Plays scrabble.
 *
 * @param noPlayers The number of players.
 *
 * @returns None
 */
void playScrabble(int noPlayers)
{

    initGame(noPlayers);
    printf("\n\n");
    initializeBoard(board);
    initializeTileBag(TileBag, NumTiles);
    int l;
    int m = 0;
    int fw = 0;
    do
    {

        for (int i = 0; i < noPlayers; i++)
        {
            printf("\n\n");
            displayPoints(noPlayers);
            printf("\n\n");
            getPlayerTiles(i + 1);
            printf("\n\n");
            displayBoard(board);
            printf("\n");

            for (int j = 0; j < strlen(playerArr[i].name) - 1; j++)
            {

                printf("%c", playerArr[i].name[j]);
            }

            printf("'s turn:  ");
        play:

            displayPlayerTiles(i + 1);

            printf("Enter Your Word. Enter \'!\' to skip turn\n");

            Word w;
            w = getWord(m);
            if (w.word[0] == '!')
            {
                playerArr[i].skip = 1;
                system("CLS");
                continue;
            }

            m++;
            int validTiles;
            saveStateBoard();

            do
            {
                if (w.word[0] == '!')
                    break;
                if (fw == 0)
                {

                    l = validateFirstWord(w);
                }
                else
                {

                    l = validatePosition(w);
                }

                validTiles = validateTiles(w, i + 1);
                if (validTiles == 0 || l == 0)
                {
                    displayPlayerTiles(i + 1);
                    w = getWord(m);
                }
                else
                {
                    saveStateTiles(i);
                    removeTiles(w, i + 1);
                    break;
                }

            } while ((validTiles == 0 || l == 0));

            if (w.word[0] == '!')
            {
                playerArr[i].skip = 1;
                system("CLS");
                continue;
            }
            openFile();

            int wExists = enterWordOnBoard(w);

            if (wExists == 0)
            {
                restoreStateBoard();
                for (int i = 0; i < cwPtr; i++)
                {
                    CurrentWord[i].c = '\0';
                }
                cwPtr = 0;
                restoreStateTiles(i);
                closeFile();
                goto play;
            }
            printf("\n");
            fw++;

            playerArr[i].total_points += TotalPoints;
            TotalPoints = 0;
        }
        int skipTotal = 0;
        for (int i = 0; i < noPlayers; i++)
        {
            skipTotal += playerArr[i].skip;
            playerArr[i].skip = 0;
        };
        if (skipTotal == noPlayers)
            return;
        closeFile();
        reset();
    } while (gameOver(noPlayers) != 0);
}