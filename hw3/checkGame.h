#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAT_SIZE 10

//checks if the file openned
void checkOpenFile(FILE* fp, char* fileName);

//closes the file
void myCloseFile(FILE* fp);

//check if the move is good
int checkMoveIsGood(int row, int line);

//checks if the game is ended
int checkIfEnded(char matGame[MAT_SIZE][MAT_SIZE], char* playerNum, FILE* f);


int CheckDirection(char matGame[MAT_SIZE][MAT_SIZE], int x , int y);