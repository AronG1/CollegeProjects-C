#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int sljedeci = 0; // globalna variabla zaduzena za pracenje di se upisje u strukturu

void glavniIzbornik(struct Kalendar dogadaj[BRDOGADAJA])
{
	int a;
	printf("\nGlavni izbornik:\nOdaberite:\n1 - Pregled upisanih dogadaja\n2 - Dodavanje novih dogadaja\n3 - Brisanje postojecih dogadaja\n4 - Ispis dogadaja u datoteku Kalendar.txt\n0 - Izlaz iz programa\n");
	scanf("%d", &a);
	switch (a)
	{
	case 0:
		ispisDatoteku(dogadaj);
		exit(0);
		break;
	case 1:
		pregledDogadaja(dogadaj);
		break;
	case 2:
		dodavanjeDogadaja(dogadaj);
		break;
	case 3:
		brisanjeDogadaja(dogadaj);
		break;
	case 4:
		ispisKalendara(dogadaj);
		break;
	default:
		printf("Netocan unos!\n");
		glavniIzbornik(dogadaj);
		break;
	}

}

void dodavanjeDogadaja(struct Kalendar dogadaj[BRDOGADAJA])
{
	int dan, mjesec, godina;
	// unos godine
	do
	{
		printf("Unesite godinu dogadaja: \n");
		scanf("%d", &godina);
		if (godina < 2018)
		{
			printf("Godina mora biti tekuca ili u buducnosti!\n");
		}
		else
		{
			dogadaj[sljedeci].datumDogadaja.godina = godina; // godina nije u proslosti unesi ju u strukturu
			break;
		}
	} while (1);

	//unos mjeseca
	do
	{
		printf("Unesite mjesec dogadaja: \n");
		scanf("%d", &mjesec);
		// ako je mjesec manji od 1 ili veci od 12 ponovo pozovi funkciju za unos
		if (mjesec < 1 || mjesec > 12)
		{
			printf("Mjesec mora biti u rasponu 1 do 12\n");
		}
		else
		{
			dogadaj[sljedeci].datumDogadaja.mjesec = mjesec; // mjesec valja unesi ga u strukturu
			break;
		}
	} while (1);

	// unos dana
	do
	{
		printf("Unesite dan dogadaja: \n");
		scanf("%d", &dan);
		// ako mjesec ima 31 ili 30 dana
		if (mjesec == (1 || 3 || 5 || 7 || 8 || 10 || 12))
		{
			// ima 31
			if (dan < 1 || dan > 31) // jel uneseni dan unutar raspona 1 do 31
			{
				printf("Dan mora biti u rasponu 1 do 31\n");
				dodavanjeDogadaja(dogadaj);
			}
			else
			{
				dogadaj[sljedeci].datumDogadaja.dan = dan; // dan valja unesi ga u strukturu
				break;
			}
		}
		else // ima 30
		{
			if (dan < 1 || dan > 30) // jel uneseni dan unutar raspona 1 do 30
			{
				printf("Dan mora biti u rasponu 1 do 30\n");
				dodavanjeDogadaja(dogadaj);
			}
			else
			{
				dogadaj[sljedeci].datumDogadaja.dan = dan; // dan valja unesi ga u strukturu
				break;
			}
		}

	} while (1);

	printf("Unesite opis dogadaja: \n");
	// potrebno za rad fgetsa! =======
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	// =======
	// upis opisa u strukturu
	fgets(dogadaj[sljedeci].opis, 101, stdin);
	sljedeci++;
	printf("Dogadaj je uspjesno zabiljezen. \n");
	// povratak na glavni izborinik
	glavniIzbornik(dogadaj);
}

void pregledDogadaja(struct Kalendar dogadaj[BRDOGADAJA])
{
	// ispis svih unesenih dogadaja
	printf("Svi uneseni dogadaji: \n\n");
	// ako nema unesenih dogadaja
	if (sljedeci < 1)
	{
		printf("Nema unesenih dogadaja.\n");
	}
	else
	{
		sortiranje(dogadaj);
		for (int i = 0; i < sljedeci; i++)
		{
			printf("%d =  %d.%d.%d. - %s\n", i + 1, dogadaj[i].datumDogadaja.dan, dogadaj[i].datumDogadaja.mjesec, dogadaj[i].datumDogadaja.godina, dogadaj[i].opis);
		}
	}

	// povratak na glavni izbornik
	glavniIzbornik(dogadaj);
}

