#ifndef ROUTE_H
#define ROUTE_H

typedef struct {
    char routeID[10];
    char origin[50];
    char destination[50];
    int numStops;
    char type[10];  // e.g., Bus, Train, Metro
    int popularity;
} Route;

void addRoute();
void displayRoutes();
void displayPopularRoutes();
void filterRoutesByType();

#endif
