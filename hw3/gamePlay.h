#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "checkGame.h"
#include "gameBoard.h"

#define MAT_SIZE 10

int IfSubGone(char matGame[MAT_SIZE][MAT_SIZE] , int x , int y);

//fires on the board
int fireOnBoard(char matGame[MAT_SIZE][MAT_SIZE], int line, int row);

//reads all the moves from the simulation file
void readMoves(char p1Mat[MAT_SIZE][MAT_SIZE], char p2Mat[MAT_SIZE][MAT_SIZE], FILE* f);