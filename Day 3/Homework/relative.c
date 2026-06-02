// relative.c
// Prints the ET-function for each integer from 2 to n
// ET(x) = count of integers less than x that are relatively prime with x
// Parameters: none (reads n from user input)
// Returns: 0 on success

#include <stdio.h>

// gcd
//   finds the greatest common divisor of two integers using Euclidean algorithm
// Parameters:
//   int a   first integer
//   int b   second integer
// Returns:
//   int     the greatest common divisor

int gcd(int a, int b) {
    // base case: if b is 0, gcd is a
    if (b == 0) {
        return (a);
    }
    return gcd(b, a % b);
}

// et
//   counts how many integers less than x are relatively prime with x
//   two numbers are relatively prime if their gcd is 1
// Parameters:
//   int x   the number to evaluate
// Returns:
//   int     count of integers less than x that are relatively prime with x

int et(int x) {
    int count = 0;
    for (int i = 1; i < x; i++) {
        if (gcd(i, x) == 1) {
            count += 1;
        }
    }
    return (count);
}

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    // print ET value for each integer from 2 to n
    for (int i = 2; i <= n; i++) {
        printf("ET(%d) = %d\n", i, et(i));
    }

    return (0);
}

