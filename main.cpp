#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS_GLOBALS
#define _CRT_NONSTDC_NO_WARNINGS
#define _getch getch // para o getch funcionar

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <lab.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>

#define DECK_SIZE 81

/*
void dealer()
{
	
}
*/

void shuffle_position(char *x, char *y)
{
	char aux;
	aux = *x;
	*x = *y;
	*y = aux;
}

/*
void shuffle(char *w)
{
}
*/

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

int main(void)
{
	setlocale(LC_ALL, "Portuguese");
	
	char deck[DECK_SIZE];
	char teste[50];
	char *a= teste;
	int op = -1;
	int position = 1;
	int keypressed = 0;

	do
	{
		gotoxy(50, 5); arrowHere(1, position); printf("1 - Novo Jogo\n");
		gotoxy(50, 6); arrowHere(2, position); printf("2 - Carregar Jogo\n");
		gotoxy(50, 7); arrowHere(3, position); printf("3 - Sair\n");
		
		//scanf("%d", &op);
		//getch();
		keypressed = getch();
		if (keypressed == 80 && position!=3)
		{
			position++;
		}
		else if (keypressed == 72 && position!=1)
		{
			position--;
		}
	} while (keypressed != 13);

		switch (position)
		{
		case 1:
			printf("teste");
			break;

		case 2:
			break;
		case 3:
			exit(-1);
		}
	

	// fgets(teste, sizeof(teste), stdin); // gets nao funcionava, com o fgets funciona, utilizar stdin no fim para ler isto caso contrario ler do ficheiro que for

	//showRectCenteredAt(0, 20, 30, 30);
	// printfAt(50, 5, a);

}
