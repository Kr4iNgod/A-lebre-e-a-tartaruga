#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS_GLOBALS
#define _CRT_NONSTDC_NO_WARNINGS
#define _getch getch // para o getch funcionar

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <lab.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>

#define DECK_SIZE 81

typedef struct {
	char runner;
	int color;
}card;

typedef struct {
	card v[DECK_SIZE];
	int m;
}deck;

typedef struct {
	card v[8];
	int m;
}hand;

typedef struct {
	char name[20];
	hand mao;
}p1;

void shuffle_position(char* x, char* y)
{
	char aux;
	aux = *x;
	*x = *y;
	*y = aux;
}

void InitDeck(deck * baralho)
{
	int i = 0;
	int x = 0;
	srand((unsigned)time(NULL));

	baralho->m = 0;
	(*baralho).m = 0;

	for (i = 0; i < 18; i++)
		baralho->v[i].runner = 'h';
	baralho->m = 18;
	for (i = 0; i < 17; i++)
		baralho->v[i + baralho->m].runner = 't';
	baralho->m += 17;
	for (i = 0; i < 16; i++)
		baralho->v[i + baralho->m].runner = 'w';
	baralho->m += 16;
	for (i = 0; i < 15; i++)
		baralho->v[i + baralho->m].runner = 'f';
	baralho->m += 15;
	for (i = 0; i < 15; i++)
		baralho->v[i + baralho->m].runner = 'l';
	baralho->m += 15;

	for (i = 0; i < 81; i++)
	{
		x = rand() % 81;
		shuffle_position(&baralho->v[i].runner, &baralho->v[x].runner);
	}
}

void arrowHere(int realPosition, int arrowPosition)
{
	if (realPosition == arrowPosition) {
		printf("----> ");
	}
	else
	{
		printf("      ");
	}
}

int menu()
{
	int position = 1;
	int keypressed = 0;
	
	do
	{
		gotoxy(40, 5); arrowHere(1, position); printf("1 - Novo Jogo\n");
		gotoxy(40, 6); arrowHere(2, position); printf("2 - Carregar Jogo\n");
		gotoxy(40, 7); arrowHere(3, position); printf("3 - Sair\n");

		keypressed = getch();

		if (keypressed == 80 && position != 3)
		{
			position++;
		}
		else if (keypressed == 72 && position != 1)
		{
			position--;
		}
	} while (keypressed != 13);

	return position;
}

int main(void)
{
	setlocale(LC_ALL, "Portuguese");
	
	int i = 0;
	int op=0;

	deck baralho;

	InitDeck(&baralho);

	switch (menu())
	{
	case 1:
		for (i = 0; i < 81; i++)
			printf("%c  ", baralho.v[i]);
		break;

	case 2:
		break;
	case 3:
		exit(-1);
	}
		
}