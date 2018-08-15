#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main(void)
{
	int numPl = 0;
	int input = 0;
	PLAYERS *pl = NULL;
	pl = allocation();
	if (pl == NULL)
	{
		printf("Nemoguce zauzeti memoriju.");
		exit(0);
	}
	else
	{
		numPl = load(pl);
		do
		{
			printf("\n\nIZBORNIK\n");
			printf("1. Ispis igraca po slobodnim bacanjima\n");
			printf("2. Ispis igraca po ubacenim dvicama\n");
			printf("3. Ispis igraca po ubacenim tricama\n");
			printf("4. Pretrazi igraca\n");
			printf("5. Dodaj igraca\n");
			printf("0. Izlaz iz programa\n");
			scanf("%d", &input);
			if (input == 1)
			{
				sortFreeThrow(pl, numPl);
			}
			else if (input == 2)
			{
				sortDoublePoints(pl, numPl);
			}
			else if (input == 3)
			{
				sortTriplePoints(pl, numPl);
			}
			else if (input == 4)
			{
				search(pl, numPl);
			}
			else if (input == 5)
			{
				numPl = addPlayer(pl, numPl);
			}
			else if (input != 0)
			{
				printf("Krivi unos\n");
			}
		} while (input != 0);
		free(pl);
	}

	return 0;
}