#include <stdio.h>
#include <conio.h>
//#define MAX_SIZE 10

void main() {
	printf("\n│Project 2:: ");
	printf("\n│Array를 이용한 Selection Sort \n\n");
	printf("┌─────────────────────────────┐\n");
	printf("│         다음 정수들을 순서대로 입력하세요.               │\n");
	printf("│        11  8  42  24  96  7  15  3  26  49               │\n");
	printf("└─────────────────────────────┘\n");

	int list[10];
	int i,j,temp;
	printf(" 입력   :  ");
	for (i = 0; i < 10; i++) {
		scanf_s("%d", &list[i]);
	}
	printf("\n───────────────────────────────\n");
	printf(" 정렬 전: ");
	for (i = 0; i < 10; i++) {
		printf("%d ", list[i]);
	}
	printf("\n───────────────────────────────\n");

	for (i = 0; i < 9; i++) {
		for (j = i + 1; j < 10; j++) {
			if (list[j] < list[i]) {
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}	
	}
	printf(" 정렬 후: ");
	for (i = 0; i < 10; i++) {
		printf("%d ", list[i]);
	}
	printf("\n───────────────────────────────\n\n");
	printf("Press <Enter> to quit.\n");
	_getch();
}