void ispisDatoteku(struct Kalendar dogadaj[BRDOGADAJA])
{
	// datoteke koje pamte dogadaje kada program prekine s radom
	FILE *database = NULL;
	FILE *databaseOpis = NULL;

	database = fopen("Database.txt", "w");
	databaseOpis = fopen("DatabaseOpis.txt", "w");
	// provjera jel ima gresaka s datotekama
	if (database == NULL || databaseOpis == NULL)
	{
		printf("Datoteku nije moguce stvoriti. Svi podatci su odbaceni.\n");
	}
	else // nema gresaka upisi u datoteke
	{
		for (int i = 0; i < sljedeci; i++)
		{
			// upis datuma u prvu datoteku
			fprintf(database, "%d %d %d\n", dogadaj[i].datumDogadaja.dan, dogadaj[i].datumDogadaja.mjesec, dogadaj[i].datumDogadaja.godina);
			// upis opis u drugu datoteku
			fprintf(databaseOpis, "%s", dogadaj[i].opis);
		}
		fclose(database);
		fclose(databaseOpis);
	}

}

void ucitavanjeDatoteke(struct Kalendar dogadaj[BRDOGADAJA])
{
	// vanjske datoteke koje pamte upisane dogadaje pri predhodnom radu programa
	FILE *datoteka = fopen("Database.txt", "r");
	FILE *datotekaOpis = fopen("DatabaseOpis.txt", "r");
	// provjera ispravnosti rada s datotekama
	if (datoteka == NULL)
	{
		printf("Nema prethodno unesenih dogadaja.\n");
	}
	else // sve je u redu ucitaj podatke u strukturu
	{
		// ucitavanje datuma u strukturu
		int i = 0;
		while (fscanf(datoteka, "%d %d %d\n", &dogadaj[i].datumDogadaja.dan, &dogadaj[i].datumDogadaja.mjesec, &dogadaj[i].datumDogadaja.godina) != EOF)
		{
			//printf("%d - %d %d %d\n", i, dan, mjesec, godina, opis);
			i++;
			sljedeci++;
		}
		i = 0;
		// ucitavanje opisa u strukturu
		while (fgets(dogadaj[i].opis, 100, datotekaOpis) != NULL)
		{
			i++;
		}
		fclose(datoteka);
		fclose(datotekaOpis);
	}
}

void brisanjeDogadaja(struct Kalendar dogadaj[BRDOGADAJA])
{
	int odabir = 0;
	// ispis svih unesenih dogadaja
	printf("Svi uneseni dogadaji: \n\n");
	// ako nema dogadaja
	if (sljedeci < 1)
	{
		printf("Nema unesenih dogadaja.\n");
		glavniIzbornik(dogadaj);
	}
	else // ako ih ima ispisi ih i pitaj sta treba obrisat
	{
		for (int i = 0; i < sljedeci; i++)
		{
			printf("%d =  %d.%d.%d. - %s\n", i + 1, dogadaj[i].datumDogadaja.dan, dogadaj[i].datumDogadaja.mjesec, dogadaj[i].datumDogadaja.godina, dogadaj[i].opis);
		}

		printf("Odaberite redni broj dogadaja koji zelite obrisat. Unesite 0 za otkazivanje.\n");
		scanf("%d", &odabir);
		if (odabir == 0) // ako je odabir 0 otkazi brisanje
		{
			glavniIzbornik(dogadaj);
		}
		else if (odabir > sljedeci) // ako je uneseni broj pogresan
		{
			printf("Nevazeci dogadaj\n");
			glavniIzbornik(dogadaj);
		}
		else if (odabir == sljedeci) // ako je zadnji dogadaj samo ga ponisti
		{
			// ponisti zadnji dogadaj
			dogadaj[odabir - 1].datumDogadaja.dan = 0;
			dogadaj[odabir - 1].datumDogadaja.mjesec = 0;
			dogadaj[odabir - 1].datumDogadaja.godina = 0;
			strcpy(dogadaj[odabir - 1].opis, "");
			sljedeci--; // umanji var. sljedeci za jedan da se sljedece upisivanje vrsi na obrisani dogadaj
			glavniIzbornik(dogadaj); // vracanje na glavni izbornik
		}
		else // ako je odabir vazeci a nije zadnji
		{
			for (int i = odabir; i <= sljedeci; i++) // prodi sve dogadaje od odabira prema kraju
			{
				if (i == sljedeci) // ako je zadnji dogadaj samo ga ponisti i vrati se na glavni izbornik
				{
					dogadaj[i - 1].datumDogadaja.dan = 0;
					dogadaj[i - 1].datumDogadaja.mjesec = 0;
					dogadaj[i - 1].datumDogadaja.godina = 0;
					strcpy(dogadaj[i - 1].opis, "");
					sljedeci--;
					glavniIzbornik(dogadaj);
				}
				else // ako nije zadnji dogadaj, trenutni prepisi podatcima od dogadaja unesenog poslije, pomakni za jedan dok ne dodes do zadnjeg
				{
					dogadaj[i - 1].datumDogadaja.dan = dogadaj[i].datumDogadaja.dan;
					dogadaj[i - 1].datumDogadaja.mjesec = dogadaj[i].datumDogadaja.mjesec;
					dogadaj[i - 1].datumDogadaja.godina = dogadaj[i].datumDogadaja.godina;
					strcpy(dogadaj[i - 1].opis, dogadaj[i].opis);
				}

			}
		}
	}
	


}

