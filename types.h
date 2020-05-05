#pragma once

enum shape{clover, diamond, heart, spade};
enum betting{check, bet, call, raise, die, all_in};
enum rank{ straight_flush, full_house, flush, straight, trips, two_pairs, one_pair, high_card };


void print_card(card, int);
void playgame();

typedef struct card {
	int number;
	enum shape s;
}card;

typedef struct player {
	int card_number;
	card cards[7];
	double money;
	double bet_money;
}player;

typedef struct dealer {
	card game_card[52];
	player curr_player;
	double betted_money;
	double call_money;

}dealer;