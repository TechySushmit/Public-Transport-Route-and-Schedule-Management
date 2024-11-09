#include <stdio.h>
#include <string.h>
#include "schedule.h"

int calculateTravelTime(char *departure, char *arrival) {
    int depHours, depMinutes, arrHours, arrMinutes;
    sscanf(departure, "%d:%d", &depHours, &depMinutes);
    sscanf(arrival, "%d:%d", &arrHours, &arrMinutes);

    int depTotal = depHours * 60 + depMinutes;
    int arrTotal = arrHours * 60 + arrMinutes;
    return arrTotal - depTotal;
}

void addSchedule() {
    FILE *file = fopen("schedules.txt", "a");
    Schedule schedule;

    printf("Enter Route ID: ");
    scanf("%s", schedule.routeID);
    printf("Enter Departure Time (HH:MM): ");
    scanf("%s", schedule.departure);
    printf("Enter Arrival Time (HH:MM): ");
    scanf("%s", schedule.arrival);
    printf("Enter Frequency (in minutes): ");
    scanf("%d", &schedule.frequency);

    schedule.travelTime = calculateTravelTime(schedule.departure, schedule.arrival);
    fprintf(file, "%s %s %s %d %d\n", schedule.routeID, schedule.departure, schedule.arrival, schedule.frequency, schedule.travelTime);
    fclose(file);
    printf("Schedule added successfully with a travel time of %d minutes!\n", schedule.travelTime);
}

void displaySchedules() {
    FILE *file = fopen("schedules.txt", "r");
    Schedule schedule;

    printf("\nSchedules:\n");
    printf("-----------------------------------------------\n");
    printf("| %-10s | %-8s | %-8s | %-10s |\n", "Route ID", "Depart", "Arrival", "Frequency");
    printf("-----------------------------------------------\n");

    while (fscanf(file, "%s %s %s %d %d", schedule.routeID, schedule.departure, schedule.arrival, 
                  &schedule.frequency, &schedule.travelTime) != EOF) {
        printf("| %-10s | %-8s | %-8s | %-10d |\n", schedule.routeID, schedule.departure, schedule.arrival, schedule.frequency);
    }
    printf("-----------------------------------------------\n");
    fclose(file);
}
