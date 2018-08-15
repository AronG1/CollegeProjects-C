#include <stdio.h>
#include "Methods.h"

char *extension = ".txt"; // var for file extension
int numOfPassagers = 0;
struct list passagerList[ROW * COLS];

// displays main menu
void mainMenu()
{
	int choice;
	printf("\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", "Unesite: ",
		"1 za rezervaciju u prvoj klasi",
		"2 za rezervaciju u ekonomskoj klasi",
		"3 za pogledati kartu slobodnih mjesta u avionu",
		"4 za odabrati mjesto po zelji",
		"5 za prikazati popis putnika",
		"6 za ispis putnika sortiranih po mjestima",
		"0 za izlaz");
	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		firstClassCheckIn();
		break;
	case 2:
		economyClassCheckIn();
		break;
	case 3:
		viewSeatingChart();
		break;
	case 4:
		selectOwnSeat();
		break;
	case 5:
		readPassagersList();
		break;
	case 6:
		sorting();
		break;
	case 0:
		printf("\nHvala na koristenju aplikacije. Aron Gaspic.\n");
		return;
		break;
	default:
		printf("Netocan unos!\n");
		mainMenu();
		break;
	}

}

// check in, in first class in order
void firstClassCheckIn()
{
	int choice;
	passager PassagerFirstClass;

	printf("\nUnesite ime putnika:\n ");
	scanf("%s", &PassagerFirstClass.name);
	printf("\nUnesite prezime putnika:\n ");
	scanf("%s", &PassagerFirstClass.lastName);

	// looking for empty seat in first class
	for (int i = 1; i < ECONOM_START; i++)
	{
		for (int j = 1; j <= COLS; j++)
		{
			if (plane[i][j] == 0)
			{
				printf("\nVase mjesto je u redu %d, sjedalo %d.\n", i, j);
				plane[i][j] = 1;
				PassagerFirstClass.row = i;
				PassagerFirstClass.seat = j;
				printPassager(PassagerFirstClass);
				return;
			}

		}
	}
	// only if there is no empty seat in first class
	printf("\nNazalost u prvoj klasni nema slobodnog mjesta. Zelite li rezervirati mjesto u ekonomskoj klasi?\n Pritisnite: \n1 za da\n0 za povratak na glavni izbornik.\n");
	scanf("%d", &choice);
	if (choice == 1)
	{
		economyClassCheckIn();
	}
	else
	{
		mainMenu();
	}

}

// prints passager in file
void printPassager(struct passager Passager)
{
	FILE *printFile;

	char *fileName = malloc(strlen(flightName) + strlen(extension) + 1);
	// making file name from flightName and extension
	strcpy(fileName, flightName);
	strcat(fileName, extension);
	// print passager to file
	printFile = fopen(fileName, "a");
	fprintf(printFile, "%s %s, mjesto: %d - %d\n", Passager.name, Passager.lastName, Passager.row, Passager.seat);
	// break point
	printf("num of pas: %d\n", numOfPassagers);
	strcpy(passagerList[numOfPassagers].name, Passager.name);
	strcat(passagerList[numOfPassagers].lastName, Passager.lastName);
	passagerList[numOfPassagers].row = Passager.row;
	passagerList[numOfPassagers].seat = Passager.seat;
	numOfPassagers++;

	// good to go
	fclose(printFile);
	free(fileName);
	mainMenu();
}

// check in, in economy class in order
void economyClassCheckIn()
{
	int choice;
	passager passagerEconomyClass;

	printf("\nUnesite ime putnika:\n ");
	scanf("%s", &passagerEconomyClass.name);
	printf("\nUnesite prezime putnika:\n ");
	scanf("%s", &passagerEconomyClass.lastName);

	// looking for empty seat in economy class
	for (int i = ECONOM_START; i <= ROW; i++)
	{
		for (int j = 1; j <= COLS; j++)
		{
			if (plane[i][j] == 0)
			{
				printf("\nVase mjesto je u redu %d, sjedalo %d.\n", i, j);
				plane[i][j] = 1;
				passagerEconomyClass.row = i;
				passagerEconomyClass.seat = j;
				printPassager(passagerEconomyClass);
				return;
			}
		}

	}
	// only if no empty seat in econmy class
	printf("\nNazalost u ekonomskoj klasni nema slobodnog mjesta. Zelite li rezervirati mjesto u prvoj klasi?\n Pritisnite: \n1 za da\n0 za povratak na glavni izbornik.\n");
	scanf("%d", &choice);
	if (choice == 1)
	{
		firstClassCheckIn();
	}
	else
	{
		mainMenu();
	}

}

