#include"function.h"
#include<windows.h>
#include<stdio.h>




void playgame();
void print_table(dealer, player[]);
void print_com_cards(player*);
void gotoxy(int x, int y);
void print_card(card, int);


void print_table(dealer d, player players[]) {
	printf("-------------------------------------------------------------------------------------------------------------------------");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");
	printf("|                                                                                                                        |");

	printf("-----------------------------------------------------------------------");

}

void print_com_cards(player* c) {
	
}


void print_card(card c, int hiding) {
		char shape_list[4] = { '¢À', '¡ß', '¢¾','¢¼' };
		if (hiding == 0) {
			char chr;
			switch (c.number) {
			case 14:
				chr = 'A';
				break;
			case 11:
				chr = 'J';
				break;
			case 12:
				chr = 'Q';
				break;
			case 13:
				chr = 'K';
				break;
			default:
				chr = c.number + '0';
			}
			printf("\n");
			printf(" _____\n");
			printf("|%c    |\n", chr);
			printf("|  %c   |\n", shape_list[c.s]);
			printf("|    %c|\n", chr);
			printf(" ----- \n");
		}
		else {
			printf("\n");
			printf(" _____\n");
			printf("|     |\n");
			printf("|  c  |\n", shape_list[c.s]);
			printf("|     |\n", chr);
			printf(" ----- \n");
		}
}	

void playgame() {


}

void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}