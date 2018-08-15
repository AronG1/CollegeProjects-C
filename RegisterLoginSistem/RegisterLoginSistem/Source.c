#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main()
{
	printf("Dobrodosli u program za registraciju korisnika pasa.\n");
	USER *user = NULL; // pokazivac na strukturu (polje)
	user = allocation(); // alokcaija 
	if (user == NULL)
	{
		printf("Greska pri alokaciji.\n");
		exit(0); // izadi iz programa
	}
	else
	{
		mainMenu(user); // poziv mainMenu
	}

	return 0;
}