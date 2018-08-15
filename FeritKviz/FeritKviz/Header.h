#ifndef HEADER_H
#define HEADER_H

struct player {

	char firstName[50];
	char lastName[50];
	int points;
};

void Start();
void Help();
void ScoreList();
void sorting(struct player igrac[100], int brIgraca);


void mainMenu();


#endif // HEADER_H
