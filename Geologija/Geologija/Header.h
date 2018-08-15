#pragma once

typedef struct Mineral
{
	char ime[50];
	int tip; // 1 olivin, 2 granatin, 3 cirkon
	int boja; // 1 zelena, 2 plava, 3 crvena, 4 roza 
	int struktura; // 1 vlaknasto 2 grudasto
	int oblik; // 1 kockasto  2 valjkasto 3 okruglasto 4 trokutasto
}MINERAL;

MINERAL* memorija();
int dodaj(MINERAL *, int);
int ucitajMinerale(MINERAL*);
void ispis(MINERAL *);
void ispisMinerala(MINERAL *, int);
void sortiranje(MINERAL *, int);
int trazenje(MINERAL *, int);