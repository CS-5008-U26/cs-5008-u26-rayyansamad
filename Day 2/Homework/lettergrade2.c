/* lettergrade2.c
 * Accepts a score from 0 to 100 and prints the letter grade with +/- mod.
 *
 * Grade ranges:
 *   0-60   -> F  (no +/-)
 *   61-70  -> D
 *   71-80  -> C
 *   81-90  -> B
 *   91-100 -> A
 *
 * For scores 61-100, mod based on last digit:
 *   1, 2, 3       -> minus (-)
 *   4, 5, 6, 7    -> nothing
 *   8, 9, 0       -> plus (+)
 *
 * Name: Rayyan Samad
 * CS-5008 Summer 2026
 */

#include <stdio.h>

int main() {

    int score;      /* score from 0 to 100 */
    int last_digit;  /* last digit of score, used to determine +/- */
    char letter;    /* letter grade A through F */
    char mod;  /* '+', '-', or ' ' (space means no mod) */

    printf("Enter the number score: ");
    scanf("%d", &score);

    /* assign letter grade based on score range */
    if (score < 0 || score > 100) {
        printf("Error: score must be between 0 and 100.\n");
        return 1;
    } else if (score <= 60) {
        /* F has no mod */
        printf("Your grade is F\n");
        return 0;
    } else if (score <= 70) {
        letter = 'D';
    } else if (score <= 80) {
        letter = 'C';
    } else if (score <= 90) {
        letter = 'B';
    } else {
        letter = 'A';
    }

    /* figure out +/- based on the last digit */
    last_digit = score % 10;
    if (last_digit == 1 || last_digit == 2 || last_digit == 3) {
        mod = '-';
    } else if (last_digit == 8 || last_digit == 9 || last_digit == 0) {
        mod = '+';
    } else {
        mod = ' ';  /* no mod */
    }

    /* print result -- skip the space if there's no mod */
    if (mod == ' ') {
        printf("Your grade is %c\n", letter);
    } else {
        printf("Your grade is %c%c\n", letter, mod);
    }

    return 0;
}