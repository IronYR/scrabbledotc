#pragma once
#include <stdio.h>
#include <string.h>
#include "definitions.h"
#include "prototypes.h"
/***********************************************************************************************************************
                                                            POSITION VALIDATION
*************************************************************************************************************************/

/**
 * Saves the current state of the board.
 *
 * @returns None
 */
void saveStateBoard()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int l = 0; l < BOARD_SIZE; l++)
        {
            OldBoard[i][l] = board[i][l];
        }
    }
}

/**
 * Restores the state of the board to the previous state.
 *
 * @returns None
 */
void restoreStateBoard()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int l = 0; l < BOARD_SIZE; l++)
        {
            board[i][l] = OldBoard[i][l];
        }
    }
}

/**
 * Saves the tiles of a player.
 *
 * @param player The player whose tiles are to be saved.
 *
 * @returns None
 */
void saveStateTiles(int player)
{
    tempTileptr = playerArr[player].ptr;
    for (int i = 0; i < USER_TILES_SIZE; i++)
    {
        tempTileArray[i] = playerArr[player].tiles[i];
    }
}

/**
 * Restores the tiles of a player.
 *
 * @param player The player whose tiles are to be restored.
 *
 * @returns None
 */
void restoreStateTiles(int player)
{
    playerArr[player].ptr = tempTileptr;
    for (int i = 0; i < USER_TILES_SIZE; i++)
    {
        playerArr[player].tiles[i] = tempTileArray[i];
    }
}

/**
 * Validates the tiles chosen by the player.
 *
 * @param w The word to be played.
 * @param player The player who is playing the word.
 *
 * @returns 1 if the tiles are valid, 0 otherwise.
 */
int validateTiles(Word w, int player)
{
    int found = 0;
    for (int i = 0; i < strlen(w.word) - 1; i++)
    {
        for (int j = 0; j < USER_TILES_SIZE; j++)
        {
            if (playerArr[player - 1].tiles[j].c == w.word[i])
            {
                found = 1;
                break;
            }
        }
        if (found == 0)
        {
            printf("Invalid Tile Choice. try again\n");
            return 0;
        }
        found = 0;
    }
}

/**
 * Removes tiles from the player's hand.
 *
 * @param w The word to be removed.
 * @param player The player whose hand is to be modified.
 *
 * @returns None
 */
void removeTiles(Word w, int player)
{
    if (strlen(w.word) - 1 == USER_TILES_SIZE)
    {
        playerArr[player - 1].total_points += 50;
    }
    for (int i = 0; i < strlen(w.word) - 1; i++)
    {
        for (int j = 0; j < USER_TILES_SIZE; j++)
        {
            if (playerArr[player - 1].tiles[j].c == w.word[i])
            {

                for (int k = j; k < USER_TILES_SIZE; k++)
                {
                    playerArr[player - 1].tiles[k] = playerArr[player - 1].tiles[k + 1];
                }
                playerArr[player - 1].tiles[6].c = '\0';
                playerArr[player - 1].tiles[6].points = 0;

                playerArr[player - 1].ptr--;
                break;
            }
        }
    }
}
/**
 * Checks if the word is out of bounds.
 *
 * @param w The word to check.
 *
 * @returns 0 if the word is out of bounds, 1 otherwise.
 */
int outOfBounds(Word w)
{
    int j = 0;

    switch (w.dire)
    {
    case right:

        for (int i = 0; i < strlen(w.word) - 1; i++)
        {

            while (board[w.y][w.x + j].c != ' ' && board[w.y][w.x + j].c != '!' && board[w.y][w.x + j].c != '*' && board[w.y][w.x + j].c != '2' && board[w.y][w.x + j].c != '3')
            {

                j++;
            }
            if (w.x + j > 15)
            {
                printf("Out of bounds\n");
                restoreStateBoard();
                return 0;
            }

            j++;
        }

        break;

    case down:
        for (int i = 0; i < strlen(w.word) - 1; i++)
        {

            while (board[w.y + j][w.x].c != ' ' && board[w.y + j][w.x].c != '!' && board[w.y + j][w.x].c != '*' && board[w.y + j][w.x].c != '2' && board[w.y + j][w.x].c != '3')
            {

                j++;
            }
            if (w.y + j > 15)
            {
                printf("Out of bounds\n");
                restoreStateBoard();
                return 0;
            }

            j++;
        }

        break;
    }
    return 1;
}

