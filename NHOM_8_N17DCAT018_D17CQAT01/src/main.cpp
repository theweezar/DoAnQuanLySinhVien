#include"lib_init.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// Set console width = 150, console height = 56

int main(int argc, char** argv) { // 1944 dong`
	system("color 0F");
//	font(10,14);
	QLSV *qlsv = new QLSV();
	qlsv->GUI_Menu();
//	qlsv->test();
//	char c = getch();
//	if (c == 0) {
//		c = getch();
//		cout << int(c);
//	}
	// F1: 59, F2: 60, F3: 61, F4: 62, F5: 63, F6: 64
	// left_arrow : 75, right_arrow: 77, up_arrow: 72, down_arrow: 80
	gotoxy(0,45);
	return 0;
}
