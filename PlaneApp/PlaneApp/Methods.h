#pragma once

#define ROW 10 // number of rows
#define COLS 3 // number of colums
#define ECONOM_START 4 // at what colum economy class starts
#define FLIGHTNAMELONG 21 // how long can flight name be

int plane[ROW + 1][COLS + 1];	// plane array
char *flightName;	// char - flight name 


// struct for passager informations
typedef struct passager
{
	char name[20];
	char lastName[20];
	int row;
	int seat;

}passager;

struct list
{
	char name[20];
	char lastName[20];
	int row;
	int seat;
};

struct list passagerList[ROW * COLS];

void mainMenu();
void firstClassCheckIn();
void printPassager(struct passager);
void economyClassCheckIn();
void viewSeatingChart();
void selectOwnSeat();
void readPassagersList();
void setFlightName();
void checkIsFlightExist();
void sorting();