/**
 * Validates the position of a word.
 *
 * @param w The word to validate.
 *
 * @returns 1 if the word is valid, 0 otherwise.
 */
int validatePosition(Word w)
{

    int o = outOfBounds(w);
    if (o == 0)
    {
        return 0;
    }
    for (int i = 0; i < strlen(w.word) - 1; i++)
    {

        switch (w.dire)
        {
        case (right):
            if (w.y + 1 < 16 && board[w.y + 1][w.x + i].c >= 'A' && board[w.y + 1][w.x + i].c <= 'Z')
                return 1;
            if (w.y - 1 != 0 && board[w.y - 1][w.x + i].c >= 'A' && board[w.y - 1][w.x + i].c <= 'Z')
                return 1;
            if (w.x - 1 != 0 && board[w.y][w.x - 1].c >= 'A' && board[w.y][w.x - 1].c <= 'Z')
                return 1;
            if (w.x + strlen(w.word) - 1 < 16 && board[w.y][w.x + strlen(w.word) - 1].c >= 'A' && board[w.y][w.x + strlen(w.word) - 1].c <= 'Z')
                return 1;
            break;
        case (down):
            if (w.x + 1 < 16 && board[w.y + i][w.x + 1].c >= 'A' && board[w.y + i][w.x + 1].c <= 'Z')
                return 1;
            if (w.x - 1 != 0 && board[w.y + i][w.x - 1].c >= 'A' && board[w.y + i][w.x - 1].c <= 'Z')
                return 1;
            if (w.y - 1 != 0 && board[w.y - 1][w.x].c >= 'A' && board[w.y - 1][w.x].c <= 'Z')
                return 1;
            if (w.y + strlen(w.word) - 1 < 16 && board[w.y + strlen(w.word) - 1][w.x].c >= 'A' && board[w.y + strlen(w.word) - 1][w.x].c <= 'Z')
                return 1;
            break;
        default:
            printf("Invalid word positioning. Try again\n");
            return 0;
            break;
        }
    }
    printf("Invalid word positioning. Try again\n");
    return 0;
}

/**
 * Validates the position of the first word of the game.
 *
 * @param w The first word of the game.
 *
 * @returns 1 if the first word is valid, 0 otherwise.
 */
int validateFirstWord(Word w)
{
    switch (w.dire)
    {
    case right:
        for (int i = 0; i < strlen(w.word) - 1; i++)
        {
            if (w.x + i == 8 && w.y == 8)
                return 1;
        }
        printf("Invalid first word positioning. Try again\n");
        return 0;
        break;
    case down:
        for (int i = 0; i < strlen(w.word) - 1; i++)
        {
            if (w.x == 8 && w.y + i == 8)
                return 1;
        }
        printf("Invalid first word positioning. Try again\n");
        return 0;
        break;
    }
}

/**
 * Displays the tiles of a player.
 *
 * @param playerNo The player number.
 *
 * @returns None
 */
void displayPlayerTiles(int playerNo)
{

    printf("\n\n");
    for (int i = 0; i < strlen(playerArr[playerNo - 1].name) - 1; i++)
    {
        printf("%c", playerArr[playerNo - 1].name[i]);
    }
    printf("'s tiles:  ");
    for (int i = 0; i < playerArr[playerNo - 1].ptr; i++)
    {

        green();
        printf("|");
        reset();
        printf("%c_", playerArr[playerNo - 1].tiles[i].c);
        magenta();
        printf("%d", playerArr[playerNo - 1].tiles[i].points);
        green();
        printf("|  ");
        reset();
    }
    printf("\n\n");
}

/**
 * Gets the tiles for a player.
 *
 * @param player The player to get the tiles for.
 *
 * @returns None
 */
void getPlayerTiles(int player)
{

    while (playerArr[player - 1].ptr != USER_TILES_SIZE && NumTiles != 0)
    {
        srand((unsigned)time(NULL));
        int num = rand() % NumTiles;
        NumTiles--;
        playerArr[player - 1].tiles[playerArr[player - 1].ptr] = TileBag[num];
        playerArr[player - 1].ptr++;
        for (int j = num; j < NumTiles; j++)
        {
            TileBag[j] = TileBag[j + 1];
        }
    }
}

/******************************************************************************************************************************
 *                                                          ENTERING CHARACTERS/WORDS
 ********************************************************************************************************************************/

