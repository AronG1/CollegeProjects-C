#include <stdio.h>
#include <stdlib.h>
#include "Functions.h"

void mainMenu()
{
	// ispis i odabir u izborniku
	int choose;
	printf("\nMain menu: \n1. Popis skladista\n2. Dodavanje skladista\n3. Brisanje skladista\n4. Izlaz iz programa\n");
	scanf("%d", &choose);
	switch (choose)
	{
	case 1:
		storageList();
		break;
	case 2:
		addStorage();
		break;
	case 3:
		deleteStorage();
		break;
	case 4:
		exit(0);
		break;
	default:
		printf("Netoncan unos!\n");
		mainMenu();
		break;
	}
}
int readNumStorage()
{
	int numStorages = 0; // varijabla koja sadrzi broj skladista, izcitava se iz datoteke
	FILE *stream = NULL;
	stream = fopen("Broj skladista.txt", "r"); // datoteka koja sadrzi broj skladista, otvori za citanje
	if (stream == NULL) // ako ne postoji datoteka
	{	
		stream = fopen("Broj skladista.txt", "w"); // otvori ju za upis
		if (stream == NULL) // ako se desi greska
		{
			printf("Greska s datotekom za broj skladista\n");
		}
		else 
		{
			fprintf(stream, "-1"); // otvori i upis -1, nema skladista jos
		}
		fclose(stream); // zatvori
		return -1; // vrati -1
	}
	else
	{
		fscanf(stream, "%d", &numStorages); // procitaj broj iz datoteke
		return numStorages; // vrati taj broj 
		fclose(stream);
	}
}
void storageList()
{
	int numOfStorages = 0; // broj skladista
	int choose = 0; // odabir korisnika
	int sortChoose = 0; // odabir korisnika za sortiranje
	int numOfItems = 0; // broj itema u skladistu
	numOfStorages = readNumStorage(); // pozivanje fje za broj skladista
	if (numOfStorages == -1) // ako je -1 znaci nema skladista
	{
		printf("Nema jos unesenog skladista\n");
		mainMenu();
		return;
	}
	else
	{
		// pitaj korisnika da odabere skladiste za ispis
		do
		{
			printf("Odaberi skladiste koje zelis ispisat (od 0 do %d): ", numOfStorages - 1);
			scanf("%d", &choose);
		} while (choose < 0 || choose > numOfStorages - 1);

		// varijable za spajanje imena datoteke
		char name[100] = "skladiste";
		char storageNum[50];
		char temp[100];
		// spajanje tih varijabli u jednu
		sprintf(storageNum, "%d", choose);
		strcat(name, storageNum);
		strcat(name, ".txt");
		// daoteka za citanje
		FILE *stream = NULL;
		stream = fopen(name, "r"); // otvori za citanje
		if (stream == NULL)
		{
			printf("Nema takvog skladista\n");
			mainMenu();
			return;
		}
		else
		{
			// ispis skladiste
			printf("Popis skladista broj %d: \nNaziv\tKolicina\n", choose);
			while (fgets(temp, sizeof temp, stream) != NULL) // dohvati svaki red u datoteci do kraja datoteke
			{
				fputs(temp, stdout); // ispisi svaki taj red na konzolu
				numOfItems++; // povecaj broj itema
			}
			fclose(stream);
			// biranje za sortiranje ili ne
			printf("\nUnesite 1 za sortiranje, 0 za nastavak na izbornik: ");
			scanf("%d", &sortChoose);
			if (sortChoose == 1)
			{
				sort( numOfItems, name); // pozovi fju za sortiranje
			}
			fclose(stream);
		}

	}
	mainMenu(); // povratatk na meni


}
void addStorage()
{

	char itemName[100];
	int itemAmount = 0;
	int choose = 0;
	int numOfStorages = 0;
	numOfStorages = readNumStorage(); // pozivanje fje za broj skladista
	if (numOfStorages == -1) // ako je -1 znaci nema skladista jos, postavi ovo kao prvo (od 0 se krece)
	{
		numOfStorages = 0;
	}
	// varijable za ime
	char name[100] = "skladiste";
	char storageNum[50];
	// spajanje varijabli u ime
	sprintf(storageNum, "%d", numOfStorages);
	strcat(name, storageNum);
	strcat(name, ".txt");
	FILE *stream = NULL;
	stream = fopen(name, "w"); // otvaranje za pisanje
	if (stream == NULL)
	{
		printf("Greska\n");
	}
	else
	{
		// unos itema u skladiste
		do
		{
			printf("Unesite ime predmeta \n");
			scanf("%s", itemName);
			printf("Unesite kolicinu predmeta \n");
			scanf("%d", &itemAmount);
			fprintf(stream, "%s %d\n", itemName, itemAmount);
			printf("Za dodavanje novog itema odabrati 1, za spremanje skladista 0\n");
			scanf("%d", &choose);
		} while (choose != 0);
		fclose(stream);
		// upisi u datoteku br skladista jedno vise skladiste
		stream = fopen("Broj skladista.txt", "w");
		if (stream == NULL) // greska
		{
			printf("Broj skladista se ne moze spremiti.\n");
		}
		else
		{
			// upisi sadasnji broj + 1
			fprintf(stream, "%d", numOfStorages + 1);
			fclose(stream);
		}

	}
	mainMenu(); // meni
}
void deleteStorage()
{
	int numOfStorages = 0;
	int choose;
	numOfStorages = readNumStorage(); // pozivanje fje za broj skladista
	if (numOfStorages == -1) // ako je -1 znaci nema skladista
	{
		printf("Nema jos unesenog skladista\n");
		mainMenu();
		return;
	}
	do
	{
		// odabir korisnika koje zeli izbrisati
		printf("Odaberi skladiste koje zelis izbrisati (od 0 do %d): ", numOfStorages - 1);
		scanf("%d", &choose);
	} while (choose < 0 || choose > numOfStorages - 1);

	// varijable za ime
	char name[100] = "skladiste";
	char storageNum[50];
	char temp[100];
	// spajanje tih varijabli u jednu
	sprintf(storageNum, "%d", choose);
	strcat(name, storageNum);
	strcat(name, ".txt");
	
	int status; // status - 0 uspjesno obrisano
	status = remove(name); // poziv fje za brisanje datoteke
	if (status == 0)
	{
		printf("%s skladiste uspjesno obrisano\n", name);
	}
	else
	{
		printf("%s skladiste se nije moglo obrisati.\n", name);
	}
	mainMenu(); // meni

}
void sort(int numOfItems, char name[100])
{
	// struktura it
	struct item *it;
	it = malloc(numOfItems * sizeof(struct item)); // alokacija memorije za polje strukture
	char nameTemp[50]; // temprorary varijabla za swap name kod sort
	int amount; // temprorary varijabla za swap amount kod sort
	int n = 0; // brojac
	FILE *stream = fopen(name, "r"); // otvori za citanje
	if (stream == NULL)
	{
		printf("Greska");
	}
	else
	{
		while (fscanf(stream, "%s %d\n", it[n].name, &it[n].amount) != EOF) // dok ne dodes do kraja filea citaj podatke i spremaj ih u strukturu
		{
			n++; // dodaj brojac
		}
		// sortiranje (selection sort)
		for (int i = 0; i < numOfItems - 1; i++)
		{
			for (int j = i + 1; j < numOfItems; j++)
			{
				if (it[j].amount < it[i].amount) // ako je veci
				{
					// swap
					amount = it[j].amount;
					it[j].amount = it[i].amount;
					it[i].amount = amount;
					strcpy(nameTemp, it[j].name);
					strcpy(it[j].name, it[i].name);
					strcpy(it[i].name, nameTemp);
				}
			}
		}
		// ispis cijele sortirane strukture
		for (int i = 0; i < n; i++)
		{
			printf("%d. %s %d\n", i + 1, it[i].name, it[i].amount);
		}

	}
	
}