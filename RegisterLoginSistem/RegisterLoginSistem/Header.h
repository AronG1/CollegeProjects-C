#pragma once
#define BRKORISNIKA 100 // broj mogucih korisnika, koristi se za alokaciju memorije
// struktura
typedef struct User
{
	char name[50];
	char lastName[50];
	char username[50];
	char password[50];
	int numDogs;
}USER;
// deklaracija funkcija
USER* allocation();
void mainMenu(USER*);
void registration(USER*);
void database(USER*);
void login(USER*, int);
void subMeni(USER*, int);
void search(USER*, int);
void printUser(USER*, int);
void sort(USER*, int);
void printAllUsers(USER*, int);
void memoryFree(USER*);