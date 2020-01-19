#include "queue.h"

struct Queue_t {
    int** data;
    int head, tail;
    int count, maxSize;

    CompareFunction compareData;
    CopyFunction copyData;
    FreeFunction freeData;
};

Bool isEmpty(Queue queue) {
    //	TODO:	complete this section yourselves, you may also change and improve this function as you like
}

Bool isFull(Queue queue) {
    //	TODO:	complete this section yourselves, you may also change and improve this function as you like
}

Queue createQueue(int maxSize, CompareFunction compareData, CopyFunction copyData, FreeFunction freeData) {
    //	TODO:	complete this section yourselves

    queue->head = queue->tail = 0;
    queue->count = 0;
    queue->maxSize = maxSize + 1;
    queue->compareData = compareData;
    queue->copyData = copyData;
    queue->freeData = freeData;

    return queue;
}

Result enqueue(Queue queue, int* data) {
    if (NULL == queue || NULL == data) return BAD_ARGUMENT;

    if (TRUE == isFull(queue)) return FULL;

    int* copy = queue->copyData(data);
    if (NULL == copy) return FAIL;

    queue->data[queue->tail++] = copy;
    queue->tail %= queue->maxSize;
    ++queue->count;

    return SUCCESS;
}

Result dequeue(Queue queue) {
    if (NULL == queue) return BAD_ARGUMENT;

    if (TRUE == isEmpty(queue)) return EMPTY;

    queue->freeData(queue->data[queue->head++]);
    queue->head %= queue->maxSize;
    --queue->count;

    return SUCCESS;
}

Result queueTop(Queue queue, int** res) {
    //	TODO:	complete this section yourselves
}

Result contains(Queue queue, int* data, Bool* res) {
    if (NULL == queue || NULL == data || NULL == res) return BAD_ARGUMENT;

    if (TRUE == isEmpty(queue)) return EMPTY;

    for (int i = queue->head; i != queue->tail; i = (i+1) % queue->maxSize)
        if (0 == queue->compareData(queue->data[i], data)) {
            *res = TRUE;
            return SUCCESS;
        }

    return FAIL;
}

Result mergeQueue(Queue source, Queue destination) {
    if (NULL == source || NULL == destination || source->compareData != destination->compareData) return FAIL;

    if (TRUE == isFull(destination)) return FULL;
    if (TRUE == isEmpty(source)) return EMPTY;

    if (destination->maxSize - 1 - destination->count < source->count) return FAIL;

    //	TODO:	complete this section yourselves
}

void freeQueue(Queue queue) {
    while (SUCCESS == dequeue(queue));
    free(queue->data);
    free(queue);
}