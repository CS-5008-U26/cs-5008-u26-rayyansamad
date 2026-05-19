/* thirdcprogram.c
 * Asks the user for their name and favorite color, then responds.
 * Based on secondcprogram.c with one additional input and output.
 *
 * Put your name here: Rayyan Samad
 * CS-5008 Summer 2026
 */

#include <stdio.h>

int main() {
    char s[100];
    char color[100];
    char t[100];

    printf("What is your name?  ");
    scanf("%s", s);
    printf("%s?  That's a funny name\n", s);

    printf("What is your favorite color?  ");
    scanf("%s", color);
    printf("%s?  That's a great color!\n", color);

    /* Pause the console so it doesn't vanish */
    fgets(t, 100, stdin);
}