#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif
#include "auth.h"

typedef struct {
    char username[50];
    char password[50];
} User;

// Function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to capture password without echoing it on the screen
void getHiddenPassword(char *password) {
    int i = 0;
    char ch;

    printf("Enter password: ");

#ifdef _WIN32
    // Windows implementation using conio.h
    while (1) {
        ch = _getch();
        if (ch == '\r' || ch == '\n') {
            password[i] = '\0';
            printf("\n");
            break;
        } else if (ch == '\b' && i > 0) { // Handle backspace
            i--;
            printf("\b \b");
        } else if (ch != '\b' && i < 49) {
            password[i++] = ch;
            printf("*");
        }
    }
#else
    // Linux/Unix implementation
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while (1) {
        ch = getchar();
        if (ch == '\n') {
            password[i] = '\0';
            printf("\n");
            break;
        } else if (ch == 127 && i > 0) { // Handle backspace
            i--;
            printf("\b \b");
        } else if (ch != 127 && i < 49) {
            password[i++] = ch;
            printf("*");
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
}

int registerUser() {
    FILE *file = fopen("users.txt", "a");
    if (!file) {
        perror("Failed to open users file for registration");
        return -1;
    }

    User user;
    printf("Enter username: ");
    if (scanf("%49s", user.username) != 1) {
        printf("Error reading username\n");
        fclose(file);
        return -1;
    }
    clearInputBuffer();

    getHiddenPassword(user.password);

    // Validate input
    if (strlen(user.username) < 1 || strlen(user.password) < 1) {
        printf("Username and password cannot be empty\n");
        fclose(file);
        return -1;
    }

    // Write user data to file
    fprintf(file, "%s %s\n", user.username, user.password);
    fclose(file);

    printf("Registration successful!\n");
    return 0;
}

int loginUser() {
    FILE *file = fopen("users.txt", "r");
    if (!file) {
        perror("Failed to open users file for login");
        return -1;
    }

    User user;
    char username[50], password[50];
    
    printf("Enter username: ");
    if (scanf("%49s", username) != 1) {
        printf("Error reading username\n");
        fclose(file);
        return -1;
    }
    clearInputBuffer();

    getHiddenPassword(password);

    // Search for matching username and password
    while (fscanf(file, "%s %s", user.username, user.password) != EOF) {
        if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0) {
            fclose(file);
            printf("Login successful!\n");
            return 1;
        }
    }
    fclose(file);
    printf("Invalid credentials!\n");
    return 0;
}
