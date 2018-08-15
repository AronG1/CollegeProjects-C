#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

// glavna funkcija
int main(void)
{
	struct Automobil *automobil; // pokazivac strukture automobil
	automobil = malloc(100 * sizeof(struct Automobil)); // dinamicko zauzimanje memorije za 100 automobila
	if (automobil == NULL) // provjera jel uspjesno zauzeta memorija
	{
		printf("Ne moze se zauzeti memorija.");
	}
	else
	{
		ucitajBazu(automobil, 0); // ucitavanje vec unesenih automobila
	}

	return 0;
}