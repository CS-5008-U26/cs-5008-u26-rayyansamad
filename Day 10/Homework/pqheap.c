/* pqheap.c
 * Priority queue using a min-heap (smallest value at root)
 * Alternates asking how many numbers to add and remove
 * Uses heapifyUp on enqueue and heapifyDown on dequeue
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

// heapifyUp
//   bubbles a[here] up until min-heap property is restored
void heapifyUp(int *a, int here) {
    if (here == 0) return;
    int parent = (here - 1) / 2;
    if (a[here] < a[parent]) {
        int tmp = a[here]; a[here] = a[parent]; a[parent] = tmp;
        heapifyUp(a, parent);
    }
}

// heapifyDown
//   pushes a[here] down until min-heap property is restored
void heapifyDown(int *a, int n, int here) {
    int left = 2 * here + 1;
    int right = 2 * here + 2;
    int smallest = here;
    if (left < n && a[left] < a[smallest])   smallest = left;
    if (right < n && a[right] < a[smallest]) smallest = right;
    if (smallest != here) {
        int tmp = a[here]; a[here] = a[smallest]; a[smallest] = tmp;
        heapifyDown(a, n, smallest);
    }
}

// enqueue
//   adds a value to the heap, doubles backing store if needed
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
    heapifyUp(p->a, p->n - 1);
}

// dequeue
//   removes and returns the smallest value (root of min-heap)
int dequeue(pq *p) {
    int val = p->a[0];
    p->a[0] = p->a[--p->n];
    heapifyDown(p->a, p->n, 0);
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