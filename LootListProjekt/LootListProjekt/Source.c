#include <stdio.h>
#include "Header.h"
#include <stdlib.h>

int main()
{
	int unos;
	ITEM *it = NULL; // pokazivac (polje) za rad s items
	it = (ITEM*)calloc(100, sizeof(ITEM)); // alokacija memorije 100 itema moze se spremit
	if (it == NULL) // ako se ne moze alocirati
	{
		printf("Nema memorije\n");
	}
	else
	{
		ucitajIteme(it); // poziv funkcije da ucita iteme iz datoteke u strukturu
		do
		{
			// main menu
			printf("Odaberi: \n1 Ispis svih itema\n2 Pretrazi item\n3 Dodat novi item\n0 Izlaz\n");
			scanf("%d", &unos);
			if (unos == 1)
			{
				ispisiIteme(it);
			}
			else if (unos == 2)
			{
				searchItem(it);
			}
			else if (unos == 3)
			{
				addItem(it);
			}
			else if (unos > 3)
			{
				printf("Pogresan unos.\n");
			}
		} while (unos != 0); // dok ne unese 0 ispisuj meni kad unese 0 izadi
	}
	return 0;
}