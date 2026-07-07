// Citylist.c
// Reads N cities from uscities.csv into a vector, builds BSTs by latitude
// and FIPS code, then does linear and binary search on sorted arrays
// Returns: 0 on success

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct cityData {
    char *name;
    char *state;
    int fips;
    double lat;
    double lng;
    int population;
} city;

// vector struct — size is how much memory we have, used is how much we're using
typedef struct vec_s {
    int size;
    int used;
    void **data;
} vec;

// makeVec
//   creates an empty vector with a small starting backing store
vec *makeVec() {
    vec *v = malloc(sizeof(vec));
    v->size = 4;
    v->used = 0;
    v->data = malloc(4 * sizeof(void *));
    return v;
}

// vecAdd
//   adds an element to the end of the vector
//   doubles the backing store if we run out of space
void vecAdd(vec *v, void *x) {
    if (v->used == v->size) {
        // ran out of room, double it
        int newSize = v->size * 2;
        void **newData = malloc(newSize * sizeof(void *));
        for (int i = 0; i < v->used; i++) {
            newData[i] = v->data[i];
        }
        free(v->data);
        v->data = newData;
        v->size = newSize;
    }
    v->data[v->used] = x;
    v->used++;
}

// vecGet
//   returns element at index i, or NULL if out of range
void *vecGet(vec *v, int i) {
    if (i < 0 || i >= v->used) return NULL;
    return v->data[i];
}

// BST node
typedef struct bstNode {
    void *data;
    struct bstNode *left;
    struct bstNode *right;
} bNode;

// newBNode
//   makes a new BST node with the given data pointer
bNode *newBNode(void *d) {
    bNode *n = malloc(sizeof(bNode));
    n->data = d;
    n->left = NULL;
    n->right = NULL;
    return n;
}

// insertLat
//   inserts city into BST ordered by latitude
bNode *insertLat(bNode *t, city *c) {
    if (t == NULL) return newBNode(c);
    city *cur = (city *)t->data;
    if (c->lat < cur->lat)
        t->left = insertLat(t->left, c);
    else if (c->lat > cur->lat)
        t->right = insertLat(t->right, c);
    return t;
}

// insertFips
//   inserts city into BST ordered by FIPS code, skips duplicates
bNode *insertFips(bNode *t, city *c) {
    if (t == NULL) return newBNode(c);
    city *cur = (city *)t->data;
    if (c->fips == cur->fips) return t;  // skip duplicate FIPS
    if (c->fips < cur->fips)
        t->left = insertFips(t->left, c);
    else
        t->right = insertFips(t->right, c);
    return t;
}

// fillArr
//   inorder traversal — fills arr with city pointers in sorted order
int fillArr(bNode *t, city **arr, int i) {
    if (t == NULL) return i;
    i = fillArr(t->left, arr, i);
    arr[i++] = (city *)t->data;
    i = fillArr(t->right, arr, i);
    return i;
}

// linearSearch
//   walks the array looking for New York, returns its index
int linearSearch(city **arr, int n) {
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i]->name, "New York") == 0) return i;
    }
    return -1;
}

// binarySearch
//   searches sorted array by FIPS code, returns index or -1
int binarySearch(city **arr, int lo, int hi, int fips) {
    if (lo > hi) return -1;
    int mid = (lo + hi) / 2;
    if (arr[mid]->fips == fips) return mid;
    if (fips < arr[mid]->fips)
        return binarySearch(arr, lo, mid - 1, fips);
    return binarySearch(arr, mid + 1, hi, fips);
}

// freeBST
//   frees all the BST nodes (not the city data itself)
void freeBST(bNode *t) {
    if (t == NULL) return;
    freeBST(t->left);
    freeBST(t->right);
    free(t);
}

// killNewline
//   removes trailing newline from string
void killNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n')
        str[len-1] = '\0';
}

// getNextField
//   gets the next comma-separated field, handles quoted fields
char *getNextField(char *start, char *out) {
    if (*start == '\0') return NULL;

    if (*start == '"') {
        start++;
        char *q = strchr(start, '"');
        if (q == NULL) {
            strcpy(out, start);
            return start + strlen(start);
        }
        int len = q - start;
        strncpy(out, start, len);
        out[len] = '\0';
        if (*(q + 1) == ',') return q + 2;
        return q + 1;
    }

    char *comma = strchr(start, ',');
    if (comma == NULL) {
        strcpy(out, start);
        return start + strlen(start);
    }
    int len = comma - start;
    strncpy(out, start, len);
    out[len] = '\0';
    return comma + 1;
}

// stringToCity
//   parses one CSV line into a city struct on the heap
city *stringToCity(char *line) {
    city *c = malloc(sizeof(city));
    static char field[5000];
    char *p = line;
    int col = 1;

    while (p != NULL) {
        p = getNextField(p, field);
        if (p != NULL) {
            if (col == 2) c->name       = strdup(field);
            if (col == 3) c->state      = strdup(field);
            if (col == 5) c->fips       = atoi(field);
            if (col == 7) c->lat        = atof(field);
            if (col == 8) c->lng        = atof(field);
            if (col == 9) c->population = atoi(field);
            col++;
        }
    }
    return c;
}

int main() {
    static char line[50000];
    int n;

    printf("How many cities: ");
    scanf("%d", &n);
    getchar();

    FILE *f = fopen("uscities.csv", "r");
    if (f == NULL) {
        printf("couldn't open file\n");
        return 1;
    }

    // skip header line
    fgets(line, 50000, f);

    // read n cities into vector
    vec *v = makeVec();
    int count = 0;
    while (count < n && fgets(line, 50000, f) != NULL) {
        killNewline(line);
        city *c = stringToCity(line);
        vecAdd(v, c);
        count++;
    }
    fclose(f);

    // task 1: print all cities
    for (int i = 0; i < v->used; i++) {
        city *c = (city *)vecGet(v, i);
        printf("%s %s, population %d, at (%.4f, %.4f)\n",
            c->name, c->state, c->population, c->lat, c->lng);
    }

    // task 2: BST by latitude, inorder into array, linear search for New York
    bNode *latTree = NULL;
    for (int i = 0; i < v->used; i++) {
        latTree = insertLat(latTree, (city *)vecGet(v, i));
    }
    city **latArr = malloc(n * sizeof(city *));
    fillArr(latTree, latArr, 0);

    int nyIdx = linearSearch(latArr, n);
    printf("By latitude, New York is index %d\n", nyIdx);

    freeBST(latTree);
    free(latArr);

    // task 3: BST by FIPS, inorder into array, binary search for 36081
    bNode *fipsTree = NULL;
    for (int i = 0; i < v->used; i++) {
        fipsTree = insertFips(fipsTree, (city *)vecGet(v, i));
    }
    city **fipsArr = malloc(n * sizeof(city *));
    fillArr(fipsTree, fipsArr, 0);

    int fi = binarySearch(fipsArr, 0, n - 1, 36081);
    if (fi >= 0) {
        printf("By FIPS code, %s is index %d\n", fipsArr[fi]->name, fi);
    }

    freeBST(fipsTree);
    free(fipsArr);

    // free everything
    for (int i = 0; i < v->used; i++) {
        city *c = (city *)vecGet(v, i);
        free(c->name);
        free(c->state);
        free(c);
    }
    free(v->data);
    free(v);

    return 0;
}