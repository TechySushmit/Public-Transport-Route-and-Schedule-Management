#include <stdio.h>
#include <string.h>
#include "ui_utils.h"

void printHeader(const char *title) {
    printf("\033[1;34m"); // Set color to blue
    int len = strlen(title);
    int padding = (50 - len) / 2;

    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s\n", title);
    printLine(50);
    printf("\033[0m"); // Reset color
}

void printLine(int length) {
    for (int i = 0; i < length; i++) {
        printf("-");
    }
    printf("\n");
}
