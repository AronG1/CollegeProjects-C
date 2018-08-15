#include <stdio.h>
#include <stdlib.h>
#include "Funkcije.h"
#include <time.h>

// fja za unos ekipa od strane korisnika
void unosEkipa(struct Ekipe ekipa[BREKIPAUGRUPI * BRGRUPA])
{
	int n = 1, j = 1;
	char ime[50];
	for (int i = 0; i < 16; i++)
	{
		printf("Unesi ime %d. ekipu u %d. grupi: \n", j, n);
		scanf("%s", ime);
		strcpy(ekipa[i].ime, ime);
		ekipa[i].brojBodova = 0;
		ekipa[i].grupa = n;
		j++;	
		if (j >= 5) // ako je j 5 ili vise postavi na 1 i idi na sljedecu grupu (n)
		{
			j = 1;
			n++;
		}
		//printf("ime %s, grupa %d, bodovi: %d \n", ekipa[i].ime, ekipa[i].grupa, ekipa[i].brojBodova); // za provjeru unesenih ekipa
	}

}
// fja za random rezultate i ispis
void generiranjeIspisRezultata(struct Ekipe ekipa[BREKIPAUGRUPI * BRGRUPA])
{
	srand((unsigned)time(NULL)); // postavljanje sjemena za random fju
	int rez1, rez2;
	FILE* ispis = fopen("Rezultati.txt", "w"); // datoteka u koju ce se ispisat rezultati
	if (ispis == NULL)
	{
		printf("Greska. Ne moze se otvoriti datoteka.\n");

	}
	else
	{
		for (int n = 0; n < BRGRUPA*BREKIPAUGRUPI; n = n + BREKIPAUGRUPI)
		{
			for (int i = n; i < n + BREKIPAUGRUPI - 1; i++)
			{
				for (int j = i + 1; j < n + BREKIPAUGRUPI; j++)
				{
					//printf("n = %d, i = %d, j = %d\n", n, i, j);
					rez1 = rand() % 5;
					rez2 = rand() % 5;
					if (rez1 == rez2)
					{
						// izjednaceno
						ekipa[i].brojBodova = ekipa[i].brojBodova + 1;
						ekipa[j].brojBodova = ekipa[j].brojBodova + 1;
					}
					else if (rez1 > rez2)
					{
						// pob domacina
						ekipa[i].brojBodova = ekipa[i].brojBodova + 3;
					}
					else
					{
						// pob gosta
						ekipa[j].brojBodova = ekipa[j].brojBodova + 3;
					}
					//printf("%s - %s %d:%d\n", ekipa[i].ime, ekipa[j].ime, rez1, rez2); // ispis rez na konzolu
					fprintf(ispis, "%s - %s %d:%d\n", ekipa[i].ime, ekipa[j].ime, rez1, rez2); // ispis u datoteku
				}
			}
			
		}
		fclose(ispis);
		printf("Utakmice su odigrane. Rezultate mozete pogledati u datoteci Rezultati.txt\n");
	}
	
	
	

}
// fja za sortiranje grupa
void sortiranje(struct Ekipe ekipa[BREKIPAUGRUPI * BRGRUPA])
{
	int brBodova;
	char ime[20];

	// sortira prvu grupu
	for (int i = 0; i < 4 -1; i++) // prolazi kroz sve
	{
		for (int j = i+1; j < 4; j++) //prolzi kroz sve pokraj i
		{
			if (ekipa[j].brojBodova > ekipa[i].brojBodova) // ako ima vise bodova zamjeni
			{
				// zamjeni sve vrijednosti strukture pomocu varijable brBodova i ime
				brBodova = ekipa[j].brojBodova;
				ekipa[j].brojBodova = ekipa[i].brojBodova;
				ekipa[i].brojBodova = brBodova;
				strcpy(ime, ekipa[j].ime);
				strcpy(ekipa[j].ime, ekipa[i].ime);
				strcpy(ekipa[i].ime, ime);
			}
		}
	}
	// sortira drugu grupu
	for (int i = 4; i < 8 - 1; i++)
	{
		for (int j = i + 1; j < 8; j++)
		{
			if (ekipa[j].brojBodova > ekipa[i].brojBodova)
			{
				brBodova = ekipa[j].brojBodova;
				ekipa[j].brojBodova = ekipa[i].brojBodova;
				ekipa[i].brojBodova = brBodova;
				strcpy(ime, ekipa[j].ime);
				strcpy(ekipa[j].ime, ekipa[i].ime);
				strcpy(ekipa[i].ime, ime);
			}
		}
	}
	// sortira trecu grupu
	for (int i = 8; i < 12 - 1; i++)
	{
		for (int j = i + 1; j < 12; j++)
		{
			if (ekipa[j].brojBodova > ekipa[i].brojBodova)
			{
				brBodova = ekipa[j].brojBodova;
				ekipa[j].brojBodova = ekipa[i].brojBodova;
				ekipa[i].brojBodova = brBodova;
				strcpy(ime, ekipa[j].ime);
				strcpy(ekipa[j].ime, ekipa[i].ime);
				strcpy(ekipa[i].ime, ime);
			}
		}
	}
	// sortira cetvrtu grupu
	for (int i = 12; i < 16 - 1; i++)
	{
		for (int j = i + 1; j < 16; j++)
		{
			if (ekipa[j].brojBodova > ekipa[i].brojBodova)
			{
				brBodova = ekipa[j].brojBodova;
				ekipa[j].brojBodova = ekipa[i].brojBodova;
				ekipa[i].brojBodova = brBodova;
				strcpy(ime, ekipa[j].ime);
				strcpy(ekipa[j].ime, ekipa[i].ime);
				strcpy(ekipa[i].ime, ime);
			}
		}
	}


}
// fja za ispis grupa
void ispisGrupa(struct Ekipe ekipa[BREKIPAUGRUPI * BRGRUPA])
{
	int n = 1, j = 1;
	printf("Ime\t\t bodovi\n");
	printf("Grupa 1:\n\n");
	for (int i = 0; i < BREKIPAUGRUPI * BRGRUPA; i++)
	{
		printf("%s\t%10d\n", ekipa[i].ime, ekipa[i].brojBodova);
		j++;
		if (j >= BREKIPAUGRUPI + 1) // kad produ 4 ekipe prijedi na slj grupu i postavi j na 1
		{
			j = 1; 
			n++;
			if (n < BREKIPAUGRUPI + 1) // da ne ispise grupu 5
			{
				printf("\nGrupa %d:\n\n", n);
			}		
		}
	}
}
// fja za cetvrtinu finala
void cetvrtinaFinala(struct Ekipe ekipa[BREKIPAUGRUPI * BRGRUPA], struct EkipeCetvrtina ekipaCet[8])
{
	/*Shema
	1A - 2B =====			====== 1C - 2D
				============
	1B - 2C =====			====== 1D - 2A
	*/
	// prepisat prve dvije ekipe iz svih grupa u novu strukturu
	strcpy(ekipaCet[0].ime, ekipa[0].ime);
	strcpy(ekipaCet[1].ime, ekipa[5].ime);
	strcpy(ekipaCet[2].ime, ekipa[4].ime);
	strcpy(ekipaCet[3].ime, ekipa[9].ime);
	strcpy(ekipaCet[4].ime, ekipa[8].ime);
	strcpy(ekipaCet[5].ime, ekipa[13].ime);
	strcpy(ekipaCet[6].ime, ekipa[12].ime);
	strcpy(ekipaCet[7].ime, ekipa[1].ime);
	
	printf("\nParovi u cetvrtini finala: \n");
	for (int i = 0; i < 8; i = i + 2)
	{
		printf("%s - %s \n", ekipaCet[i].ime, ekipaCet[i + 1].ime);
	}

	printf("\nUtakmice su odigrane.\n");

	int rez1, rez2;
	for (int i = 0; i < 8; i = i + 2) // proci kroz sve utakmice
	{
		// random rezultati do 4
		rez1 = rand() % 5;
		rez2 = rand() % 5;
		if (rez1 > rez2)
		{
			// domacin pob
			ekipaCet[i].prosao = 1;
			ekipaCet[i + 1].prosao = 0;
			ekipaCet[i].rezultat = rez1;
			ekipaCet[i + 1].rezultat = rez2;
		}
		else if (rez1 < rez2)
		{
			// gost pob
			ekipaCet[i].prosao = 0;
			ekipaCet[i + 1].prosao = 1;
			ekipaCet[i].rezultat = rez1;
			ekipaCet[i + 1].rezultat = rez2;
		}
		else if (rez1 == rez2) // ako je izjednaceno random generiraj dok se ne dobije pobjednik
		{
			do
			{
				rez1 = rand() % 5;
				rez2 = rand() % 5;
				if (rez1 > rez2)
				{
					ekipaCet[i].prosao = 1;
					ekipaCet[i + 1].prosao = 0;
					ekipaCet[i].rezultat = rez1;
					ekipaCet[i + 1].rezultat = rez2;
					break;
				}
				else if (rez1 < rez2)
				{
					ekipaCet[i].prosao = 0;
					ekipaCet[i + 1].prosao = 1;
					ekipaCet[i].rezultat = rez1;
					ekipaCet[i + 1].rezultat = rez2;
					break;
				}
			} while (rez1 == rez2);
		}
	}
	// ispis rezultata
	printf("\nRezultat cetvrtine finala: \n");
	for (int i = 0; i < 8; i = i + 2)
	{
		printf("%s %d - %s %d\n", ekipaCet[i].ime, ekipaCet[i].rezultat, ekipaCet[i + 1].ime, ekipaCet[i + 1].rezultat);
	}

	
}
// fja polufinala
void polufinale(struct EkipeCetvrtina ekipaCet[8], struct EkipePolufinale ekipaPolu[4])
{
	// kopiraj sve koji su prosli u novu struktruru
	int j = 0;
	for (int i = 0; i < 8; i++)
	{
		if (ekipaCet[i].prosao == 1)
		{
			strcpy(ekipaPolu[j].ime, ekipaCet[i].ime);
			j++;
		}
	}
	// random rez kao i u cetvritni
	int rez1, rez2;
	for (int i = 0; i < 4; i = i + 2)
	{
		rez1 = rand() % 5;
		rez2 = rand() % 5;
		if (rez1 > rez2)
		{
			ekipaPolu[i].prosao = 1;
			ekipaPolu[i + 1].prosao = 0;
			ekipaPolu[i].rezultat = rez1;
			ekipaPolu[i + 1].rezultat = rez2;
		}
		else if (rez1 < rez2)
		{
			ekipaPolu[i].prosao = 0;
			ekipaPolu[i + 1].prosao = 1;
			ekipaPolu[i].rezultat = rez1;
			ekipaPolu[i + 1].rezultat = rez2;
		}
		else if (rez1 == rez2)
		{
			do
			{
				rez1 = rand() % 5;
				rez2 = rand() % 5;
				if (rez1 > rez2)
				{
					ekipaPolu[i].prosao = 1;
					ekipaPolu[i + 1].prosao = 0;
					ekipaPolu[i].rezultat = rez1;
					ekipaPolu[i + 1].rezultat = rez2;
					break;
				}
				else if (rez1 < rez2)
				{
					ekipaPolu[i].prosao = 0;
					ekipaPolu[i + 1].prosao = 1;
					ekipaPolu[i].rezultat = rez1;
					ekipaPolu[i + 1].rezultat = rez2;
					break;
				}
			} while (rez1 == rez2);
		}
	}
	// ispisi rezultate
	printf("\nRezultat polufinala: \n");
	for (int i = 0; i < 4; i = i + 2)
	{
		printf("%s %d - %s %d\n", ekipaPolu[i].ime, ekipaPolu[i].rezultat, ekipaPolu[i + 1].ime, ekipaPolu[i + 1].rezultat);
	}

}
// fja finala
void finale(struct EkipePolufinale ekipaPolu[4], struct EkipeFinale ekipaFinale[2])
{
	// kopiraj sve koji su prosli u novu strukturu
	int j = 0;
	for (int i = 0; i < 4; i++)
	{
		if (ekipaPolu[i].prosao == 1)
		{
			strcpy(ekipaFinale[j].ime, ekipaPolu[i].ime);
			j++;
		}
	}
	// random rezultati, ne moze biti nerjeseno
	int rez1, rez2;
	do
	{
		rez1 = rand() % 5;
		rez2 = rand() % 5;
		if (rez1 > rez2)
		{
			ekipaFinale[0].pobjednik = 1;
			ekipaFinale[1].pobjednik = 0;
			ekipaFinale[0].rezultat = rez1;
			ekipaFinale[1].rezultat = rez2;
		}
		else if(rez1 < rez2)
		{
			ekipaFinale[0].pobjednik = 0;
			ekipaFinale[1].pobjednik = 1;
			ekipaFinale[0].rezultat = rez1;
			ekipaFinale[1].rezultat = rez2;
		}
	} while (rez1 == rez2);
	// ispis pobjednikaa
	printf("Turnir je zavrsen: \n");
	printf("%s %d - %s %d \n", ekipaFinale[0].ime , ekipaFinale[0].rezultat, ekipaFinale[1].ime, ekipaFinale[1].rezultat);
	if (ekipaFinale[0].pobjednik == 1)
	{
		printf("Turnir je osvojila ekipa: %s\n", ekipaFinale[0].ime);
	}
	else
	{
		printf("Turnir je osvojila ekipa: %s\n", ekipaFinale[1].ime);
	}


}