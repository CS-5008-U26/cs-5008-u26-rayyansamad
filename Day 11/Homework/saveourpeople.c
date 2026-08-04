#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ITEMS 200
#define CAPACITY 200
#define MAX_LINE 1024
#define MAX_NAME 128

typedef struct {
    char name[MAX_NAME];
    int name_len;
    long long population;
} city;

/* Simple helper: remove trailing newline and carriage return */
static void strip_newline(char *s) {
    size_t len = strlen(s);
    while (len > 0 && (s[len-1] == '\n' || s[len-1] == '\r')) {
        s[len-1] = '\0';
        len--;
    }
}

/* Remove optional surrounding quotes from a name in-place */
static void unquote(char *s) {
    size_t len = strlen(s);
    if (len >= 2 && s[0] == '"' && s[len-1] == '"') {
        memmove(s, s+1, len-2);
        s[len-2] = '\0';
    }
}

/* Parse a CSV line:
   - out_name gets the first field (truncated to MAX_NAME-1)
   - out_pop gets digits-only population string (no commas)
   Returns 1 on success, 0 on failure.
   This is a minimal parser and does not handle embedded commas inside quotes.
*/
static int parse_city_line(char *line, char *out_name, char *out_pop) {
    strip_newline(line);

    /* find first comma for the name */
    char *c1 = strchr(line, ',');
    if (!c1) return 0;
    size_t nlen = (size_t)(c1 - line);
    if (nlen >= MAX_NAME) nlen = MAX_NAME - 1;
    strncpy(out_name, line, nlen);
    out_name[nlen] = '\0';
    unquote(out_name);

    /* find last comma for the population field */
    char *last = strrchr(line, ',');
    if (!last || last[1] == '\0') return 0;
    char *p = last + 1;

    /* build digits-only population string (remove commas/spaces) */
    int pi = 0;
    for (; *p != '\0' && pi < 63; p++) {
        if (isdigit((unsigned char)*p)) out_pop[pi++] = *p;
    }
    out_pop[pi] = '\0';
    if (pi == 0) return 0; /* no digits found */

    return 1;
}

int main() {

    FILE *f = fopen("uscities.csv", "r");
    if (!f) {
        perror("fopen");
        return 1;
    }

    city items[MAX_ITEMS];
    int n = 0;
    char line[MAX_LINE];

    /* skip header line */
    if (!fgets(line, sizeof(line), f)) {
        fprintf(stderr, "Empty file\n");
        fclose(f);
        return 1;
    }

    city items[MAX_ITEMS];
    int n = 0;
    char line[MAX_LINE];

    /* skip header line (simpler than detecting it) */
    if (!fgets(line, sizeof(line), f)) {
        fprintf(stderr, "Empty file\n");
        fclose(f);
        return 1;
    }

    /* read up to MAX_ITEMS lines */
    while (n < MAX_ITEMS && fgets(line, sizeof(line), f)) {
        char nm[MAX_NAME];
        char popstr[64];
        if (!parse_city_line(line, nm, popstr)) continue;

        long long pop = atoll(popstr);
        if (pop <= 0) continue;

        strncpy(items[n].name, nm, MAX_NAME-1);
        items[n].name[MAX_NAME-1] = '\0';
        items[n].name_len = (int)strlen(items[n].name);

        /* skip cities whose name alone exceeds capacity */
        if (items[n].name_len > CAPACITY) continue;

        items[n].population = pop;
        n++;
    }
    fclose(f);

    if (n == 0) {
    fprintf(stderr, "No city data read.\n");
    return 1;
}

    /* 0/1 knapsack (simple 2D DP) */
    static long long dp[MAX_ITEMS+1][CAPACITY+1];
    static int keep[MAX_ITEMS+1][CAPACITY+1];

    for (int w = 0; w <= CAPACITY; w++) dp[0][w] = 0;

    for (int i = 1; i <= n; i++) {
        int wt = items[i-1].name_len;
        long long val = items[i-1].population;
        for (int w = 0; w <= CAPACITY; w++) {
            if (wt <= w) {
                long long take = dp[i-1][w-wt] + val;
                long long notake = dp[i-1][w];
                if (take > notake) {
                    dp[i][w] = take;
                    keep[i][w] = 1;
                } else {
                    dp[i][w] = notake;
                    keep[i][w] = 0;
                }
            } else {
                dp[i][w] = dp[i-1][w];
                keep[i][w] = 0;
            }
        }
    }

    long long best = dp[n][CAPACITY];

    /* backtrack to find chosen cities */
    int chosen[MAX_ITEMS] = {0};
    int w = CAPACITY;
    for (int i = n; i >= 1; i--) {
        if (keep[i][w]) {
            chosen[i-1] = 1;
            w -= items[i-1].name_len;
            if (w < 0) w = 0;
        }
    }

    printf("Total population saved: %lld\n\n", best);
    printf("Cities saved:\n");
    for (int i = 0; i < n; i++) {
        if (chosen[i]) {
            printf("%s (%d)\n", items[i].name, items[i].name_len);
        }
    }

    return 0;
}