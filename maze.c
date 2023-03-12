#include <stdio.h>
#include <stdlib.h>

#define EXIT_ROW 5
#define EXIT_COL 5
#define numRow 5
#define numCol 5
#define MAX_STACK 6
#define Y 1
#define N 0
#define TRUE 1
#define FALSE 0

int maze[7][7];
int mark[7][7];
//과제 함수
void setup_maze() {
	short int s_maze[numRow][numCol] = {
			{0,1,1,1,1},
			{1,0,1,0,1},
			{1,0,0,1,0},
			{0,0,1,0,1},
			{1,0,0,1,0}
	};
	for (int col0 = 0; col0 < 7; col0++) {
		maze[0][col0] = 1;
		maze[6][col0] = 1;
	}
	for (int row0 = 0; row0 < 7; row0++) {
		maze[row0][0] = 1;
		maze[row0][6] = 1;
	}
	for (int row1 = 1; row1 < 6; row1++) {
		for (int col1 = 1; col1 < 6; col1++)
			maze[row1][col1] = s_maze[row1 - 1][col1 - 1];

	}
}

typedef struct {
	short int row;
	short int col;
	short int dir;
}element; //행 열 방향 구조체


typedef struct {
	short int vert;
	short int horiz;
}offsets;

offsets move[8] = { {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1} };

//스택 연결리스트
typedef struct stack {
	short int col;
	struct stack* link;
} stack;

stack* top;
stack* head;
stack* newnode;

int r; //행값 저장 변수

//연결리스트 스택 추가
void push(element item) {
	r = item.row;
	head = (stack*)malloc(sizeof(stack));
	newnode = (stack*)malloc(sizeof(stack));
	newnode->col = item.col;
	newnode->link = head->link;
	head->link = newnode;
}
//최종 출력
void final_maze() {
	printf("row/col   ");
	printf("1  2  3  4  5\n");


	for (int i = 1; i < 6; i++) {
		printf("%3d       ", i);
		for (int j = 1; j < 6; j++) {
			if (maze[i][j] == 1)
				printf("x  ");
			else if (maze[i][j] == 0)
				printf("   ");
			else if (maze[i][j] == '2')
				printf("*  ");
		}
		putchar('\n');
	}
}

//출력
void print_maze() {
	maze[r][newnode->col] = '2';
	printf("row/col   ");
	printf("1  2  3  4  5\n");


	for (int i = 1; i < 6; i++) {
		printf("%3d       ", i);
		for (int j = 1; j < 6; j++) {
			if (maze[i][j] == 1)
				printf("x  ");
			else if (maze[i][j] == 0)
				printf("   ");
			else if (maze[i][j] == '2')
				printf("*  ");
		}
		putchar('\n');
	}
}
//패스 함수
void path(void)
{
	top = NULL;
	char ask = 'Y';
	int row, col, nextRow, nextCol, dir, found = FALSE;
	mark[1][1] = 1;
	element position;
	position.row = 1;
	position.col = 1;
	position.dir = 1;
	while (!found && ask == 'Y') {
		row = position.row;
		col = position.col;
		dir = position.dir;
		while (dir < 8 && found == FALSE && ask == 'Y') {
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (nextRow == EXIT_ROW && nextCol == EXIT_COL) {
				found = TRUE;
				position.row = row;
				position.col = col;
				push(position);
				print_maze();
				printf("continue(Y/N)? : ");
				scanf_s(" %c", &ask);
				fflush(stdin);
				position.row = nextRow;
				position.col = nextCol;
				push(position);
				print_maze();
				printf("continue(Y/N)? : ");//출력 진행여부 묻기
				scanf_s(" %c", &ask);
				fflush(stdin);

			}
			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
				mark[nextRow][nextCol] = 1;
				position.row = row;
				position.col = col;
				position.dir = ++dir;
				push(position);
				print_maze();
				printf("continue(Y/N)? : ");//출력 진행여부 묻
				scanf_s(" %c", &ask);
				fflush(stdin);
				row = nextRow;
				col = nextCol;
				dir = 0;
			}
			else dir++;
		}
	}
	printf("탐색 종료\n");
}

int main(void)
{
	setup_maze();
	path();
	printf("-------최종 maze 출력-------\n");
	final_maze();
}
