#ifndef GRAPHS_H
#define GRAPHS_H
#define BLACK 0
#define DARKBLUE 1
#define DARKGREEN 2
#define DARKCYAN 3
#define DARKRED 4
#define DARKPINK 5
#define DARKYELLOW 6
#define WHITESMOKE 7
#define GRAY 8
#define BLUE 9
#define GREEN 10
#define CYAN 11
#define RED 12
#define PINK 13
#define YELLOW 14
#define WHITE 15
#define str(x) char(x)


void gotoxy(int x,int y);
void getxy(int &x,int &y);
void Cursor(bool on);
int GetConsoleWidth();
int GetConsoleHeight();
void resizeConsole();
void setFullscreen();
void disableMinimize();
void setColor(int x);
//void font(int width,int height);
void listColor();
void drawTitle_1(int START_X, int START_Y);
void drawTitle_2(int START_X, int START_Y);
void drawTitle_3(int START_X, int START_Y);
void floatText(int x, int y);
void drawRect(int START_X, int START_Y, int width, int height);
void drawFillRect(int START_X, int START_Y, int width, int height, int color);
void drawText(int x, int y, string text, int color);
void drawNumber(int x, int y, int number, int color);
void draw_high_line(int START_X,int START_Y,int height);
void draw_flat_line(int START_X,int START_Y,int width);
void clearRect(int X,int Y,int width,int height);
void frame_not_choose_item(int x, int y, string item_name, int color);
void frame_choose_item(int x, int y, string item_name, int color);
void drawButton(int x, int y, int color, int width, int ascii, string name, string do_what); // ascii or name, chi chon 1 trong 2 cai
void Message(string msg, int color);
void clearMessage();
void VeDauCongChiaDoi();

void gotoxy(int x,int y){
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void getxy(int &x, int&y) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {	
		x = csbi.dwCursorPosition.X;
		y = csbi.dwCursorPosition.Y;		
	}
}
void Cursor(bool on){
	CONSOLE_CURSOR_INFO info; info.dwSize = 10;
	if (on) info.bVisible = TRUE;
	else info.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
int GetConsoleWidth(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return width;
}
int GetConsoleHeight(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return height;
}
void resizeConsole(){ // w = 150, h = 56;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//	COORD t = GetLargestConsoleWindowSize(hConsole); // Lay max width, height cua~ console
	// ==================== Set SCREEN CONSOLE BUFFER ========================= //
	COORD dwSize;
	dwSize.X = 150;
	dwSize.Y = 56;
	SetConsoleScreenBufferSize(hConsole,dwSize);
	// ==================== Set WINDOW SIZE Cach 1 ====================== //
//	SMALL_RECT windowSize = {0, 0, 150, 55};
//	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
    SetConsoleTitle("CHUONG TRINH QUAN LY SINH VIEN");
    // ==================== Set WINDOW SIZE Cach 2 ====================== //
    HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1250 , 720 , TRUE); // 1220x715
}
void setFullscreen(){
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_MAXIMIZE);
}
void disableMinimize(){
	HWND hwnd = GetConsoleWindow();
	DWORD style = GetWindowLong(hwnd, GWL_STYLE);
	style &= ~WS_MAXIMIZEBOX;
	SetWindowLong(hwnd, GWL_STYLE, style);
	SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE|SWP_FRAMECHANGED);
}
void setColor(int x){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
}
//void font(int width,int height){
//	CONSOLE_FONT_INFOEX cfi;
//	cfi.cbSize = sizeof(cfi);
//	cfi.nFont = 0;
//	cfi.dwFontSize.X = width;                   // Width of each character in the font
//	cfi.dwFontSize.Y = height;                  // Height
//	cfi.FontFamily = FF_DONTCARE;
//	cfi.FontWeight = FW_NORMAL;
//	wcscpy(cfi.FaceName, L"Raster Fonts"); // Choose your font
//	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
//}

void listColor(){
	for(int i=0;i<=255;i++){
		setColor(15);
		printf("%3d :",i);
		setColor(i);
		cout <<"This is color"<<endl;
	}
	setColor(15);
}

void drawTitle_1(int START_X, int START_Y){
	drawText(START_X,START_Y,  " __  __                  ",RED);
	drawText(START_X,START_Y+1,"|  \\/  |                 ",RED);
	drawText(START_X,START_Y+2,"| \\  / | ___ _ __  _   _ ",BLUE);
	drawText(START_X,START_Y+3,"| |\\/| |/ _ \\ '_ \\| | | |",PINK);
	drawText(START_X,START_Y+4,"| |  | |  __/ | | | |_| |",BLUE);
	drawText(START_X,START_Y+5,"|_|  |_|\\___|_| |_|\\__,_|",RED);
}

