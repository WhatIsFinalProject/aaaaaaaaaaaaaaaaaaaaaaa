#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <wchar.h>
#include <io.h>
#include <fcntl.h>

#define length  22
#define width   50
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

	scrn.X = xpos + 2; scrn.Y = ypos + 1;       //調整起始位置

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
	wprintf(L"Speed: %3d            ", 100 - speed);
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



int main(int argc, char *argv[])

{
	_setmode(_fileno(stdout), _O_U16TEXT);   //使用Unicode
	XY_str foodSite, coor, last;

	int startBodyLenght = 5, startFood = 0, bodyLenght, Food;
	int keyinFirst, keyinSecond;
	int i, j, gameOver = false, FoodAppear = false, xyChanged = false;
	int path = 2; // 方向
	int SnakeSpeed = 103;
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



		while (!gameOver)
		{
			Information(Food, SnakeSpeed);

			if (!FoodAppear)// 如果沒食物, 隨機算出一個食物的位置
			{
				foodcolor = (rand() % 4) + 1;
				foodSite.x = ((rand() % (width / 2 - 1)) * 2) + 2;
				foodSite.y = rand() % (length - 2) + 1;
				FoodAppear = true;
			}
			gotoxy(foodSite.x, foodSite.y);
			switch (foodcolor)
			{
			case 1:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 0X01);
				wprintf(L"■");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 0X0f);
				break;
			case 2:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 0X02);
				wprintf(L"■");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 0X0f);
				break;
			case 3:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 0X04);
				wprintf(L"■");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 0X0f);
				break;
			case 4:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 0X08);
				wprintf(L"■");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 0X0f);
				break;
			case 5:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 0X16);
				wprintf(L"■");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 0X0f);
				break;
			default:
				break;
			}

			xyChanged = false;

			if (_kbhit()){ // 鍵盤敲擊

				keyinFirst = _getch();

				if (keyinFirst == 224) {

					keyinSecond = _getch();

					switch (keyinSecond)
					{

					case  72: /* up, 1 */

						if (path != 2)
						{
							coor.y--;
							path = 1;
							xyChanged = true;
						}
						break;

					case  80: /* down, 2 */

						if (path != 1)
						{
							coor.y++;
							path = 2;
							xyChanged = true;
						}
						break;

					case  75: /* left, 3 */

						if (path != 4)
						{
							coor.x -= 2;
							path = 3;
							xyChanged = true;
						}
						break;

					case  77: /* right, 4 */

						if (path != 3)
						{
							coor.x += 2;
							path = 4;
							xyChanged = true;
						}
						break;

					}


				}

				if (keyinFirst == 'p' || keyinFirst == 'P')
				{
					do{
						gotoxy(width + 4, 20);
						wprintf(L"Ｐａｕｓｅ.");
						gameKey = _getch();
						gotoxy(width + 4, 20);
						wprintf(L"          ");
					} while (gameKey != 'p' && gameKey != 'P');
				}



			}
			if (xyChanged == false) { // 沒有任何動作則順著path(方向)前進

				switch (path){

				case  1: /* up, 1 */

					if (path != 2)
					{
						coor.y--;
						path = 1;
					}
					break;

				case  2: /* down, 2 */

					if (path != 1)
					{
						coor.y++;
						path = 2;
					}
					break;

				case  3: /* left, 3 */

					if (path != 4)
					{
						coor.x -= 2;
						path = 3;
					}
					break;

				case  4: /* right, 4 */

					if (path != 3)
					{
						coor.x += 2;
						path = 4;
					}
					break;

				}

				xyChanged = true;

			}
			for (i = 1; i<bodyLenght; i++){ /* Did XY_str die? */

				if (coor.x == sBody[i].x && coor.y == sBody[i].y)

					gameOver = true;

			}

			if (gameOver == 0 && xyChanged == 1){ /* XY_str moving */

				if (coor.x>0 && coor.x<width - 1 && coor.y>0 && coor.y<length - 1)
				{

					last.x = sBody[bodyLenght - 1].x;

					last.y = sBody[bodyLenght - 1].y;

					for (i = bodyLenght - 1; i >= 0; i--)
					{
						if (i == 0)
						{
							setSite(i, coor.x, coor.y);
						}
						else

							setSite(i, sBody[i - 1].x, sBody[i - 1].y);  //讓後面一格的身體(x,y) = 前一格的身體(x,y)
					}

					if (last.x != 0 && last.y != 0)
					{
						gotoxy(last.x, last.y); // 清尾巴

						wprintf(L"  ");
					}
					Snake(bodyLenght, foodcolor);

					SnakeSpeed = -0.0001*bodyLenght*bodyLenght*bodyLenght + 0.040*bodyLenght*bodyLenght - 3.4088*bodyLenght + 113.52;
					Sleep(SnakeSpeed);

				}
				else if (coor.x == 0)
				{
					coor.x = width;
				}
				else if (coor.x == width)
				{
					coor.x = 0;
				}
				else if (coor.y == length - 1)
				{
					coor.y = 0;
				}
				else if (coor.y == 0)
				{
					coor.y = length - 1;
				}
				else gameOver = true;



				if (sBody[0].x == foodSite.x && sBody[0].y == foodSite.y) /* snakeHead ate food? */
				{
					FoodAppear = false;
					if (bodyLenght<2000) bodyLenght++; // 避免蛇身超出陣列長度
					Food++;
				}

			}

		}

		/* Game over ? */

		while (1){

			system("CLS");

			wprintf(L"Your Grade: %d\n", Food * 100);

			wprintf(L"Game over.\nPlay again? (y/n) \n");

			gameKey = _getch();

			if (gameKey == 'y' || gameKey == 'Y' || gameKey == 'n' || gameKey == 'N'){

				system("CLS");

				break;

			}

		}

	}

	wprintf(L"Bye!\n");

	system("pause");

	return 0;

}
