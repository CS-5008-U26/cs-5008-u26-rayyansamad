/* roman.c
 * Takes a number from 1 to 4000 and prints it as a Roman numeral.
 *
 * Name: Rayyan Samad
 * CS-5008 Summer 2026
 */

#include <stdio.h>

int main() {

    int n; /* number the user types in */

    printf("Enter a number between 1 and 4000: ");
    scanf("%d", &n);

    if (n < 1 || n > 4000) {
        printf("Error: number must be between 1 and 4000.\n");
        return 1;
    }

    printf("The Roman Numeral:  ");

    /* keep subtracting the biggest value that fits and print the symbol */
    while (n >= 1000) { printf("M"); n -= 1000; }
    while (n >= 900) { printf("CM"); n -= 900; }
    while (n >= 500) { printf("D"); n -= 500; }
    while (n >= 400) { printf("CD"); n -= 400; }
    while (n >= 100) { printf("C"); n -= 100; }
    while (n >= 90) { printf("XC"); n -= 90; }
    while (n >= 50) { printf("L"); n -= 50; }
    while (n >= 40) { printf("XL"); n -= 40; }
    while (n >= 10) { printf("X"); n -= 10; }
    while (n >= 9) { printf("IX"); n -= 9; }
    while (n >= 5) { printf("V"); n -= 5; }
    while (n >= 4) { printf("IV"); n -= 4; }
    while (n >= 1) { printf("I"); n -= 1; }

    printf("\n");

    return 0;
}