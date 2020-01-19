#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_NAME 30
#define SIZE_LINE 256

typedef struct Book {
    char code[SIZE_NAME];
    char bookName[SIZE_NAME];
    char authorName[SIZE_NAME];
    int pages;
    int yearPublish;
    char category[SIZE_NAME];
}Book;

int printMainMenu()
{
    int choice;

    printf("press the number you want: \n");
    printf("1. add book\n");
    printf("2. delete book\n");
    printf("3. search book\n");
    printf("4. print all the books\n");
    printf("5. save all the library in file\n");
    printf("6. get more books from file\n");
    printf("7. exit\n");
    scanf("%d", &choice);

    return choice;
}

void myStringLen(char* word)
{
    int i = 0;

    while(word[i] != '\0')
    {
        i++;
    }

    printf(">>>>>%d\n", i);
}

int howManyLines(FILE* fp)
{
    char str[SIZE_LINE];
    int counter = 0;
    while (fgets(str, SIZE_LINE, fp) != NULL)
    {
        counter++;
    }

    fseek(fp, 0, SEEK_SET);
    return counter;
}

void checkOpenFile(FILE* fp)
{
    if(fp == NULL)
    {
        printf("file did not openned\n");
        exit(1);
    }
    else
    {
        printf("file openned\n");
    }
}

void myCloseFile(FILE* fp)
{
    fclose(fp);
    printf("file closed\n");
}

void putFileIntoArr(FILE* fp, int size, Book* bookArr)
{
    char str[SIZE_LINE];
    int i;
    for(i=0; i<size; i++)
    {
        //[^\n]
        fgets(str, SIZE_LINE, fp);
        char* cutHere = strtok(str, ",");
        sscanf(cutHere, "%s", bookArr[i].code);
        //printf(">after code: %s\n", newBook->code);
        cutHere = strtok(NULL, ",");
        sscanf(cutHere, "%[^\n]s", bookArr[i].bookName);
        //printf(">after bookName: %s\n", newBook->bookName);
        cutHere = strtok(NULL, ",");
        sscanf(cutHere, "%[^\n]s", bookArr[i].authorName);
        //printf(">after authorName: %s\n", newBook->authorName);
        cutHere = strtok(NULL, ",");
        sscanf(cutHere, "%d", &bookArr[i].pages);
        //printf(">after pages: %d\n", newBook->pages);
        cutHere = strtok(NULL, ",");
        sscanf(cutHere, "%d", &bookArr[i].yearPublish);
        //printf(">after yearPublish: %d\n", newBook->yearPublish);
        cutHere = strtok(NULL, ",");
        sscanf(cutHere, "%s", bookArr[i].category);
        //printf(">after category: %s\n", newBook->category);
    }
}

void printAllBooks(Book* bookArr, int size)
{
    int i;
    for(i=0; i<size; i++)
    {
        printf("%d. %s, %s, %s, %d, %d, %s\n", i+1, bookArr[i].code, bookArr[i].bookName, bookArr[i].authorName, bookArr[i].pages, bookArr[i].yearPublish, bookArr[i].category);
    }
}

int howManyBook(Book* bookArr)
{
    int i=0;
    
    while(bookArr[i].pages > 0)
    {
        i++;
    }

    return i;
}

void searchBook(Book* bookArr, int numOfBooks)
{
    int i, comper;
    char findCode[SIZE_NAME] = {0};

    printf("put book's code that you want to find\n");
    fseek(stdin,0,SEEK_END);
    fflush(stdin);
    gets(findCode);

    for(i=0; i < numOfBooks; i++)
    {
        comper = strcmp(bookArr[i].code, findCode);
        if(comper == 0)
        {
            printf("%s, %s, %s, %d, %d, %s\n", bookArr[i].code, bookArr[i].bookName, bookArr[i].authorName, bookArr[i].pages, bookArr[i].yearPublish, bookArr[i].category);
            break;
        }
    }
    if(i==numOfBooks)
    {
        printf("sorry, there is no book with that code\n");
    }
}

void addBook(Book* bookArr, int numOfBooks)
{
    int num = numOfBooks + 1;
    
    bookArr = (Book*)realloc(bookArr, num * sizeof(Book));
    printf("Put book's serial number\n");
    fseek(stdin,0,SEEK_END);
    fflush(stdin);
    gets(bookArr[num-1].code);
    printf("Put book's name\n");
    fseek(stdin,0,SEEK_END);
    fflush(stdin);
    gets(bookArr[num-1].bookName);
    printf("Put author's name\n");
    fseek(stdin,0,SEEK_END);
    fflush(stdin);
    gets(bookArr[num-1].authorName);
    printf("Put book's number of pages\n");
    scanf("%d", &bookArr[num-1].pages);
    printf("Put book's year of publish\n");
    scanf("%d", &bookArr[num-1].yearPublish);
    printf("Put book's category\n");
    fseek(stdin,0,SEEK_END);
    fflush(stdin);
    gets(bookArr[num-1].category);
}

