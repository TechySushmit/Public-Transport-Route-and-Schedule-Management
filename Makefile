# Makefile
CC = gcc
CFLAGS = -Wall

all: main

main: main.o auth.o route.o schedule.o ui_utils.o
	$(CC) $(CFLAGS) -o main main.o auth.o route.o schedule.o ui_utils.o

main.o: main.c auth.h route.h schedule.h ui_utils.h
	$(CC) $(CFLAGS) -c main.c

auth.o: auth.c auth.h
	$(CC) $(CFLAGS) -c auth.c

route.o: route.c route.h
	$(CC) $(CFLAGS) -c route.c

schedule.o: schedule.c schedule.h
	$(CC) $(CFLAGS) -c schedule.c

ui_utils.o: ui_utils.c ui_utils.h
	$(CC) $(CFLAGS) -c ui_utils.c

clean:
	rm -f *.o main
