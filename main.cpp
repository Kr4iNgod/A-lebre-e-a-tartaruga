﻿/*
slot board(a) - animal - letra da carta - n de cartas
0 - lebre - h - 18
1 - tartaruga - t -17
2- lobo - w/s - 13/3
3 - raposa - f - 15
4 - cordeiro - l - 15
*/

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
#define HAND_SIZE 7

typedef struct {
	char runner;
	int color;
}card;

typedef struct {
	card v[DECK_SIZE];
	int m; // number of cards in the deck
}deck;

typedef struct {
	card v[8];
	int m;
}hand;

typedef struct {
	char name[20];
	hand mao;
	hand bet[2];
}player;


typedef struct {
	int a[5]; // [] slot pra cada animal , associar vetor a posiçao 
	char t[11]; // board position type
	hand mao;
}board;

void shuffle_position(char* x, char* y)
{
	char aux;
	aux = *x;
	*x = *y;
	*y = aux;
}

void shuffle_positionInt(int* x, int* y)
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
		baralho->v[i].runner = 'H'; // h - Lebre 18
		baralho->v[i].color = MY_COLOR_CYAN;
	}
	baralho->m = 18;
	for (i = 0; i < 17; i++)
	{
		baralho->v[i + baralho->m].runner = 'T'; // t - Tartaruga 17
		baralho->v[i + baralho->m].color = MY_COLOR_LIGTH_GREEN;
	}
	baralho->m += 17;
	for (i = 0; i < 13; i++)
	{
		baralho->v[i + baralho->m].runner = 'W'; // w- lobo 13
		baralho->v[i + baralho->m].color = MY_COLOR_PURPLE;
	}
	baralho->m += 13;
	for (i = 0; i < 3; i++)
	{
		baralho->v[i + baralho->m].runner = 'S'; // s - uivo lobo 3
		baralho->v[i + baralho->m].color = MY_COLOR_PINK;
	}
	baralho->m += 3;
	for (i = 0; i < 15; i++)
	{
		baralho->v[i + baralho->m].runner = 'F'; // f - raposa 15
		baralho->v[i + baralho->m].color = MY_COLOR_DARK_YELLOW;
	}
	baralho->m += 15;
	for (i = 0; i < 15; i++)
	{
		baralho->v[i + baralho->m].runner = 'L'; // l - cordeiro 15
		baralho->v[i + baralho->m].color = MY_COLOR_WHITE;
	}
	baralho->m += 15;

	for (i = 0; i < 81; i++)
	{
		x = rand() % 81;
		shuffle_position(&baralho->v[i].runner, &baralho->v[x].runner);
		shuffle_positionInt(&baralho->v[i].color, &baralho->v[x].color);
	}
}

void getname(player* jogador)
{
	size_t lenght = 0;
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
	FILE* fp;

	setlocale(LC_ALL, "Portuguese.UTF-8");

	char rules[5400];

	fp = fopen("RegrasDoJogo.txt", "r");

	while (fgets(rules, sizeof(rules), fp) != NULL)
		printf("%s", rules);

	fclose(fp);
}

void dealer(player* jogador, deck* baralho)
{
	int i = 0;

	for (i = 0; i < HAND_SIZE; i++)
	{
		jogador->mao.v[i].runner = baralho->v[baralho->m - i - 1].runner;
		jogador->mao.v[i].color = baralho->v[baralho->m - i - 1].color;
	}
	baralho->m -= 6;
	jogador->mao.m = 6;

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

void SetBoard(board* board, player* jogador)
{
	int i, x, rp, ap; // rp - real position , ap = arrow position
	x = 0; // serve como posicao x do retangulo

	for (i = 0; i < 11; i++)
		board->t[i] = 'n'; // posicoes normais;
	board->t[4] = 'r'; board->t[8] = 'r';

	for (i = 0; i < 11; i++) //imprime o tabuleiro
	{
		if (board->t[i] == 'n')
		{
			setColor(MY_COLOR_SOFT_GREEN, MY_COLOR_BLACK);
			showRectAt(x, 0, 6, 7);
		}
		else if (board->t[i] == 'r')
		{
			setColor(MY_COLOR_SOFT_BLUE, MY_COLOR_BLACK);
			show90RectAt(x - 2, 2, 5, 5);
		}
		x += 7;
	}
	setColor(MY_COLOR_WHITE, MY_COLOR_BLACK);

	for (i = 0; i < 5; i++) // Definir a posicao dos animais como 0
		board->a[i] = 0;

	x = 3;
	for (i = 0; i < HAND_SIZE; i++)
	{
		gotoxy(x, 10);
		x += 6;
	}

	x = 0;
	for (i = 0; i < HAND_SIZE; i++) // Colocar Desenho das Cartas
	{
		setColor(jogador->mao.v[i].color, MY_COLOR_BLACK);
		showRectAt(x, 15, 5, 5);
		x += 6;
	}

	x = 0;
	for (i = 0; i < HAND_SIZE; i++) // Colocar Letra do Animal Na Carta
	{
		setColor(MY_COLOR_WHITE, MY_COLOR_BLACK);
		gotoxy(x + 3, 18); printf("%c", jogador->mao.v[i].runner);
		x += 6;
	}
	gotoxy(0, 20); printf("\n");
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

	int i, op = 0;

	deck baralho;
	hand mao;
	player jogadores[2];
	board tabuleiro;

	InitDeck(&baralho);

	switch (menu())
	{
	case 1:
		setFullScreen(true);
		for (i = 0; i < 81; i++)
			printf("%c  ", baralho.v[i].runner);
		printf("\n %d", baralho.m);
		getname(&jogadores[0]);
		for (i = 0; i < 2; i++)
		{
			dealer(&jogadores[i], &baralho);
		}
		// arrowHereV(1, 1);
		for (i = 0; i < HAND_SIZE; i++)
			printf("%c  ", jogadores[1].mao.v[i].runner);

		system("pause");
		system("cls");

		SetBoard(&tabuleiro, &jogadores[0]);
		system("pause");
		break;

	case 2:
		break;
	case 3:
		system("cls");
		ReadFile();
	case 4:
		exit(-1);
	}

}