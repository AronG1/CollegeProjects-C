#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main()
{
	int brStanova = 0; 
	int brKatova = 0;
	int brStanovaPoKatu = 0; // brKatova / br stanova
	do // sve dok nije br katova djeljiv s br stanova vrti petlju
	{
		// unos
		printf("Unesite broj stanova u zgradi: \n");
		scanf("%d", &brStanova);
		printf("Unesite broj katova u zgradi: \n");
		scanf("%d", &brKatova);
		if (brStanova % brKatova != 0) // ako nije djeljivo
		{
			printf("Broj katova nije djeljiv s brojem stanova\n");
			continue;
		}
		else // djeljivo je
		{
			brStanovaPoKatu = brStanova / brKatova; // postavi brStanovaPoKatu
			break; // break while petlju
		}
	} while (1); // vrti se dok ne dode do break
	STANAR *osoba = NULL; // polje stanara
	osoba = alokacija(brStanova); // alociraj koliko ima stanova
	citanjeDatoteke(osoba, brStanovaPoKatu, brKatova); // iscitaj iz datoteke zauzete stanove
	Izbornik(osoba, brStanovaPoKatu, brKatova); // poziva izbornik
	return 0; // kraj
}