void ispisKalendara(struct Kalendar dogadaj[BRDOGADAJA])
{
	// ispisivanje u datoteku Kalendar.txt lijepo pregledno sve unesene dogadaje
	FILE *Kalendar = NULL;

	Kalendar = fopen("Kalendar.txt", "w");

	// provjera jel ima gresaka s datotekama
	if (Kalendar == NULL)
	{
		printf("Datoteku Kalendar.txt nije moguce stvoriti. Svi podatci su odbaceni.\n");
	}
	else // nema gresaka upisi u datoteke
	{
		sortiranje(dogadaj);
		// ispis u dat
		for (int i = 0; i < sljedeci; i++)
		{
			// upis
			fprintf(Kalendar, "%d.%d.%d. - %s\n", dogadaj[i].datumDogadaja.dan, dogadaj[i].datumDogadaja.mjesec, dogadaj[i].datumDogadaja.godina, dogadaj[i].opis);

		}
		fclose(Kalendar);
	}
	printf("Dogadaji su uspjesno upisani u datoteku Kalendar.txt");
	glavniIzbornik(dogadaj); // povratak na glavni izbornik

}

void sortiranje(struct Kalendar dogadaj[BRDOGADAJA])
{
	// sortitanje // selction sort
	int temp = 0;
	char tempOpis[100];
	for (int i = 0; i < sljedeci - 1; i++) // prolazi kroz cijelu strukturu
	{
		for (int j = i + 1; j < sljedeci; j++) // prolazi kroz cijelu struktur - 1
		{
			if (dogadaj[j].datumDogadaja.godina < dogadaj[i].datumDogadaja.godina) // ako je godina manja = zamjeni
			{
				temp = dogadaj[j].datumDogadaja.godina;
				dogadaj[j].datumDogadaja.godina = dogadaj[i].datumDogadaja.godina;
				dogadaj[i].datumDogadaja.godina = temp;

				temp = dogadaj[j].datumDogadaja.mjesec;
				dogadaj[j].datumDogadaja.mjesec = dogadaj[i].datumDogadaja.mjesec;
				dogadaj[i].datumDogadaja.mjesec = temp;

				temp = dogadaj[j].datumDogadaja.dan;
				dogadaj[j].datumDogadaja.dan = dogadaj[i].datumDogadaja.dan;
				dogadaj[i].datumDogadaja.dan = temp;

				strcpy(tempOpis, dogadaj[j].opis);
				strcpy(dogadaj[j].opis, dogadaj[i].opis);
				strcpy(dogadaj[i].opis, tempOpis);
			}
			else if (dogadaj[j].datumDogadaja.godina == dogadaj[i].datumDogadaja.godina) // ako je godina ista provjeri mjesec
			{
				if (dogadaj[j].datumDogadaja.mjesec < dogadaj[i].datumDogadaja.mjesec) // ako je mjesec manji = zamjeni
				{
					temp = dogadaj[j].datumDogadaja.godina;
					dogadaj[j].datumDogadaja.godina = dogadaj[i].datumDogadaja.godina;
					dogadaj[i].datumDogadaja.godina = temp;

					temp = dogadaj[j].datumDogadaja.mjesec;
					dogadaj[j].datumDogadaja.mjesec = dogadaj[i].datumDogadaja.mjesec;
					dogadaj[i].datumDogadaja.mjesec = temp;

					temp = dogadaj[j].datumDogadaja.dan;
					dogadaj[j].datumDogadaja.dan = dogadaj[i].datumDogadaja.dan;
					dogadaj[i].datumDogadaja.dan = temp;

					strcpy(tempOpis, dogadaj[j].opis);
					strcpy(dogadaj[j].opis, dogadaj[i].opis);
					strcpy(dogadaj[i].opis, tempOpis);
				}
				else if (dogadaj[j].datumDogadaja.mjesec == dogadaj[i].datumDogadaja.mjesec) // ako je mjesec isti provjeri dan
				{
					if (dogadaj[j].datumDogadaja.dan < dogadaj[i].datumDogadaja.dan) // ako je dan manji = zamjeni
					{

						temp = dogadaj[j].datumDogadaja.godina;
						dogadaj[j].datumDogadaja.godina = dogadaj[i].datumDogadaja.godina;
						dogadaj[i].datumDogadaja.godina = temp;

						temp = dogadaj[j].datumDogadaja.mjesec;
						dogadaj[j].datumDogadaja.mjesec = dogadaj[i].datumDogadaja.mjesec;
						dogadaj[i].datumDogadaja.mjesec = temp;

						temp = dogadaj[j].datumDogadaja.dan;
						dogadaj[j].datumDogadaja.dan = dogadaj[i].datumDogadaja.dan;
						dogadaj[i].datumDogadaja.dan = temp;

						strcpy(tempOpis, dogadaj[j].opis);
						strcpy(dogadaj[j].opis, dogadaj[i].opis);
						strcpy(dogadaj[i].opis, tempOpis);
					}
				}
			}
		}
	}

}