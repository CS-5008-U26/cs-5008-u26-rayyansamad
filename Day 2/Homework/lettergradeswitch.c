/* lettergradeswitch.c
 * Same as lettergrade.c but uses a switch statement instead of if/else.
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

    switch (score) {
        case 1:
        case 2:
        case 3:
            printf("Your grade is F\n");
            break;
        case 4:
        case 5:
            printf("Your grade is E\n");
            break;
        case 6:
            printf("Your grade is D\n");
            break;
        case 7:
            printf("Your grade is C\n");
            break;
        case 8:
            printf("Your grade is B\n");
            break;
        case 9:
        case 10:
            printf("Your grade is A\n");
            break;
        default:
            printf("Error: score must be between 1 and 10.\n");
            break;
    }

    return 0;
}