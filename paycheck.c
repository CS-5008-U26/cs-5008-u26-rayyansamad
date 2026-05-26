/* paycheck.c
 * Calculates pay based on hourly rate and hours worked.
 * Overtime over 40 hours is paid at 1.5x the hourly rate.
 * Keeps looping until the user enters 0 or negative for either input.
 *
 * Name: Rayyan Samad
 * CS-5008 Summer 2026
 */

#include <stdio.h>

int main() {

    double payrate;  /* hourly rate the user enters */
    double hours;    /* how many hours they worked */
    double totalpay; /* what they get paid at the end */

    while (1) {

        printf("Enter an hourly rate: ");
        scanf("%lf", &payrate);

        if (payrate <= 0)
            break;

        printf("Enter the number of hours worked: ");
        scanf("%lf", &hours);

        if (hours <= 0)
            break;

        /* anything over 40 hours gets paid at 1.5x */
        if (hours <= 40) {
            totalpay = payrate * hours;
        } else {
            totalpay = (payrate * 40) + (payrate * 1.5 * (hours - 40));
        }

        printf("You should be paid %g\n\n", totalpay);
    }

    return 0;
}