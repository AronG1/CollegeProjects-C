#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main()
{
	int odabir, brMin = 0, tr = 0;
	MINERAL *mi = NULL;
	mi = memorija();
	if (mi == NULL)
	{
		printf("Greska s memorijom!\n");
	}
	else
	{
		brMin = ucitajMinerale(mi);
		do
		{
			printf("Odaberite: \n1. dodaj novi mineral\n2. ispisi minerale\n3. trazi mineral\n0. izlaz iz programa\n");
			scanf("%d", &odabir);
			if (odabir == 1)
			{
				brMin = dodaj(mi, brMin);
			}
			else if (odabir == 2)
			{
				ispis(mi, brMin);
			}
			else if (odabir == 3)
			{
				tr = trazenje(mi, brMin);
				if (tr == 0)
				{
					printf("Trazeni mineral nije pronaden!\n");
				}
			}
		} while (odabir != 0);
	}
	


	return 0;
}