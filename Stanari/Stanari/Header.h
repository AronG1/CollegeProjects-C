#pragma once

// struktura
typedef struct Stanar
{
	char ime[50];
	char prezime[50];
	int kat;
	int stan;
	long int mobitel;
}STANAR;
// dekalaracije funkcija
void Izbornik(STANAR *, int, int);
STANAR *alokacija(int);
void upisStanara(STANAR *, int, int);
int upisUDatoteku(STANAR *, int, int);
void citanjeDatoteke(STANAR *, int , int);
void ispisStanara(STANAR *, int, int);
void sortiranje(STANAR *);
int trazenje(STANAR *, int, int);
int trazi(STANAR *, int, int);