/**
 * Adds a character to the board.
 *
 * @param ch The character to add.
 * @param y The y-coordinate of the character.
 * @param x The x-coordinate of the character.
 *
 * @returns None
 */
void enterCharacterOnBoard(char ch, int y, int x)
{
    board[y][x].lm = 1;
    board[y][x].wm = 1;
    switch (board[y][x].c)
    {
    case '2':
        board[y][x].lm = 2;

        break;
    case '3':
        board[y][x].lm = 3;
        break;
    case '*':
        board[y][x].wm = 2;
        break;
    case '!':
        board[y][x].wm = 3;
        break;

    default:
        board[y][x].lm = 1;
        board[y][x].wm = 1;
        break;
    }

    board[y][x].c = ch;

    switch (ch)
    {
    case 'A':
        board[y][x].points = 1;
        break;
    case 'B':
        board[y][x].points = 3;
        break;
    case 'C':
        board[y][x].points = 3;
        break;
    case 'D':
        board[y][x].points = 2;
        break;
    case 'E':
        board[y][x].points = 1;
        break;
    case 'F':
        board[y][x].points = 4;
        break;
    case 'G':
        board[y][x].points = 2;
        break;
    case 'H':
        board[y][x].points = 4;
        break;
    case 'I':
        board[y][x].points = 1;
        break;
    case 'J':
        board[y][x].points = 8;
        break;
    case 'K':
        board[y][x].points = 5;
        break;
    case 'L':
        board[y][x].points = 1;
        break;
    case 'M':
        board[y][x].points = 3;
        break;
    case 'N':
        board[y][x].points = 1;
        break;
    case 'O':
        board[y][x].points = 1;
        break;
    case 'P':
        board[y][x].points = 3;
        break;
    case 'Q':
        board[y][x].points = 10;
        break;
    case 'R':
        board[y][x].points = 1;
        break;
    case 'S':
        board[y][x].points = 1;
        break;
    case 'T':
        board[y][x].points = 1;
        break;
    case 'U':
        board[y][x].points = 1;
        break;
    case 'V':
        board[y][x].points = 4;
        break;
    case 'W':
        board[y][x].points = 4;
        break;
    case 'X':
        board[y][x].points = 8;
        break;
    case 'Y':
        board[y][x].points = 4;
        break;
    case 'Z':
        board[y][x].points = 10;
        break;
    default:
        board[y][x].points = 0;
        break;
    }
}

/**
 * Gets a word from the user.
 *
 * @param i The index of the word.
 *
 * @returns The word.
 */
Word getWord(int i)
{
    Word word;

    printf("Enter word: ");
    if (i == 0)
    {
        fgets(word.word, 50, stdin);
    }
    else
    {
        fgets(word.word, 50, stdin);
        fgets(word.word, 50, stdin);
    }

    if (word.word[0] == '!')
        return word;
    for (int i = 0; word.word[i] != '\0'; i++)
    {
        if (word.word[i] >= 'a' && word.word[i] <= 'z')
        {
            word.word[i] = word.word[i] - 32;
        }
    }
    char coordinate;
    do
    {
        printf("Enter x coordinate:\n ");
        scanf_s("%c", &coordinate);
        coordinate = tolower(coordinate);
        if (coordinate < 'a' || coordinate > 'z')
            printf("Invalid coordinate. Re-enter please\n");
    } while (coordinate < 'a' || coordinate > 'z');
    word.x = coordinate - 96;
    do
    {
        printf("Enter y coordinate:\n ");
        scanf_s("%c", &coordinate);
        scanf_s("%c", &coordinate);
        coordinate = tolower(coordinate);
        if (coordinate < 'a' || coordinate > 'z')
            printf("Invalid coordinate. Re-enter please\n");
    } while (coordinate < 'a' || coordinate > 'z');
    word.y = coordinate - 96;
    do
    {
        printf("Enter 0 for down, 1 for right: ");
        scanf_s("%d", &word.dire);
        if (word.dire != 0 && word.dire != 1)
            printf("Invalid direction. Retry\n");
    } while (word.dire != 0 && word.dire != 1);
    return word;
}

/**
 * Gets the subword of the board in the y-axis.
 *
 * @param y The y coordinate of the board.
 * @param x The x coordinate of the board.
 *
 * @returns None
 */
