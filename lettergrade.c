/* lettergrade.c
 * Accepts a number score from 1 to 10 and prints the letter grade.
 * Uses if/else statements.
 *
 * Grading scale:
 *   1-3  -> F
 *   4-5  -> E
 *   6    -> D
 *   7    -> C
 *   8    -> B
 *   9-10 -> A
 *
 * Name: Rayyan Samad
 * CS-5008 Summer 2026
 */

#include <stdio.h>

int main() {

    int score;  /* number score entered by the user, must be 1 to 10 */

    printf("Enter the number score: ");
    scanf("%d", &score);

    /* check range first before assigning a grade */
    if (score < 1 || score > 10) {
        printf("Error: score must be between 1 and 10.\n");
    } else if (score <= 3) {
        printf("Your grade is F\n");
    } else if (score <= 5) {
        printf("Your grade is E\n");
    } else if (score == 6) {
        printf("Your grade is D\n");
    } else if (score == 7) {
        printf("Your grade is C\n");
    } else if (score == 8) {
        printf("Your grade is B\n");
    } else {
        printf("Your grade is A\n");
    }

    return 0;
}