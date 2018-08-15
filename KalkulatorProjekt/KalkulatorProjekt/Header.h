#pragma once
#define BRMOJODABIR 20

struct osoba
{
	int dob;
	float visina;
	int spol;
	float tezina;

};

struct mojodabir
{
	char ime[50];
	float kalorije;
	float proteini;
	float ugljikohidrati;
	float masti;
};

void meni();

void unos();

float izracun(int, float, float, int);

void tablica();

void mojUnos();

void mojOdabir();

void sortiranjeIspis(struct mojodabir odabir[BRMOJODABIR], int);

void trazenje(struct mojodabir odabir[BRMOJODABIR], int);