void getSubWordY(int y, int x)
{

    int j = 0;

    while ((x - j - 1) != 0 && board[y][x - j - 1].c != ' ' && board[y][x - j - 1].c != '!' && board[y][x - j - 1].c != '*' && board[y][x - j - 1].c != '2' && board[y][x - j - 1].c != '3')
    {

        j++;
    }
    for (int i = 0; i < j; i++)
    {
        CurrentSubWord[i] = board[y][x - j + i];
    }
    CurrentSubWord[j] = board[y][x];
    j++;
    while ((x + j) < BOARD_SIZE && board[y][x + j].c != ' ' && board[y][x + j].c != '!' && board[y][x + j].c != '*' && board[y][x + j].c != '2' && board[y][x + j].c != '3')
    {
        CurrentSubWord[j] = board[y][x + j];
        j++;
    }

    cswPtr = j;
}

/**
 * Gets the subword of the board in the x-axis.
 *
 * @param y The y coordinate of the board.
 * @param x The x coordinate of the board.
 *
 * @returns None
 */
void getSubWordX(int y, int x)
{

    int j = 0;
    while ((y - j - 1) != 0 && board[y - j - 1][x].c != ' ' && board[y - j - 1][x].c != '!' && board[y - j - 1][x].c != '*' && board[y - j - 1][x].c != '2' && board[y - j - 1][x].c != '3')
    {

        j++;
    }
    for (int i = 0; i < j; i++)
    {
        CurrentSubWord[i] = board[y - j + i][x];
    }

    CurrentSubWord[j] = board[y][x];
    j++;
    while ((x + j) < BOARD_SIZE && board[y + j][x].c != ' ' && board[y + j][x].c != '!' && board[y + j][x].c != '*' && board[y + j][x].c != '2' && board[y + j][x].c != '3')
    {
        CurrentSubWord[j] = board[y + j][x];
        j++;
    }
    cswPtr = j;
}

/**
 * Enters word on board.
 *
 * @param w The word to check.
 * @returns 1 if the word is valid and can be entered on the board, 0 otherwise.
 */
