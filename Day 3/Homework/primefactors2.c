// primefactors2.c
// Prints the prime factorization of a number using a recursive function
// Parameters: none (reads from user input)
// Returns: 0 on success

#include <stdio.h>

// printFactors
//   recursively prints prime factors of n starting from divisor
//   prints " * " between factors but not before first or after last
// Parameters:
//   int n         the remaining number to factor
//   int divisor   the current divisor being tried
//   int first     1 if no factor has been printed yet, 0 otherwise
// Returns:
//   void

void printFactors(int n, int divisor, int first) {
    // base case: nothing left to factor
    if (n <= 1) {
        return;
    }

    // if divisor divides n, print it and recurse on the reduced n
    if (n % divisor == 0) {
        if (first) {
            printf("%d", divisor);
        } else {
            printf(" * %d", divisor);
        }
        printFactors(n / divisor, divisor, 0);
    } else {
        // try the next divisor
        printFactors(n, divisor + 1, first);
    }
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    printf("The prime factors are ");
    printFactors(n, 2, 1);
    printf("\n");

    return (0);
}