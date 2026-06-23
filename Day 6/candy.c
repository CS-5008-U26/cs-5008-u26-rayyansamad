// candy.c
// Reads candy-data.csv and stores each candy in a struct
// Prints all candy names, lists chocolate candies, and prints summary stats
// Parameters: none (reads filename from user input)
// Returns: 0 on success

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct candy_struct {
    char *name;
    int chocolate;
    int fruity;
    int caramel;
    int peanutalmondy;
    int nougat;
    int crispedricewafer;
    int hard;
    int bar;
    int pluribus;
    double sugarpercent;
    double pricepercent;
    double winpercent;
} candy_t;

// killNewline
//   removes the newline from the end of a string if there is one
// Parameters:
//   char *str   the string to modify
// Returns:
//   nothing

void killNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

// getNextField
//   gets the next comma-separated field from a string
//   copies it into out and returns a pointer past the comma
//   returns NULL if no more fields
// Parameters:
//   char *start   current position in the line
//   char *out     buffer to copy the field into
// Returns:
//   char *   pointer to next field, or NULL if done

char *getNextField(char *start, char *out) {
    if (*start == '\0') {
        return NULL;
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

// parseCandy
//   parses one CSV line into a candy struct on the heap
// Parameters:
//   char *line   one line from the CSV file
// Returns:
//   candy_t *   pointer to the new candy struct

candy_t *parseCandy(char *line) {
    candy_t *c = malloc(sizeof(candy_t));
    char field[1000];
    char *p = line;
    int col = 1;

    while (p != NULL) {
        p = getNextField(p, field);
        if (p != NULL) {
            if (col == 1)  c->name             = strdup(field);
            if (col == 2)  c->chocolate        = atoi(field);
            if (col == 3)  c->fruity           = atoi(field);
            if (col == 4)  c->caramel          = atoi(field);
            if (col == 5)  c->peanutalmondy    = atoi(field);
            if (col == 6)  c->nougat           = atoi(field);
            if (col == 7)  c->crispedricewafer = atoi(field);
            if (col == 8)  c->hard             = atoi(field);
            if (col == 9)  c->bar              = atoi(field);
            if (col == 10) c->pluribus         = atoi(field);
            if (col == 11) c->sugarpercent     = atof(field);
            if (col == 12) c->pricepercent     = atof(field);
            if (col == 13) c->winpercent       = atof(field);
            col++;
        }
    }

    return c;
}

int main() {
    char filename[1000];
    static char line[5000];
    char field[1000];

    printf("Enter the file name: ");
    fgets(filename, 1000, stdin);
    killNewline(filename);

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("couldn't open file\n");
        return 1;
    }

    // skip the header line
    fgets(line, 5000, f);

    candy_t *candies[200];
    int count = 0;

    while (fgets(line, 5000, f) != NULL) {
        killNewline(line);
        candies[count] = parseCandy(line);
        count++;
    }

    fclose(f);

    // task 1: print all candy names
    printf("\n--- All Candies ---\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", candies[i]->name);
    }

    // task 2: print chocolate candies
    // upper case if caramel, lower case if not
    printf("\n--- Chocolate Candies ---\n");
    int chocCount = 0;
    int chocCaramel = 0;

    for (int i = 0; i < count; i++) {
        if (candies[i]->chocolate == 1) {
            chocCount++;
            if (candies[i]->caramel == 1) {
                chocCaramel++;
                int j;
                for (j = 0; candies[i]->name[j] != '\0'; j++) {
                    field[j] = toupper(candies[i]->name[j]);
                }
                field[j] = '\0';
            } else {
                int j;
                for (j = 0; candies[i]->name[j] != '\0'; j++) {
                    field[j] = tolower(candies[i]->name[j]);
                }
                field[j] = '\0';
            }
            printf("%s\n", field);
        }
    }

    printf("%.1f%% of chocolate candies also have caramel\n",
        (double)chocCaramel / chocCount * 100.0);

    // task 3: summary stats per attribute
    printf("\n--- Attribute Summaries ---\n");

    char *attrNames[] = { "chocolate", "fruity", "caramel", "peanutalmondy",
                          "nougat", "crispedricewafer", "hard", "bar", "pluribus" };

    for (int a = 0; a < 9; a++) {
        double sumSugar = 0, sumPrice = 0, sumWin = 0;
        int n = 0;

        for (int i = 0; i < count; i++) {
            int has = 0;
            if (a == 0) has = candies[i]->chocolate;
            if (a == 1) has = candies[i]->fruity;
            if (a == 2) has = candies[i]->caramel;
            if (a == 3) has = candies[i]->peanutalmondy;
            if (a == 4) has = candies[i]->nougat;
            if (a == 5) has = candies[i]->crispedricewafer;
            if (a == 6) has = candies[i]->hard;
            if (a == 7) has = candies[i]->bar;
            if (a == 8) has = candies[i]->pluribus;

            if (has == 1) {
                sumSugar += candies[i]->sugarpercent;
                sumPrice += candies[i]->pricepercent;
                sumWin   += candies[i]->winpercent;
                n++;
            }
        }

        printf("%s: avg sugar=%.3f, avg price=%.3f, avg win=%.3f\n",
            attrNames[a], sumSugar/n, sumPrice/n, sumWin/n);
    }

    // find overall avg sugar and price
    double totalSugar = 0, totalPrice = 0;
    for (int i = 0; i < count; i++) {
        totalSugar += candies[i]->sugarpercent;
        totalPrice += candies[i]->pricepercent;
    }
    double avgSugar = totalSugar / count;
    double avgPrice = totalPrice / count;

    // above average sugar
    double sumS = 0, sumP = 0, sumW = 0;
    int n = 0;
    for (int i = 0; i < count; i++) {
        if (candies[i]->sugarpercent > avgSugar) {
            sumS += candies[i]->sugarpercent;
            sumP += candies[i]->pricepercent;
            sumW += candies[i]->winpercent;
            n++;
        }
    }
    printf("\nAbove avg sugar: avg sugar=%.3f, avg price=%.3f, avg win=%.3f\n",
        sumS/n, sumP/n, sumW/n);

    // above average price
    sumS = 0; sumP = 0; sumW = 0; n = 0;
    for (int i = 0; i < count; i++) {
        if (candies[i]->pricepercent > avgPrice) {
            sumS += candies[i]->sugarpercent;
            sumP += candies[i]->pricepercent;
            sumW += candies[i]->winpercent;
            n++;
        }
    }
    printf("Above avg price: avg sugar=%.3f, avg price=%.3f, avg win=%.3f\n",
        sumS/n, sumP/n, sumW/n);

    // free everything
    for (int i = 0; i < count; i++) {
        free(candies[i]->name);
        free(candies[i]);
    }

    return 0;
}