int enterWordOnBoard(Word w)
{
    for (int i = 0; i < cwPtr; i++)
    {
        CurrentWord[i].c = '\0';
    }
    exists = false;
    int j = 0;
    cwPtr = 0;
    switch (w.dire)
    {
    case right:
        while ((w.x - cwPtr - 1) != 0 && board[w.y][w.x - cwPtr - 1].c != ' ' && board[w.y][w.x - cwPtr - 1].c != '!' && board[w.y][w.x - cwPtr - 1].c != '*' && board[w.y][w.x - cwPtr - 1].c != '2' && board[w.y][w.x - cwPtr - 1].c != '3')
        {
            cwPtr++;
        }
        for (int i = 0; i < cwPtr; i++)
        {
            CurrentWord[i] = board[w.y][w.x - cwPtr + i];
        }
        for (int i = 0; i < strlen(w.word) - 1; i++)
        {

            while (board[w.y][w.x + j].c != ' ' && board[w.y][w.x + j].c != '!' && board[w.y][w.x + j].c != '*' && board[w.y][w.x + j].c != '2' && board[w.y][w.x + j].c != '3')
            {
                CurrentWord[cwPtr] = board[w.y][w.x + j];

                cwPtr++;
                j++;
            }

            enterCharacterOnBoard(w.word[i], w.y, w.x + j);
            getSubWordX(w.y, w.x + j);

            if (cswPtr > 1)
            {
                exists = wordExists(CurrentSubWord, 16);
                if (!exists)
                {
                    return 0;
                }
                TotalPoints = TotalPoints + calculatePointsWord(CurrentSubWord, cswPtr);
            }

            for (int i = 0; i < cswPtr; i++)
            {

                CurrentSubWord[i].c = '\0';
                CurrentSubWord[i].points = 0;
            }
            CurrentWord[cwPtr] = board[w.y][w.x + j];

            cwPtr++;
            j++;
        }
        while ((w.x + cwPtr) < BOARD_SIZE && board[w.y][w.x + cwPtr].c != ' ' && board[w.y][w.x + cwPtr].c != '!' && board[w.y][w.x + cwPtr].c != '*' && board[w.y][w.x + cwPtr].c != '2' && board[w.y][w.x + cwPtr].c != '3')
        {
            CurrentWord[cwPtr] = board[w.y][w.x + cwPtr];

            cwPtr++;
        }
        exists = wordExists(CurrentWord, 16);
        if (!exists)
        {
            return 0;
        }
        TotalPoints = TotalPoints + calculatePointsWord(CurrentWord, cwPtr);
        break;

    case down:
        while ((w.y - cwPtr - 1) != 0 && board[w.y - cwPtr - 1][w.x].c != ' ' && board[w.y - cwPtr - 1][w.x].c != '!' && board[w.y - cwPtr - 1][w.x].c != '*' && board[w.y - cwPtr - 1][w.x].c != '2' && board[w.y - cwPtr - 1][w.x].c != '3')
        {
            cwPtr++;
        }
        for (int i = 0; i < cwPtr; i++)
        {
            CurrentWord[i] = board[w.y - cwPtr + i][w.x];
        }
        for (int i = 0; i < strlen(w.word) - 1; i++)
        {
            while (board[w.y + j][w.x].c != ' ' && board[w.y + j][w.x].c != '!' && board[w.y + j][w.x].c != '*' && board[w.y + j][w.x].c != '2' && board[w.y + j][w.x].c != '3')
            {
                CurrentWord[cwPtr] = board[w.y + j][w.x];
                cwPtr++;
                j++;
            }

            enterCharacterOnBoard(w.word[i], w.y + j, w.x);
            getSubWordY(w.y + j, w.x);

            if (cswPtr > 1)
            {
                exists = wordExists(CurrentSubWord, 16);
                if (!exists)
                {
                    return 0;
                }
                TotalPoints = TotalPoints + calculatePointsWord(CurrentSubWord, cswPtr);
            }

            for (int i = 0; i < cswPtr; i++)
            {

                CurrentSubWord[i].c = '\0';
                CurrentSubWord[i].points = 0;
            }

            CurrentWord[cwPtr] = board[w.y + j][w.x];
            cwPtr++;
            j++;
        }
        while ((w.y + cwPtr) < BOARD_SIZE && board[w.y + cwPtr][w.x].c != ' ' && board[w.y + cwPtr][w.x].c != '!' && board[w.y + cwPtr][w.x].c != '*' && board[w.y + cwPtr][w.x].c != '2' && board[w.y + cwPtr][w.x].c != '3')
        {
            CurrentWord[cwPtr] = board[w.y + cwPtr][w.x];
            cwPtr++;
        }
        exists = wordExists(CurrentWord, 16);
        if (!exists)
        {
            return 0;
        }

        TotalPoints = TotalPoints + calculatePointsWord(CurrentWord, cwPtr);
        break;
    }
    resetFlags();
    return 1;
}
/**
 * Checks if a word exissts in the dictionary.
 *
 * @param word The word to check.
 *
 * @returns True if the word exists in the dictionary, false otherwise.
 */
bool wordExists(Letter word[], int n)
{

    int line_num = 1;
    int find_result = 0;
    bool wExists = false;
    char temp[512];
    char w[100];
    printf("Word: ");
    for (int ks = 0; ks < n; ks++)
    {
        w[ks] = word[ks].c;
        printf("%c", w[ks]);
    }
    printf("\n");
    // strtok(w, "\n");
    w[strcspn(w, "\n")] = 0;
    while (fgets(temp, 512, fp) != NULL)
    {
        temp[strcspn(temp, "\n")] = 0;
        // strtok(temp, "\n");
        if ((strstr(temp, w)) != NULL)
        {
            int res = strcmp(temp, w);
            if (res == 0)
            {
                find_result++;
                line_num++;
                wExists = true;
                break;
            }
        }
        line_num++;
    }

    if (find_result == 0)
    {
        printf("\n%s is an incorrect word. Enter a valid word\n", w);
    }

    return wExists;
}

/**
 * Calculates the points for a word.
 *
 * @param word The word to calculate the points for.
 * @param length The length of the word.
 *
 * @returns The points for the word.
 */
int calculatePointsWord(Letter word[], int length)
{
    int wordPoints = 0;
    int WordMultiplier = 1;

    for (int i = 0; i < length; i++)
    {

        int charPoint = word[i].points * word[i].lm;
        wordPoints += charPoint;
        WordMultiplier = word[i].wm * WordMultiplier;
    }
    // First calculates all the points of the tile and then multiplies the total by the word multiplication factor

    wordPoints *= WordMultiplier;

    return wordPoints;
}

/**
 * Resets the flags for the board.
 *
 * @returns None
 */
void resetFlags()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j].lm = 1;
            board[i][j].wm = 1;
        }
    }
}
