#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

#include "definitions.h" // contains type definitions, enums, and macros
#include "prototypes.h"  // contains function prototypes
#include "colors.h"      // contains the different colors
#include "board.h"       // contains functions related to the board
#include "file.h"        // contains functions related to file operations
#include "validation.h"  // contains functions related to word and tile validation
#include "playgame.h"    // contains functions related to playing the game
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
