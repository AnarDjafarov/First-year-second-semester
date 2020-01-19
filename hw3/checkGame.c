#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAT_SIZE 10

void checkOpenFile(FILE* fp, char* fileName)
{
    if(fp == NULL)
    {
        printf("file did not openned\n");
        exit(1);
    }
    else
    {
        printf("file (%s) openned \n", fileName);
    }
}

void myCloseFile(FILE* fp)
{
    fclose(fp);
    printf("file closed\n");
}

int checkMoveIsGood(int row, int line)
{
    if(row>=0 && row<11 && line>=0 && line<11)
    {
        return 1;
    }
    
    return 0;
}

int checkIfEnded(char matGame[MAT_SIZE][MAT_SIZE], char* playerNum, FILE* f)
{
    int i, j, counter=0;

    for(i=0; i<MAT_SIZE; i++)
    {
        for(j=0; j<MAT_SIZE; j++)
        {
            if(matGame[i][j] == 'O')
            {
                counter++;
            }
        }
    }

    if(counter > 0)
    {
        return 0;
    }

    fprintf(f ,"%s WON!!\n", playerNum);

    return 1;
}

int CheckDirection(char matGame[MAT_SIZE][MAT_SIZE], int x , int y)
{
    int direction;
    if(matGame[x][y] == 'X')
    {
        if(matGame[x - 1][y] == 'X' || matGame[x - 1][y] == 'O' || matGame[x + 1][y] == 'X' || matGame[x + 1][y] == 'O')
            return 1;
        if(matGame[x][y + 1] == 'X' || matGame[x][y - 1] == 'O' || matGame[x][y + 1] == 'X' || matGame[x][y + 1] == 'O')
            return 2;
    }   
    return 0;
}