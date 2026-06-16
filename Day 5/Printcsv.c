// Printcsv.c
// Reads a CSV file and prints each line and its fields
// Returns: 0 on success

#include <stdio.h>
#include <string.h>

// removes newline from end of string
void killNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

// gets the next comma-separated field, returns pointer past the separator
// returns NULL if no more fields
char *getNextField(char *start, char separator, char *out) {
    if (*start == '\0') {
        return NULL;
    }

    char *comma = strchr(start, separator);

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

// removes double quotes from around a field if there are any
void stripQuotes(char *field) {
    int len = strlen(field);
    if (len >= 2 && field[0] == '"' && field[len-1] == '"') {
        int i;
        for (i = 0; i < len-2; i++) {
            field[i] = field[i+1];
        }
        field[len-2] = '\0';
    }
}

int main() {
    char filename[1000];
    char line[1000];
    char field[1000];

    printf("Enter the file name: ");
    fgets(filename, 1000, stdin);
    killNewline(filename);

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("couldn't open file\n");
        return 1;
    }

    while (fgets(line, 1000, f) != NULL) {
        killNewline(line);
        printf(">%s<\n", line);

        char *p = line;
        while (p != NULL) {
            p = getNextField(p, ',', field);
            if (p != NULL) {
                stripQuotes(field);
                printf("    >%s<\n", field);
            }
        }
    }

    fclose(f);
    return 0;
}