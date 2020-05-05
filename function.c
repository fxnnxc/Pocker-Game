/*



		게임 진행을 위한 함수 구현 프로그램 실행은 game.c



*/


#define _CRT_SECURE_NO_WARNINGS

#include"function.h"
#include<windows.h>
#include<stdio.h>
#include<time.h>

//define
#define SWAP(A,B,C) (C=A, A=B,B=C)


//Global Variables
dealer d;
player players[3];

// Implementation
void playgame() {
	
	// Dealer manage the game and has cards 
	// player 0 is user. Plyaer 1 and Plyaer2 is a computer
	
	players[0].money = 10000000;
	players[1].money = 10000000;
	players[2].money = 10000000;

	getchar();
	char ch = 'o';
	while (ch == 'o') {
		//setting
		suffling_card_GUI();
		make_card(&d);
		d.betted_money = 0;
		d.curr_player = 0;
		d.call_money = 100;
		shuffle_card(d.game_card);
		for (int i = 0; i < 3; i++) {
			players[i].card_number = 0;
			players[i].isAlive = TRUE;
			players[i].bet_money = 0;
			players[i].choice = -1;
			players[i].rank = 13;
			players[i].Raise_possible = TRUE;
		}

		//play the game
		int turn = 2;
		d.turn = 2;
		int player_number = 3;
		int distributed_card_number = 0;
		int finished = FALSE;
		// 2장의 카드 배분
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 2; j++) {
				players[i].cards[j] = d.game_card[2 * i + j];
				players[i].card_number++;
				distributed_card_number++;
				update(players, &d);
			}
		}

		while (turn <= 7 && player_number > 1) {

			// 배팅
			while (1) {
				for (int i = 0; i < 3; i++) {
					if (players[d.curr_player].isAlive == TRUE) {
						// 선수의 선택
						int choice;
						if (d.curr_player == 0){
						choice_player(&players[d.curr_player], &d);
						}
						else {
							choosing_GUI(50, 7);
							choice_computer(&players[d.curr_player], &d);
						}
						 choice = players[d.curr_player].choice;

						 // RAISE
						if (choice == RAISE) {
							players[d.curr_player].Raise_possible = FALSE;
							if (d.curr_player == 0) {
								d.call_money += bet_player(&players[d.curr_player], &d);
							}
							else {
								d.call_money += bet_computer(&players[d.curr_player], &d);
							}
							players[d.curr_player].bet_money = d.call_money;
						}
						 // CALL
						else if (choice == CALL) {
							if (players[d.curr_player].money < d.call_money) { // ALL IN
								players[d.curr_player].bet_money = players[d.curr_player].money;
								players[d.curr_player].isAlive = ALLIN;
							}
							players[d.curr_player].bet_money = d.call_money;
							
						}
						else if (choice == DIE) {
							players[d.curr_player].bet_money = 0;
							players[d.curr_player].isAlive = FALSE;
							player_number--;
						}
						else {  // ALL IN
							players[d.curr_player].bet_money = players[d.curr_player].money;
							players[d.curr_player].isAlive = ALLIN;
							player_number--;
						}

						update(players, &d);
						if (player_number == 1) { finished = TRUE; break; }
					}
					d.curr_player = (d.curr_player + 1) % 3;
				}
				if (finished) break;
				// 모두 값이 같으면 돈을 걷고 카드배분
				int consensus = TRUE;
				int curr_money;
				for (int i = 0; i < 3; i++) {
					if (players[i].isAlive) {
						curr_money = players[i].bet_money;
					}
				}
				// 모두 베팅값이 같고 0이 아닌지 확인
				for (int i = 0; i < 3; i++) {
					if (players[i].isAlive) {
						if (curr_money == 0 || curr_money != players[i].bet_money)
							consensus = FALSE;
					}
				}

				if (consensus) {
					for (int i = 0; i < 3; i++) {
						if (players[i].isAlive) {
							d.betted_money += players[i].bet_money;
							players[i].money -= players[i].bet_money;
							players[i].bet_money = 0;
						}
					}
					break;
				}
			}
			if (finished) break;
			// RAISE_POSSIBLE 초기화
			for (int i = 0; i < 3; i++) {
				players[i].Raise_possible = TRUE;
			}


			// 카드 배분
			if (turn == 7 || player_number == 1) break;
			for (int i = 0; i < 3; i++) {
				if (players[i].isAlive) {
					players[i].cards[turn] = d.game_card[distributed_card_number + i];
					distributed_card_number++;
					players[i].card_number++;
					update(players, &d);
				}
			}
			turn++;
			d.turn++;
			
			
		} // 1 Game end
		// 돈 배분....
		// 1명 남았을 때.
		if (player_number == 1) {
			for (int i = 0; i < 3; i++) {
				if (players[i].isAlive) {
					players[i].money += d.betted_money;
					d.curr_player = i;
					rank_of_player_card(&players[i]);
				}
			}
		}
		// 여러명 남았을 때.
		else {
			d.turn++;

			for (int i = 0; i < 3; i++) {
				if (players[i].isAlive) {
					d.curr_player = i;
					rank_of_player_card(&players[i]);
				}
			}
			for (int i = 0; i < 3; i++) {
				if (players[i].isAlive) {
					if (players[i].rank < (players[d.curr_player].rank)) {
						d.curr_player = i;
					}
					else if (players[i].rank == (players[d.curr_player].rank)) {
						if (players[i].highest_card.number > (players[d.curr_player].highest_card.number)) {
							d.curr_player = i;
						}
						else if(players[i].highest_card.number == (players[d.curr_player].highest_card.number)){
							if (players[i].highest_card.s > players[d.curr_player].highest_card.number) {
								d.curr_player = i;
							}
						}
					}

				}
			}
			players[d.curr_player].money += d.betted_money;			
		}
		update(players, &d);
		gotoxy(35, 8);
		printf("Winner's rank is ");
		printRank(players[d.curr_player].rank);
		gotoxy(35, 9);
		if(d.curr_player ==0)
			printf("Winner : User");
		else {
				printf("Winner :Computer %d", d.curr_player);
		}
		gotoxy(35, 10);
		printf("Money : +%d", d.betted_money);
		gotoxy(35, 11);
		printf("== NEXT : o | EXIT : x ==");
		gotoxy(35, 12);
		while(1){
			ch = getchar();
			if (ch == 'o' || ch == 'x')
				break;
		}
		
	} // All game end
}


