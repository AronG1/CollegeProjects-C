#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

void mainMenu()
{
	int choice;
	printf("IZBORNIK : \n");
	printf("1. Zapocnite igru!\n");
	printf("2. Pravila igre.\n");
	printf("3. Rang lista.\n");
	printf("4. Izlaz iz igre.\n");
	printf("*Vas odabir* \n");
	scanf("%d", &choice);
	system("cls");
	if (choice == 1) {
		Start();
	}
	else if (choice == 2) {
		Help();
	}
	else if (choice == 3) {
		ScoreList();
	}
	else if (choice == 4) {
		exit(0);
	}
	else
	{
		printf("Netocan unos!\n");
		mainMenu();
	}
}

void Start(){
	int correctAnswersCounter = 0;
	char firstAns[50];
	char secondAns[50];
	char thirdAns[50];
	char fourthAns[50];
	int firstAnsCor = 0;
	int secondAnsCor = 0;
	int thirdAnsCor = 0;
	int fouthAnsCor = 0;
	int counter = 1;
	char question[200];
	int answer;
	int correctAnswer = 0;
	char name[50];
	char lastname[50];
	printf("Unesite svoje ime : \n");
	scanf("%15s", name);
	printf("Unesite svoje prezime : \n");
	scanf("%15s", lastname);
	FILE *pToFile = fopen("text.txt", "r");
	FILE *pToQuestion = fopen("pitanja.txt", "r");
	FILE *pToPlayer = fopen("igraci.txt", "a");
	if (pToFile == NULL)
	{
		printf("Greska!\n");
	}
	else
	{
		if (pToQuestion == NULL)
		{
			printf("Greska!\n");
		}
		else
		{
			while (fscanf(pToFile, "%s%d\n%s%d\n%s%d\n%s%d\n", firstAns, &firstAnsCor, secondAns, &secondAnsCor, thirdAns, &thirdAnsCor, fourthAns, &fouthAnsCor) != EOF)
			{
				fgets(question, 201, pToQuestion);
				printf("%d. pitanje %s", counter, question);
				printf("1. %s\n2. %s \n3. %s \n4. %s \n", firstAns, secondAns, thirdAns, fourthAns);
				counter++;
				printf("Unesi odgovor: \n");
				scanf("%d", &answer);

				if (firstAnsCor == 1)
				{
					correctAnswer = 1;
				}
				else if (secondAnsCor == 1)
				{
					correctAnswer = 2;
				}
				else if (thirdAnsCor == 1)
				{
					correctAnswer = 3;
				}
				else if(fouthAnsCor == 1)
				{
					correctAnswer = 4;
				}

				if (answer == correctAnswer)
				{
					printf("Tocan odgovor!\n");
					correctAnswersCounter++;
				}
				else
				{
					printf("Netocno!\n");
				}
			}
			printf("\n\nBroj tocnih odgovora je %d\n", correctAnswersCounter);
			fclose(pToFile);
			fclose(pToQuestion);
			if (pToPlayer == NULL)
			{
				printf("Greska!\n");
			}
			else
			{
				fprintf(pToPlayer, "%s %s %d\n", name, lastname, correctAnswersCounter);
				fclose(pToPlayer);
			}
		}
	}
	mainMenu();
}

void Help(){
	printf("PRAVILA FERIT KVIZA : \n");
	printf("1. FERIT kviz mogu zaigrati profesori i studenti Fakulteta elektrotehnike, racunarstva i informacijskih znanosti.\n");
	printf("2. Kviz se sastoji od ukupno 10 pitanja vezana za podrucje elektrotehnike i racunarstva.\n");
	printf("3. Svaki tocan odgovor nosi 1 bod te nema negativnog bodovanja.\n");
	printf("_________________________________________________________________________________________________________________\n");
	printf("\t\t\t\t\t\t SRETNO!!! \t\t\t\t\t\t\n");
	mainMenu();
	
}

void ScoreList(){
	
	FILE *pToPlayer = NULL;
	pToPlayer = fopen("igraci.txt", "r");
	int br = 0;

	struct player *igrac;
	igrac = malloc(100 * sizeof(struct player));
	if (pToPlayer == NULL)
	{
		printf("Nema jos igraca!\n");
	}
	else
	{
		while (fscanf(pToPlayer, "%s %s %d\n", igrac[br].firstName, igrac[br].lastName, &igrac[br].points) != EOF)
		{
			br++;
		}
		sorting(igrac, br);
		for (int j = 0; j < br; j++)
		{
			printf("%d. %s %s %d\n", j + 1, igrac[j].firstName, igrac[j].lastName, igrac[j].points);
		}
		fclose(pToPlayer);
	}
	mainMenu();
}

void sorting(struct player igrac[100], int brIgraca)
{
	int temp; 
	char tempC[50]; 
	for (int i = 0; i < brIgraca - 1; i++)
	{
		for (int j = i + 1; j < brIgraca; j++)
		{
			if (igrac[j].points > igrac[i].points) 
			{
				temp = igrac[j].points;
				igrac[j].points = igrac[i].points;
				igrac[i].points = temp;

				strcpy(tempC, igrac[j].firstName);
				strcpy(igrac[j].firstName, igrac[i].firstName);
				strcpy(igrac[i].firstName, tempC);

				strcpy(tempC, igrac[j].lastName);
				strcpy(igrac[j].lastName, igrac[i].lastName);
				strcpy(igrac[i].lastName, tempC);

			}
		}
	}

}