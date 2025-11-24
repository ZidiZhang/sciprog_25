#include <stdio.h>
#include <stdlib.h>
#define MAX_FILE_NAME 100
#include "magic_square.h"

int getlines(char filename[MAX_FILE_NAME]);

int main() {

    FILE *f;
    char filename[MAX_FILE_NAME];
    printf("Enter file name: ");
    scanf("%s", filename);

    // Get the matrix dimension n
    int n = getlines(filename);
    printf("Matrix size: %d x %d\n", n, n);

    // Open the file
    f = fopen(filename, "r");
    if (f == NULL) {
        printf("!! CAN'T OPEN THE FILE !!\n");
        exit(1);
    }

    // Allocate an n×n matrix
    int **magicSquare = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        magicSquare[i] = malloc(n * sizeof(int));
    }

    // Read matrix values
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            // Check if fscanf successfully read an integer
            if (fscanf(f, "%d", &magicSquare[i][j]) != 1) {
                printf("Error: invalid matrix format at row %d column %d\n", i, j);
                fclose(f);

                // Free memory before exiting
                for (int k = 0; k < n; k++) free(magicSquare[k]);
                free(magicSquare);
                exit(1);
            }
        }
    }

    fclose(f);

    // Check if the matrix is a magic square
    printf("This square %s magic.\n",
           isMagicSquare(magicSquare, n) ? "IS" : "is NOT");

    // Free memory
    for (int i = 0; i < n; i++) {
        free(magicSquare[i]);
    }
    free(magicSquare);

    return 0;
}


// Count the number of lines in the file
int getlines(char filename[MAX_FILE_NAME]) {

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Can't open file %s\n", filename);
        exit(1);
    }

    int ch, count = 0;
    int lastChar = 0;

    // Count newline characters
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') count++;
        lastChar = ch;
    }

    // If file does not end with a newline, count the last line
    if (lastChar != '\n') count++;

    fclose(fp);
    return count;
}
