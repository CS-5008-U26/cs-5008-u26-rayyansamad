// complement.c
// Prints the 10's complement of an integer using recursion
// Parameters: none (reads from user input)
// Returns: 0 on success

#include <stdio.h>

// complement
//   calculates the 10's complement of an integer recursively
// Parameters:
//   int x   the integer to complement
// Returns:
//   int     the complemented integer

int complement(int x) {
    // base case: single digit
    if (x / 10 == 0) {
        return (9 - x);
    }

    // strip the rightmost digit, complement the rest, then put back the complemented digit
    int rightDigit = x % 10;
    int rest = x / 10;

    return (complement(rest) * 10) + (9 - rightDigit);
}

int main() {
    int n;
    printf("Enter an integer: ");
    scanf("%d", &n);
    printf("The complement is %d\n", complement(n));
    return (0);
}