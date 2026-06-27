// radius.c
// Prints the integer area of a circle given a radius
// Parameters: none (reads radius from user input)
// Returns: 0 on success

#include <stdio.h>
#include <math.h>

int main() {
    double pi = acos(-1);
    int r;

    printf("Enter an integer radius: ");
    scanf("%d", &r);

    int area = (int)(pi * r * r);
    printf("For a circle of radius %d.0 the area is %d\n", r, area);

    return 0;
}