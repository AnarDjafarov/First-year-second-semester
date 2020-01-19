#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct Queue_t* Queue;

typedef int (*CompareFunction)(int*, int*);
typedef int* (*CopyFunction)(int*);
typedef void (*FreeFunction)(int*);

typedef enum { SUCCESS, FAIL, BAD_ARGUMENT, FULL, EMPTY } Result;
typedef enum { FALSE, TRUE } Bool;

Queue createQueue(int maxSize, CompareFunction compareData, CopyFunction copyData, FreeFunction freeData);
Bool isEmpty(Queue queue);
Bool isFull(Queue queue);
Result enqueue(Queue queue, int* data);
Result dequeue(Queue queue);
Result queueTop(Queue queue, int** res);
Result contains(Queue queue, int* data, Bool* res);
Result mergeQueue(Queue source, Queue destination);
void freeQueue(Queue queue);

#endif  //QUEUE_H_