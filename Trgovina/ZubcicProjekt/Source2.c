#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int brNam = 0;
float racun = 0.0f;

PROIZVOD* memorija()
{
	return malloc(100 * sizeof(PROIZVOD));
}

void ucitavanje(PROIZVOD* pr)
{
	FILE* stream = NULL;
	stream = fopen("proizvodi.bin", "rb");
	if (stream == NULL)
	{
		brNam = 0;
	}
	else
	{
		brNam = fread(pr, sizeof(PROIZVOD), 100, stream);
		fclose(stream);
	}
}

void meni(PROIZVOD* pr)
{
	int odabir = 0;
	printf("Odaberi: \n");
	printf("1. Naruci namirnicu \n");
	printf("2. Prodaja \n");
	printf("3. Izlaz  \n");
	scanf("%d", &odabir);
	switch (odabir)
	{
	case 1:
		dodaj(pr);
		break;
	case 2:
		meni2(pr);
		break;
	case 3:
		exit(0);
		break;
	default:
		printf("Krivi unos.\n");
		meni(pr);
		break;
	}
}

void dodaj(PROIZVOD* pr)
{
	FILE* stream = NULL;
	stream = fopen("proizvodi.bin", "wb");
	if (stream == NULL)
	{
		printf("Greska.");
	}
	else
	{
		printf("Unesi ime namirnice: ");
		scanf("%s", pr[brNam].ime);
		printf("Unesi kolicinu: ");
		scanf("%d", &pr[brNam].kolicina);
		printf("Unesi cijenu: ");
		scanf("%f", &pr[brNam].cijena);
		fwrite(pr, sizeof(PROIZVOD), brNam + 1, stream);
		fclose(stream);
		brNam++;
		printf("Namirnica je narucena.\n");
		ucitavanje(pr);
	}
	meni(pr);
}

void meni2(PROIZVOD* pr)
{
	int odabir = 0;
	printf("\nRacun: %.2f HRK\n", racun);
	printf("Odaberi: \n");
	printf("1. Lista namirnica \n");
	printf("2. Trazi namirnicu \n");
	printf("3. Povratak  \n");
	scanf("%d", &odabir);
	switch (odabir)
	{
	case 1:
		soritiranje(pr);
		lista(pr);
		break;
	case 2:
		trazi(pr);
		break;
	case 3:
		meni(pr);
		break;
	default:
		printf("Krivi unos.\n");
		meni(pr);
		break;
	}
}

void lista(PROIZVOD* pr)
{
	int odabir = 0;
	printf("Rb\tNamirnica\tKolicina\tCijena\n");
	for (int i = 0; i < brNam; i++)
	{
		printf("%d.\t%s\t\t%d\t\t%.2f\n", i + 1, pr[i].ime, pr[i].kolicina, pr[i].cijena);
	}

	printf("Unesite redni broj namirnice koju zelite kupiti (0 za odustani): ");
	scanf("%d", &odabir);
	if (odabir != 0)
	{
		if (pr[odabir - 1].kolicina > 0)
		{
			racun = racun + pr[odabir - 1].cijena;
			pr[odabir - 1].kolicina--;
			printf("\nProizvod kupljen\n");
		}
		else
		{
			printf("\nProizvod nije dostupan\n");
		}
	}
	meni2(pr);
}

void soritiranje(PROIZVOD* pr)
{
	int temp;
	float cijenaTemp;
	char imeTemp[50];
	for (int i = 0; i < brNam - 1; i++)
	{
		for (int j = i + 1; j < brNam; j++)
		{
			if (pr[j].cijena < pr[i].cijena)
			{
				temp = pr[j].kolicina;
				pr[j].kolicina = pr[i].kolicina;
				pr[i].kolicina = temp;

				cijenaTemp = pr[j].cijena;
				pr[j].cijena = pr[i].cijena;
				pr[i].cijena = cijenaTemp;


				strcpy(imeTemp, pr[j].ime);
				strcpy(pr[j].ime, pr[i].ime);
				strcpy(pr[i].ime, imeTemp);

			}
		}
	}
}

void trazi(PROIZVOD* pr)
{
	int odabir = 0;
	char tr[100];
	printf("Unesi ime proizvoda za traziti: ");
	scanf("%s", tr);
	for (int i = 0; i < brNam; i++)
	{
		if (strncmp(pr[i].ime, tr) == 0)
		{
			printf("Pronadeni proizvod: \n");
			printf("Ime: %s\n", pr[i].ime);
			printf("Cijena: %.2f\n", pr[i].cijena);
			printf("Kolicina: %d\n", pr[i].kolicina);
			printf("Kupiti (1 DA 0 NE): ");
			scanf("%d", &odabir);
			if (odabir == 1)
			{
				if (pr[i].kolicina > 0)
				{
					racun = racun + pr[i].cijena;
					pr[i].kolicina--;
					printf("\nProizvod kupljen\n");
				}
				else
				{
					printf("\nProizvod nije dostupan\n");
				}
			}
			meni2(pr);
		}
	}
	printf("Proizvod nije pronaden\n");
	meni2(pr);
}