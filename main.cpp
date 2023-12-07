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
#define HAND_SIZE 8

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
	hand mao[2];
}player;

typedef struct {
	int p[11];
	hand mao[2];
}table;

void shuffle_position(char* x, char* y)
{
	char aux;
	aux = *x;
	*x = *y;
	*y = aux;
}

void InitDeck(deck* baralho)
{
	int i = 0;
	int x = 0;
	srand((unsigned)time(NULL));

	baralho->m = 0;
	(*baralho).m = 0;

	for (i = 0; i < 18; i++)
	{
		baralho->v[i].runner = 'h';
		baralho->v[i].color = MY_COLOR_LIGTH_YELLOW;
	}
	baralho->m = 18;
	for (i = 0; i < 17; i++)
	{
		baralho->v[i + baralho->m].runner = 't';
		baralho->v[i + baralho->m].color = MY_COLOR_LIGTH_GREEN;
	}
	baralho->m += 17;
	for (i = 0; i < 16; i++)
	{
		baralho->v[i + baralho->m].runner = 'w';
		baralho->v[i + baralho->m].color = MY_COLOR_GRAY;
	}
	baralho->m += 16;
	for (i = 0; i < 15; i++)
	{	
		baralho->v[i + baralho->m].runner = 'f';
		baralho->v[i + baralho->m].color = MY_COLOR_DARK_YELLOW;
	}
	baralho->m += 15;
	for (i = 0; i < 15; i++)
	{
		baralho->v[i + baralho->m].runner = 'l';
		baralho->v[i + baralho->m].color = MY_COLOR_WHITE;
	}
	baralho->m += 15;

	for (i = 0; i < 81; i++)
	{
		x = rand() % 81;
		shuffle_position(&baralho->v[i].runner, &baralho->v[x].runner);
	}
}

void getname(player *jogador)
{
	size_t lenght= 0;	
	int i = 0;
	
	while (true)
	{
		printf("Introduza o seu nome: ");
		fgets(jogador->name, sizeof(jogador->name), stdin);
		lenght = strlen(jogador->name) - 1;

		if (lenght < 20 && lenght > 0)
		{
			printf("Ola %s \n", jogador->name);
			break;
		}
		else if (lenght > 20)
		{
			printf("O nome nao pode ter mais que 20 caracteres! \n");
			strcpy(jogador->name, "");
		}
		else if (lenght <= 0)
		{
			printf("Por favor insira um nome!\n");
		}
	}
}

void ReadFile()
{
	FILE *fp;
	
	setlocale(LC_ALL, "Portuguese.UTF-8");

	char rules[5400];

	fp = fopen("RegrasDoJogo.txt", "r");
	
	while (fgets(rules, sizeof(rules), fp) != NULL)
		printf("%s", rules);

	fclose(fp);
}

void dealer(player* jogador, deck *baralho, hand* mao)
{
	int i = 0;

	for (i = 0; i< baralho->m; i++)
	{
		jogador->mao[0].v[i].runner = baralho->v[baralho->m - i - 1].runner;
		jogador->mao[0].v[i].color = baralho->v[baralho->m - i - 1].color;
	}
	baralho->m -= 8;
	for (i = 0; i < baralho->m; i++)
	{
		jogador->mao[1].v[i].runner = baralho->v[baralho->m - i - 1].runner;
		jogador->mao[1].v[i].color = baralho->v[baralho->m - i - 1].color;
	}
	baralho->m -= 8;
	jogador->mao[0].m += 8;
	jogador->mao[1].m += 8;
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

void arrowHereV(int realPosition, int arrowPosition)
{
	int i = 0;
	
	if (realPosition == arrowPosition) {
		printf("\n");
		for (i = 0; i < 2; i++)
			printf("|\n");
		printf("V\n");
	}
	else
	{
		printf("      ");
	}
}

void SetTable(int *table)
{
	int i;

	for (i = 0; i < 11; i++)
		table[i] += 1;
}

int menu()
{
	int position = 1;
	int keypressed = 0;
	
	do
	{
		gotoxy(40, 5); arrowHere(1, position); printf("1 - Novo Jogo\n");
		gotoxy(40, 6); arrowHere(2, position); printf("2 - Carregar Jogo\n");
		gotoxy(40, 7); arrowHere(3, position); printf("3 - Regras\n");
		gotoxy(40, 8); arrowHere(4, position); printf("4 - Sair\n");

		keypressed = getch();

		if (keypressed == 80 && position != 4)
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
	player jogador;
	hand mao;

	InitDeck(&baralho);

	switch (menu())
	{
	case 1:
		for (i = 0; i < 81; i++)
			printf("%c  ", baralho.v[i].runner);
		printf("\n %d", baralho.m);
		getname(&jogador);

		dealer(&jogador, &baralho, &mao);

		for (i = 0; i < 8; i++)
			printf("%c  ", jogador.mao[0].v[i].runner);
		arrowHereV(1, 1);
		for (i = 0; i < 8; i++)
			printf("%c  ", jogador.mao[1].v[i].runner);

		break;

	case 2:
		break;
	case 3:
		ReadFile();
	case 4:
		exit(-1);
	}
		
}