#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <wchar.h>
#include <io.h>
#include <fcntl.h>

#define length  25
#define width   80
#define true     1
#define false    0

typedef struct XY_str
{
	int x;
	int y;
}XY_str;     XY_str sBody[2500]; // range = 20*50 = 1000

void gotoxy(int xpos, int ypos)

{

	COORD scrn;

	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

	scrn.X = xpos + 8; scrn.Y = ypos + 1;       //調整起始位置

	SetConsoleCursorPosition(hOuput, scrn); //設定游標位置

}
void showCursor(int visible)
{
	CONSOLE_CURSOR_INFO ConCurInf;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleCursorInfo(hStdOut, &ConCurInf);

	ConCurInf.bVisible = visible;

	SetConsoleCursorInfo(hStdOut, &ConCurInf);

}
void Snake(int bodylenhgt, int foodcolor)
{
	int color[2000] = { 0 };
	for (int i = 0; i < bodylenhgt; i++)
	{
		if (i<1)
		{
			gotoxy(sBody[i].x, sBody[i].y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 0X032);
			wprintf(L"■");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 0X0f);
		}
		else
		{
			color[i] = foodcolor;
			gotoxy(sBody[i].x, sBody[i].y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 0X0E);
			wprintf(L"■");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 0X0f);
		}

	}
}
void Wall()
{
	int i, j;
	for (i = 0; i<length; i++)
	{
		for (j = 0; j<width + 1; j += 2)
		{
			if (i == 0 || i == length - 1 || j == 0 || j == width)
			{
				gotoxy(j, i);
				wprintf(L"■");
			}

		}

	}

}
void Information(int food, int speed)
{
	gotoxy(width + 4, 7);
	wprintf(L"Use P to pause.");
	gotoxy(width + 4, 9);
	wprintf(L"Grade: %d", food * 10);
	gotoxy(width + 4, 11);
	wprintf(L"Speed: %3d            ", 97 - speed);
}
void setSite(int i, int site_x, int site_y)
{
	sBody[i].x = site_x;
	sBody[i].y = site_y;
}
void setStartSite()
{
	int i;
	sBody[0].x = sBody[1].x = sBody[2].x = sBody[3].x = sBody[4].x = 2;
	for (i = 0; i<5; i++) sBody[i].y = abs(5 - i);
}




int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);   //使用Unicode
	XY_str foodSite, coor, last;

	int startBodyLenght = 5, startFood = 0, bodyLenght, Food;
	int keyinFirst, keyinSecond;
	int i, j, gameOver = false, FoodAppear = false, xyChanged = false;
	int path = 2; // 方向
	int SnakeSpeed = 100;
	int foodcolor;
	char gameKey = 'y';
	srand(time(NULL));
	showCursor(0);

	foodcolor = (rand() % 4) + 1;

	while (1)
	{

		if (gameKey == 'n' || gameKey == 'N') break;

		setStartSite();
		Wall();
		bodyLenght = startBodyLenght;
		Food = startFood;
		SnakeSpeed = 100;
		coor.x = 2;
		coor.y = 4;
		path = 2;
		FoodAppear = false;
		gameOver = false;
		xyChanged = false;
		Information(startFood, SnakeSpeed);
		Snake(bodyLenght, foodcolor);

		do{
			gotoxy(width + 4, 13);
			wprintf(L"Enter to start.");
			gameKey = _getch();
			gotoxy(width + 4, 13);
			wprintf(L"               ");
		} while (gameKey != 13);

	}
	return 0;
}