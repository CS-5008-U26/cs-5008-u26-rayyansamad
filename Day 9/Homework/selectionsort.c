/* bubblesort.c
 * Selection sort implementation using sorttemplate.c as a base
 * Sorts by finding the largest element in unsorted portion and swapping to end
 * Time is O(n2) regardless of data order
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TO_PRINT 100
#define MAX_VALUE 100000000

int test1[] =       { 3 };
int expected1[] =   { 3 };
int n1 =            1;
int test2[] =       { 5, 3 };
int expected2[] =   { 3, 5 };
int n2 =            2;
int test3[] =       { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int expected3[] =   { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int n3 =            10;
int test4[] =       { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
int expected4[] =   { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int n4 =            10;
int test5[] =       { 2, 4, 6, 8, 10, 1, 3, 5, 7, 9 };
int expected5[] =   { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int n5 =            10;
int test6[] =       { 1, 2, 3, 2, 2 };
int expected6[] =   { 1, 2, 2, 2, 3 };
int n6 =            5;

// sortarray - selection sort
// finds the largest element in the unsorted portion and swaps it to the end
void sortarray(int a[], int n) {
    for (int i = n - 1; i >= 1; i--) {
        int biggest = 0;
        for (int j = 1; j <= i; j++) {
            if (a[j] > a[biggest]) biggest = j;
        }
        if (biggest != i) {
            int tmp = a[biggest];
            a[biggest] = a[i];
            a[i] = tmp;
        }
    }
}

void printarray(int a[], int n) {
    int numberToPrint = ((n < MAX_TO_PRINT) ? n : MAX_TO_PRINT);
    for (int i = 0; i < numberToPrint; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int *genarray(int numberofelements) {
    int *result = malloc(numberofelements * sizeof(int));
    if (result == NULL) {
        printf("malloc failed");
    } else {
        for (int i = 0; i < numberofelements; i++) {
            long long int r1 = rand();
            long long int r2 = rand();
            long long int randomValue = (r1 << 14) + (r2 & 0x3fff);
            result[i] = (int)(randomValue % MAX_VALUE);
        }
    }
    return result;
}

void timedsort(int a[], int n) {
    clock_t startTime = clock();
    sortarray(a, n);
    clock_t endTime = clock();
    double elapsedTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf("Result: ");
    printarray(a, n);
    printf("Elapsed time: %f seconds\n\n", elapsedTime);
}

void testsort(int a[], int n, int expected[]) {
    printf("Test case: ");
    printarray(a, n);
    sortarray(a, n);
    printf("Result: ");
    printarray(a, n);
    int ok = 1;
    for (int i = 0; ok && (i < n); i++) {
        ok = (a[i] == expected[i]);
    }
    printf("%s\n\n", (ok ? "PASSED" : "FAILED"));
}

void main() {
    char buffer[100];
    int nelements;
    int *randomdata;

    srand(time(NULL));

    testsort(test1, n1, expected1);
    testsort(test2, n2, expected2);
    testsort(test3, n3, expected3);
    testsort(test4, n4, expected4);
    testsort(test5, n5, expected5);
    testsort(test6, n6, expected6);

    // random data
    int keepgoing = 1;
    while (keepgoing) {
        printf("How many elements? ");
        fgets(buffer, 100, stdin);
        if (buffer[0] == '\n') {
            keepgoing = 0;
        } else {
            nelements = atoi(buffer);
            if (nelements <= 0) {
                printf("Must be a positive number of elements\n");
            } else {
                randomdata = genarray(nelements);
                if (randomdata != NULL) {
                    timedsort(randomdata, nelements);
                    free(randomdata);
                }
            }
        }
    }

    // sorted data
    printf("\n--- Sorted Data ---\n");
    keepgoing = 1;
    while (keepgoing) {
        printf("How many elements? ");
        fgets(buffer, 100, stdin);
        if (buffer[0] == '\n') {
            keepgoing = 0;
        } else {
            nelements = atoi(buffer);
            if (nelements <= 0) {
                printf("Must be a positive number of elements\n");
            } else {
                int *a = malloc(nelements * sizeof(int));
                for (int i = 0; i < nelements; i++) a[i] = i;
                timedsort(a, nelements);
                free(a);
            }
        }
    }

    // reverse sorted data
    printf("\n--- Reverse Sorted Data ---\n");
    keepgoing = 1;
    while (keepgoing) {
        printf("How many elements? ");
        fgets(buffer, 100, stdin);
        if (buffer[0] == '\n') {
            keepgoing = 0;
        } else {
            nelements = atoi(buffer);
            if (nelements <= 0) {
                printf("Must be a positive number of elements\n");
            } else {
                int *a = malloc(nelements * sizeof(int));
                for (int i = 0; i < nelements; i++) a[i] = nelements - 1 - i;
                timedsort(a, nelements);
                free(a);
            }
        }
    }
}