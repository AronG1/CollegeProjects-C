#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main()
{
	//struct Kalendar dogadaj[BRDOGADAJA]; // struktura Kalendar sa brojem dogadaja definiranim konstantom BRDOGADAJA
	struct Kalendar *dogadaj;
	dogadaj = malloc(BRDOGADAJA * sizeof(struct Kalendar));
	if (dogadaj == NULL)
	{
		printf("Noooo");

	}
	else
	{
		ucitavanjeDatoteke(dogadaj); // ucitat stare dogadaje, unesene prijasnjim radom aplikacije
		glavniIzbornik(dogadaj); // ispis glavnog izbornika
		free(dogadaj);
	}

	return 0;
}