#pragma once

typedef struct players
{
	char name[50];
	char lastName[50];
	int freeThrow;
	int doublePoints;
	int triplePoints;
}PLAYERS;

PLAYERS *allocation();
int load(PLAYERS*);
int addPlayer(PLAYERS*, int);
void sortFreeThrow(PLAYERS*, int);
void print(PLAYERS*, int);
void sortDoublePoints(PLAYERS*, int);
void sortTriplePoints(PLAYERS*, int);
void search(PLAYERS*, int);