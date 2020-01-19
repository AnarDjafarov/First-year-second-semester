#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "checkGame.h"
#include "gameBoard.h"
#include "gamePlay.h"

int main(int arvc, char* argv[])
{
    FILE* ff;
    FILE* sf;
    FILE* simf;
    char matGame1[MAT_SIZE][MAT_SIZE];
    char matGame2[MAT_SIZE][MAT_SIZE];
    char* fileName1 = argv[1];
    char* fileName2 = argv[2];
    char* fileName3 = argv[3];

    //Files treatment
    ff = fopen(fileName1, "r");
    checkOpenFile(ff, fileName1);
    
    sf = fopen(fileName2, "r");
    checkOpenFile(sf, fileName2);

    simf = fopen(fileName3, "r");
    checkOpenFile(simf, fileName3);
    //End files treatment

    //The game starts here
    //
    //
    resetMat(matGame1);
    resetMat(matGame2);
    printf(">> got here after resetMat\n");

    putFileIntoMat(matGame1, ff);
    putFileIntoMat(matGame2, sf);
    printf(">> got here after put into file\n");

    readMoves(matGame1, matGame2, simf);
    printf(">> the game is ended\n");

    myCloseFile(ff);
    myCloseFile(sf);
    myCloseFile(simf);
}

// ./prog p1.txt p2.txt Simulation.txt