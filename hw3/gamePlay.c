#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gameBoard.h"
#include "checkGame.h"

#define MAT_SIZE 10
#define LINE_SIZE 30

#define CAPITAL_LETTER_TO_INT(a) (a - 65)

typedef struct player_t{
    char* playerNum;
    int count;
}player_t;

int IfSubGone(char matGame[MAT_SIZE][MAT_SIZE] , int x , int y)
{
    int temp_X = x , temp_Y = y , flag = 1;
    if(CheckDirection(matGame , x , y) == 1)
            {
                while(matGame[temp_X][temp_Y] != '-' && matGame[temp_X][temp_Y] != 'x')
                {
                    if(matGame[temp_X][temp_Y] == 'O')
                        flag = 0;
                    temp_X++;
                }
                temp_X = x;
                while(matGame[temp_X][temp_Y] != '-' && matGame[temp_X][temp_Y] != 'x')
                {
                    if(matGame[temp_X][temp_Y] == 'O')
                        flag = 0;
                    temp_X--;
                }
            }
            if(CheckDirection(matGame , x , y) == 2)
            {
                while(matGame[temp_X][temp_Y] != '-' && matGame[temp_X][temp_Y] != 'x')
                {
                    if(matGame[temp_X][temp_Y] == 'O')
                        flag = 0;
                    temp_Y++;
                }
                temp_Y = y;
                while(matGame[temp_X][temp_Y] != '-' && matGame[temp_X][temp_Y] != 'x')
                {
                    if(matGame[temp_X][temp_Y] == 'O')
                        flag = 0;
                    temp_Y--;
                }
            }
            return flag;
}

//fires on the board
int fireOnBoard(char matGame[MAT_SIZE][MAT_SIZE], int line, int row)
{
    if(matGame[line][row] == 'O')
    {
        matGame[line][row] = 'X';
        return 1;
    }

    matGame[line][row] = 'x';
    return 0;
}

//reads all the moves from the simulation file
void readMoves(char p1Mat[MAT_SIZE][MAT_SIZE], char p2Mat[MAT_SIZE][MAT_SIZE], FILE* f)
{
    FILE* fp;
    char str[LINE_SIZE], tempStr[LINE_SIZE], movment[LINE_SIZE];
    char fileName[] = "Result.txt";
    int line, row, hit, end, im=0;
    player_t p1, p2;
    char movmentMat[100][30];


    p1.playerNum = "PLAYER_1";
    p2.playerNum = "PLAYER_2";
    p1.count = 0;
    p2.count = 0;

    fp = fopen(fileName, "w+");
    checkOpenFile(fp, fileName);
    while(fgets(str, LINE_SIZE, f) != NULL)
    {
        char* cuthere = strtok(str, " \n");
        sscanf(cuthere, "%s", tempStr);
        if(strcmp(p1.playerNum, tempStr) == 0)
        {
            cuthere = strtok(NULL, " \n");
            strcpy(movment, cuthere);
            row = CAPITAL_LETTER_TO_INT(movment[0]);
            sscanf(&movment[1], "%d", &line);
            line--;
            if(p1.count == p2.count && checkMoveIsGood(row, line) == 1)
            {
                p1.count++;
                hit = fireOnBoard(p2Mat, line, row);
                if(hit == 1)
                {
                    fprintf(fp, "hit %s %s\n", p1.playerNum, movment);
                    strcpy(movmentMat[im], "hit\t\t");
                    strcat(movmentMat[im], p1.playerNum);
                    strcat(movmentMat[im], " ");
                    strcat(movmentMat[im], movment);
                    im++;
                    if(IfSubGone(p2Mat, line, row) == 1)
                    {
                        fprintf(fp, "The submarine was destroyed\n");
                    }
                }
                else
                {
                    fprintf(fp, "miss %s %s\n", p1.playerNum, movment);
                    strcpy(movmentMat[im], "miss\t");
                    strcat(movmentMat[im], p1.playerNum);
                    strcat(movmentMat[im], " ");
                    strcat(movmentMat[im], movment);
                    im++;
                }
            }
            else
            {
                if(checkMoveIsGood(row, line) == 0)
                {
                    p1.count++;
                }
                fprintf(fp, "ILLEAGAL_MOVE %s %s\n", p1.playerNum, movment);
                strcpy(movmentMat[im], "ILLEAGAL_MOVE\t");
                strcat(movmentMat[im], p1.playerNum);
                strcat(movmentMat[im], " ");
                strcat(movmentMat[im], movment);
                im++;
            }
            
        }
        else if(strcmp(p2.playerNum, tempStr) == 0)
        {
            cuthere = strtok(NULL, " \n");
            strcpy(movment, cuthere);
            row = CAPITAL_LETTER_TO_INT(movment[0]);
            sscanf(&movment[1], "%d", &line);
            line--;
            if(p1.count == (p2.count + 1) && checkMoveIsGood(row, line) == 1)
            {
                p2.count++;
                hit = fireOnBoard(p1Mat, line, row);
                if(hit == 1)
                {
                    fprintf(fp, "hit %s %s\n", p2.playerNum, movment);
                    strcpy(movmentMat[im], "hit\t\t");
                    strcat(movmentMat[im], p2.playerNum);
                    strcat(movmentMat[im], " ");
                    strcat(movmentMat[im], movment);
                    im++;
                    if(IfSubGone(p1Mat, line, row) == 1)
                    {
                        fprintf(fp, "The submarine was destroyed\n");
                    }
                }
                else
                {
                    fprintf(fp, "miss %s %s\n", p2.playerNum,movment);
                    strcpy(movmentMat[im], "miss\t");
                    strcat(movmentMat[im], p2.playerNum);
                    strcat(movmentMat[im], " ");
                    strcat(movmentMat[im], movment);
                    im++;
                }
            }
            else
            {
                if(checkMoveIsGood(row, line) == 0)
                {
                    p2.count++;
                }
                fprintf(fp, "ILLEAGAL_MOVE %s %s\n", p2.playerNum, movment);
                strcpy(movmentMat[im], "ILLEAGAL_MOVE\t");
                strcat(movmentMat[im], p2.playerNum);
                strcat(movmentMat[im], " ");
                strcat(movmentMat[im], movment);
                im++;
            }
        }
        else if(strcmp("PRINT_BOARD", tempStr) == 0)
        {
            printMat(p1Mat, p2Mat, fp);
        }
        else if(strcmp("PRINT_MOVEMENTS", tempStr) == 0)
        {
            fprintf(fp, "All the movments:\n");
            for(int i=0; i<im; i++)
            {
                fprintf(fp, "%s\n", movmentMat[i]);
            }
        }

        if(checkIfEnded(p1Mat, p2.playerNum, fp) == 1 || checkIfEnded(p2Mat, p1.playerNum, fp) == 1)
        {
            printMat(p1Mat, p2Mat, fp);
            fprintf(fp, "All the movments:\n");
            for(int i=0; i<im; i++)
            {
                fprintf(fp, "%s\n", movmentMat[i]);
            }

            break;
        }
    }

    myCloseFile(fp);
}