void rank_of_player_card(playerPointer playerPTR)
{
	playerPTR->highest_card.number = 0;
	playerPTR->highest_card.s = 1;
	playerPTR->rank = HIGH_CARD;
	// royal_flush, straight_flush,four_of_kind, full_house, flush, straight, three_of_kind, two_pair, one_pair, high_card
	int numbers[7];
	int shapes[7];
	int card_number = playerPTR->card_number;

	// Store numbers and values --> sort... --> expansion
	for (int i = 0; i < 7; i++) {
		numbers[i] = playerPTR->cards[i].number;
		shapes[i] = playerPTR->cards[i].s;
	}
	insertion_sort(numbers, shapes, card_number);
	// 1. straight_flush
	if (card_number >= 5) {
		int succ = 0;
		int last = 0;
		int last_shape = 0;
		for (int i = 0; i < card_number; i++) {
			if (numbers[i + 1] - numbers[i] == 1) {
				succ++;
				last = numbers[i + 1];
				last_shape = shapes[i + 1];
			}
			if (numbers[i + 1] - numbers[i] >= 2) {
				succ = 0;
			}
		}
		if (succ >= 4) {
			playerPTR->rank = STRAIGHT;
			playerPTR->highest_card.number = last;
			playerPTR->highest_card.s = last_shape;
			int my_shapes[4] = { 0,0,0,0 };
			for (int j = 0; j < card_number; j++) {
				if (shapes[j] == DIAMOND)
					my_shapes[1]++;
				if (shapes[j] == CLOVER)
					my_shapes[0]++;
				if (shapes[j] == HEART)
					my_shapes[2]++;
				if (shapes[j] == SPADE)
					my_shapes[3]++;
			}
			if (my_shapes[1] >= 5 || my_shapes[0] >= 5 || my_shapes[2] >= 5 || my_shapes[3] >= 5) {
				playerPTR->rank = STRAIGHT_FLUSH;
				return;
			}
		}
		// 2. four_of_kind
		if (card_number >= 4) {
			for (int i = 0; i < card_number - 3; i++) {
				if (numbers[i] - numbers[i + 1] == 0 && numbers[i + 1] - numbers[i + 2] == 0 && numbers[i + 2] - numbers[i + 3] == 0) {
					playerPTR->highest_card.number = numbers[i];
					playerPTR->highest_card.s = shapes[i];
					playerPTR->rank = FULL_HOUSE;
				}
			}
			if (playerPTR->rank == FULL_HOUSE)
				return;
		}
		// 3. full_house
		if (card_number >= 5) {
			for (int i = 0; i < card_number - 2; i++) {
				if (numbers[i] - numbers[i + 1] == 0 && numbers[i + 1] - numbers[i + 2] == 0) {
					playerPTR->highest_card.number = numbers[i];
					playerPTR->highest_card.s = shapes[i];
					playerPTR->rank = THREE_OF_KIND;
				}
			}
			if (playerPTR->rank == THREE_OF_KIND) {
				for (int i = 0; i < card_number - 1; i++) {
					if (numbers[i] - numbers[i + 1] == 0 && playerPTR->highest_card.number != numbers[i]) {
						playerPTR->rank = FULL_HOUSE;
					}
				}
				if (playerPTR->rank == FULL_HOUSE)
					return;
			}

		}
		// 4. flush
		if (card_number >= 5) {
			int my_shapes[4] = { 0,0,0,0 };
			for (int i = 0; i < card_number; i++) {
				if (shapes[i] == DIAMOND)
					my_shapes[1]++;
				if (shapes[i] == CLOVER)
					my_shapes[0]++;
				if (shapes[i] == HEART)
					my_shapes[2]++;
				if (shapes[i] == SPADE)
					my_shapes[3]++;
			}
			if (my_shapes[1] >= 5 || my_shapes[0] >= 5 || my_shapes[2] >= 5 || my_shapes[3] >= 5) {
				playerPTR->rank = FLUSH;
				for (int shape = 0; shape < 4; shape++) {
					if (my_shapes[shape] >= 5) {
						for (int i = 0; i < card_number; i++) {
							if (shapes[i] == shape) {
								playerPTR->highest_card.number = numbers[i];
								playerPTR->highest_card.s = shape;
							}


						}
					}
				}
				return;
			}
		}

		// 5. straight
		if (card_number >= 5) {
			int succ = 0;
			int last = 0;
			int last_shape = 0;
			for (int i = 0; i < card_number; i++) {
				if (numbers[i + 1] - numbers[i] == 1) {
					succ++;
					last = numbers[i + 1];
					last_shape = shapes[i + 1];
				}
				if (numbers[i + 1] - numbers[i] >= 2) {
					succ = 0;
				}
			}
			if (succ == 4) {
				playerPTR->rank = STRAIGHT;
				playerPTR->highest_card.number = last;
				playerPTR->highest_card.s = last_shape;
				return;
			}
		}
		// 6. three_of_kind
		if (card_number >= 3) {
			for (int i = 0; i < card_number - 2; i++) {
				if (numbers[i] - numbers[i + 1] == 0 && numbers[i + 1] - numbers[i + 2] == 0) {
					playerPTR->highest_card.number = numbers[i];
					playerPTR->highest_card.s = shapes[i];
					playerPTR->rank = THREE_OF_KIND;
				}
			}
			if (playerPTR->rank == THREE_OF_KIND)
				return;
		}

		// 7. two_pair
		if (card_number >= 4) {
			int count = 0;
			for (int i = 0; i < card_number - 1; i++) {
				if (numbers[i] - numbers[i + 1] == 0) {
					playerPTR->highest_card.number = numbers[i];
					playerPTR->highest_card.s = shapes[i];
					count++;
				}
			}
			if (count >= 2) {
				playerPTR->rank = TWO_PAIR;
				return;
			}
		}

		// 8. one_pair
		if (card_number >= 2) {
			for (int i = 0; i < card_number - 1; i++) {
				if (numbers[i] - numbers[i + 1] == 0) {
					playerPTR->highest_card.number = numbers[i];
					playerPTR->highest_card.s = shapes[i];
					playerPTR->rank = ONE_PAIR;
				}
			}
			if (playerPTR->rank == ONE_PAIR)
				return;
		}

		// 9. high_card
		if (card_number >= 1) {
			playerPTR->highest_card.number = numbers[card_number - 1];
			playerPTR->highest_card.s = shapes[card_number - 1];
			playerPTR->rank = HIGH_CARD;
			return;
		}

	}
}
void make_card(dealer* d1){
	//4가지 문양에 대하여 13개의 카드를 만든다.
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			d1->game_card[i * 13 + j].number =j+2;
			d1->game_card[i * 13 + j].s = i;
		}
	}
}
void shuffle_card(card*c ) {
	srand(time(NULL));
	int a, b;
	card temp;
	for (int i = 0; i < 100; i++) {
		a = rand() % 52;
		b = rand() % 52;
		SWAP(c[a], c[b], temp);
	}
}

