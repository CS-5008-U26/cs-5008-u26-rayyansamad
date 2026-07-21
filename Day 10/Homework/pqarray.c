/* pqarray.c
 * Priority queue using a sorted array (smallest value at front)
 * Alternates asking how many numbers to add and remove
 * After each add batch, sorts the array so smallest is at front
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VALUE 100000000

typedef struct pqStruct {
    int *a;
    int n;
    int aSize;
} pq;

// createPQ
//   creates an empty priority queue
pq *createPQ() {
    pq *p = malloc(sizeof(pq));
    p->a = malloc(4 * sizeof(int));
    p->n = 0;
    p->aSize = 4;
    return p;
}

// compare
//   helper for qsort
int compare(const void *x, const void *y) {
    return (*(int *)x - *(int *)y);
}

// enqueue
//   adds a value, doubles backing store if needed
void enqueue(pq *p, int val) {
    if (p->n >= p->aSize) {
        int newSize = p->aSize * 2;
        int *newA = malloc(newSize * sizeof(int));
        for (int i = 0; i < p->n; i++) newA[i] = p->a[i];
        free(p->a);
        p->a = newA;
        p->aSize = newSize;
    }
    p->a[p->n++] = val;
}

// dequeue
//   removes and returns the smallest value (front of sorted array)
int dequeue(pq *p) {
    int val = p->a[0];
    for (int i = 0; i < p->n - 1; i++) p->a[i] = p->a[i+1];
    p->n--;
    return val;
}

// genRandom
//   generates a random number between 0 and MAX_VALUE
int genRandom() {
    long long int r1 = rand();
    long long int r2 = rand();
    return (int)(((r1 << 14) + (r2 & 0x3fff)) % MAX_VALUE);
}

void main() {
    char buf[100];
    pq *p = createPQ();
    srand(time(NULL));

    while (1) {
        printf("How many numbers to add: ");
        fgets(buf, 100, stdin);
        if (buf[0] == '\n') break;

        int toAdd = atoi(buf);
        for (int i = 0; i < toAdd; i++) enqueue(p, genRandom());

        // sort so smallest is at front
        qsort(p->a, p->n, sizeof(int), compare);

        printf("How many numbers to remove: ");
        fgets(buf, 100, stdin);
        if (buf[0] == '\n') break;

        int toRemove = atoi(buf);
        for (int i = 0; i < toRemove && p->n > 0; i++)
            printf("%d  ", dequeue(p));
        printf("\n");
    }

    free(p->a);
    free(p);
}