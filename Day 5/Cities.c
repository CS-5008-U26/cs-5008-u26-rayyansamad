// Cities.c
// Reads uscities.csv and prints the total population of the 20 largest cities
// and the name of the northernmost city among them
// Returns: 0 on success

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// removes newline from end of string
void killNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

// gets the next comma-separated field, handles quoted fields
// returns pointer past the separator, or NULL if no more fields
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

static char line[50000];
static char field[50000];

int main() {
    char filename[1000];

    printf("Enter the file name: ");
    fgets(filename, 1000, stdin);
    killNewline(filename);

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("couldn't open file\n");
        return 1;
    }

    // skip the header line
    fgets(line, 50000, f);

    long int totalPop = 0;
    double maxLat = -999.0;
    char northCity[1000];
    northCity[0] = '\0';

    int count = 0;

    while (count < 20 && fgets(line, 50000, f) != NULL) {
        killNewline(line);

        char *p = line;
        int col = 1;
        char cityName[1000];
        double lat = 0.0;
        int pop = 0;

        while (p != NULL) {
            p = getNextField(p, field);
            if (p != NULL) {
                if (col == 2) {
                    strcpy(cityName, field);
                } else if (col == 7) {
                    lat = atof(field);
                } else if (col == 9) {
                    pop = atoi(field);
                }
                col++;
            }
        }

        totalPop += pop;

        if (lat > maxLat) {
            maxLat = lat;
            strcpy(northCity, cityName);
        }

        count++;
    }

    fclose(f);

    printf("Sum of the populations: %ld\n", totalPop);
    printf("Northernmost city is %s\n", northCity);

    return 0;
}