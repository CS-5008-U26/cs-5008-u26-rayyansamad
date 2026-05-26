/* cents.c
 * Accepts a number of cents (1-100) and prints the coins needed.
 * Uses the largest denominations first.
 *
 * Name: Rayyan Samad
 * CS-5008 Summer 2026
 */

#include <stdio.h>

int main() {

    int cents;      /* number of cents entered by user */
    int quarters;   /* number of quarters needed */
    int dimes;      /* number of dimes needed */
    int nickels;    /* number of nickels needed */
    int pennies;    /* number of pennies left over */

    printf("Enter a number of cents: ");
    scanf("%d", &cents);

    if (cents < 1 || cents > 100) {
        printf("Please enter a number between 1 and 100.\n");
        return 1;
    }

    /* figure out how many of each coin we need */
    quarters = cents / 25;
    cents = cents % 25;

    dimes = cents / 10;
    cents = cents % 10;

    nickels = cents / 5;
    cents = cents % 5;

    pennies = cents;

    /* print each coin, singular or plural */
    if (quarters == 1)
        printf("1 quarter\n");
    else if (quarters > 1)
        printf("%d quarters\n", quarters);

    if (dimes == 1)
        printf("1 dime\n");
    else if (dimes > 1)
        printf("%d dimes\n", dimes);

    if (nickels == 1)
        printf("1 nickel\n");
    else if (nickels > 1)
        printf("%d nickels\n", nickels);

    if (pennies == 1)
        printf("1 penny\n");
    else if (pennies > 1)
        printf("%d pennies\n", pennies);

    return 0;
}