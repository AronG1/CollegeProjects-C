#pragma once

typedef struct proizvod
{
	char ime[100];
	int kolicina;
	float cijena;
}PROIZVOD;


PROIZVOD* memorija();
void ucitavanje(PROIZVOD*);
void meni(PROIZVOD*);
void dodaj(PROIZVOD*);
void meni2(PROIZVOD*);
void lista(PROIZVOD*);
void soritiranje(PROIZVOD*);
void trazi(PROIZVOD*);