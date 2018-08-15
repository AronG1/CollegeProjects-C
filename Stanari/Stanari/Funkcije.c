#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int brStanara = 0; // prati broj stanara
STANAR *alokacija(int n) // samo alocira memoriju i salje nazad alokaciju
{
	return (STANAR*)calloc(n, sizeof(STANAR));
}
void Izbornik(STANAR *osoba, int brStanovaPoKatu, int brKatova) // ispisuje izbornik
{
	int izbor = 0; // unosi korisnik
	printf("\nOdaberite:\n1 za ispis stanara\n2 za upis novog stanra\n3 za provjeru stana\n4 za izlaz iz programa\n");
	scanf("%d", &izbor);
	switch (izbor) // s obzirom na unos korisnika pozovi funkciju
	{
	case 1:
		ispisStanara(osoba, brStanovaPoKatu, brKatova);
		break;
	case 2:
		upisStanara(osoba, brStanovaPoKatu, brKatova);
		break;
	case 3:
		trazenje(osoba, brStanovaPoKatu, brKatova);
		break;
	case 4:
		exit(0);
		break;
	default:
		printf("Neispravan odabir.\n");
		break;
	}
}
void upisStanara(STANAR *osoba, int brStanovaPoKatu, int brKatova) // upisuje stanara u strukturu
{
	int kat, stan;
	int zauzeto = 0; // 0 slobodno 1 zauzeto
	// unos
	printf("Unesi kat zgrade (max. %d): \n", brKatova);
	scanf("%d", &kat);
	if (kat > brKatova || kat < 1) // provjera unosa
	{
		printf("Nema toliko katova u zgradi.\n");
		upisStanara(osoba, brStanovaPoKatu, brKatova); // ponovo unesi
		return;
	}
	// unos stana
	printf("Unesi broj stana na %d katu (max. %d): \n", kat, brStanovaPoKatu);
	scanf("%d", &stan);
	if (stan > brStanovaPoKatu || stan < 1) // provjera unosa
	{
		printf("Nema toliko stanova na katu.\n");
		upisStanara(osoba, brStanovaPoKatu, brKatova); // ponovi unos
		return;
	}
	// provjera jel stan slobodan
	for (int i = 0; i < brStanara; i++)
	{
		if ((osoba + i)->kat == kat)
		{
			if ((osoba + i)->stan == stan)
			{
				zauzeto = 1; // zauzet je
				printf("Zao nam je ali stan je vec izdan.\n");
				Izbornik(osoba, brStanovaPoKatu, brKatova); // vraca na izbornik
				return;
			}
		}
	}
	if (zauzeto == 0) // ako nije zauzet
	{
		// unos ostalih podataka
		printf("Unesi ime stanara: \n");
		scanf("%s", (osoba + brStanara)->ime);
		printf("Unesi prezime stanara: \n");
		scanf("%s", (osoba + brStanara)->prezime);
		printf("Unesi broj mobitela stanara: \n");
		scanf("%ld", &(osoba + brStanara)->mobitel);
		// unos vec unesenih podataka
		(osoba + brStanara)->kat = kat; 
		(osoba + brStanara)->stan = stan;
		if (upisUDatoteku(osoba, brStanovaPoKatu, brKatova) == 1) // upisiDatoteku fja vraca 0 ili 1 ovisno jel uspjesno zapisano u datoteku
		{
			// ako je uspjesno
			printf("Gosp. %s uspjesno ste zakupili stan broj %d, na %d. katu\n", (osoba + brStanara)->prezime, (osoba + brStanara)->stan, (osoba + brStanara)->kat);
			brStanara++; // zato sto je uspjesno povecaj broj stanara
			Izbornik(osoba, brStanovaPoKatu, brKatova);// vraca na izbornik
		}
		else
		{
			// nije uspjesno
			printf("Zao nam je ne mozemo vam izdati trazeni stan\n");
			Izbornik(osoba, brStanovaPoKatu, brKatova);// vraca na izbornik
		}

	}

}
int upisUDatoteku(STANAR *osoba, int brStanovaPoKatu, int brKatova)// upisuje u datoteku, vraca 1 ako je uspjesno 0 ako nije
{
	FILE* datoteka = NULL; // datoteka
	char ime[100] = "zgrada"; // osnovno ime datoteke
	char brStan[20]; // broj stana
	char brKat[20]; // broj katova
	sprintf(brStan, "%d", brStanovaPoKatu);  // pretvori iz int u string
	sprintf(brKat, "%d", brKatova);  // pretvori iz int u string
	strcat(ime, brStan); // na osnovno ime dodaj br stanova
	strcat(ime, brKat); // na to sve jos dodaj broj stanova po katu
	strcat(ime, ".txt"); // i za kraj jos nadodaj ekstenziju
	datoteka = fopen(ime, "a"); // otvori datoteku od sklepanog imena
	if (datoteka == NULL) // greska
	{
		printf("Datoteka se ne moze otvoriti.\n");
		return 0; // vrati 0 neuspjesno
	}
	else
	{
		// ispis u datoteku
		fprintf(datoteka, "%s %s kat %d stan %d mob %ld\n", (osoba + brStanara)->ime, (osoba + brStanara)->prezime, (osoba + brStanara)->kat, (osoba + brStanara)->stan, (osoba + brStanara)->mobitel);
		return 1; // vrati 1 uspjesno
	}
}
void citanjeDatoteke(STANAR *osoba, int brStanovaPoKatu, int brKatova) // na pocetku ucitaj stanare u zgradi ako postoji
{
	FILE* datoteka = NULL; // datoteka
	// varijable za sastavljanje imena datoteke
	char ime[100] = "zgrada";
	char brStan[20];
	char brKat[20];
	// temp varijable za iscitavanje
	char katTemp[20];
	char stanTemp[20];
	char mobTemp[20];
	sprintf(brStan, "%d", brStanovaPoKatu); // int u char
	sprintf(brKat, "%d", brKatova); // int u char
	strcat(ime, brStan); // nadodaj na zgrada
	strcat(ime, brKat); // nadodaj na zgrada + brstanova
	strcat(ime, ".txt"); // nadodaj ekstenziju na zgrada + brstanova + brstanvapokatu
	datoteka = fopen(ime, "r"); // otvori datoteku
	if (datoteka == NULL)
	{
		printf("Nema stanara u zgradi jos.\n");
	}
	else
	{
		// sve dok ne dodes do kraja filea citaj sve
		while (fscanf(datoteka, "%s %s %s %d %s %d %s %ld\n", (osoba + brStanara)->ime, (osoba + brStanara)->prezime, katTemp, &(osoba + brStanara)->kat, stanTemp, &(osoba + brStanara)->stan, mobTemp, &(osoba + brStanara)->mobitel) != EOF)
		{
			brStanara++; // za svaki ucitani red dodaj 1 stanar
		}
	}

}
void ispisStanara(STANAR *osoba, int brStanovaPoKatu, int brKatova) // ispisuje stanare i zove fju za sortiranje
{	
	sortiranje(osoba); // zove fju za sortiranje
	// ispis
	printf("Stanari: \n");
	for (int i = 0; i < brStanara; i++)
	{
		printf("%d. %d - %d %s %s, mob: %ld \n", i + 1, (osoba + i)->kat, (osoba + i)->stan, (osoba + i)->ime, (osoba + i)->prezime, (osoba + i)->mobitel);
	}
	Izbornik(osoba, brStanovaPoKatu, brKatova); // vracanje na izbornik

}
void sortiranje(STANAR *osoba) // fja za sortiranje, selection sort
{
	// pomocne varijable
	char ime[50];
	char prezime[50];
	int temp;
	long int tempMob;
	// prodi kroz cijelu  strukturu i usporeduj
	for (int i = 0; i < brStanara - 1; i++)
	{
		for (int j = i + 1; j < brStanara; j++)
		{
			if((osoba + j)->kat < (osoba + i)->kat) // usporedi kat
			{
				// zamjeni mjesta
				strcpy(ime, (osoba + j)->ime);
				strcpy((osoba + j)->ime, (osoba + i)->ime);
				strcpy((osoba + i)->ime, ime);

				strcpy(prezime, (osoba + j)->prezime);
				strcpy((osoba + j)->prezime, (osoba + i)->prezime);
				strcpy((osoba + i)->prezime, prezime);

				temp = (osoba + j)->kat;
				(osoba + j)->kat = (osoba + i)->kat;
				(osoba + i)->kat = temp;

				temp = (osoba + j)->stan;
				(osoba + j)->stan = (osoba + i)->stan;
				(osoba + i)->stan = temp;

				tempMob = (osoba + j)->mobitel;
				(osoba + j)->mobitel = (osoba + i)->mobitel;
				(osoba + i)->mobitel = tempMob;

			}
			else if (((osoba + j)->kat) == ((osoba + i)->stan)) // ako je kat isti 
			{
				if (((osoba + j)->stan) < ((osoba + i)->stan)) // usporedi stan
				{
					// zamjeni mjesta
					strcpy(ime, (osoba + j)->ime);
					strcpy((osoba + j)->ime, (osoba + i)->ime);
					strcpy((osoba + i)->ime, ime);

					strcpy(prezime, (osoba + j)->prezime);
					strcpy((osoba + j)->prezime, (osoba + i)->prezime);
					strcpy((osoba + i)->prezime, prezime);

					temp = (osoba + j)->kat;
					(osoba + j)->kat = (osoba + i)->kat;
					(osoba + i)->kat = temp;

					temp = (osoba + j)->stan;
					(osoba + j)->stan = (osoba + i)->stan;
					(osoba + i)->stan = temp;

					tempMob = (osoba + j)->mobitel;
					(osoba + j)->mobitel = (osoba + i)->mobitel;
					(osoba + i)->mobitel = tempMob;
				}
			}
		}
	}
	return;
}
int trazenje(STANAR *osoba, int brStanovaPoKatu, int brKatova)// funkcija za unos podataka za trazenje stana
{
	// pomocne varijable
	int kat, stan;
	int bol; // prima vrijednost koju vraca funkcija trazi, 1 nadeno 0 stan prazan
	// unos
	printf("Unesi kat zgrade (max. %d): \n", brKatova);
	scanf("%d", &kat);
	if (kat > brKatova || kat < 1)  // provjera unosa
	{
		printf("Nema toliko katova u zgradi.\n");
		trazenje(osoba, brStanovaPoKatu, brKatova); // vracanje na izbornik
		return;
	}
	// unos stana
	printf("Unesi broj stana na %d katu (max. %d): \n", kat, brStanovaPoKatu);
	scanf("%d", &stan);
	if (stan > brStanovaPoKatu || stan < 1) // provjera unosa
	{
		printf("Nema toliko stanova na katu.\n");
		trazenje(osoba, brStanovaPoKatu, brKatova); // vracanje na izbornik
		return;
	}
	bol = trazi(osoba, kat, stan); // poziv fje trazi, vraca 1 ili 0
	if (bol == 0) // ako je bol varijabla 0 ispis da je stan prazan
	{
		printf("Stan broj: %d na katu %d je prazan.\n", stan, kat);
	}
	Izbornik(osoba, brStanovaPoKatu, brKatova);// vracanje na izbornik
}
int trazi(STANAR *osoba, int kat, int stan) // funkcija trazi stan i vraca 0 ako je prazan ili 1 i ispise osobu iz stana ako je zauzet
{
	// prolazi kroz cijelu strukturu
	for (int i = 0; i < brStanara; i++)
	{
		if (kat == (osoba + i)->kat && stan == (osoba + i)->stan) // ako odgovara i kat i stan
		{
			// ispisi i vrati 1
			printf("U stanu broj %d na katu %d se nalazi: %s %s\n", stan, kat, (osoba + i)->ime, (osoba + i)->prezime);
			return 1;
		}
	}
	return 0; // vrati 0
}