void deleteBook(Book* bookArr, int numOfBooks)
{
    int i, num = numOfBooks - 1;
    char findCode[SIZE_NAME] = {0};

    printf("put book's code that you want to delete\n");
    fseek(stdin,0,SEEK_END);
    fflush(stdin);
    gets(findCode);

    for(i=0; i<numOfBooks; i++)
    {
        if(strcmp(bookArr[i].code, findCode) == 0)
        {
            break;
        }
    }

    for(; i<numOfBooks - 1; i++)
    {
        bookArr[i] = bookArr[i+1];
    }
    
    *bookArr[numOfBooks - 1].code = 0;
    *bookArr[numOfBooks - 1].bookName = 0;
    *bookArr[numOfBooks - 1].authorName = 0;
    bookArr[numOfBooks - 1].pages = 0;
    bookArr[numOfBooks - 1].yearPublish = 0;
    *bookArr[numOfBooks - 1].category = 0;
    
    bookArr = (Book*)realloc(bookArr, num * sizeof(Book));
    printAllBooks(bookArr, numOfBooks);
}

void putIntoFile(Book* bookArr, int numOfBooks)
{
    FILE* fnw;
    char newFileName[SIZE_NAME];
    int i;

    printf("put new file's name to write into:\n");
    fseek(stdin,0,SEEK_END);
    fflush(stdin);
    gets(newFileName);
    fnw = fopen(newFileName, "w");
    checkOpenFile(fnw);

    for(i=0; i<numOfBooks; i++)
    {
        fprintf(fnw, "%s,%s,%s,%d,%d,%s\n", bookArr[i].code, bookArr[i].bookName, bookArr[i].authorName, bookArr[i].pages, bookArr[i].yearPublish, bookArr[i].category);
    }

    myCloseFile(fnw);
}

void loadNewFile(Book* bookArr, int numOfBooks)
{
    FILE* flb;
    int numNewBooks, choice;
    char newFileName[SIZE_NAME];

    printf("put new file's name to load from:\n");
    fseek(stdin,0,SEEK_END);
    fflush(stdin);
    gets(newFileName);
    flb = fopen(newFileName, "w");
    checkOpenFile(flb);
    
    NEW_FILE_AGAIN:
    printf("choose:\n");
    printf("1. add to current library\n");
    printf("2. create new library\n");
    scanf("%d", &choice);

    numNewBooks = howManyLines(flb);

    if(choice == 1)
    {
        int sumOfBooks = numNewBooks + numOfBooks;
        bookArr = (Book*)realloc(bookArr, sumOfBooks * sizeof(Book));
        putFileIntoArr(flb, numNewBooks, &bookArr[numOfBooks-1]);
    }
    else if(choice == 2)
    {
        bookArr = (Book*)realloc(bookArr, numNewBooks * sizeof(Book));
        putFileIntoArr(flb, numNewBooks, bookArr);
    }
    else
    {
        printf("wrong number, choose again\n");
        goto NEW_FILE_AGAIN;
    }

    myCloseFile(flb);
}

int main()
{
    FILE* fp;
    char fileName[SIZE_NAME], str[SIZE_LINE], findCode[SIZE_NAME];
    int i, choice, linesInFile, numOfBooks;
    Book* bookArr;

    printf("put file's name:\n");
    fflush(stdin);
    gets(fileName);
    fp = fopen(fileName, "r");
    checkOpenFile(fp);

    linesInFile = howManyLines(fp);

    //printf(">number of lines in the file %d\n", linesInFile);

    bookArr = (Book*)calloc(linesInFile, sizeof(Book));

    putFileIntoArr(fp, linesInFile, bookArr);

    //printAllBooks(bookArr, linesInFile);

    choice = printMainMenu();
    while(choice != 7)
    {
        if(choice == 1)
        {
            addBook(bookArr, howManyBook(bookArr));
        }
        else if(choice == 2)
        {
            deleteBook(bookArr, howManyBook(bookArr));
        }
        else if(choice == 3)
        {
            searchBook(bookArr, howManyBook(bookArr));
        }
        else if(choice == 4)
        {
            printAllBooks(bookArr, howManyBook(bookArr));
        }
        else if(choice == 5)
        {
            putIntoFile(bookArr, howManyBook(bookArr));
        }
        else if(choice == 6)
        {
            loadNewFile(bookArr, howManyBook(bookArr));
        }
        else
        {
            printf("whrong choice try again\n");
        }
        choice = printMainMenu();
    }

    myCloseFile(fp);
    printf("bye bye\n");
    free(bookArr);

    return 0;
}