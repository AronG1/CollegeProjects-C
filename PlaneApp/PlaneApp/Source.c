// aplikacija za usmeni ispit iz kolegija Programiranje II. Aplikacija rezerviranja mjesta u avionu. Aron Gaspic
#include <stdio.h>
#include "Methods.h" // my header file

int main()
{
	printf("Dobrodosli u aplikaciju za rezervaciju avionskih mjesta.\n");
	flightName = (char*)malloc((FLIGHTNAMELONG) * sizeof(char)); // alocate memory for flight name

	setFlightName();

	free(flightName);
	return 0;
}


