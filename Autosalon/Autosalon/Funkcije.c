#include <stdio.h>
#include "Header.h"

// funkcija za prikaz main menu-a
void mainMenu(struct Automobil automobil[100], int brAuta)
{
	int odabir = 0;
	printf("\nOdaberite: \n 1.Pregled dostupnih automobila \n 2.Kupnja automobila \n 3.Narucit novo vozilo \n 4.Pretrazivanje automobila do odredene cijene \n 5.Izlaz iz programa\n");
	scanf("%d", &odabir);
	if (odabir == 1) // ovisno o odabiru korisnika program poziva funkcije
	{
		dostupni(automobil, brAuta);
	}
	else if(odabir == 2)
	{
		kupnja(automobil, brAuta);
	}
	else if (odabir == 3)
	{
		narudzba(automobil, brAuta);
	}
	else if (odabir == 4)
	{
		pretrazi(automobil, brAuta);
	}
	else if (odabir == 5)
	{
		exit(0);
	}
	else
	{
		printf("Netocan unos!\n");
		mainMenu(automobil, brAuta);
	}

}
// funkcija za ucitavanje prije unesenih automobila
void ucitajBazu(struct Automobil automobil[100], int brAuta)
{
	FILE *baza = fopen("Automobili.txt", "r");
	if (baza == NULL) // baza jos ne postoji
	{
		printf("U bazi se ne nalazi niti jedan automobil, unesite jedan:\n\n");
		narudzba(automobil, brAuta);
	}
	else // baza postoji -- ucitavaj sve do kraja datoteke i spremi podatke u strukturu
	{
		while (fscanf(baza, "%s %s %d %f %f", automobil[brAuta].marka, automobil[brAuta].model, &automobil[brAuta].godiste, &automobil[brAuta].kilometri, &automobil[brAuta].cijena) != EOF)
		{
			brAuta++; // dodaj broj auta
		}
		fclose(baza); // zatvori datoteku
	}
	mainMenu(automobil, brAuta); // vrati se u main menu
}
// funkcija za ispis na ekran dostupnih automobila sortiranih po cijeni
void dostupni(struct Automobil automobil[100], int brAuta)
{
	if (brAuta == 0) // ako nema automobila
	{
		printf("Trenutno nema dostupnih automobila.\n\n");
	}
	else
	{
		sortiranje(automobil, brAuta); // pozivanje funkcije za sortiranje
		printf("Dostupni automobili sortirani po cijeni: \n\n");
		printf("Marka\tModel\tGodiste\tBroj km\tCijena(EUR): \n");
		for (int i = 0; i < brAuta; i++) // ispis svih automobila iz strukture
		{
			printf("%s\t%s\t%d\t%.2f\t%.2f\n", automobil[i].marka, automobil[i].model, automobil[i].godiste, automobil[i].kilometri, automobil[i].cijena);
		}
	}
	mainMenu(automobil, brAuta); // vracanje u main menu
}
// funkcija za dodavanje novih automobila u bazu
void narudzba(struct Automobil automobil[100], int brAuta)
{
	// unos podataka od strane korisnika
	printf("Unesite marku, model, godiste, broj kilometara i cijenu u eurima za automobil koji zelite naruciti.\n");
	scanf("%s %s %d %f %f", automobil[brAuta].marka, automobil[brAuta].model, &automobil[brAuta].godiste, &automobil[brAuta].kilometri, &automobil[brAuta].cijena);
	
	FILE* baza = fopen("Automobili.txt", "a");
	if (baza == NULL) // ako je greska
	{
		printf("Pogreska s bazom!\n");
	}
	else
	{
		// unos podataka koje je korisnik unio u strukturu
		fprintf(baza, "%s %s %d %f %f\n", automobil[brAuta].marka, automobil[brAuta].model, automobil[brAuta].godiste, automobil[brAuta].kilometri, automobil[brAuta].cijena);
		brAuta++; // povecaj broj automobila za jedan
		fclose(baza); //zatvori datoteku
		printf("Vasa narudzba je uspjesno narucena.\n\n");
	}
	mainMenu(automobil, brAuta); // vracanje u main menu


}
// funkcija za brisanje automobila iz strukture
void kupnja(struct Automobil automobil[100], int brAuta)
{
	if (brAuta <= 0) // ako nema automobila nema se sto obrisati
	{
		printf("Nema automobila u ponudi.\n\n");
	}
	else
	{
		printf("Automobili na prodaju: \n\n");
		printf("Marka\tModel\tGodiste\tBroj km\tCijena(EUR): \n");
		for (int i = 0; i < brAuta; i++) // ispisat sve automobile u ponudi
		{
			printf("%d. %s\t%s\t%d\t%.2f\t%.2f\n", i+1, automobil[i].marka, automobil[i].model, automobil[i].godiste, automobil[i].kilometri, automobil[i].cijena);
		}
		int odabir; // korisnik bira automobil koji zeli "kupiti" i on se brise iz strukture
		printf("Odaberite redni broj automobila koji zelite kupit. 0 za ponistit.\n\n");
		scanf("%d", &odabir);
		if (odabir == 0) // ako je odabir 0 ponisti kupnju
		{
			mainMenu(automobil, brAuta);
		}
		if (odabir < 0 || odabir > brAuta) // krivi unos
		{
			printf("Pogresan odabir. Pokusajte ponovo!\n");
			kupnja(automobil, brAuta);
		}
		else
		{
			for (int i = odabir; i <= brAuta; i++) // prodi kroz sve automobile u strukturi nakon kupljenog auta te ih pomakni za jedno mjesto da se obrise zadnje mjesto
			{
				if (i == brAuta) // kad dode do zadnjeg automobila u strukturi samo ga ponisti
				{
					automobil[i - 1].cijena = 0;
					automobil[i - 1].kilometri = 0;
					automobil[i - 1].godiste = 0;
					strcpy(automobil[i - 1].marka, "");
					strcpy(automobil[i - 1].model, "");
					printf("Uspjesno ste kupili automobil.\n");
					updateBazu(automobil, brAuta-1);
				}
				else // svaki automobil u strukturi pomakni za jedno mjesto
				{
					automobil[i - 1].cijena = automobil[i].cijena;
					automobil[i - 1].kilometri = automobil[i].kilometri;
					automobil[i - 1].godiste = automobil[i].godiste;
					strcpy(automobil[i - 1].marka, automobil[i].marka);
					strcpy(automobil[i - 1].model, automobil[i].model);
				}
			}
			
		}

	}
}
// funkcija za update baze podataka nakon brisanja automobila
void updateBazu(struct Automobil automobil[100], int brAuta)
{
	FILE* baza = fopen("Automobili.txt", "w");
	if (baza == NULL) // greska
	{
		printf("Greska s bazom!\n");
	}
	else
	{
		for (int i = 0; i < brAuta; i++) // ponovo prepisi sve automobile iz struktre u bazu u datoteku
		{
			fprintf(baza, "%s %s %d %f %f\n", automobil[i].marka, automobil[i].model, automobil[i].godiste, automobil[i].kilometri, automobil[i].cijena);
		}
		fclose(baza); // zatvori datoteku
	}
	mainMenu(automobil, brAuta); // povratak u main menu

}
// funkcija za sortiranje
void sortiranje(struct Automobil automobil[100], int brAuta)
{
	int temp; // temp varijabla
	char tempC[50]; // temp varijabla tipa char
	for (int i = 0; i < brAuta - 1; i++) // selection sort - nacin sortiranja
	{
		for (int j = i + 1; j < brAuta; j++)// prodi kroz cijelu strukturu
		{
			if (automobil[j].cijena > automobil[i].cijena) // usporedivanje cijena
			{
				// zamjena mjesta vrijednosti u strukturi pomocu pomocne varijable
				temp = automobil[j].cijena;
				automobil[j].cijena = automobil[i].cijena;
				automobil[i].cijena = temp;
				// za godiste...
				temp = automobil[j].godiste;
				automobil[j].godiste = automobil[i].godiste;
				automobil[i].godiste = temp;
				// kilometre...
				temp = automobil[j].kilometri;
				automobil[j].kilometri = automobil[i].kilometri;
				automobil[i].kilometri = temp;
				// itd...
				strcpy(tempC, automobil[j].marka);
				strcpy(automobil[j].marka, automobil[i].marka);
				strcpy(automobil[i].marka, tempC);

				strcpy(tempC, automobil[j].model);
				strcpy(automobil[j].model, automobil[i].model);
				strcpy(automobil[i].model, tempC);
			}

		}
	}

}
// funkcija koja trazi sve automobile koji imaju cijenu manju od trazene
void pretrazi(struct Automobil automobil[100], int brAuta)
{
	float unos;
	int bol = 0; // bool varijabla, TRUE or FALSE, al na int nacin
	// unos do koje cijene
	printf("Unesi najvisu cijenu u eurima: \n");
	scanf("%f", &unos);
	printf("Automobili u cijenovnom ranku su: \n\n");
	printf("Marka\tModel\tGodiste\tBroj km\tCijena(EUR): \n");
	for (int i = 0; i < brAuta; i++) // prolazi kroz strukturu
	{
		if (automobil[i].cijena <= unos) // provjera jel iznos manji ili jednak unesenom
		{
			bol = 1; // ako se pronade automobil unutar cijene postvi na 1
			printf("%s\t%s\t%d\t%.2f\t%.2f\n", automobil[i].marka, automobil[i].model, automobil[i].godiste, automobil[i].kilometri, automobil[i].cijena); // ako je ispis automobil
		}
	}
	if (bol == 0) // ako se ne nade niti jedan automobil ispisi da nema
	{
		printf("Nema automobila unutar trazene cijene.\n\n");
	}
	mainMenu(automobil, brAuta); // vracanje u main menu
}