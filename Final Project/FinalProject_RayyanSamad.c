// maze.c
// Generates a random maze using recursive backtracking
// Solves it with DFS (recursive) and BFS (queue-based)
// Prints step-by-step visualization and comparison metrics
// Parameters: optional seed as command line argument
// Returns: 0 on success

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ROWS 21
#define COLS 21
#define WALL '#'
#define OPEN ' '
#define START 'S'
#define END   'E'
#define PATH  '*'
#define SEEN  '.'

char maze[ROWS][COLS];
int visited[ROWS][COLS];

// directions for maze carving (move 2 cells at a time)
int dr[] = {-2, 2,  0, 0};
int dc[] = { 0, 0, -2, 2};

// directions for solving (move 1 cell at a time)
int sr[] = {-1, 1, 0, 0};
int sc[] = { 0, 0, -1, 1};

// --- queue node for BFS ---
// singly linked list, same structure as Day 7

typedef struct qNode {
    int r, c;
    struct qNode *next;
} qNode;

typedef struct {
    qNode *head;
    qNode *tail;
} queue;

// makeQueue
//   creates an empty queue
queue *makeQueue() {
    queue *q = malloc(sizeof(queue));
    q->head = NULL;
    q->tail = NULL;
    return q;
}

// enqueue
//   adds (r,c) to the back of the queue
void enqueue(queue *q, int r, int c) {
    qNode *n = malloc(sizeof(qNode));
    n->r = r; n->c = c; n->next = NULL;
    if (q->tail == NULL) {
        q->head = q->tail = n;
    } else {
        q->tail->next = n;
        q->tail = n;
    }
}

// dequeue
//   removes and returns the front node
qNode *dequeue(queue *q) {
    if (q->head == NULL) return NULL;
    qNode *n = q->head;
    q->head = q->head->next;
    if (q->head == NULL) q->tail = NULL;
    return n;
}

// isEmpty
//   returns 1 if queue is empty
int isEmpty(queue *q) {
    return q->head == NULL;
}

// --- maze helpers ---

// printMaze
//   prints the current state of the maze
void printMaze() {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) printf("%c", maze[r][c]);
        printf("\n");
    }
    printf("\n");
}

// inBounds
//   returns 1 if (r,c) is a valid cell inside the maze
int inBounds(int r, int c) {
    return r >= 0 && r < ROWS && c >= 0 && c < COLS;
}

// shuffle
//   shuffles array of 4 ints for random direction order
void shuffle(int *a, int n) {
    for (int i = n-1; i > 0; i--) {
        int j = rand() % (i+1);
        int tmp = a[i]; a[i] = a[j]; a[j] = tmp;
    }
}

// carve
//   recursive backtracking maze generator
//   carves open paths from (r,c) to random unvisited neighbors
void carve(int r, int c) {
    visited[r][c] = 1;
    int order[] = {0, 1, 2, 3};
    shuffle(order, 4);

    for (int i = 0; i < 4; i++) {
        int nr = r + dr[order[i]];
        int nc = c + dc[order[i]];
        if (inBounds(nr, nc) && !visited[nr][nc] && maze[nr][nc] == WALL) {
            // knock down the wall between (r,c) and (nr,nc)
            maze[(r+nr)/2][(c+nc)/2] = OPEN;
            maze[nr][nc] = OPEN;
            carve(nr, nc);
        }
    }
}

// generateMaze
//   fills everything with walls then carves a solvable maze
void generateMaze() {
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            maze[r][c] = WALL;

    memset(visited, 0, sizeof(visited));
    maze[1][1] = OPEN;
    carve(1, 1);

    maze[1][1] = START;
    maze[ROWS-2][COLS-2] = END;
}

// tracePath
//   walks back from END to START using parent arrays, marks path with *
int tracePath(int pr[ROWS][COLS], int pc[ROWS][COLS]) {
    int r = ROWS-2, c = COLS-2;
    int len = 0;
    while (!(r == 1 && c == 1)) {
        if (maze[r][c] != START && maze[r][c] != END)
            maze[r][c] = PATH;
        int nr = pr[r][c];
        int nc = pc[r][c];
        r = nr; c = nc;
        len++;
    }
    return len;
}

// --- DFS ---

int dfsVisited[ROWS][COLS];
int dfsParentR[ROWS][COLS];
int dfsParentC[ROWS][COLS];
int dfsCells;

