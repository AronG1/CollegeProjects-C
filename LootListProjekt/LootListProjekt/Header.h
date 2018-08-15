#pragma once

typedef struct item
{
	char name[100];
	int slot; // 1 head, 2 arms, 3 chest, 4 legs
	int rarity; // 1 common, 2 uncommon, 3 rare, 4 epic, 5 legendary
	int type; // 1 leather, 2 plate, 3 mail, 4 cloth
}ITEM;

// dodaje item u polje struktura i datoteku
void addItem(ITEM *);
// trazi item iz struktre po unesenim podatcima
void searchItem(ITEM *);
// na pocetku programa ucita iteme iz datoteke u strukturu
void ucitajIteme(ITEM *);
// ispisuje sve iteme
void ispisiIteme(ITEM *);
// soritra strukturu po rarity od common do legendary
void sortiranje(ITEM *);