int bet_computer(player* p, dealer *d) {
	int money;
	while (1) {
		money = rand() % d->call_money ;
		if (money <= p->money && money <= d->call_money) {
			break;
		}
	}
	return money;
}
int bet_player(player* p, dealer *d) {
	int money, scan;
	printf("돈을 입력하세요>>");
	while (1) {
		scan = scanf("%d", &money);
		while (getchar() != '\n');
		if (money > p->money) {
			printf("돈을 초과할 수 없습니다..");
		}
		else if (scan != 1) {
			printf("정수를 입력하세요..");
		}
		else if (money >  d->call_money) {
			printf("CALL MONEY를 넘을 수 없습니다.");
		}
		else {
			break;
		}
	}
	return money;
}
void choice_player(player* p, dealer* d) {
	gotoxy(0, 0);
	printf("선택하세요 : | RAISE : 0 | CALL : 1 | Die : 2 | ALl in : 3 |");
	rank_of_player_card(p);
	int myChoice, scan;
	while (1) {
		while (1) {  // Get right number
			scan = scanf("%d", &myChoice);
			while (getchar() != '\n');
			if (scan == 1 && myChoice >= 0 && myChoice <= 3)
				break;
		}
		// CALL  할 경우
		if (myChoice == 1) {
			if (d->call_money <= p->money)
				break;
			else {
				print_message("You must all in", 30,8);
				myChoice = 3;
				break;
			}
		}
		// RAISE 할 경우
		if (myChoice == 0) {
			if (d->call_money >= p->money || p->Raise_possible == FALSE)
				print_message("You can't raise. CALL or DIE",30,8);
			else {
				break;
			}
		}
		if (myChoice == 2) { //DIE
			break;
		}
		if (myChoice == 3) // ALL IN
		{
			if (d->call_money > p->money)
				break;
			else {
				printf("Call을 할 수 있으므로 All in 을 할 수 없습니다.");
			}
		}
			
	}
	p->choice = myChoice;
}
void choice_computer(player* p, dealer* d) {
	int myChoice;
	rank_of_player_card(p);
	while (1) {
		int random = rand() % 100;
		printf("%d", random);
		if (p->rank <= FULL_HOUSE) {
			if (random < 68)
				myChoice = RAISE; //Raise 68%
			else if (random < 98)
				myChoice = CALL;  //Call 30%
			else
				myChoice = DIE;   //Die 2%
		}
		else if (p->rank <= THREE_OF_KIND) {
			if (random < 40)
				myChoice = RAISE; //Raise 40%
			else if (random < 90)
				myChoice = CALL;  //Call 50%
			else
				myChoice = DIE;   //Die 10%
		}
		else if (p->rank < HIGH_CARD) {
			if (random < 30)
				myChoice = RAISE; //Raise 30%
			else if (random < 85)
				myChoice = CALL;  //Call 55%
			else
				myChoice = DIE;   //Die 15%
		}
		else {
			if (d->turn < 3) {
				if (random < 10)
					myChoice = RAISE; //Raise 10%
				else if (random < 90)
					myChoice = CALL;  //Call 70%
				else
					myChoice = DIE;   //Die 10%
			}
			else if (d->turn < 5) {
				if (random < 10)
					myChoice = RAISE; //Raise 10%
				else if (random < 90)
					myChoice = CALL;  //Call 60%
				else
					myChoice = DIE;   //Die 30%
			}
			else {
				if (random < 10)
					myChoice = RAISE; //Raise 10%
				else if (random < 70)
					myChoice = CALL;  //Call 70%
				else
					myChoice = DIE;   //Die 30%
			}
		}
		// CALL  할 경우
		if (myChoice == 1) {
			if (d->call_money <= p->money)
				break;
			else {
				myChoice = 3;
				break;
			}

		}
		// RAISE 할 경우
		if (myChoice == 0) {
			if (d->call_money >= p->money || p->Raise_possible == FALSE) {}
			else {
				break;
			}
		}
		if (myChoice == 2) { //DIE
			break;
		}
	}
	p->choice = myChoice;
}

// sorting 
void insertion_sort(int* numbers, int* shapes, int n) {
	int temp, temp_shape, i, j;
	for (i = 1; i < n; i++) {
		temp = numbers[i];
		temp_shape = shapes[i];
		for (j = i - 1; numbers[j] > temp && j >= 0; j--) {
			numbers[j + 1] = numbers[j];
			shapes[j + 1] = shapes[j];
		}
		numbers[j + 1] = temp;
		shapes[j + 1] = temp_shape;
	}
}

void printRank(int rank) {
	if (rank == STRAIGHT_FLUSH)
		printf("STRAIGHT_FLUSH");
	if (rank == FOUR_OF_KIND)
		printf("FOUR_OF_KIND");
	if (rank == FULL_HOUSE)
		printf("FULL_HOUSE");
	if (rank == FLUSH)
		printf("FLUSH");
	if (rank == STRAIGHT)
		printf("STRAIGHT");
	if (rank == THREE_OF_KIND)
		printf("THREE_OF_KIND");
	if (rank == TWO_PAIR)
		printf("TWO_PAIR");
	if (rank == ONE_PAIR)
		printf("ONE_PAIR");
	
}