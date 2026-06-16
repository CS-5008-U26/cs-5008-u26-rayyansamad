// size.c
// Prints the size in bytes of a given file
// Parameters: optional filename as command line argument
//             if no argument given, reads filename from user input
// Returns: 0 on success

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

// killNewline
//   removes the newline character from the end of a string if there is one
// Parameters:
//   char *str   the string to modify
// Returns:
//   nothing

void killNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

int main(int argc, char **argv) {
    char filename[1000];

    // get filename from argument or ask the user
    if (argc >= 2) {
        strcpy(filename, argv[1]);
    } else {
        printf("Enter the name of a file: ");
        fgets(filename, 1000, stdin);
        killNewline(filename);
    }

    struct stat fileStat;
    if (stat(filename, &fileStat) < 0) {
        printf("couldn't get info for that file\n");
        return 1;
    }

    printf("%s has %ld bytes\n", filename, (long int)fileStat.st_size);

    return 0;
}