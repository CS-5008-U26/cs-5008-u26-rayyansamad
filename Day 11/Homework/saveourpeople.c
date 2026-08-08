#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 200
#define MAX_CHARS 200
#define MAX_NAME 100
#define MAX_LINE 5000

typedef struct cityStruct {
    char name[MAX_NAME];
    long long int population;
    int length;
} city;


/*
 * getField
 *   gets one quoted field from a CSV line
 *   fieldNumber starts at 0
 */
void getField(char line[], int fieldNumber, char result[]) {
    int field = 0;
    int i = 0;
    int j = 0;

    while (line[i] != '\0') {

        if (line[i] == '"') {
            i++;

            if (field == fieldNumber) {
                while (line[i] != '"' && line[i] != '\0') {
                    result[j] = line[i];
                    j++;
                    i++;
                }

                result[j] = '\0';
                return;
            }

            while (line[i] != '"' && line[i] != '\0') {
                i++;
            }

            field++;
        }

        i++;
    }

    result[0] = '\0';
}


/*
 * readCities
 *   reads the first 200 cities from uscities.csv
 */
void readCities(city cities[], int *n) {
    FILE *f = fopen("uscities.csv", "r");

    if (f == NULL) {
        printf("Could not open uscities.csv\n");
        return;
    }

    char line[MAX_LINE];

    // skip header
    fgets(line, MAX_LINE, f);

    while (*n < MAX_CITIES && fgets(line, MAX_LINE, f) != NULL) {

        char name[MAX_NAME];
        char populationString[50];

        // city is field 0
        getField(line, 0, name);

        // population is field 8
        getField(line, 8, populationString);

        strcpy(cities[*n].name, name);

        cities[*n].population = atoll(populationString);

        cities[*n].length = strlen(cities[*n].name);

        (*n)++;
    }

    fclose(f);
}


/*
 * findBestCities
 *   solves the problem using 0/1 knapsack dynamic programming
 */
void findBestCities(city cities[], int n, int selected[]) {

    long long int dp[MAX_CITIES + 1][MAX_CHARS + 1];

    // initialize table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= MAX_CHARS; w++) {
            dp[i][w] = 0;
        }
    }

    // build DP table
    for (int i = 1; i <= n; i++) {

        int cityLength = cities[i - 1].length;
        long long int population = cities[i - 1].population;

        for (int w = 0; w <= MAX_CHARS; w++) {

            // don't choose this city
            dp[i][w] = dp[i - 1][w];

            // choose this city if it fits
            if (cityLength <= w) {

                long long int take =
                    population +
                    dp[i - 1][w - cityLength];

                if (take > dp[i][w]) {
                    dp[i][w] = take;
                }
            }
        }
    }

    // start with no cities selected
    for (int i = 0; i < n; i++) {
        selected[i] = 0;
    }

    // backtrack through table
    int w = MAX_CHARS;

    for (int i = n; i > 0; i--) {

        // value changed, so this city was selected
        if (dp[i][w] != dp[i - 1][w]) {

            selected[i - 1] = 1;

            w -= cities[i - 1].length;
        }
    }
}


/*
 * printAnswer
 *   prints selected cities and total population
 */
void printAnswer(city cities[], int selected[], int n) {

    long long int totalPopulation = 0;
    int totalCharacters = 0;

    printf("Cities saved:\n");

    for (int i = 0; i < n; i++) {

        if (selected[i]) {

            printf("%s\n", cities[i].name);

            totalPopulation += cities[i].population;
            totalCharacters += cities[i].length;
        }
    }

    printf("\nTotal population saved: %lld\n",
           totalPopulation);

    printf("Total characters used: %d\n",
           totalCharacters);
}


int main() {

    city cities[MAX_CITIES];

    int n = 0;

    int selected[MAX_CITIES];

    readCities(cities, &n);

    if (n == 0) {
        printf("No cities were read.\n");
        return 1;
    }

    findBestCities(cities, n, selected);

    printAnswer(cities, selected, n);

    return 0;
}