#pragma once

// struktura
struct Automobil
{
	char marka[20];
	char model[50];
	int godiste;
	float kilometri;
	float cijena;

};

// deklaracije funkcija
void mainMenu(struct Automobil automobil[100], int brAuta);

void ucitajBazu(struct Automobil automobil[100], int brAuta);

void dostupni(struct Automobil automobil[100], int brAuta);

void narudzba(struct Automobil automobil[100], int brAuta);

void kupnja(struct Automobil automobil[100], int brAuta);

void updateBazu(struct Automobil automobil[100], int brAuta);

void sortiranje(struct Automobil automobil[100], int brAuta);

void pretrazi(struct Automobil automobil[100], int brAuta);