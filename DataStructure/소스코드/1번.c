//maze.c
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STACK_SIZE 100
#define MAZE_SIZE 6
typedef struct element{
	short r;
	short c;
} element;

typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
} StackType;

element stack[MAX_STACK_SIZE];
int top = -1;
element here = { 1,0 }, entry = { 1,0 };

char maze[MAZE_SIZE][MAZE_SIZE] = {
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'},
};

void init(StackType *s) {
	s->top = -1;
}

int is_empty(StackType *s) {
	return (s->top == -1);
}

int is_full(StackType *s) {
	return(s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType *s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}

element pop(StackType *s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else 
		return s->stack[(s->top)--];
}

void pushLoc(StackType *s,int r, int c) {
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.')
	{
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s,tmp);
	}
}
 
void printMaze(char m[MAZE_SIZE][MAZE_SIZE]) {
	int i = 0;
	int j = 0;
	for (i = 0; i<MAZE_SIZE; i++) {
		for (j = 0; j<MAZE_SIZE; j++) {
			printf(" %c", maze[i][j]);
		}
		printf("\n");
	}
}

void printStack(StackType *s)
{
	int i;
	for (i = 5; i> s->top; i--)
		printf("|      |\n");
	for (i=s->top; i>=0; i--)
		printf("|(%d,%d)|\n", s->stack[i].r, s->stack[i].c);
	printf("|───|\n");
}


void main() {
	int r, c;
	StackType s;
	char enter;
	init(&s);
	here = entry;
	printMaze(maze);
	printStack(&s);
	printf("────────\n");
	while (maze[here.r][here.c] != 'x') {
		printMaze(maze);
		r = here.r;
		c = here.c;
		maze[r][c] = '.';
		pushLoc(&s,r - 1, c);
		pushLoc(&s,r + 1, c);
		pushLoc(&s,r, c - 1);
		pushLoc(&s,r, c + 1);
		printStack(&s);
		printf("────────\n");
		if (is_empty(&s)) {
			printf("실패\n");
			return;
		}
		else here = pop(&s);
		printMaze(maze);
		printStack(&s);
		printf("────────\n");
		printf("Press Enter\n");
		scanf("%c",&enter);
	}
	printf("성공\n");
	printf("Press <Enter> to quit.\n");
	scanf_s("%c", &enter, 1);
}