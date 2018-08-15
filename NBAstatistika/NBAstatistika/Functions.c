#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

PLAYERS *allocation()
{
	return malloc(100 * sizeof(PLAYERS));
}

int load(PLAYERS* pl)
{
	int numPl = 0;
	FILE* stream = NULL;
	stream = fopen("players.bin", "rb");
	if (stream == NULL)
	{
		return 0;
	}
	else
	{
		numPl = fread(pl, sizeof(PLAYERS), 100, stream);
		fclose(stream);
		return numPl;
	}

}

int addPlayer(PLAYERS* pl, int numPlayers)
{
	FILE* stream = NULL;
	stream = fopen("players.bin", "wb");
	if (stream == NULL)
	{
		printf("Greska pri upisu!\n");
	}
	else
	{
		printf("\n\nUNOS IGRACA\n");
		printf("Unesi ime igraca: ");
		scanf("%s", pl[numPlayers].name);
		printf("Unesi prezime igraca: ");
		scanf("%s", pl[numPlayers].lastName);
		printf("Unesi broj ubacenih slobodnih bacanja: ");
		scanf("%d", &pl[numPlayers].freeThrow);
		printf("Unesi broj ubacenih dvica: ");
		scanf("%d", &pl[numPlayers].doublePoints);
		printf("Unesi broj ubacenih trica: ");
		scanf("%d", &pl[numPlayers].triplePoints);
		numPlayers++;
		fwrite(pl, sizeof(PLAYERS), numPlayers, stream);
		fclose(stream);
		printf("Uspjesno dodan igrac\n");
	}
	return numPlayers;
}

void sortFreeThrow(PLAYERS* pl, int numPlayers)
{
	int temp;
	char charTemp[50];
	for (int i = 0; i < numPlayers - 1; i++)
	{
		for (int j = i + 1; j < numPlayers; j++)
		{
			if (pl[j].freeThrow > pl[i].freeThrow)
			{
				strcpy(charTemp, pl[j].name);
				strcpy(pl[j].name, pl[i].name);
				strcpy(pl[i].name, charTemp);

				strcpy(charTemp, pl[j].lastName);
				strcpy(pl[j].lastName, pl[i].lastName);
				strcpy(pl[i].lastName, charTemp);

				temp = pl[j].freeThrow;
				pl[j].freeThrow = pl[i].freeThrow;
				pl[i].freeThrow = temp;

				temp = pl[j].doublePoints;
				pl[j].doublePoints = pl[i].doublePoints;
				pl[i].doublePoints = temp;

				temp = pl[j].triplePoints;
				pl[j].triplePoints = pl[i].triplePoints;
				pl[i].triplePoints = temp;
			}
		}
	}
	print(pl, numPlayers);
}

void print(PLAYERS* pl, int numPlayers)
{
	if (numPlayers <= 0)
	{
		printf("Nema unesenih igraca\n");
		return;
	}
	else
	{
		printf("\n\nIGRACI\n");
		for (int i = 0; i < numPlayers; i++)
		{
			printf("Igrac: %s %s\n", pl[i].name, pl[i].lastName);
			printf("Slobodna bacanja: %d\n", pl[i].freeThrow);
			printf("Broj pogodenih dvica: %d\n", pl[i].doublePoints);
			printf("Broj pogodenih trica: %d\n\n", pl[i].triplePoints);
		}
	}

}

void sortDoublePoints(PLAYERS* pl, int numPlayers)
{
	int temp;
	char charTemp[50];
	for (int i = 0; i < numPlayers - 1; i++)
	{
		for (int j = i + 1; j < numPlayers; j++)
		{
			if (pl[j].doublePoints > pl[i].doublePoints)
			{
				strcpy(charTemp, pl[j].name);
				strcpy(pl[j].name, pl[i].name);
				strcpy(pl[i].name, charTemp);

				strcpy(charTemp, pl[j].lastName);
				strcpy(pl[j].lastName, pl[i].lastName);
				strcpy(pl[i].lastName, charTemp);

				temp = pl[j].freeThrow;
				pl[j].freeThrow = pl[i].freeThrow;
				pl[i].freeThrow = temp;

				temp = pl[j].doublePoints;
				pl[j].doublePoints = pl[i].doublePoints;
				pl[i].doublePoints = temp;

				temp = pl[j].triplePoints;
				pl[j].triplePoints = pl[i].triplePoints;
				pl[i].triplePoints = temp;
			}
		}
	}
	print(pl, numPlayers);
}

void sortTriplePoints(PLAYERS* pl, int numPlayers)
{
	int temp;
	char charTemp[50];
	for (int i = 0; i < numPlayers - 1; i++)
	{
		for (int j = i + 1; j < numPlayers; j++)
		{
			if (pl[j].triplePoints > pl[i].triplePoints)
			{
				strcpy(charTemp, pl[j].name);
				strcpy(pl[j].name, pl[i].name);
				strcpy(pl[i].name, charTemp);

				strcpy(charTemp, pl[j].lastName);
				strcpy(pl[j].lastName, pl[i].lastName);
				strcpy(pl[i].lastName, charTemp);

				temp = pl[j].freeThrow;
				pl[j].freeThrow = pl[i].freeThrow;
				pl[i].freeThrow = temp;

				temp = pl[j].doublePoints;
				pl[j].doublePoints = pl[i].doublePoints;
				pl[i].doublePoints = temp;

				temp = pl[j].triplePoints;
				pl[j].triplePoints = pl[i].triplePoints;
				pl[i].triplePoints = temp;
			}
		}
	}
	print(pl, numPlayers);
}

void search(PLAYERS* pl, int numPl)
{
	int searchNum = 0;
	int returnNum = 0;
	printf("\n\nPRETRAZI\n");
	printf("Unesi najmanji broj ubacenih dvica: ");
	scanf("%d", &searchNum);
	printf("Igraci s vise od %d postignutih koseva: \n", searchNum);
	for (int i = 0; i < numPl; i++)
	{
		if (pl[i].doublePoints > searchNum)
		{
			printf("%s %s, broj koseva: %d\n", pl[i].name, pl[i].lastName, pl[i].doublePoints);
			returnNum = 1;
		}
	}
	if (returnNum == 0)
	{
		printf("Nema igraca koji su postigli vise od %d koseva\n", searchNum);
	}
}