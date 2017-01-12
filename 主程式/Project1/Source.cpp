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

unsigned int map(int x, int y,int foodx,int foody);
unsigned int scrn ();
void Snake(int xi, int yi);
unsigned int movekey(int xm, int ym,int foodx, int foody);

char *temp;
int x = (mm + 6) / 2, 
    y = (mm * 2 - 2) / 2;

char *craft[mm + 8][mm * 2];
char *snake[mm + 6][mm * 2 - 2];

int wrun(int xw, int yw);
int arun(int xa, int ya);
int srun(int xs, int ys);
int drun(int xd, int yd);
int MyGetCh();


volatile bool bEscape;

int MyGetCh() //----------------按鍵回傳值 q-->END
{
	int ch = _getch();
	if (ch == 113)
	{
		bEscape = !bEscape;
		return ch;
	}

	else if (ch == 119)
	{
		bEscape = false;
		return ch;
	}
	else if (ch == 97)
	{
		bEscape = false;
		return ch;
	}
	else if (ch == 115)
	{
		bEscape = false;
		return ch;
	}
	else if (ch == 100)
	{
		bEscape = false;
		return ch;
	}
}

int main()
{
	srand(time(0));
	
	int foodx = (rand() % 16 + 1);
	int foody = (rand() % 18 + 1);
	while (1)
	{

		system("cls");
		printf("開始");
		Sleep(1000);
	
	c:
		
		while (!bEscape)
		{
			if ((foodx != x) && (foody != y))
				movekey(x, y, foodx, foody);
			else if ((foodx == arun(x,y))&&(foody == wrun(x,y)))
			{
				foodx = (rand() % 16 + 1);
				foody = (rand() % 18 + 1);
				goto c;
			}
			else
				goto c;
			
			//x = arun(x, y);
			//y = wrun(x, y);
			//scrn(x, y);
			//printf("\n%d  %d", x, y);
			
		}
		MyGetCh();
		//system("pause");

	}

}

//----------keyBoard partion--------------//

unsigned int movekey(int xm, int ym, int foodx, int foody)
{

	int MyGetCh();
	int chh = 119;
	map(xm, ym,foodx,foody);  //載入地圖

a:
	system("cls"); //清除

	while (_kbhit())
	{
		chh = MyGetCh();

	}

	while (!bEscape)
	{
		//printf("------------%d  %d\n", arun(xm, ym), wrun(xm, ym));
		system("cls");
		map(xm, ym, foodx, foody);
		system("cls");
		//Sleep(20);
		if (xm + ym == map(xm, ym, foodx, foody))
		{
			if (chh == 119)
			{
				if (wrun(xm, ym) != (ym))
					goto a;
				else
				{
					wrun(xm, ym);
				}

				if (xm <= 1)
					xm = 16;
				else
					xm--;

			}
			else if (chh == 115)
			{

				if (srun(xm, ym) != (ym))
					goto a;
				else
				{
					srun(xm, ym);

				}
				if (xm >= 16)
					xm = 1;
				else
					xm++;

			}
			else if (chh == 100)
			{
				if (drun(xm, ym) != (xm))
					goto a;
				else
				{
					drun(xm, ym);

				}
				if (ym >= 18)
					ym = 1;
				else
					ym++;

			}
			else if (chh == 97)
			{
				if (arun(xm, ym) != (xm))
					goto a;
				else
				{
					arun(xm, ym);

				}
				if (ym <= 1)
					ym = 18;
				else
					ym--;

			}
			else if (_kbhit())

			{
				goto a;

			}
		}
		
	}

	printf("暫停");
	return 0;
}

//----------keyBoard partion--------------//


//----------change partion--------------//

int wrun(int xw, int yw) //向上移動,回傳y值
{
	Sleep(delay);

	if (_kbhit())
	{
		return 1 + yw;
	}
	else
	{
		/*temp = craft[xw][yw];
		craft[xw][yw] = craft[xw - 1][yw];
		craft[xw - 1][yw] = temp;*/
		//xw--;
		//printf("%d %d\n", xw, yw);
		return 0 + yw;
	}
}
int arun(int xa, int ya) //向左移動, 回傳x值
{
	Sleep(delay);

	if (_kbhit())
	{
		return 1 + xa;
	}
	else
	{
		/*temp = craft[xa][ya];
		craft[xa][ya] = craft[xa][ya - 1];
		craft[xa][ya - 1] = temp;*/
		//ya = ya - 1;
		//printf("%d %d\n", xa, ya);
		return 0 + xa;
	}
}
int srun(int xs, int ys)
{
	Sleep(delay);

	if (_kbhit())
	{
		return 1 + ys;
	}
	else
	{
		/*temp = craft[xs][ys];
		craft[xs][ys] = craft[xs + 1][ys];
		craft[xs + 1][ys] = temp;*/
		//xs++;
		//printf("%d %d\n", xs, ys);
		return 0 + ys;
	}
}
int drun(int xd, int yd)
{
	Sleep(delay);

	if (_kbhit())
	{
		return 1 + xd;
	}
	else
	{
		/*temp = craft[xd][yd];
		craft[xd][yd] = craft[xd][yd + 1];
		craft[xd][yd + 1] = temp;*/
		//yd = yd + 1;
		//printf("%d %d\n", xd, yd);
		return 0 + xd;
	}
}

//----------change partion--------------//

unsigned int map(int x, int y, int foodx, int foody)
{

	int i, j = 0;
	

	for (i = 0; i < mm + 8; i++)
	{
		for (j = 0; j < mm * 2; j++)
		{
			if ((i == 0) || (i == mm + 8 - 1) || (j == 0) || (j == (mm * 2 - 1)))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 0x0f);
				craft[i][j] = "■";
				printf("%s", craft[i][j]);
			}
			else if ((i == x) && (j == y))//((i != x) && (j != y) && (i != 0) && (i != 29) && (j != 0) && (j != 43))
			{

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE );
				
				craft[x][y] = "■";
				printf("%s", craft[x][y]);

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else if (( foodx == i) && (foody == j))
			{

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);

				craft[i][j] = "■";
				printf("%s", craft[i][j]);

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else //if ((i != x) || (j != y) && (i != 0) && (i != 29) && (j != 0) && (j != 43))//((i == x) && (j == y))
			{
				craft[i][j] = "  ";
				printf("%s", craft[i][j]);
			}

		}
		printf("\n");
	}
	return x+y;

}

/*unsigned int scrn()
{
	for (int i = 0; i < mm + 8; i++)
	{
		for (int j = 0; j < mm * 2; j++)
		{
			if ((j%19)!=0)
			{
				printf("%s", craft[i][j]);
			}
			else
				printf("\n");
				    
		}
				
	}
	return 1;

}*/