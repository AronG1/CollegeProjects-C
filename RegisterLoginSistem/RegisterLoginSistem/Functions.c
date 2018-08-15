#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

USER* allocation()
{
	return malloc(BRKORISNIKA * sizeof(USER)); // vraca u main() alociranje memorije
}

void mainMenu(USER* us)
{
	int choosing = 0;
	printf("\n------------------------------------------------------------");
	printf("\nGlavni izbornik:\n");
	printf("1 - Registracija\n");
	printf("2 - Prijava\n");
	printf("3 - Izlaz iz programa\n");
	printf("Odabir: ");
	scanf("%d", &choosing);
	switch (choosing)
	{
	case 1:
		registration(us);
		break;
	case 2:
		database(us);
		break;
	case 3:
		memoryFree(us);
		exit(0);
		break;
	default:
		printf("Krivi unos.\n");
		mainMenu(us);
		break;
	}
}

void registration(USER* us)
{
	printf("\n------------------------------------------------------------\n");
	printf("Registracija: \n");
	char name[50];
	char lastName[50];
	char username[50];
	char password[50];
	int dogs = 0;
	FILE* file = NULL;
	file = fopen("User.txt", "a");
	if (file == NULL)
	{
		printf("Greska s datotekom.\n");
	}
	else
	{
		printf("Unesite ime: ");
		scanf("%s", name);
		printf("Unesite prezime: ");
		scanf("%s", lastName);
		printf("Unesite korisnicko ime: ");
		scanf("%s", username);
		printf("Unesite lozinku: ");
		scanf("%s", password);
		printf("Unesite broj pasa: ");
		scanf("%d", &dogs);
		fprintf(file, "%s\n%s\n%s\n%s\n%d\n", name, lastName, username, password, dogs); // upisuje u datoteku podatke od novog korisnika
		printf("Uspjesno ste se registrirali\n");
		fclose(file);
		database(us); // funkcija prije login funkcije
	}
	mainMenu(us);
}

void database(USER* us) // iscita sve korisnike iz datoteke i spremi ih u strukturu
{
	int numOfUsers = 0;
	FILE* file = NULL;
	file = fopen("User.txt", "r");
	if (file == NULL)
	{
		printf("Nema jos registriranih korisnika.\n");
		mainMenu(us);
	}
	else
	{
		int i = 0;
		while (fscanf(file, "%s\n%s\n%s\n%s\n%d\n", us[i].name, us[i].lastName, us[i].username, us[i].password, &us[i].numDogs)!= EOF) // citaj sve dok ne dodes do kraja filea
		{
			i++;
		}
		fclose(file);
		numOfUsers = i;
		login(us, numOfUsers); // poziv login fje
	}
	
}

void login(USER* us, int numOfUsers)
{
	printf("\n------------------------------------------------------------\n");
	char username[50];
	char password[50];
	printf("\nPrijava: \n");
	printf("Unesite korisnicko ime: ");
	scanf("%s", username);
	printf("Unesite lozinku: ");
	scanf("%s", password);
	for (int i = 0; i < numOfUsers; i++) // pretrazi cijelu strukturu
	{
		if (strncmp(us[i].username, username) == 0) // ako je username pronaden
		{
			if (strncmp(us[i].password, password) == 0) // ako je password pronaden
			{
				printf("Uspjesno ste se prijavili.\n");
				subMeni(us, numOfUsers); // udi u drugi menu
				return;
			}
		}
	}
	printf("Netocno korisnicko ime ili lozinka.\n"); // ako lozinka nije tocna ili ako ne postoji takav korisnik
	mainMenu(us); // povratak u mainMenu
}

void subMeni(USER* us, int numOfUsers)
{
	int choosing = 0;
	printf("\n------------------------------------------------------------");
	printf("\nKorisnicki izbornik:\n");
	printf("1 - Trazi korisnika\n");
	printf("2 - Ispisi korisnike poredane po broju pasa\n");
	printf("3 - Odjava i povratak u glavni izbornik\n");
	printf("Odabir: ");
	scanf("%d", &choosing);
	switch (choosing)
	{
	case 1:
		search(us, numOfUsers);
		break;
	case 2:
		sort(us, numOfUsers);
		break;
	case 3:
		mainMenu(us);
		break;
	default:
		printf("Krivi unos.\n");
		subMeni(us, numOfUsers);
		break;
	}
}

void search(USER* us, int numOfUsers)
{
	printf("\n------------------------------------------------------------\n");
	char username[50];
	printf("Unesite korisnicko ime za pretrazivanje: ");
	scanf("%s", username);
	for (int i = 0; i < numOfUsers; i++) // prodi cijelu strukturu
	{
		if (strncmp(us[i].username, username) == 0) // ako nades takav username
		{
			printUser(us, i); // pozovi fju za isprintat
			subMeni(us, numOfUsers); // i vrati se na meni
			return;
		}
	}
	printf("Korisnik s takvim korisnickim imenom ne postoji.\n");
	subMeni(us, numOfUsers);
}

void printUser(USER* us, int userIndex)
{
	printf("\nPronadeni korisnik: \n");
	printf("Ime: %s\n", us[userIndex].name);
	printf("Prezime: %s\n", us[userIndex].lastName);
	printf("Broj pasa: %d\n", us[userIndex].numDogs);
}

void sort(USER* us, int numOfUsers) // selection sort
{
	int temp;
	char Ctemp[50];
	for (int i = 0; i < numOfUsers - 1; i++)
	{
		for (int j = i + 1; j < numOfUsers; j++)
		{
			if (us[j].numDogs > us[i].numDogs)
			{
				temp = us[j].numDogs;
				us[j].numDogs = us[i].numDogs;
				us[i].numDogs = temp;

				strcpy(Ctemp, us[j].name);
				strcpy(us[j].name, us[i].name);
				strcpy(us[i].name, Ctemp);

				strcpy(Ctemp, us[j].lastName);
				strcpy(us[j].lastName, us[i].lastName);
				strcpy(us[i].lastName, Ctemp);

				strcpy(Ctemp, us[j].username);
				strcpy(us[j].username, us[i].username);
				strcpy(us[i].username, Ctemp);

				strcpy(Ctemp, us[j].password);
				strcpy(us[j].password, us[i].password);
				strcpy(us[i].password, Ctemp);
			}
		}
	}
	printAllUsers(us, numOfUsers);
}

void printAllUsers(USER* us, int numOfUsers)
{
	printf("\n------------------------------------------------------------\n");
	printf("Sortirani korisnici: \n");
	printf("RB | Kor.Ime | broj pasa\n");
	for (int i = 0; i < numOfUsers; i++)
	{
		printf("%d. %s\t%d \n", i + 1, us[i].username, us[i].numDogs);
	}
	subMeni(us, numOfUsers);
}

void memoryFree(USER* us)
{
	free(us);
}
