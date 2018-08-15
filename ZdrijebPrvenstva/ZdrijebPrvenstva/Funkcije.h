#pragma once


#define BRGRUPA 4 // br grupa
#define BREKIPAUGRUPI 4	// br ekipa u jednoj grupi

struct Ekipe // struktura za sve ekipe
{
	char ime[50];
	int grupa;
	int brojBodova;
};

struct EkipeCetvrtina // struktura cetvrtine finala
{
	char ime[50];
	int rezultat;
	int prosao;
};

struct EkipePolufinale // struktura polufinala
{
	char ime[50];
	int rezultat;
	int prosao;
};

struct EkipeFinale // struktura finala
{
	char ime[50];
	int rezultat;
	int pobjednik;
};
// definicije svih funkcija

void unosEkipa(struct Ekipe ekipa[BREKIPAUGRUPI * BRGRUPA]);

void generiranjeIspisRezultata(struct Ekipe ekipa[BREKIPAUGRUPI * BRGRUPA]);

void ispisGrupa(struct Ekipe ekipa[BREKIPAUGRUPI * BRGRUPA]);

void sortiranje(struct Ekipe ekipa[BREKIPAUGRUPI * BRGRUPA]);

void cetvrtinaFinala(struct Ekipe ekipa[BREKIPAUGRUPI * BRGRUPA], struct EkipeCetvrtina ekipaCet[8]);

void polufinale(struct EkipeCetvrtina ekipaCet[8], struct EkipePolufinale ekipaPolu[4]);

void finale(struct EkipePolufinale ekipaPolu[4], struct EkipeFinale ekipaFinale[2]);