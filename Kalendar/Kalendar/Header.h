#pragma once
#ifndef HEADER
#define HEADER


#define BRDOGADAJA 100 // maksimalni broj koliko se moze unijeti dogadaja

 

// struktura datum podstrukture Kalendar
struct Datum
{
	int dan;
	int mjesec;
	int godina;
};
// struktura kalendar
struct Kalendar
{
	char opis[100];
	struct Datum datumDogadaja;
};

void glavniIzbornik(Kalendar);
void dodavanjeDogadaja( Kalendar);
void pregledDogadaja( Kalendar );
void ispisDatoteku( Kalendar );
void ucitavanjeDatoteke( Kalendar );
void brisanjeDogadaja( Kalendar );
void ispisKalendara( Kalendar );
void sortiranje(Kalendar);

#endif // !HEADER