// displays seating chart
void viewSeatingChart()
{
	puts("\n        ^ ");
	puts("       / \\ ");
	puts("      /   \\ ");
	puts("     /     \\ ");
	puts("    /       \\");
	puts("    |       |");
	puts("    | 1 2 3 |");
	puts("    |       |");

	for (int i = 1; i <= ROW; i++)
	{
		if (i == ECONOM_START)// makes one row empty between first and economy class
		{
			puts("    |       |");
		}
		if (i < 10)
			printf("  %d | ", i);	// needs to be one space more bcs one digits numbers and print left side of plane
		else
			printf(" %d | ", i);	// needs to be one space less bcs two digits numbers and print left side of plane
		for (int j = 1; j <= COLS; j++)	// goes through plane array and print free and ocupied seats
		{
			if (plane[i][j])
				printf("x ");
			else
				printf("o ");
		}
		puts("|"); // right side of plane
	}

	puts("    |       |");
	puts("    \\       / ");
	puts("     \\     / ");
	puts("       |||  ");
	printf("\no - slobodno mjesto\nx - zauzeto mjesto\n");

	mainMenu();

}

// choose your own seat, check in
void selectOwnSeat()
{
	int rows;
	int seat;
	int choice;
	do
	{
		printf("\nUnesite red u kojem zelite rezervirati sjedalo (od 1 do %d)\n", ROW);
		scanf("%d", &rows);
		if (rows < 1 || rows > ROW)
		{
			printf("\nNetocan unos. Pokusajte ponovo.\n");
			continue;
		}
		else
		{
			break;
		}
	} while (1); // check input
	do
	{
		printf("\nUnesite sjedalo koje zelite rezervirati (od 1 do %d)\n", COLS);
		scanf("%d", &seat);
		if (seat < 1 || seat > COLS)
		{
			printf("\nNetocan unos. Pokusajte ponovo.\n");
			continue;
		}
		else
		{
			break;
		}
	} while (1); // check input

	if (plane[rows][seat] == 0)	// check if seat is empty
	{
		passager passagerOwnSeat;
		printf("\nUnesite ime putnika: \n");
		scanf("%s", &passagerOwnSeat.name);
		printf("\nUnesite prezime putnika: \n");
		scanf("%s", &passagerOwnSeat.lastName);
		passagerOwnSeat.row = rows;
		passagerOwnSeat.seat = seat;
		plane[rows][seat] = 1;
		printf("\nUspjesno ste rezervirali mjesto. \n");
		printPassager(passagerOwnSeat);
	}
	else // if seat is not empty
	{
		printf("Zeljeno mjesto nije slobodno. Pritisnite:\n1 za odabir novog sjedala\n2 za pregled slobodnih sjedala u avionu\n0 za povratak na glavni izbornik\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			selectOwnSeat();
			break;
		case 2:
			viewSeatingChart();
			break;
		case 0:
			mainMenu();
			break;
		default:
			mainMenu();
			break;
		}
	}

}

// reads passagers from file and print them to console
void readPassagersList()
{
	char *fileName = malloc(strlen(flightName) + strlen(extension) + 1);

	strcpy(fileName, flightName);
	strcat(fileName, extension);

	FILE *read = fopen(fileName, "r");
	char line[100];
	if (read == NULL) // if file not exist
	{
		//printf("\nDatoteka ne postoji.\n");
		printf("\nNa ovom letu nema putnika jos.\n");
		mainMenu();
		return;
	}
	printf("\nPopis putnika: \n");
	while (fgets(line, sizeof line, read) != NULL) // read all lines in file
	{
		fputs(line, stdout); // print those lines to console
	}
	fclose(read);
	free(fileName);
	printf("\n");
	mainMenu();
}

