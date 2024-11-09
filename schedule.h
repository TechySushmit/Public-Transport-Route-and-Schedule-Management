#ifndef SCHEDULE_H
#define SCHEDULE_H

typedef struct {
    char routeID[10];
    char departure[6];
    char arrival[6];
    int frequency;
    int travelTime;
} Schedule;

void addSchedule();
void displaySchedules();

#endif
