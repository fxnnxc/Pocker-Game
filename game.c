
/*


		Term Project

		Name    : 포커게임
		Version : 1.01

		작성자   : 박 범진
		학번     : 20165396


*/

#include"function.h"

int main() {

	// 시작화면
	print_table();
	gotoxy(40, 7);
	printf("  FENNEC POKER GAME");
	gotoxy(40, 10);
	printf("PRESS ENTER TO START...");

	// 게임 시작
	playgame();


	// 게임 끝
	print_table();
	gotoxy(40, 7);
	printf("  FENNEC POKER GAME");
	gotoxy(40, 10);
	printf("  ......  END ......");
	gotoxy(40, 15);


	return 0;


}