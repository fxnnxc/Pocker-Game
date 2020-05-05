#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include"function.h"

struct SMALL_RECT {
	SHORT Left;
	SHORT Top;
	SHORT Right;
	SHORT Bottom;
};

void update(playerPointer, dealerPointer);
void print_card(card);
void gotoxy(int, int);
void print_table();
void adjustWindowSize();
void suffling_card_GUI();
void print_message(char[]);