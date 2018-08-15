#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

void meni() {
	int n;
	printf("\nPritisnite: \n1 - Izracun preporucenog unosa kalorija \n2 - Pregled tablice nutritivnih vrijednosti hrane \n3 - Moj Odabir \n4 - Dodavanje hrane u Moj Odabir\n5 - Izlaz\n");
	scanf("%d", &n);
	switch (n)
	{
	case 1:
		unos();
		break;
	case 2:
		tablica();
		break;
	case 3:
		mojOdabir();
		break;
	case 4:
		mojUnos();
		break;
	case 5:
		exit(0);
		break;
	default:
		printf("Krivi unos!\n");
		meni();
		break;
	}
}

void unos(){
	struct osoba covjek;
	printf("Za izracun preporucenog unosa kalorija, popunite sljedece podatke: \n");
	printf("Spol: 1 - musko, 2 - zensko \n");
	scanf("%d", &covjek.spol);
	printf("Visina: (u cm)\n");
	scanf("%f", &covjek.visina);
	printf("Tezina: (u kg)\n");
	scanf("%f", &covjek.tezina);
	printf("Broj godina:\n");
	scanf("%d", &covjek.dob);
	printf("Vas dnevni unos kalorija iznos %.2f\n\n", izracun(covjek.spol, covjek.visina, covjek.tezina, covjek.dob));
	meni();

}

float izracun(int spol, float visina, float tezina, int dob){
	float rj;
	if (spol == 1)
	{
		rj = 1.55 * (88.362 + (12.397 * tezina) + (4.799 * visina) - (5.677 * dob));
	}
	else
	{
		rj = 1.55 * (447.593 + (9.247 * tezina) + (3.098 * visina) - (4.330 * dob));
	}

	return rj;
}

void tablica() {
	FILE *stream = fopen("tablica.txt", "r");
	if (stream == NULL)
	{
		printf("Ne moze se otvoriti tablica\n");
	}
	else
	{
		char hrana[100];
		printf("Tablica hranjivih vrijdnosti: \n");
		printf("Hrana\t\tKalorije Proteini Ugljikohidrati Masti \n");
		while (fgets(hrana, 100, stream) != NULL)
		{
			printf("%s", hrana);
		}
		fclose(stream);
	}
	meni();


}

void mojUnos(){
	struct mojodabir odabir1;
	FILE *stream = fopen("mojodabri.txt", "a");
	char ime[50];
	if (stream == NULL)
	{
		printf("Ne moze se otvoriti datoteka.\n");
	}
	else
	{
		printf("Unesi naziv hrane: \n");
		scanf("%s", ime);
		strcpy(odabir1.ime, ime);
		printf("Unesi kolicinu kalorija: \n");
		scanf("%f", &odabir1.kalorije);
		printf("Unesi kolicinu proteina: \n");
		scanf("%f", &odabir1.proteini);
		printf("Unesi kolicinu ugljikohidrata: \n");
		scanf("%f", &odabir1.ugljikohidrati);
		printf("Unesi kolicinu masti: \n");
		scanf("%f", &odabir1.masti);
		fprintf(stream, "%s %f %f %f %f\n", odabir1.ime, odabir1.kalorije, odabir1.proteini, odabir1.ugljikohidrati, odabir1.masti);
		printf("Uspjesno ste unijeli hranu u Moj Odabir.\n");
		fclose(stream);
	}
	meni();

}

void mojOdabir(){
	int i = 0;
	int izbor;
	struct mojodabir *odabir;
	odabir = malloc(BRMOJODABIR * sizeof(struct mojodabir));
	if (odabir == NULL)
	{
		printf("Ne moze se memorija zauzeti.\n");
		meni();
	}
	else
	{
		FILE* stream = fopen("mojodabri.txt", "r");
		if (stream == NULL)
		{
			printf("Nema dodane hrane u Moj Odabir.\n");
			meni();
		}
		else
		{
			while (fscanf(stream, "%s %f %f %f %f\n", odabir[i].ime, &odabir[i].kalorije, &odabir[i].proteini, &odabir[i].ugljikohidrati, &odabir[i].masti) != EOF)
			{
				i++;
			}

			fclose(stream);
			do
			{
				printf("Odaberite: \n1 - Pretrazivanje hrane \n2 - Ispis Mojega Odabira\n");
				scanf("%d", &izbor);
				if (izbor != 1 && izbor != 2)
				{
					printf("Netocan unos.");
				}
				else
				{
					break;
				}
			} while (1);
			if (izbor == 1)
			{
				trazenje(odabir, i);
			}
			else
			{
				sortiranjeIspis(odabir, i);
			}


			
		}
		meni();
	}

	
	

}

void sortiranjeIspis(struct mojodabir odabir[BRMOJODABIR], int n){
	char tempIme[50];
	float temp;
	for (int i = 0; i < n - 1; i++) // prolazi kroz cijelu strukturu
	{
		for (int j = i + 1; j < n; j++) // prolazi kroz cijelu struktur - 1
		{
			if (odabir[j].kalorije < odabir[i].kalorije)
			{
				temp = odabir[j].kalorije;
				odabir[j].kalorije = odabir[i].kalorije;
				odabir[i].kalorije = temp;

				temp = odabir[j].proteini;
				odabir[j].proteini = odabir[i].proteini;
				odabir[i].proteini = temp;

				temp = odabir[j].ugljikohidrati;
				odabir[j].ugljikohidrati = odabir[i].ugljikohidrati;
				odabir[i].ugljikohidrati = temp;

				temp = odabir[j].masti;
				odabir[j].masti = odabir[i].masti;
				odabir[i].masti = temp;

				strcpy(tempIme, odabir[j].ime);
				strcpy(odabir[j].ime, odabir[i].ime);
				strcpy(odabir[i].ime, tempIme);
			}
		}
	}
	// ispis
	printf("Tablica moje hrane sortirane po kalorijama: \n");
	printf("Hrana\tKalorije Proteini Ugljikohidrati Masti \n");
	for (int j = 0; j < n; j++)
	{
		printf("%s \t%.2f\t %.2f\t %.2f\t %.2f\n", odabir[j].ime, odabir[j].kalorije, odabir[j].proteini, odabir[j].ugljikohidrati, odabir[j].masti);
	}
}

void trazenje(struct mojodabir odabir[BRMOJODABIR], int n) {
	float kalorije;
	printf("Unesi najveci broj kalorija: ");
	scanf("%f", &kalorije);
	printf("Hrana koja ima manje od %f kalorija: \n", kalorije);
	for (int i = 0; i < n; i++)
	{
		if (odabir[i].kalorije <= kalorije)
		{
			printf("%s - %f kalorija\n", odabir[i].ime, odabir[i].kalorije);
		}
	}
}