// dfsHelper
//   recursively explores from (r,c), returns 1 if END found
int dfsHelper(int r, int c) {
    if (!inBounds(r, c)) return 0;
    if (dfsVisited[r][c]) return 0;
    if (maze[r][c] == WALL) return 0;

    dfsVisited[r][c] = 1;
    dfsCells++;

    if (maze[r][c] != START && maze[r][c] != END)
        maze[r][c] = SEEN;

    if (r == ROWS-2 && c == COLS-2) return 1;

    for (int i = 0; i < 4; i++) {
        int nr = r + sr[i];
        int nc = c + sc[i];
        if (inBounds(nr, nc) && !dfsVisited[nr][nc] && maze[nr][nc] != WALL) {
            dfsParentR[nr][nc] = r;
            dfsParentC[nr][nc] = c;
            if (dfsHelper(nr, nc)) return 1;
        }
    }
    return 0;
}

// solveDFS
//   runs DFS on a fresh copy of the maze and prints results
void solveDFS(char saved[ROWS][COLS]) {
    memcpy(maze, saved, sizeof(maze));
    memset(dfsVisited, 0, sizeof(dfsVisited));
    memset(dfsParentR, -1, sizeof(dfsParentR));
    memset(dfsParentC, -1, sizeof(dfsParentC));
    dfsCells = 0;

    printf("=== DFS ===\n");
    clock_t start = clock();
    int found = dfsHelper(1, 1);
    clock_t end = clock();
    double secs = (double)(end - start) / CLOCKS_PER_SEC;

    if (found) {
        int len = tracePath(dfsParentR, dfsParentC);
        printMaze();
        printf("Path length:    %d\n", len);
        printf("Cells explored: %d\n", dfsCells);
        printf("Time:           %.6f seconds\n\n", secs);
    } else {
        printf("No path found.\n\n");
    }
}

// solveBFS
//   runs BFS on a fresh copy of the maze and prints results
void solveBFS(char saved[ROWS][COLS]) {
    memcpy(maze, saved, sizeof(maze));

    int bfsVisited[ROWS][COLS];
    int bfsParentR[ROWS][COLS];
    int bfsParentC[ROWS][COLS];
    memset(bfsVisited, 0, sizeof(bfsVisited));
    memset(bfsParentR, -1, sizeof(bfsParentR));
    memset(bfsParentC, -1, sizeof(bfsParentC));

    int cells = 0;
    int found = 0;

    queue *q = makeQueue();
    enqueue(q, 1, 1);
    bfsVisited[1][1] = 1;

    clock_t start = clock();

    while (!isEmpty(q)) {
        qNode *cur = dequeue(q);
        int r = cur->r, c = cur->c;
        free(cur);
        cells++;

        if (maze[r][c] != START && maze[r][c] != END)
            maze[r][c] = SEEN;

        if (r == ROWS-2 && c == COLS-2) { found = 1; break; }

        for (int i = 0; i < 4; i++) {
            int nr = r + sr[i];
            int nc = c + sc[i];
            if (inBounds(nr, nc) && !bfsVisited[nr][nc] && maze[nr][nc] != WALL) {
                bfsVisited[nr][nc] = 1;
                bfsParentR[nr][nc] = r;
                bfsParentC[nr][nc] = c;
                enqueue(q, nr, nc);
            }
        }
    }

    clock_t end = clock();
    double secs = (double)(end - start) / CLOCKS_PER_SEC;

    // free any leftover nodes
    while (!isEmpty(q)) { qNode *n = dequeue(q); free(n); }
    free(q);

    printf("=== BFS ===\n");
    if (found) {
        int len = tracePath(bfsParentR, bfsParentC);
        printMaze();
        printf("Path length:    %d\n", len);
        printf("Cells explored: %d\n", cells);
        printf("Time:           %.6f seconds\n\n", secs);
    } else {
        printf("No path found.\n\n");
    }
}

int main(int argc, char **argv) {
    int seed = (argc >= 2) ? atoi(argv[1]) : (int)time(NULL);
    printf("Seed: %d\n\n", seed);
    srand(seed);

    generateMaze();

    char saved[ROWS][COLS];
    memcpy(saved, maze, sizeof(maze));

    printf("=== Generated Maze ===\n");
    printMaze();

    solveDFS(saved);
    solveBFS(saved);

    return 0;
}
