#include <stdio.h>
#include "auth.h"
#include "route.h"
#include "schedule.h"
#include "ui_utils.h"

void displayMenu() {
    printHeader("Public Transport Management System");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Add Route\n");
    printf("4. Display Routes\n");
    printf("5. Add Schedule\n");
    printf("6. Display Schedules\n");
    printf("7. Display Popular Routes\n");
    printf("8. Filter Routes by Type\n");
    printf("0. Exit\n");
}

int main() {
    int choice, loggedIn = 0;

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            scanf("%*s"); // Clear the input buffer
            continue;
        }

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loggedIn = loginUser();
                break;
            case 3:
                if (loggedIn) addRoute();
                else printf("Please login first!\n");
                break;
            case 4:
                if (loggedIn) displayRoutes();
                else printf("Please login first!\n");
                break;
            case 5:
                if (loggedIn) addSchedule();
                else printf("Please login first!\n");
                break;
            case 6:
                if (loggedIn) displaySchedules();
                else printf("Please login first!\n");
                break;
            case 7:
                if (loggedIn) displayPopularRoutes();
                else printf("Please login first!\n");
                break;
            case 8:
                if (loggedIn) filterRoutesByType();
                else printf("Please login first!\n");
                break;
            case 0:
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}
