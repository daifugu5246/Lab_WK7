#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<conio.h>
#include <windows.h>
#include <time.h>

char ch = ' ';
int x = 38, y = 30;
int x_star, y_star;
int score=0;
char direction = 's';
int Mag, i = 0;
int bulletstat[5] = { 0,0,0,0,0 };
int bulpos_x[5], bulpos_y[5];

void showScore(int x,int y,int s);
char cursor(int x, int y);
void draw_star(int x, int y);
void erase_star(int x, int y);
void draw_ship(int x, int y);
void erase_ship(int x, int y);
void bullet(int x, int y);
void setcursor(bool visible);
void setcolor(int fg, int bg);
void erase_bullet(int x, int y);
void bulletLaunch(int Mag);
void move(char direction);

int main()
{
	setcursor(0);
	showScore(79, 1, score);
	srand(time(NULL));
	for (int i = 0; i < 20; i++) {
		x_star = 10 + rand() % 60;
		y_star = 2 + rand() % 5;
		draw_star(x_star, y_star);
	}
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a' || ch == 'A')
			{
				direction = 'a';
			}
			if (ch == 'd' || ch == 'D')
			{
				direction = 'd';
			}
			if (ch == 's' || ch == 'S')
			{
				direction = 's';
			}
			if (bulletstat[i] != 1 && ch == ' ' && bulletstat[i] == 0)
			{
				bulletstat[i] = 1;
				bulpos_x[i] = x + 4;
				bulpos_y[i] = y - 1;
				if (i <= 4) {
					i++;
				}
				if (i > 4) {
					i = 0;
				}
			}
			fflush(stdin);
		}
		for (int j = 0; j <= 4; j++)
			bulletLaunch(j);
		move(direction);
		Sleep(30);
	} while (ch != 'x');
	return 0;
}
void showScore(int x, int y,int s) {
	if (x >= 0 && x <= 80 && y >= 1 && y <= 30) {
		COORD pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		setcolor(3, 0);
		printf("SCORE : %d",s);
	}
}
char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
		return buf[0];

}
void draw_ship(int x, int y)
{
	if (x >= 0 && x <= 80 && y >= 1 && y <= 30) {
		COORD pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		setcolor(15, 0);
		printf(" _|=^=|_ ");
	}
}
void draw_star(int x, int y)
{
	if (x >= 0 && x <= 80 && y >= 1 && y <= 30) {
		COORD pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		setcolor(13, 0);
		printf("*");
	}
}
void erase_ship(int x, int y)
{
	if (x >= 0 && x <= 80 && y >= 1 && y <= 30) {
		COORD pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		setcolor(0, 0);
		printf("         ");
	}
}
void erase_bullet(int x, int y)
{
	if (x >= 0 && x <= 80 && y >= 1 && y <= 30) {
		COORD pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		setcolor(0, 0);
		printf(" ");
	}
}
void erase_star(int x, int y)
{
	if (x >= 0 && x <= 80 && y >= 1 && y <= 30) {
		COORD pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		setcolor(0, 0);
		printf(" ");
	}
}
void bullet(int x, int y)
{
	if (x >= 0 && x <= 80 && y >= 1 && y <= 30) {
		COORD pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		setcolor(12, 0);
		printf("=");
	}
}
void bulletLaunch(int Mag)
{
	if (bulletstat[Mag] == 1)
	{
		erase_bullet(bulpos_x[Mag], bulpos_y[Mag]);
		if (bulpos_y[Mag] > 0 && cursor(bulpos_x[Mag], bulpos_y[Mag] - 1) != '*')
		{
			bullet(bulpos_x[Mag], --bulpos_y[Mag]);
		}
		else if ( cursor(bulpos_x[Mag], bulpos_y[Mag] - 1) == '*')
		{
			erase_star(bulpos_x[Mag], bulpos_y[Mag] - 1);
			Beep(500, 230);
			score++;
			srand(time(NULL));
			x_star = 10 + rand() % 60;
			y_star = 2 + rand() % 5;
			draw_star(x_star, y_star);
			showScore(79, 1, score);
			bulletstat[Mag] = 0;
		}
		else if (bulpos_y[Mag] <= 0 )
		{
			bulletstat[Mag] = 0;
		}
	}
}
void move(char  direct)
{
	if (direct == 'a' && x > 0) {
		erase_ship(x, y);
		draw_ship(--x, y);
	}
	else if (direct == 'd' && x < 80) {
		erase_ship(x, y);
		draw_ship(++x, y);
	}
	else if (direct == 's')
	{
		erase_ship(x, y);
		draw_ship(x, y);
	}
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}