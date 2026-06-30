// double.c
// Reads the first 20 cities from uscities.csv into a doubly linked list
// Lets the user size, delete, reverse, get, or print nodes in the list
// Returns: 0 on success

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct cityData {
    char *name;
    char *nameAscii;
    char *stateCode;
    char *stateName;
    char *countyFips;
    char *countyName;
    double lat;
    double lng;
    int population;
} city;

typedef struct doubleNode {
    void *data;
    struct doubleNode *next;
    struct doubleNode *prev;
} dNode;

// killNewline
//   removes newline from end of string
void killNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

// getNextField
//   gets the next comma-separated field, handles quoted fields
//   returns pointer past the separator, or NULL if no more fields
char *getNextField(char *start, char *out) {
    if (*start == '\0') {
        return NULL;
    }

    if (*start == '"') {
        start++;
        char *endQuote = strchr(start, '"');
        if (endQuote == NULL) {
            strcpy(out, start);
            return start + strlen(start);
        }
        int len = endQuote - start;
        strncpy(out, start, len);
        out[len] = '\0';
        if (*(endQuote + 1) == ',') {
            return endQuote + 2;
        }
        return endQuote + 1;
    }

    char *comma = strchr(start, ',');
    if (comma == NULL) {
        strcpy(out, start);
        return start + strlen(start);
    } else {
        int len = comma - start;
        strncpy(out, start, len);
        out[len] = '\0';
        return comma + 1;
    }
}

// stringToCity
//   builds a city struct on the heap from one line of csv text
city *stringToCity(char *line) {
    city *c = malloc(sizeof(city));
    static char field[5000];
    char *p = line;
    int col = 1;

    while (p != NULL) {
        p = getNextField(p, field);
        if (p != NULL) {
            if (col == 1) c->name = strdup(field);
            if (col == 2) c->nameAscii = strdup(field);
            if (col == 3) c->stateCode = strdup(field);
            if (col == 4) c->stateName = strdup(field);
            if (col == 5) c->countyFips = strdup(field);
            if (col == 6) c->countyName = strdup(field);
            if (col == 7) c->lat = atof(field);
            if (col == 8) c->lng = atof(field);
            if (col == 9) c->population = atoi(field);
            col++;
        }
    }

    return c;
}

// makeNode
//   wraps a city pointer in a new dNode
dNode *makeNode(city *c) {
    dNode *n = malloc(sizeof(dNode));
    n->data = c;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

// addFront
//   adds a node to the front of the list, returns the new head
dNode *addFront(dNode *list, dNode *n) {
    n->next = list;
    n->prev = NULL;
    if (list != NULL) {
        list->prev = n;
    }
    return n;
}

// addBack
//   adds a node to the end of the list, returns the (possibly new) head
dNode *addBack(dNode *list, dNode *n) {
    if (list == NULL) {
        return n;
    }
    dNode *p = list;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = n;
    n->prev = p;
    return list;
}

// getNode
//   returns a pointer to the n-th node (1-indexed), or NULL if out of range
dNode *getNode(dNode *list, int n) {
    if (n <= 0) {
        return NULL;
    }
    dNode *p = list;
    int i = 1;
    while (p != NULL && i < n) {
        p = p->next;
        i++;
    }
    return p;
}

// deleteNode
//   removes the given node from the list, returns the (possibly new) head
dNode *deleteNode(dNode *list, dNode *target) {
    if (list == NULL || target == NULL) {
        return list;
    }

    if (target->prev != NULL) {
        target->prev->next = target->next;
    } else {
        list = target->next;
    }

    if (target->next != NULL) {
        target->next->prev = target->prev;
    }

    return list;
}

// listLength
//   counts how many nodes are in the list
int listLength(dNode *list) {
    int count = 0;
    dNode *p = list;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    return count;
}

// reverseList
//   reverses the order of the nodes, returns the new head
dNode *reverseList(dNode *list) {
    dNode *curr = list;
    dNode *newHead = list;

    while (curr != NULL) {
        dNode *next = curr->next;
        curr->next = curr->prev;
        curr->prev = next;
        newHead = curr;
        curr = next;
    }

    return newHead;
}

// printCity
//   prints one city's name, state, and population
void printCity(city *c) {
    printf("%s %s, population %d\n", c->nameAscii, c->stateCode, c->population);
}

int main() {
    static char line[50000];

    FILE *f = fopen("uscities.csv", "r");;
    if (f == NULL) {
        printf("couldn't open file\n");
        return 1;
    }

    // skip the header line
    fgets(line, 50000, f);

    dNode *list = NULL;

    // read first 20 cities, add each to the tail of the list
    int count = 0;
    while (count < 20 && fgets(line, 50000, f) != NULL) {
        killNewline(line);
        city *c = stringToCity(line);
        dNode *n = makeNode(c);
        list = addBack(list, n);
        count++;
    }

    fclose(f);

    char command[100];
    int running = 1;

    while (running) {
        printf("size, delete, reverse, get, or print: ");
        fgets(command, 100, stdin);
        killNewline(command);

        if (strcmp(command, "size") == 0) {
            printf("Size is %d\n", listLength(list));

        } else if (strcmp(command, "delete") == 0) {
            int n;
            printf("Enter a number: ");
            scanf("%d", &n);
            getchar(); // eat the leftover newline
            dNode *target = getNode(list, n);
            list = deleteNode(list, target);
            free(target);

        } else if (strcmp(command, "reverse") == 0) {
            list = reverseList(list);

        } else if (strcmp(command, "get") == 0) {
            int n;
            printf("Enter a number: ");
            scanf("%d", &n);
            getchar();
            dNode *target = getNode(list, n);
            if (target != NULL) {
                list = deleteNode(list, target);
                list = addFront(list, target);
            }

        } else if (strcmp(command, "print") == 0) {
            int n;
            printf("Enter a number: ");
            scanf("%d", &n);
            getchar();
            dNode *p = list;
            int i = 0;
            while (p != NULL && i < n) {
                printCity((city *)p->data);
                p = p->next;
                i++;
            }

        } else {
            running = 0;
        }
    }

    // free everything
    dNode *p = list;
    while (p != NULL) {
        dNode *next = p->next;
        city *c = (city *)p->data;
        free(c->name);
        free(c->nameAscii);
        free(c->stateCode);
        free(c->stateName);
        free(c->countyFips);
        free(c->countyName);
        free(c);
        free(p);
        p = next;
    }

    return 0;
}