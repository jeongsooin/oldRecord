#include <stdio.h>
#include <conio.h>
int binsearch(int *array, int searchnum, int left, int right) {
	int middle;
	//printf("LEFT: %d\n", left);
	//printf("RIGHTT: %d\n", right);
	//printf("Searcjnum: %d\n", searchnum);
	while (left <= right) {
		middle = (left + right) / 2;
		if (searchnum < array[middle])
			right = middle - 1;

		else if (searchnum == array[middle])
			return middle;

		else left = middle + 1;
	}
	printf("찾는 수가 배열에 없습니다.\n");
	return -1;
}
void main() {
	printf("\n│Project 4:: ");
	printf("\n│Array를 이용한 Selection Sort와 Binary Search \n\n");
	printf("┌─────────────────────────────┐\n");
	printf("│         다음 정수들을 순서대로 입력하세요.               │\n");
	printf("│        11  8  42  24  96  7  15  3  26  49               │\n");
	printf("└─────────────────────────────┘\n");
	int list[10];
	int i, j, temp, searchnum;
	printf("입력   :  ");
	for (i = 0; i < 10; i++) {
		scanf_s("%d", &list[i]);
	}
	printf("\n───────────────────────────────\n");
	printf("정렬 전: ");
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
	printf("정렬 후: ");
	for (i = 0; i < 10; i++) {
		printf("%d ", list[i]);
	}
	printf("\n───────────────────────────────\n");
	printf("찾고자 하는 정수를 입력하세요:\n");
	scanf_s("%d", &searchnum);
	printf("\n───────────────────────────────\n");
	printf(" %d :: 배열의 %d번 인덱스에 있습니다.\n\n", searchnum, binsearch(list, searchnum, 0, 9));
	printf("\n───────────────────────────────\n");

	printf("Press <Enter> to quit.\n");
	_getch();
}