void drawTitle_2(int START_X, int START_Y){
	int align = 3; 
	setColor(11);
	gotoxy(START_X+align,START_Y);
	printf("######               #           ");
	gotoxy(START_X+align,START_Y+1);
	printf("#     #  ####       # #   #    # ");
	gotoxy(START_X+align,START_Y+2);
	printf("#     # #    #     #   #  ##   # ");
	gotoxy(START_X+align,START_Y+3);
	printf("#     # #    #    #     # # #  # ");
	gotoxy(START_X+align,START_Y+4);
	printf("#     # #    #    ####### #  # # ");
	gotoxy(START_X+align,START_Y+5);
	printf("#     # #    #    #     # #   ## ");
	gotoxy(START_X+align,START_Y+6);
	printf("######   ####     #     # #    # ");
	setColor(14);
	START_Y += 9;
	gotoxy(START_X,START_Y);
	printf(" #####  #       ######   #####  #     # ");
	gotoxy(START_X,START_Y+1);
	printf("#     # #       #     # #     # #     # ");
	gotoxy(START_X,START_Y+2);
	printf("#     # #       #     # #       #     # ");
	gotoxy(START_X,START_Y+3);
	printf("#     # #       #     #  #####  #     # ");
	gotoxy(START_X,START_Y+4);
	printf("#   # # #       #     #       #  #   #  ");
	gotoxy(START_X,START_Y+5);
	printf("#    #  #       #     # #     #   # #   ");
	gotoxy(START_X,START_Y+6);
	printf(" #### # ####### ######   #####     #    ");
	setColor(5);
	gotoxy(START_X+7,START_Y+9);
	printf("<--- Press something --->");
	gotoxy(0,0);
	getch();
	setColor(15);
}

void drawTitle_3(int START_X, int START_Y){
	drawText(START_X,START_Y,  "  _____                            ____                      _             _____  _                   _____ _       _      __      ___            ",CYAN);
	drawText(START_X,START_Y+1," |  __ \\            /\\            / __ \\                    | |           |  __ \\(_)                 / ____(_)     | |     \\ \\    / (_)           ",CYAN);
	drawText(START_X,START_Y+2," | |  | | ___      /  \\   _ __   | |  | |_   _  __ _ _ __   | |    _   _  | |  | |_  ___ _ __ ___   | (___  _ _ __ | |__    \\ \\  / / _  ___ _ __  ",CYAN);
	drawText(START_X,START_Y+3," | |  | |/ _ \\    / /\\ \\ | '_ \\  | |  | | | | |/ _` | '_ \\  | |   | | | | | |  | | |/ _ \\ '_ ` _ \\   \\___ \\| | '_ \\| '_ \\    \\ \\/ / | |/ _ \\ '_ \\ ",CYAN);
	drawText(START_X,START_Y+4," | |__| | (_) |  / ____ \\| | | | | |__| | |_| | (_| | | | | | |___| |_| | | |__| | |  __/ | | | | |  ____) | | | | | | | |    \\  /  | |  __/ | | |",CYAN);
	drawText(START_X,START_Y+5," |_____/ \\___/  /_/    \\_\\_| |_|  \\___\\_\\\\__,_|\\__,_|_| |_| |______\\__, | |_____/|_|\\___|_| |_| |_| |_____/|_|_| |_|_| |_|     \\/   |_|\\___|_| |_|",CYAN);
	drawText(START_X,START_Y+6,"                                                                    __/ |                                                                         ",CYAN);
	drawText(START_X,START_Y+7,"                                                                   |___/                                                                          ",CYAN);
}

void floatText(int x, int y){
//	drawRect(x,y,)
}

