
/*


		Term Project

		Name    : ��Ŀ����
		Version : 1.01

		�ۼ���   : �� ����
		�й�     : 20165396


*/

#include"function.h"

int main() {

	// ����ȭ��
	print_table();
	gotoxy(40, 7);
	printf("  FENNEC POKER GAME");
	gotoxy(40, 10);
	printf("PRESS ENTER TO START...");

	// ���� ����
	playgame();


	// ���� ��
	print_table();
	gotoxy(40, 7);
	printf("  FENNEC POKER GAME");
	gotoxy(40, 10);
	printf("  ......  END ......");
	gotoxy(40, 15);


	return 0;


}