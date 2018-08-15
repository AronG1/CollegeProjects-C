#include <stdio.h>
#include <stdlib.h>
#include "Funkcije.h"

int main()
{
	int nastavak;
	struct Ekipe *ekipa; // struktura za sve ekipe
	ekipa = malloc((BREKIPAUGRUPI * BRGRUPA) * sizeof(struct Ekipe)); // alokacija memorije za sve ekipe
	if (ekipa == NULL)
	{
		printf("Greska. Memorija se ne moze zauzeti.\n");
	}
	else
	{
		unosEkipa(ekipa); // pozivanje funkciju za unos ekipa
		generiranjeIspisRezultata(ekipa); // pozivanje fje za random rezultate i ispis istih
		sortiranje(ekipa); // pozivanje fje za sortiranje tablica
		ispisGrupa(ekipa); // ispis sortiranih tablica
		struct EkipeCetvrtina *ekipaCet; // struktura za cetvritnu
		ekipaCet = malloc(8 * sizeof(struct EkipeCetvrtina)); // alokacija cetvrtine
		if (ekipa == NULL)
		{
			printf("Greska. Memorija se ne moze zauzeti.\n");
		}
		else
		{
			// za nastavak unijeti 1
			do
			{
				printf("\nUnesite 1 za nastavak\n");
				scanf("%d", &nastavak);
				if (nastavak != 1)
				{
					printf("Pogresan unos!\n");
					continue;
				}
				else
				{
					break;
				}
			} while (1);
			cetvrtinaFinala(ekipa, ekipaCet); // pozivanje fje za odigravanje cetvrtine finala
			struct EkipePolufinale *ekipaPolu; // struktura za polufinale
			ekipaPolu = malloc(4 * sizeof(struct EkipeCetvrtina)); // alokacija polufinala
			if (ekipa == NULL)
			{
				printf("Greska. Memorija se ne moze zauzeti.\n");
			}
			else
			{
				// za nastavak unijeti 1
				do
				{
					printf("\nUnesite 1 za nastavak\n");
					scanf("%d", &nastavak);
					if (nastavak != 1)
					{
						printf("Pogresan unos!\n");
						continue;
					}
					else
					{
						break;
					}
				} while (1);
				polufinale(ekipaCet, ekipaPolu); // pozivanje fje za odigravanje polufinala
				struct EkipeFinale *ekipaFinale; // struktrura finala 
				ekipaFinale = malloc(2 * sizeof(struct EkipeCetvrtina)); // alokacija finala
				if (ekipa == NULL)
				{
					printf("Greska. Memorija se ne moze zauzeti.\n");
				}
				else
				{
					// za nastavak unijeti 1
					do
					{
						printf("\nUnesite 1 za nastavak\n");
						scanf("%d", &nastavak);
						if (nastavak != 1)
						{
							printf("Pogresan unos!\n");
							continue;
						}
						else
						{
							break;
						}
					} while (1);
					finale(ekipaPolu, ekipaFinale); // pozivanje fje za odigravanje finala
				}
			}
		}
	}


	return 0;
}