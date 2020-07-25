#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define mapx 42 
#define mapy 42


int map[mapx][mapy]; 

int basposy = (int)(mapy / 2.0);
int basposx = (int)(mapx / 2.0);

int foodposy; 
int foodposx;

int ch; 

int iy = 0; 
int ix = 1;

int tt = 0;

int st = 0;

int posx[600];
int posy[600];

int foodnum = 0;

int level = 1;

int num1 = 0;

int renum = 0; 

int sc = 0;  

unsigned int velx = 100;

int mapre = 0;

int numstart;

int head_c = 12;
int head_s = 0;
int tail_c = 14;
int tail_s = 0;
int food_s = 0;
int food_c = 9;
int bgc = 2;


void ending();
void re();
void vel();
int start();

void cursorview(bool show) 
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void scolor(unsigned short text = 15, unsigned short back = 0)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

void gotoxy(int x, int y)
{

	COORD cur;
	cur.X = x;
	cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

void food(int x, int y)  
{
	map[x][y] = 3;
	foodnum++;
}

inline int cheakfoodpos()
{                       
	int nmnm = 0;
	num1 = st + 2;
	for (int a = 0; a <= st + 2; a++)
	{
		if (foodposx == posx[a] && foodposy == posy[a])
			nmnm += 1;
		else
			nmnm += 0;
	}
	return nmnm;
}

inline void rafood()
{
	int num = 1;
	while (num == 1)
	{
		srand(time(NULL));
		foodposx = rand() % mapx;
		foodposy = rand() % mapy;


		if (cheakfoodpos() == 0)
		{
			food(foodposx, foodposy);
			num--;
		}
	}
}

void zmap()
{
	for (int i = 0; i < mapy; i++)
	{
		for (int j = 0; j < mapx; j++)
			map[j][i] = 0;

	}
}

void mapline()
{

	gotoxy(0, 0);
	for (int i = 0; i < 44; i++)
	{
		printf("■");
	}
	gotoxy(0, 43);
	for (int i = 0; i < 44; i++)
	{
		printf("■");
	}
	for (int i = 0; i < 44; i++)
	{
		gotoxy(0, i);
		printf("■\n");
	}
	for (int i = 0; i < 44; i++)
	{
		gotoxy(86, i);
		printf("■\n");
	}

}

void print(int a)
{

	for (int i = 0; i < mapy; i++)
	{

		gotoxy(2, i + 1);
		for (int j = 0; j < mapx; j++)
		{

			if (a == 1)
				printf("%d", map[j][i]);

			else if (a == 0)
			{
				if (map[j][i] == 0) 
				{
					scolor(bgc, bgc);
					printf("□");
				}
				else if (map[j][i] == 1)  
				{
					scolor(head_c, bgc);

					if (head_s == 0)
						printf("■");
					else if (head_s == 1)
						printf("★");
					else if (head_s == 2)
						printf("●");
					else if (head_s == 3)
						printf("◆");

				}
				else if (map[j][i] == 2)
				{
					scolor(tail_c, bgc);

					if (tail_s == 0)
						printf("■");
					else if (tail_s == 1)
						printf("★");
					else if (tail_s == 2)
						printf("●");
					else if (tail_s == 3)
						printf("◆");
				}
				else if (map[j][i] == 3) 
				{
					scolor(food_c, bgc);

					if (food_s == 0)
						printf("■");
					else if (food_s == 1)
						printf("★");
					else if (food_s == 2)
						printf("●");
					else if (food_s == 3)
						printf("◆");
				}


			}

		}


	}
	printf("\n");
	scolor();
}

int scan()
{
	int add = 0;
	for (int i = 0; i < mapy; i++)
	{
		for (int j = 0; j < mapx; j++)
			if (map[j][i] == 3)
				add++;

	}
	return add;
}

inline void play(int num, int co)
{
	
	for (;;)
	{

		if (_kbhit())
		{

			ch = _getch();
			ch = _getch();

			if (ch == 72)
			{
				if (iy == 1)
				{
					ix = 0;
					iy = 1;
				}
				else
				{
					ix = 0;
					iy = -1;
				}
			}

			else if (ch == 75)
			{
				if (ix == 1)
				{
					ix = 1;
					iy = 0;
				}
				else
				{
					ix = -1;
					iy = 0;
				}
			}

			else if (ch == 77)
			{
				if (ix == -1)
				{
					ix = -1;
					iy = 0;
				}
				else
				{
					ix = 1;
					iy = 0;
				}

			}

			else if (ch == 80)
			{
				if (iy == -1)
				{
					ix = 0;
					iy = -1;
				}
				else
				{
					ix = 0;
					iy = 1;
				}
			}

		}

		if (foodnum == 1)
		{
			if (scan() == 0)

			{
				Sleep(1);

				
				st += 2;   		

				if (level == 2)
					st++;
				else if (level == 3)
					st += 2;
				else if (level == 4)
					st += 3;
				else if (level >= 5)
					st += 4;

				foodnum--;
				sc++;

			}

		}

		num1 = st + 2;

		map[posx[num1]][posy[num1]] = 0;


		for (int a = num1 + 6; a >= 1; a--)  
		{

			posx[a] = posx[a - 1];
			posy[a] = posy[a - 1];
		}

		map[posx[0]][posy[0]] = 2;

		posx[0] += ix;  
		posy[0] += iy;

		if (posy[0] == -1)
			break;
		if (posy[0] == mapy)
			break;
		if (posx[0] == -1)
			break;
		if (posx[0] == mapx)
			break;

		if (map[posx[0]][posy[0]] == 0)
			map[posx[0]][posy[0]] = 1;
		else if (map[posx[0]][posy[0]] == 2)
			break;

		if (sc == 100)
		{
			break;
		}
		if (foodnum == 0)
			rafood();

		if (sc == 5)
		{
			level = 2;
		}
		else if (sc == 15)
		{
			level = 3;
		}
		else if (sc == 25)
		{
			level = 4;
		}
		else if (sc == 40)
		{
			level = 5;
		}
		else if (sc == 55)
		{
			level = 6;
		}
		else if (sc == 75)
		{
			level = 7;
		}


		if (co == 1) 
		{

			gotoxy(88, 0);
			printf("posx[0]:%d ", posx[0]); 
			gotoxy(88, 1);
			printf("posy[0]:%d ", posy[0]);
			gotoxy(88, 2);
			printf("st:%d ", st);
			gotoxy(88, 3);
			printf("foodnum:%d ", foodnum);
		}
		else if (co == 0)
		{
			gotoxy(88, 0);
			if (level == 7)
			{
				printf("leval: fin");
			}
			else
			{
				printf("level: %d", level);
			}

			gotoxy(88, 1);
			printf("score: %d", sc);
			gotoxy(88, 2);
			printf("꼬리 수: %d", num1);	
		}

		print(num);
		Sleep(velx);

	}

}


int startpage()
{
	int ch;
	int namchang = 0;
	while (1)
	{
		system("cls");
		gotoxy(0, 0);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(37, 7);
		printf("Snake Game.\n");
		gotoxy(39, 8);
		printf("Ver.2.1\n");
		gotoxy(mapx / 4, 15);
		printf("1.게임 시작");
		gotoxy(mapx / 4, 16);
		printf("2.속도 설정");
		gotoxy(mapx / 4, 17);
		printf("3.종료");
		gotoxy(0, 43);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

		gotoxy(40, 19);
		scanf("%d", &ch);

		if (ch == 1)
		{
			return 1;
		}
		else if (ch == 2)
		{
			vel();
		}
		else if (ch == 3)
		{
			for (int i = 5; i >= 1; i--)
			{
				gotoxy(0, 44);
				printf("                                        ");
				gotoxy(0, 44);
				printf("%d초 후에 게임이 자동으로 종료 됨니다.", i);
				Sleep(1000);
			}
			return 2;
		}
		else
		{
			gotoxy(34, 19);
			printf("그런 선택지는 없습니다.");
			Sleep(2500);
			gotoxy(34, 19);
			printf("                                ");
		}
	}
}

void vel()
{
	int ch;
	system("cls");
	gotoxy(0, 0);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(37, 7);
	printf("속도 조절");
	gotoxy(mapx / 4, 15);
	printf("1.쉬움");
	gotoxy(mapx / 4, 16);
	printf("2.보통");
	gotoxy(mapx / 4, 17);
	printf("3.어려윰");
	gotoxy(mapx / 4, 18);
	printf("4.임의 값");
	gotoxy(0, 43);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	gotoxy(40, 19);
	scanf("%d", &ch);

	while (1)
	{
		if (ch == 1)
		{
			velx = 150;

		}

		else if (ch == 2)
		{
			velx = 100;


		}

		else if (ch == 3)
		{
			velx = 50;

		}

		else if (ch == 4)
		{
			system("cls");
			gotoxy(0, 0);
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
			gotoxy(26, 13);
			printf("50 어려움 100이 보통 150이 쉬움 입니다.");
			gotoxy(26, 19);
			printf("속도: ");
			gotoxy(0, 43);
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
			gotoxy(32, 19);
			scanf("%d", &velx);



		}
		else
		{
			gotoxy(34, 19);
			printf("그런 선택지는 없습니다.");
			Sleep(2500);
			gotoxy(34, 19);
			printf("                                ");
		}
		break;
	}


}

void howtp()
{
	system("cls");
	gotoxy(0, 0);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");

	gotoxy(37, 7);
	printf("규칙 및 조작법");
	gotoxy(14, 15);
	printf("벽에 머리를 박으면 죽습니다.또한 머리를 꼬리에 부딪쳐도 죽습니다.");
	gotoxy(14, 16);
	printf("조작키는 키보드 방향키입니다.");
	gotoxy(14, 17);
	printf("돈모양의 먹이를 먹으면 꼬리가 늘어납니다.");

	gotoxy(0, 43);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	for (int i = 5; i >= 1; i--)
	{
		gotoxy(0, 44);
		printf("                                                 ");
		gotoxy(0, 44);
		printf("%d초 후에 게임이 시작됨니다.", i);
		Sleep(1000);
	}
	system("cls");

}

void score()
{

	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");

	gotoxy(37, 7);
	printf("Game Over!!\n\n\n\n");
	printf("\t                  leval:%d\n", level);
	printf("\t                  score:%d\n", sc);
	printf("\t               꼬리 수: %d\n", num1);
	gotoxy(0, 43);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(2500);
	re();

}

void renums()
{
	basposy = (int)(mapy / 2.0);
	basposx = (int)(mapx / 2.0);

	foodposy = 0;
	foodposx = 0;

	iy = 0;
	ix = 1;

	tt = 0;

	sc = 0;

	st = 0;

	for (int a = 0; a < 600; a++)
	{
		posx[a] = 0;
		posy[a] = 0;
	}

	foodnum = 0;

	level = 1;

	num1 = 0;

	numstart = 0;
}

void retry()
{
	system("cls");

	system("cls");
	gotoxy(0, 0);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");

	gotoxy(0, 43);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	gotoxy(34, 17);
	printf("변수 및 맵 초기화중..");
	renums();

	Sleep(3000);

	gotoxy(0, 0);

	system("cls");

	cursorview(false);
	zmap();

	map[basposx][basposy] = 1;
	map[basposx - 1][basposy] = 2;
	map[basposx - 2][basposy] = 2;

	posx[0] = basposx;
	posy[0] = basposy;
	posx[1] = basposx - 1;
	posy[1] = basposy;
	posx[2] = basposx - 2;
	posy[2] = basposy;

	mapline();

	food(10, 5);

	play(0, 0);
	ending();
}

void re()
{
	int re;
	cursorview(true);
	while (renum == 0)
	{
		system("cls");
		gotoxy(0, 0);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");

		gotoxy(0, 43);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(37, 15);
		printf("1.다시하기");
		gotoxy(37, 16);
		printf("2.속도 조절");
		gotoxy(37, 17);
		printf("3.매인 화면");
		gotoxy(37, 18);
		printf("4.종료하기");
		gotoxy(37, 20);
		scanf("%d", &re);

		if (re == 4)
		{
			for (int i = 5; i >= 1; i--)
			{
				gotoxy(0, 44);
				printf("                                        ");
				gotoxy(0, 44);
				printf("%d초 후에 게임이 자동으로 종료 됨니다.", i);
				Sleep(1000);
				renum = 1;
			}
		}

		else if (re == 2)
		{
			vel();
			retry();
		}

		else if (re == 1)
		{
			retry();
			
		}

		else if (re == 3)
		{
			renums();
			start();
			if (numstart == 1)
			{
				play(0, 0);	 
							
				ending();
				
			}
			break;
		}
		else
		{
			gotoxy(32, 20);
			printf("그런 선택지는 없습니다.");
			Sleep(1500);
			printf("                        ");
			renum = 0;
		}
	}
}

void cl()
{

	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");

	gotoxy(37, 7);
	printf("Game Clear!!\n");

	gotoxy(0, 43);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	Sleep(2500);
	re();

}

void title()
{
	SetConsoleTitle("Snake Game");
}

int start() 
{
	int re = 0;

	title();
	system("mode con cols=105  lines=46");
	numstart = startpage();
	if (numstart == 1)
	{
		
		howtp();

		cursorview(false);

		zmap();

		map[basposx][basposy] = 1;
		map[basposx - 1][basposy] = 2;
		map[basposx - 2][basposy] = 2;

		posx[0] = basposx;
		posy[0] = basposy;
		posx[1] = basposx - 1;
		posy[1] = basposy;
		posx[2] = basposx - 2;
		posy[2] = basposy;

		mapline();

		food(10, 5);
		re = 1;
	}
	else if (numstart == 2)
	{
		re = 2;
	}

	return re;
}

void ending()
{
	
	if (sc != 100)
		score();
	else if (sc == 100)
		cl();
}

int main()
{

	//title();
	//system("mode con cols=110  lines=40");
	//startpage();
	//vel();
	//print(1);
	//mapline();
	//howtp();
	//score();
	//re();

	numstart = start();
	if (numstart == 1)
	{
		play(0, 0);	 
					 
		ending();
		
	}

	return 0;
}
