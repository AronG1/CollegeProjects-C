#include <stdio.h>
#include "Header.h"

int brItema = 0; // varijabla koja prati broj itema
void ispisiIteme(ITEM *it)
{
	// pozivanje funkcije da sortira polje prije ispisa
	sortiranje(it);
	//ispis svih itema
	printf("Items:\n");
	for (int i = 0; i < brItema; i++)
	{
		// ispis imena itema
		printf("%d. \n - Ime: %s\n", i+1, (it + i)->name);
		// ispis slota itema
		if ((it + i)->slot == 1)
		{
			printf(" - Slot: Head\n");
		}
		else if((it + i)->slot == 2)
		{
			printf(" - Slot: Arms\n");
		}
		else if ((it + i)->slot == 3)
		{
			printf(" - Slot: Chest\n");
		}
		else if ((it + i)->slot == 4)
		{
			printf(" - Slot: Legs\n");
		}
		else
		{
			printf(" - Slot: Unknown\n");
		}
		// ispis rarity
		if ((it + i)->rarity == 1)
		{
			printf(" - Rarity: Common\n");
		}
		else if ((it + i)->rarity == 2)
		{
			printf(" - Rarity: Uncommon\n");
		}
		else if ((it + i)->rarity == 3)
		{
			printf(" - Rarity: Rare\n");
		}
		else if ((it + i)->rarity == 4)
		{
			printf(" - Rarity: Epic\n");
		}
		else if ((it + i)->rarity == 5)
		{
			printf(" - Rarity: Legendary\n");
		}
		else
		{
			printf(" - Rarity: Unknown\n");
		}
		// ispis type
		if ((it + i)->type == 1)
		{
			printf(" - Type: Leather\n");
		}
		else if ((it + i)->type == 2)
		{
			printf(" - Type: Plate\n");
		}
		else if ((it + i)->type == 3)
		{
			printf(" - Type: Mail\n");
		}
		else if ((it + i)->type == 4)
		{
			printf(" - Type: Cloth\n");
		}
		else
		{
			printf(" - Type: Unknown\n");
		}
	}
}
void addItem(ITEM *it)
{
	char temp[100]; // pomocna varijabla, potrebno za rad gets()
	printf("Unesi ime itema:(umjesto razmaka koristit: _ )\n");
	gets(temp, 101, stdin); // pokupi \n zadnji pa radi slj gets
	gets((it + brItema)->name, 101, stdin); // prima ime koje korisnik unese i stavlja u strukturu
	printf("Unesi slot itema: (1 za head, 2 za arms, 3 za chest, 4 za legs)\n");
	scanf("%d", &(it + brItema)->slot);
	printf("Unesi rarity itema: (1 za common, 2 za uncommon, 3 za rare, 4 za epic i 5 za legendary)\n");
	scanf("%d", &(it + brItema)->rarity);
	printf("Unesi type itema: (1 za leather, 2 za plate, 3 za mail i 4 za cloth)\n");
	scanf("%d", &(it + brItema)->type);
	FILE *stream = fopen("items.txt", "a"); // datoteka za dodavanje itema, otvaranje datoteke
	if (stream == NULL) // ako se datoteka ne moze otvoriti
	{
		printf("Item se ne moze dodati\n");
	}
	else
	{
		fprintf(stream, "%s %d %d %d\n", (it + brItema)->name, (it + brItema)->slot, (it + brItema)->rarity, (it + brItema)->type); // ispisuje item u datoteku
		fclose(stream); // zatvara datoteku
	}
	brItema++; // povecava varijabli vrijednost za jedan jer smo dodali jedan item
}
void searchItem(ITEM *it)
{
	int slot, rarity, type; // varijable koje ce unijeti korisnik koje ce se provjeravati jel postoje takvi itemi
	int find = 0; // varijabla pomocu koje se zna jel item pronaden 0 - nije 1 - je
	// unos podataka
	printf("Unesi slot itema: (1 za head, 2 za arms, 3 za chest, 4 za legs)\n");
	scanf("%d", &slot);
	printf("Unesi rarity itema: (1 za common, 2 za uncommon, 3 za rare, 4 za epic i 5 za legendary)\n");
	scanf("%d", &rarity);
	printf("Unesi type itema: (1 za leather, 2 za plate, 3 za mail i 4 za cloth)\n");
	scanf("%d", &type);
	// ispis itema koji se podudaraju
	printf("\nPronadeni itemi: \n");
	for (int i = 0; i < brItema; i++)
	{
		if ((it + i)->slot == slot) // ako je isti slot
		{
			if ((it + i)->rarity == rarity) // ako je isti rarity
			{
				if ((it + i)->type == type) // ako je isti type
				{
					find = 1; // postavi na 1, znaci da je pronaden item
					printf(" - %s\n", (it + i)->name); // ispisi taj item
				}
			}
		}
	}
	if (find == 0) // ako nije pronaden niti jedan item ispisi poruku
	{
		printf("Nema itema tih osobina.\n");
	}
}
void ucitajIteme(ITEM *it)
{
	FILE *stream = fopen("items.txt", "r"); // datoteka za citanje, otvara datoteku
	if (stream == NULL) // ako se datoteka ne moze otvoriti ili ako ne postoji jos
	{
		printf("Nema itema\n"); // ispisi poruku
		addItem(it); // odmah odi na unos itema jer ih nema
	}
	else
	{
		// sve dok ne dode do kraja datoteke citaj red po red iz datoteke i spremaj u strukturu
		while (fscanf(stream, "%s %d %d %d\n", (it + brItema)->name, &(it + brItema)->slot, &(it + brItema)->rarity, &(it + brItema)->type) != EOF)
		{
			brItema++; // svaki put kad procitas red(jedan item) dodaj 1 varijabli brItema
		}
		fclose(stream); // zatvara datoteku
	}
}
void sortiranje(ITEM *it)
{
	int temp; // pomocna varijabla za zamjenu
	char imeTemp[100]; //pomocna varijabla za zamjenu imena
	for (int i = 0; i < brItema - 1; i++)
	{
		for (int j = i + 1; j < brItema; j++)
		{
			if ((it + j)->rarity < (it + i)->rarity) // ako je manji zamjeni
			{
				// zamjena rarity
				temp = (it + j)->rarity;
				(it + j)->rarity = (it + i)->rarity;
				(it + i)->rarity = temp;
				// zamjena slota
				temp = (it + j)->slot;
				(it + j)->slot = (it + i)->slot;
				(it + i)->slot = temp;
				// zamjena type
				temp = (it + j)->type;
				(it + j)->type = (it + i)->type;
				(it + i)->type = temp;
				// zamjena imena
				strcpy(imeTemp, (it + j)->name);
				strcpy((it + j)->name, (it + i)->name);
				strcpy((it + i)->name, imeTemp);
			}
		}
	}
	return;
}