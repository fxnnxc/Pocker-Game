/*


	
		화면 출력을 위한 함수 구현 프로그램 실행은 game.c



*/


#include"function.h"
#include"GUI.h"
#include<windows.h>
#include<stdio.h>
#include<time.h>


void print_table() {
	adjustWindowSize();
	gotoxy(0, 0);
	printf(" -------------------------------------------------------------------------------------------------------\n");
	printf("|                                                                                                       |\n");
	printf("|                                                                                                       |\n");
	printf("|                                                                                                       |\n");
	printf("|                                                                                                       |\n");
	printf("|                                                                                                       |\n");
	printf("|                                                                                                       |\n");
	printf("|                                                                                                       |\n");
	printf("|                                                                                                       |\n");
	printf("|                                                                                                       |\n");
	printf("|                                                                                                       |\n");
	printf("|                                                                                                       |\n");
	printf("|                                                                                                       |\n");
	printf("|                                                                                                       |\n");
	printf("|                                                                                                       |\n");
	printf("|                                                                                                       |\n");
	printf("|                                                                                                       |\n");
	printf("|                                                                                                       |\n");
	printf("|                                                                                                       |\n");
	printf("|                                                                                                       |\n");
	printf("|                                                                                                       |\n");
	printf("|_______________________________________________________________________________________________________|\n");
}
void print_state(player plyaers[]) {
	

}
void print_card(card c, int hiding, int x, int y) {
	if (hiding == 0) {
		char shape_list[][3] = { "♣", "◆", "♥","♠" };
		char chr = 0;
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
		case 10:
			chr = '1';
			break;
		default:
			chr = c.number + '0';
			break;
		}

		gotoxy(x, y);
		printf(" ____");
		gotoxy(x, y + 1);
		if (c.number == 10)
			printf("|10  |");
		else
			printf("|%c   |", chr);
		gotoxy(x, y + 2);
		printf("| %1s |", shape_list[c.s]);
		gotoxy(x, y + 3);
		if (c.number == 10)
			printf("|__10|");
		else
			printf("|___%c|", chr);
	}
	else {
		gotoxy(x, y);
		printf(" ____\n");
		gotoxy(x, y + 1);
		printf("|    |\n");
		gotoxy(x, y + 2);
		printf("| ?? |\n");
		gotoxy(x, y + 3);
		printf("|____|\n");
	}
	gotoxy(0, 0);

}
void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}



void adjustWindowSize()
{
	struct SMALL_RECT test;

	HANDLE hStdout;
	COORD coord;
	BOOL ok;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	coord.X = 30;
	coord.Y = 30;
	ok = SetConsoleScreenBufferSize(hStdout, coord);

	test.Left = 0;
	test.Top = 0;
	test.Right = coord.X - 1;
	test.Bottom = coord.Y - 1;

	SetConsoleWindowInfo(hStdout, ok, &test);

}

void update(player players[], dealer* d) {
	print_table();
	//print computer 1 
	player com = players[1];
	for (int i = 0; i < com.card_number; i++) {
		if ((i == 0 || i == 1)&&(d->turn < 8))
			print_card(com.cards[i], 1, 14 + 4 * i, 5);
		else
			print_card(com.cards[i], 0, 0 + 4 * i, 2);
	}
	char string[10];
	gotoxy(0, 9);
	printf("computer 1\n");
	printf("money   : %d\n", players[1].money);
	printf("betting : %d\n", players[1].bet_money);
	if (players[1].choice ==DIE)
		strcpy(string, "DIE");
	else {
		if (players[1].choice == ALLIN)
			strcpy(string, "ALL IN");
		else {
			if (players[1].choice == CALL) {
				strcpy(string, "CALL");
			}
			else if(players[1].choice == RAISE) {
				strcpy(string, "RAISE");
			}
			else {
				strcpy(string, "");
			}
		}
	}
	printf("state   : %s", string);

	//print computer 2
	com = players[2];

	for (int i = 0; i < com.card_number; i++) {
		if ((i == 0 || i == 1) && (d->turn < 8))
			print_card(com.cards[i], 1, 86 + 4 * i, 5);
		else
			print_card(com.cards[i], 0, 72 + 4 * i, 2);
	}
	gotoxy(86, 9);
	printf("computer 2\n");
	gotoxy(86, 10);
	printf("money   : %d\n", players[2].money);
	gotoxy(86, 11);
	printf("betting : %d\n", players[2].bet_money);
	gotoxy(86, 12);
	if (players[2].choice == DIE)
		strcpy(string, "DIE");
	else {
		if (players[2].choice == ALLIN)
			strcpy(string, "ALL IN");
		else {
			if (players[2].choice == CALL) {
				strcpy(string, "CALL");
			}
			else if (players[2].choice == RAISE) {
				strcpy(string, "RAISE");
			}
			else {
				strcpy(string, "");
			}
		}
	}
	printf("state   : %s", string);

	//print user
	com = players[0];
	
	for (int i = 0; i < com.card_number; i++) {
		if (i == 0 || i == 1)
			print_card(com.cards[i], 0, 46 + 4 * i, 15);

		else
			print_card(com.cards[i], 0, 32 + 4 * i, 12);
	}
	gotoxy(60, 16);
	printf("User");
	gotoxy(60, 17);
	printf("money   : %d\n", players[0].money);
	gotoxy(60, 18);
	printf("betting : %d\n", players[0].bet_money);
	gotoxy(60, 19);
	if (players[0].choice == DIE)
		strcpy(string, "DIE");
	else {
		if (players[0].choice == ALLIN)
			strcpy(string, "ALL IN");
		else {
			if (players[0].choice == CALL) {
				strcpy(string, "CALL");
			}
			else if (players[0].choice == RAISE) {
				strcpy(string, "RAISE");
			}
			else {
				strcpy(string, "");
			}
		}
	}
	printf("state   : %s", string);


	// print dealer
	gotoxy(50, 2);
	printf("call  money : %d", d->call_money);
	gotoxy(50, 3);
	printf("Total money : %d", d->betted_money);

	gotoxy(50, 4);
	
	for (int i = 0; i < 100000000; i++) {
		if(i%25000000 ==0)
			printf(".");
	}

}

void suffling_card_GUI() {

		gotoxy(40, 10);
		printf("Suffling Cards");
		gotoxy(40, 11);
	for (int i = 0; i < 100000000; i++) {
		if (i % 25000000 == 0)
			printf(".");
	}
	gotoxy(40, 10);
	printf("                 ");
	gotoxy(40, 11);
	printf("                 ");

};


void choosing_GUI(int x, int y) {
	gotoxy(x, y-1);
	printf("A computer is considering");
	for (int j = 0; j < 3; j++) {
		gotoxy(x, y);
		for (int i = 0; i < 100000000; i++) {
			if (i % 25000000 == 0)
				printf(".");
		}
	}
	gotoxy(x, y);
	printf("     ");
}

void print_message(char s[], int x, int y) {
	gotoxy(x, y);
	puts(s);
}