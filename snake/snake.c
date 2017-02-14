#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
///
#define height 20 //세로
#define width 40 //가로
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

typedef struct {
	int x;
	int y;
}ordered_pair;

int map[height][width]; // 10*20 맵
int point = 0;
int length;
int move = 0;
int life = 0;
int head = RIGHT;

ordered_pair record[4000];

void remove_cursor(void) {
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void gotoxy(int x, int y)//gotoxy
{
	COORD pos = { x - 1, y - 1 };//커서가 X좌표에서 -1 한값. Y좌표에서 -1한 값으로 이동
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void init_map(void) {
	memset(map, 0, sizeof(map));
}

void show_map(void) { //맵표현 gotoxy
	int i, j;
	gotoxy(1, 1);
	printf("\n");
	 

	printf("┌");
	for (j = 0; j < width; j++) { //메인창 바닥
		printf("─");
	}
	printf("┐");
	printf("\n");
	 
	for (i = 0; i <= height + 1; i++) { //메인창의 높이
		if (i != height + 1) {
			printf("┃"); //메인창 테두리
			for (j = 0; j < width; j++) { //메인창 너비
				if (map[i][j] == 0) {
					printf("　");
				}
				else if (map[i][j] == 1) {
					printf("■");//ㅁ한자에 있음
				}
				else {
					printf("★");
				}
			}
			printf("┃");// 테두리
			if (i == 4) {
				printf("score:%d", length - 2);
			}
			printf("\n");
		}
		else if(i == height +1) {
			printf("└");
			for (j = 0; j < width; j++) { //메인창 바닥
				printf("─");
			}
			printf("┘");
			printf("\n");
		}
		
	}
}

void make_snake(void) {
	map[0][0] = 1;
	map[0][1] = 1;
	length = 2;
	record[move].x = 0;
	record[move].y = 0;
	move++;
	record[move].x = 1;
	record[move].y = 0;
}

void delete_tail(void) {
	map[record[move - length].y][record[move - length].x] = 0;
}

void make_point(void) {
	int x, y;

	x = rand() % 39;
	y = rand() % 19;
	if (map[y][x] == 1) {
		make_point();
	}
	else {
		map[y][x] = 2;
	}
}

int move_snake(int way) {
	if (way == LEFT) {
		if (record[move].x == 0
			|| map[(record[move].y)][(record[move].x) - 1] == 1) {
			move++;
			life = 1;
			return 0;
		}
		else if (map[(record[move].y)][(record[move].x) - 1] == 2) {
			map[(record[move].y)][(record[move].x) - 1] = 1;
			move++;
			record[move].y = record[move - 1].y;
			record[move].x = record[move - 1].x - 1;
			head = LEFT;
			make_point();
			length++;
		}
		else {
			map[(record[move].y)][(record[move].x) - 1] = 1;
			move++;
			record[move].y = record[move - 1].y;
			record[move].x = record[move - 1].x - 1;
			head = LEFT;
			delete_tail();
		}
	}
	if (way == RIGHT) {
		if (record[move].x == 40 
			|| map[(record[move].y)][(record[move].x) + 1] == 1) {
			move++;
			life = 1;
			return 0;
		}
		else if (map[(record[move].y)][(record[move].x) + 1] == 2) {
			map[(record[move].y)][(record[move].x) + 1] = 1;
			move++;
			record[move].y = record[move - 1].y;
			record[move].x = record[move - 1].x + 1;
			head = RIGHT;
			make_point();
			length++;
		}
		else {
			map[(record[move].y)][(record[move].x) + 1] = 1;
			move++;
			record[move].y = record[move - 1].y;
			record[move].x = record[move - 1].x + 1;
			head = RIGHT;
			delete_tail();
		}
	}
	if (way == UP) {
		if (record[move].y == 0 
			|| map[(record[move].y - 1)][(record[move].x)] == 1) {
			move++;
			life = 1;
			return 0;
		}
		else if (map[(record[move].y - 1)][(record[move].x)] == 2) {
			map[(record[move].y - 1)][(record[move].x)] = 1;
			move++;
			record[move].y = record[move - 1].y - 1;
			record[move].x = record[move - 1].x;
			head = UP;
			make_point();
			length++;
		}
		else {
			map[(record[move].y) - 1][(record[move].x)] = 1;
			move++;
			record[move].y = record[move - 1].y - 1;
			record[move].x = record[move - 1].x;
			head = UP;
			delete_tail();
		}
	}
	if (way == DOWN) {
		if (record[move].y == 19 
			|| map[(record[move].y) + 1][(record[move].x)] == 1) {
			move++;
			life = 1;
			return 0;
		}
		else if (map[(record[move].y) + 1][(record[move].x)] == 2) {
			map[(record[move].y) + 1][(record[move].x)] = 1;
			move++;
			record[move].y = record[move - 1].y + 1;
			record[move].x = record[move - 1].x;
			head = DOWN;
			make_point();
			length++;
		}
		else {
			map[(record[move].y) + 1][(record[move].x)] = 1;
			move++;
			record[move].y = record[move - 1].y + 1;
			record[move].x = record[move - 1].x;
			head = DOWN;
			delete_tail();
		}
	}
}

void game_over(void) {
	init_map();
	show_map();
	gotoxy((width + 7) / 2, (height + 1) / 2);
	printf("Game Over");
}

int main(void) {
	remove_cursor();
	int tick=0;
	srand(time(NULL));
	init_map();
	make_snake();
	make_point();
	show_map();
	while (1) {
		if (life == 1) {
			break;
		}
		// 키보드 입력시 동작//
		while (_kbhit()) { 
			int key = getch();
			if ((head == RIGHT && key == LEFT) || (head == LEFT && key == RIGHT) || (head == UP && key == DOWN) || (head == DOWN && key == UP)) {
				life = 1;
				break;
			}
			else {
				move_snake(key);
				show_map();
			}
			fflush(stdin);
		}
		////////////////////

		/////시간의 흐름/////
		if (tick == 110) {
			move_snake(head);
			show_map();
			tick = 0;
		}
		////////////////////
		tick++;
		Sleep(1);
	}
	game_over();
	return 0;
}
