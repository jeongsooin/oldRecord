#include <stdio.h>
#include <conio.h>
//#define MAX_SIZE 10

void main() {
	printf("\n��Project 2:: ");
	printf("\n��Array�� �̿��� Selection Sort \n\n");
	printf("��������������������������������������������������������������\n");
	printf("��         ���� �������� ������� �Է��ϼ���.               ��\n");
	printf("��        11  8  42  24  96  7  15  3  26  49               ��\n");
	printf("��������������������������������������������������������������\n");

	int list[10];
	int i,j,temp;
	printf(" �Է�   :  ");
	for (i = 0; i < 10; i++) {
		scanf_s("%d", &list[i]);
	}
	printf("\n��������������������������������������������������������������\n");
	printf(" ���� ��: ");
	for (i = 0; i < 10; i++) {
		printf("%d ", list[i]);
	}
	printf("\n��������������������������������������������������������������\n");

	for (i = 0; i < 9; i++) {
		for (j = i + 1; j < 10; j++) {
			if (list[j] < list[i]) {
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}	
	}
	printf(" ���� ��: ");
	for (i = 0; i < 10; i++) {
		printf("%d ", list[i]);
	}
	printf("\n��������������������������������������������������������������\n\n");
	printf("Press <Enter> to quit.\n");
	_getch();
}