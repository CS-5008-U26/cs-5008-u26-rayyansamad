/* A First C Program - for Homework 1
 *
 * This code will start you off.  Modify it as instructed in Homework 1.
 * 
 * Put your name here: Rayyan Samad
 * CS-5008 Spring 2025

 */

/* Standard Libraries */
#include <stdio.h>

/**** MAIN PROGRAM ****/

int main() {

    int x, y;                       // x and y will be the values entered by the user
    char s[100];                    // s is used to "pause" the console so it doesn't exit too quickly

    /* Ask for the first number */
    printf("Enter a number:\n");    // prompt the user
    scanf("%d", &x);                // read a number from the console ("stdin")
    fgets(s,100,stdin);             // remove the \n that scanf leaves in stdin

    /* Ask for the second number */
    printf("Enter another number:\n");
    scanf("%d", &y);
    fgets(s,100,stdin);             // remove the \n that scanf leaves in stdin

    /* Print the sum */
    printf("Their sum is %d\n", x + y);

    /* Pause the console so we can look at it before it vanishes */
    fgets(s,100,stdin);
}