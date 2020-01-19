#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "checkGame.h"

//first lines second amudot

#define MAT_SIZE 10
#define CAPITAL_LETTER_TO_INT(a) (a - 65)


void resetMat(char matGame[MAT_SIZE][MAT_SIZE])
{
    for(int i=0; i<MAT_SIZE; i++)
    {
        for(int j=0; j<MAT_SIZE; j++)
        {
            matGame[i][j] = '-';
        }
    }
}

void putFileIntoMat(char matGame[MAT_SIZE][MAT_SIZE], FILE* f)
{
    char firstPlace[30], secondPlace[30];
    int firstLine, secondLine, firstRow, secondRow;
    char str[30];

    while(fgets(str, 30, f) != NULL)
    {
        char* cutHere = strtok(str, "-");
        strcpy(firstPlace, cutHere);
        cutHere = strtok(NULL, "-\n");
        strcpy(secondPlace, cutHere);
        sscanf(&firstPlace[1], "%d", &firstLine);
        sscanf(&secondPlace[1], "%d", &secondLine);
        firstLine--;
        secondLine--;
        firstRow = CAPITAL_LETTER_TO_INT(firstPlace[0]);
        secondRow = CAPITAL_LETTER_TO_INT(secondPlace[0]);

        if(firstRow - secondRow == 0)
        {
            for(int i=firstLine; i<=secondLine; i++)
            {
                matGame[i][firstRow] = 'O';
            }
        }
        else
        {
            for(int i=firstRow; i<=secondRow; i++)
            {
                matGame[firstLine][i] = 'O';
            }
        }
    }
}

void printMat(char matGame1[MAT_SIZE][MAT_SIZE], char matGame2[MAT_SIZE][MAT_SIZE], FILE* f)
{
    if(f == NULL)
    {
        printf("The file to print into is closed\n");
        return;
    }

    fprintf(f, "* A B C D E F G H I J\t* A B C D E F G H I J\n");
    for(int i=0; i<MAT_SIZE; i++)
    {
        fprintf(f, "%d ", i+1);
        for(int j=0; j<MAT_SIZE; j++)
        {
            fprintf(f, "%c ", matGame1[i][j]);
        }
        fprintf(f, "\t");
        fprintf(f, "%d ", i+1);
        for(int j=0; j<MAT_SIZE; j++)
        {
            fprintf(f, "%c ", matGame2[i][j]);
        }
        fprintf(f, "\n");
    }
}