// 1st function for choosing flight name
void setFlightName()
{
	printf("\nUnesite ime leta (npr.Zagreb-London)\n");
	//fflush(stdin);
	//(stdin);
	gets(flightName, 21, stdin);

	checkIsFlightExist();
}

// check if flight already exists, if exist read occupied seats
void checkIsFlightExist()
{
	char *fileName = malloc(strlen(flightName) + strlen(extension) + 1);
	char name[20], lastName[20], mjesto[10], dash[5];
	int row, seat;

	strcpy(fileName, flightName);
	strcat(fileName, extension);

	FILE *readFile = fopen(fileName, "r");

	if (readFile == NULL) // if there is no file with this flight
	{
		//printf("Let ne postoji. napravi ga");
	}
	else // if there is file with this flight, read already occupied seats
	{
		int i = 0;
		while (fscanf(readFile, "%s %s %s %d %s %d", name, lastName, mjesto, &row, dash, &seat) != EOF)
		{
			// occupy seat
			plane[row][seat] = 1;
			//printf("%s\t", name);
			// adds to array of struct for sorting
			strcpy(passagerList[i].name, name);
			strcat(passagerList[i].lastName, lastName);
			passagerList[i].row = row;
			passagerList[i].seat = seat;
			//printf("%s\n", passagerList[i].name);
			i++;
			numOfPassagers++;
		}
		fclose(readFile);
	}

	free(fileName);
	// for debug of plane array ::: check is file read correctly
	/*for (int i = 1; i <= ROW; i++)
	{
	for (int j = 1; j <= COLS; j++)
	{
	printf("%d ", plane[i][j]);
	}
	printf("\n");
	}*/
	mainMenu();
}

// sorts array with selection sort
void sorting()
{
	// break point
	printf("num of pas: %d\n", numOfPassagers);
	char temp[100];
	int tempInt = 0;
	for (int i = 0; i < numOfPassagers - 1; i++)
	{
		for (int j = i + 1; j < numOfPassagers; j++)
		{
			if (passagerList[j].row < passagerList[i].row)
			{
				// swap
				strcpy(temp, passagerList[j].name);
				strcpy(passagerList[j].name, passagerList[i].name);
				strcpy(passagerList[i].name, temp);
				strcpy(temp, passagerList[j].lastName);
				strcpy(passagerList[j].lastName, passagerList[i].lastName);
				strcpy(passagerList[i].lastName, temp);	
				tempInt = passagerList[j].row;
				passagerList[j].row = passagerList[i].row;
				passagerList[i].row = tempInt;
				tempInt = passagerList[j].seat;
				passagerList[j].seat = passagerList[i].seat;
				passagerList[i].seat = tempInt;
			}
			else if (passagerList[j].row == passagerList[i].row)
			{
				if (passagerList[j].seat < passagerList[i].seat)
				{
					// swap
					strcpy(temp, passagerList[j].name);
					strcpy(passagerList[j].name, passagerList[i].name);
					strcpy(passagerList[i].name, temp);
					strcpy(temp, passagerList[j].lastName);
					strcpy(passagerList[j].lastName, passagerList[i].lastName);
					strcpy(passagerList[i].lastName, temp);
					tempInt = passagerList[j].row;
					passagerList[j].row = passagerList[i].row;
					passagerList[i].row = tempInt;
					tempInt = passagerList[j].seat;
					passagerList[j].seat = passagerList[i].seat;
					passagerList[i].seat = tempInt;

				}
			}
		}
	}
	// print sorted array
	for (int i = 0; i < numOfPassagers; i++)
	{
		printf("%d - %d, %s %s\n", passagerList[i].row, passagerList[i].seat, passagerList[i].name, passagerList[i].lastName);
	}
	mainMenu();
}