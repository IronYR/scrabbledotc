#pragma once
#include "defs.h"
/*******************************************************************************************************************************************
                                                            Function Prototypes
********************************************************************************************************************************************/
int calculatePointsWord(Letter word[], int length);
void resetFlags();

void enterCharacterOnBoard(char ch, int y, int x);
Word getWord(int i);
void getSubWordY(int y, int x);
void getSubWordX(int y, int x);
int enterWordOnBoard(Word w);

void displayPlayerTiles(int playerNo);
int validateTiles(Word w, int player);
void removeTiles(Word w, int player);
void getPlayerTiles(int player);

bool wordExists(Letter[], int);
int openFile();
void closeFile();

void saveState();
void restoreState();
int outOfBounds(Word w);
int validatePosition(Word w);
int validateFirstWord(Word w);

void saveTiles(int player);
void restoreTiles(int player);

int gameOver(int noPlayers);
void displayPoints(int noPlayers);
void initGame(int noPlayers);
void declareWinner(int noPlayers);
void playScrabble(int noPlayers);