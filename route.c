#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "route.h"
#include "ui_utils.h"

void addRoute() {
    FILE *file = fopen("routes.txt", "a");
    Route route;

    printf("Enter Route ID: ");
    scanf("%s", route.routeID);
    printf("Enter Origin: ");
    scanf("%s", route.origin);
    printf("Enter Destination: ");
    scanf("%s", route.destination);
    printf("Enter Number of Stops: ");
    scanf("%d", &route.numStops);
    printf("Enter Type (Bus/Train/Metro): ");
    scanf("%s", route.type);
    route.popularity = 0;  // Initialize popularity to 0

    fprintf(file, "%s %s %s %d %s %d\n", route.routeID, route.origin, route.destination, route.numStops, route.type, route.popularity);
    fclose(file);
    printf("Route added successfully!\n");
}

void displayRoutes() {
    FILE *file = fopen("routes.txt", "r");
    Route route;

    printHeader("Public Transport Routes");
    printf("| %-10s | %-15s | %-15s | %-10s |\n", "Route ID", "Origin", "Destination", "Type");
    printLine(50);

    while (fscanf(file, "%s %s %s %d %s %d", route.routeID, route.origin, route.destination, &route.numStops, route.type, &route.popularity) != EOF) {
        printf("| %-10s | %-15s | %-15s | %-10s |\n", route.routeID, route.origin, route.destination, route.type);
        route.popularity++; // Increase popularity count
    }
    fclose(file);
}

void displayPopularRoutes() {
    FILE *file = fopen("routes.txt", "r");
    Route routes[100];
    int count = 0;

    // Load routes into an array
    while (fscanf(file, "%s %s %s %d %s %d", routes[count].routeID, routes[count].origin, 
                  routes[count].destination, &routes[count].numStops, routes[count].type, &routes[count].popularity) != EOF) {
        count++;
    }
    fclose(file);

    // Sort by popularity
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (routes[i].popularity < routes[j].popularity) {
                Route temp = routes[i];
                routes[i] = routes[j];
                routes[j] = temp;
            }
        }
    }

    printHeader("Top Routes by Popularity");
    for (int i = 0; i < count && i < 5; i++) {
        printf("Route ID: %s, Type: %s, Popularity: %d\n", routes[i].routeID, routes[i].type, routes[i].popularity);
    }
}

void filterRoutesByType() {
    FILE *file = fopen("routes.txt", "r");
    Route route;
    char filterType[10];

    printf("Enter transportation type to filter by (Bus/Train/Metro): ");
    scanf("%s", filterType);

    printHeader("Filtered Routes");
    while (fscanf(file, "%s %s %s %d %s %d", route.routeID, route.origin, route.destination, &route.numStops, route.type, &route.popularity) != EOF) {
        if (strcmp(route.type, filterType) == 0) {
            printf("Route ID: %s, Origin: %s, Destination: %s, Type: %s\n", route.routeID, route.origin, route.destination, route.type);
        }
    }
    fclose(file);
}
