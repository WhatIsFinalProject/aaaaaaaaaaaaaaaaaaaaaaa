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
}XY_str;   

XY_str sBody[2500]; 


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

void printWall(){

	int i, j;


	for (i = 0; i<length; i++){

		for (j = 0; j<width + 1; j += 2){

			if (i == 0 || i == length - 1 || j == 0 || j == width)
			{
				gotoxy(j, i);
				_setmode(_fileno(stdout), _O_U16TEXT);   //使用Unicode
				wprintf(L"■");

			}

		}

	}

}

void printSnake(int i){

	gotoxy(sBody[i].x, sBody[i].y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 0X0e);
	_setmode(_fileno(stdout), _O_U16TEXT);   //使用Unicode
	wprintf(L"■");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 0X0f);
}

void setSite(int i, int site_x, int site_y){

	sBody[i].x = site_x;

	sBody[i].y = site_y;

}

int main()
{

	return 0;
}