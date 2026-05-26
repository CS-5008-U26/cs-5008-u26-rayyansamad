/* paycheck.c
 * Calculates totalpay based on hourly payrate and hours worked.
 * Overtime (over 40 hours) is paid at 1.5x the hourly payrate.
 * Loops until the user enters 0 or a negative number for either input.
 *
 * Name: Rayyan Samad
 * CS-5008 Summer 2026
 */

#include <stdio.h>

int main() {

    double payrate;    /* hourly totalpay payrate entered by user */
    double hours;   /* number of hours worked */
    double totalpay;     /* total totalpay to be printed */

    /* keep asking until user enters 0 or negative */
    while (1) {

        printf("Enter an hourly payrate: ");
        scanf("%lf", &payrate);

        /* exit if payrate is 0 or negative */
        if (payrate <= 0)
            break;

        printf("Enter the number of hours worked: ");
        scanf("%lf", &hours);

        /* exit if hours is 0 or negative */
        if (hours <= 0)
            break;

        /* calculate totalpay -- overtime kicks in above 40 hours */
        if (hours <= 40) {
            totalpay = payrate * hours;
        } else {
            totalpay = (payrate * 40) + (payrate * 1.5 * (hours - 40));
        }

        printf("You should be paid %g\n\n", totalpay);
    }

    return 0;
}