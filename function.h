#pragma once


// enum
enum shape{CLOVER, DIAMOND, HEART, SPADE};
enum betting{bet, call, raise, die, all_in};
enum rank{ STRAIGHT_FLUSH, FOUR_OF_KIND, FULL_HOUSE, FLUSH, STRAIGHT, THREE_OF_KIND, TWO_PAIR, ONE_PAIR, HIGH_CARD };
enum isAlive{FALSE, TRUE, ALLIN};
enum choices{RAISE, CALL, DIE, ALL_IN};

// type define
typedef struct card {
	int number;
	enum shape s;
}card, * cardPointer;
typedef struct player {
	int card_number;
	card cards[7];
	card highest_card;
	int rank;
	int money;
	int bet_money;
	int isAlive;
	int choice;
	int Raise_possible;
}player, * playerPointer;

typedef struct dealer {
	card game_card[52];
	int curr_player;
	int betted_money;
	int call_money;
	int turn;
}dealer, *dealerPointer;

// declaration

void make_card(dealerPointer);
void shuffle_card(cardPointer);
void rank_of_player_card(playerPointer); //플레이어가 가진 카드의 랭크를 알려준다. 
void insertion_sort(int*, int*, int);
void playgame();
int bet_computer(playerPointer, dealerPointer);
int bet_player(playerPointer, dealerPointer);

void choice_player(playerPointer, dealerPointer);
void choice_computer(playerPointer, dealerPointer);
void printRank(int);