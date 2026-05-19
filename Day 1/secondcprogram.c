/* Asks the user for their name and responds with a funny comment.
 * 
 * Put your name here: Rayyan Samad
 * CS-5008 Summer 2026
 *
 * Changes made:
 * 1. Added these comments (header and change list).
 * 2. Removed the fgets(s,100,stdin) after scanf, which was overwriting the name.
 * 3. Changed printf to print s instead of t (t was never assigned a value).
 * 4. Added fgets at the end to keep the console open until Enter is pressed.
 */

#include <stdio.h>

int main() {
    char s[100];
    char t[100];

    printf("What is your name?  ");
    scanf("%s", s);
    printf("%s?  That's a funny name\n", s);  /* changed t to s */

    /* Pause the console so it doesn't vanish */
    fgets(t, 100, stdin);
}