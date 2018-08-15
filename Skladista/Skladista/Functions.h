#pragma once
// struktura
struct item
{
	char name[100];
	int amount;
};
// deklaracije svih funkcija
void mainMenu();
int readNumStorage();
void storageList();
void deleteStorage();
void addStorage();
void sort(int numOfItems, char name[100]);