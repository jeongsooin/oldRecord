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
	printf("ã�� ���� �迭�� �����ϴ�.\n");
	return -1;
}
void main() {
	printf("\n��Project 4:: ");
	printf("\n��Array�� �̿��� Selection Sort�� Binary Search \n\n");
	printf("��������������������������������������������������������������\n");
	printf("��         ���� �������� ������� �Է��ϼ���.               ��\n");
	printf("��        11  8  42  24  96  7  15  3  26  49               ��\n");
	printf("��������������������������������������������������������������\n");
	int list[10];
	int i, j, temp, searchnum;
	printf("�Է�   :  ");
	for (i = 0; i < 10; i++) {
		scanf_s("%d", &list[i]);
	}
	printf("\n��������������������������������������������������������������\n");
	printf("���� ��: ");
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
	printf("���� ��: ");
	for (i = 0; i < 10; i++) {
		printf("%d ", list[i]);
	}
	printf("\n��������������������������������������������������������������\n");
	printf("ã���� �ϴ� ������ �Է��ϼ���:\n");
	scanf_s("%d", &searchnum);
	printf("\n��������������������������������������������������������������\n");
	printf(" %d :: �迭�� %d�� �ε����� �ֽ��ϴ�.\n\n", searchnum, binsearch(list, searchnum, 0, 9));
	printf("\n��������������������������������������������������������������\n");

	printf("Press <Enter> to quit.\n");
	_getch();
}
