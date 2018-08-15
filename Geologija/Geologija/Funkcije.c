#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

MINERAL* memorija()
{
	return (MINERAL*)calloc(100, sizeof(MINERAL));
}

int ucitajMinerale(MINERAL* mi)
{
	FILE* stream = NULL;
	stream = fopen("minerali.bin", "rb");
	if (stream == NULL)
	{
		printf("Nema unesenih minerala\n");
		return 0;
	}
	else
	{
		int brMin = 0;
		brMin = fread(mi, sizeof(MINERAL), 100, stream);
		fclose(stream);
		return brMin;
	}
}

int  dodaj(MINERAL *mi, int brojMin)
{
	FILE *stream = NULL;
	stream = fopen("minerali.bin", "wb");
	if (stream == NULL)
	{
		printf("Greska s datotekom!\n");
	}
	else
	{
		printf("Unesi ime minerala: ");
		scanf("%s", mi[brojMin].ime);
		printf("Unesi tip minerala (1 olivin, 2 granatin, 3 cirkon): ");
		scanf("%d", &mi[brojMin].tip);
		printf("Unesi boju minerala (1 zelena, 2 plava, 3 crvena, 4 roza): ");
		scanf("%d", &mi[brojMin].boja);
		printf("Unesi strukuturu minerala (1 vlaknasto, 2 grudasto): ");
		scanf("%d", &mi[brojMin].struktura);
		printf("Unesi oblik minerala (1 kockasto, 2 valjkasto, 3 okruglasto, 4 trokutasto): ");
		scanf("%d", &mi[brojMin].oblik);
		fwrite(mi, sizeof(MINERAL), brojMin + 1, stream);
		fclose(stream);
		printf("Vas mineral je uspjesno spremljen!\n");
		return brojMin + 1;
	}
}

void ispis(MINERAL *mi)
{
	FILE *stream = NULL;
	stream = fopen("minerali.bin", "rb");
	if (stream == NULL)
	{
		printf("Nema unesenih minerala jos!\n");
	}
	else
	{
		int brMin = 0;
		brMin = fread(mi, sizeof(MINERAL), 100, stream);
		sortiranje(mi, brMin);
		printf("Mineral\t   Tip\t\tBoja\tStruktura\tOblik\n");
		for (int i = 0; i < brMin; i++)
		{
			ispisMinerala(mi, i);
		}
		fclose(stream);
	}
}

void ispisMinerala(MINERAL *mi, int i)
{
	// ime
	printf("%-12s", mi[i].ime);
	// tip
	if (mi[i].tip == 1)
	{
		printf("olivin\t");
	}
	else if (mi[i].tip == 2)
	{
		printf("grantin\t");
	}
	else if (mi[i].tip == 3)
	{
		printf("cirkon\t");
	}
	else
	{
		printf("unknown\t");
	}
	// boja
	if (mi[i].boja == 1)
	{
		printf("zelena\t");
	}
	else if (mi[i].boja == 2)
	{
		printf("plava\t");
	}
	else if (mi[i].boja == 3)
	{
		printf("crvena\t");
	}
	else if (mi[i].boja == 4)
	{
		printf("roza\t");
	}
	else
	{
		printf("unknown\t");
	}
	// struktura
	if (mi[i].struktura == 1)
	{
		printf("vlaknasta\t");
	}
	else if (mi[i].struktura == 2)
	{
		printf("grudasta\t");
	}
	else
	{
		printf("unknown\t");
	}
	// oblik
	if (mi[i].oblik == 1)
	{
		printf("kockasti\t");
	}
	else if (mi[i].oblik == 2)
	{
		printf("valjkasti\t");
	}
	else if (mi[i].oblik == 3)
	{
		printf("okruglasti\t");
	}
	else if (mi[i].oblik == 4)
	{
		printf("trokutasti\t");
	}
	else
	{
		printf("unknown\t");
	}
	printf("\n");
}

void sortiranje(MINERAL *mi, int brojMin)
{
	int temp;
	char imeTemp[50];
	for (int i = 0; i < brojMin - 1; i++)
	{
		for (int j = i + 1; j < brojMin; j++)
		{
			if (mi[j].tip < mi[i].tip)
			{
				temp = mi[j].tip;
				mi[j].tip = mi[i].tip;
				mi[i].tip = temp;

				temp = mi[j].boja;
				mi[j].boja = mi[i].boja;
				mi[i].boja = temp;

				temp = mi[j].struktura;
				mi[j].struktura = mi[i].struktura;
				mi[i].struktura = temp;

				temp = mi[j].oblik;
				mi[j].oblik = mi[i].oblik;
				mi[i].oblik = temp;

				strcpy(imeTemp, mi[j].ime);
				strcpy(mi[j].ime, mi[i].ime);
				strcpy(mi[i].ime, imeTemp);
			}
			else if (mi[j].tip == mi[i].tip)
			{
				if (mi[j].boja < mi[i].boja)
				{
					temp = mi[j].tip;
					mi[j].tip = mi[i].tip;
					mi[i].tip = temp;

					temp = mi[j].boja;
					mi[j].boja = mi[i].boja;
					mi[i].boja = temp;

					temp = mi[j].struktura;
					mi[j].struktura = mi[i].struktura;
					mi[i].struktura = temp;

					temp = mi[j].oblik;
					mi[j].oblik = mi[i].oblik;
					mi[i].oblik = temp;

					strcpy(imeTemp, mi[j].ime);
					strcpy(mi[j].ime, mi[i].ime);
					strcpy(mi[i].ime, imeTemp);
				}
			}
		}
	}

}

int trazenje(MINERAL *mi, int brojMin)
{
	char pretrazi[50];
	printf("Unesite ime minerala koji zelite pretraziti: ");
	scanf("%s", pretrazi);
	for (int i = 0; i < brojMin; i++)
	{
		if (strncmp(mi[i].ime, pretrazi) == 0)
		{
			printf("Pronadeni mineral: \n");
			printf("Mineral\t   Tip\t\tBoja\tStruktura\tOblik\n");
			ispisMinerala(mi, i);
			return 1;
		}
	}
	return 0;
}