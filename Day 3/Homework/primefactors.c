// primefactors.c
// Prints the prime factorization of a number using iteration only
// Parameters: none (reads from user input)
// Returns: 0 on success

#include <stdio.h>

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    printf("The prime factors are ");

    int divisor = 2;
    int firstFactor = 1;   // tracks whether we need to print " * " before a factor

    // keep dividing out factors starting from 2
    while (n > 1) {
        while (n % divisor == 0) {
            if (firstFactor) {
                printf("%d", divisor);
                firstFactor = 0;
            } else {
                printf(" * %d", divisor);
            }
            n = n / divisor;
        }
        divisor += 1;
    }

    printf("\n");
    return (0);
}