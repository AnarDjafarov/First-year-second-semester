#include "queue.h"

int compareInt(int* x, int* y) { return *x - *y; }

void freeInt(int* n) { if (NULL != n) free(n); }

int* copyInt(int* n) {
    if (NULL == n) return NULL;

    int* p = (int*)malloc(1*sizeof(int));
    if (NULL != p) *p = *n;

    return p;
}

int main() {
    Queue q1 = createQueue(10, compareInt, copyInt, freeInt);
    Queue q2 = createQueue(10, compareInt, copyInt, freeInt);
    Queue q3 = createQueue(15, compareInt, copyInt, freeInt);
    Queue q4 = createQueue(15, compareInt, copyInt, freeInt);

    for (int i = 0; i < 3; ++i)
        if (SUCCESS != enqueue(q1, &i)) break;
    
    for (int i = 3; i < 7; ++i)
        if (SUCCESS != enqueue(q2, &i)) break;
    
    for (int i = 3; i < 30; ++i)
        if (SUCCESS != enqueue(q4, &i)) break;
    
    mergeQueue(q2, q3);
    mergeQueue(q1, q3);
    mergeQueue(q4, q3);

    Bool res;
    int criteria = 0;
    contains(q3, &criteria, &res);
    if (TRUE == res) puts("q3 contains the value '0'");
    
    while (FALSE == isEmpty(q3)) {
        int* p;
        queueTop(q3, &p);
        printf("%d ", *p);
        free(p);
        dequeue(q3);
    }
    printf("\n");

    if (TRUE == isEmpty(q1) && TRUE == isEmpty(q2)) {
        printf("both queues are empty!\n");
    }

    freeQueue(q3);
    freeQueue(q4);

    return 0;
}