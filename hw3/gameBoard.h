#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "checkGame.h"

#define MAT_SIZE 10

//resets the mats before the game
void resetMat(char matGame[MAT_SIZE][MAT_SIZE]);

//puts all the player's subs into mat
void putFileIntoMat(char matGame[MAT_SIZE][MAT_SIZE], FILE* f);

//prints both mats
void printMat(char matGame1[MAT_SIZE][MAT_SIZE], char matGame2[MAT_SIZE][MAT_SIZE], FILE* f);