void drawRect(int START_X, int START_Y, int width, int height){
	int END_X = START_X + width, END_Y = START_Y + height ;
	gotoxy(START_X,START_Y);
	printf("%c",218);
	// Draw left border
	for(int y = START_Y+1; y < END_Y; y++){
		gotoxy(START_X,y);
		printf("%c",179);
	}
	gotoxy(START_X,END_Y);
	printf("%c",192);
	// Draw bottom border
//	for(int x = START_X+1; x < END_X; x++){
//		gotoxy(x,END_Y);
//		printf("%c",196);
//	}
	gotoxy(START_X+1,END_Y); // 2 dong` nay` la` cach 2, neu bi loi~ thi uncomment may dong for trong nay`
	cout << string(width-1,char(196));
	gotoxy(END_X,END_Y);
	printf("%c",217);
	// Draw right border
	for(int y = END_Y-1; y > START_Y; y--){
		gotoxy(END_X,y);
		printf("%c",179);
	}
	gotoxy(END_X,START_Y);
	printf("%c",191);
	// Draw up border
//	for(int x = END_X-1; x > START_X; x--){
//		gotoxy(x,START_Y);
//		printf("%c",196);
//	}
	gotoxy(START_X+1,START_Y); // 2 dong` nay` la` cach 2
	cout << string(width-1,char(196));
}

void drawFillRect(int START_X, int START_Y, int width, int height, int color){
	string r;
	setColor(color*16 + color);
	for(int x = 0 ; x < width ; x++) r.push_back(' ');
	for(int y = START_Y ; y < START_Y + height ; y++){
		gotoxy(START_X,y);
		cout << r;
	}
	setColor(15);
}

void drawText(int x, int y, string text, int color){
	setColor(color);
	gotoxy(x,y);
	cout << text;
	setColor(15);
}

void drawNumber(int x, int y, int number, int color){
	setColor(color);
	gotoxy(x,y);
	printf("%d",number);
	setColor(15);
}

void draw_high_line(int START_X,int START_Y,int height){
	gotoxy(START_X,START_Y);
	printf("%c",194);
	for(int y = START_Y+1; y < START_Y + height; y++){
		gotoxy(START_X,y);
		printf("%c",179);
	}
	gotoxy(START_X,START_Y + height);
	printf("%c",193);
}

void draw_flat_line(int START_X,int START_Y,int width){
	gotoxy(START_X,START_Y);
	printf("%c",195);
//	for(int x = START_X + 1; x < START_X + width; x++){
//		gotoxy(x,START_Y);
//		printf("%c",196);
//	}
	cout << string(width,char(196)); // Dong` nay` la cach 2
	gotoxy(START_X+width,START_Y);
	printf("%c",180);
}

void clearRect(int X,int Y,int width,int height){
//	for(int y = Y; y < Y + height; y++){
//		for(int x = X; x < X + width; x++){
//			gotoxy(x,y);
//			printf(" ");
//		}
//	}
	// ==================== ========================= //
//	string flat;
//	for(int x = X; x < X + width; x++) flat.push_back(' ');
	for(int y = Y; y < Y + height; y++){
		gotoxy(X,y);
//		printf("%s",flat.c_str());
		cout << string(width,' ');
	}
}

void frame_not_choose_item(int x, int y, string item_name, int color){
	setColor(0);
	drawRect(x,y,50,4);
	gotoxy(x+25-item_name.size()/2,y+2);
	setColor(color);
	cout << item_name;
	setColor(15);
}

void frame_choose_item(int x, int y, string item_name, int color){
	setColor(color);
	drawRect(x,y,50,4);
	gotoxy(x+25-item_name.size()/2,y+2);
	cout << item_name;
	setColor(15);
}

void drawButton(int x, int y, int color, int width, int ascii, string name, string do_what){
	setColor(color);
	drawRect(x,y, width, 2); // x,y
	// x+2, y+1
	if (name.size() != 0){
		if (width%2==0) gotoxy(x+width/2-name.size()/2,y+1);
		else gotoxy(x+width/2-name.size()/2+1,y+1);
		cout << name;
	}
	if (name.size() == 0){
		gotoxy(x+width/2,y+1);
		printf("%c",ascii);
	}
	gotoxy(x+width+2,y+1); // x+8, y+1
	cout << do_what;
	setColor(15);
	gotoxy(0,0);
}

void Message(string msg, int color){
	drawText(2*GetConsoleWidth()/3+24 - msg.size()/2,GetConsoleHeight()-4,msg,color);
} // 2*GetConsoleWidth()/3+24, GetConsoleHeight()-4

void clearMessage(){
	clearRect(2*GetConsoleWidth()/3-2,GetConsoleHeight()-4,52,1);
}

void VeDauCongChiaDoi(){
	draw_high_line(GetConsoleWidth()/2,0,GetConsoleHeight()-1);
	draw_flat_line(0,GetConsoleHeight()/2,GetConsoleWidth()-1);
}
#endif
