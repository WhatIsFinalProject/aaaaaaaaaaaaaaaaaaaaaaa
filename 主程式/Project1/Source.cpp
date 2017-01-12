#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdio.h>
#include <windows.h>  
#include <stdlib.h>
#include <iostream>   
#include <time.h>
#include <conio.h>
#define FOREGROUND_BLACK  0x0000
#define FOREGROUND_YELLOW 0x1111
#define mm 10
#define delay 0

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
int main()
{
	return 0;
}