#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 200
#define CAPACITY 200
#define MAX_NAME 128

typedef struct {
    char name[MAX_NAME];
    int name_len;
    long long population;
} city;

int main() {

    FILE *f = fopen("uscities.csv", "r");

    if (f == NULL) {
        printf("Could not open uscities.csv\n");
        return 1;
    }

    city items[MAX_ITEMS];
    int n = 0;

    char line[5000];

    /* Skip header */
    fgets(line, sizeof(line), f);

    /* Read first 200 cities */
    while (n < MAX_ITEMS && fgets(line, sizeof(line), f)) {

    char name[128];
    char population[50];

    // find city name (first value)
    sscanf(line, "\"%127[^\"]\"", name);

    // find population (9th value)
    char *ptr = line;
    int commas = 0;

    while (*ptr && commas < 8) {
        if (*ptr == ',')
            commas++;
        ptr++;
    }

    sscanf(ptr + 2, "\"%lld\"", &items[n].population);

    strcpy(items[n].name, name);

    items[n].name_len = strlen(items[n].name);

    n++;
}

    fclose(f);

    if (n == 0) {
        printf("No cities were read.\n");
        return 1;
    }

    long long dp[MAX_ITEMS + 1][CAPACITY + 1];
    int keep[MAX_ITEMS + 1][CAPACITY + 1];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= CAPACITY; j++) {
            dp[i][j] = 0;
            keep[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {

        int weight = items[i - 1].name_len;
        long long value = items[i - 1].population;

        for (int j = 0; j <= CAPACITY; j++) {

            dp[i][j] = dp[i - 1][j];

            if (weight <= j) {

                long long take = value + dp[i - 1][j - weight];

                if (take > dp[i][j]) {
                    dp[i][j] = take;
                    keep[i][j] = 1;
                }
            }
        }
    }

    printf("Total population saved: %lld\n\n", dp[n][CAPACITY]);

    printf("Cities saved:\n");

    int charsLeft = CAPACITY;

    for (int i = n; i > 0; i--) {

        if (keep[i][charsLeft]) {

            printf("%s\n", items[i - 1].name);

            charsLeft -= items[i - 1].name_len;
        }
    }

    return 0;
}