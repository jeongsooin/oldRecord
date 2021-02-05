#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
typedef struct list_node *list_ptr;
typedef struct list_node {
	int data;
	list_ptr link;
}node;

//입력받은 값으로 링크드 리스트를 생성
list_ptr create_list(int *arr) {
	int index = 0;
	list_ptr top, pointer = NULL;
	pointer = (list_ptr)malloc(sizeof(node));
	top = pointer;

	for (index = 0; index < 10; index++) {
		pointer->data = arr[index];
		if (index == 9) {
			pointer->link = NULL;
		}
		else {
			pointer->link = (list_ptr)malloc(sizeof(node));
			pointer = pointer->link;
		}
	}
	return top;
}

//리스트 출력
void print_list(list_ptr ptr) {
	while (ptr != NULL)
	{
		printf("%4d", ptr->data);
		ptr = ptr->link;
	}
	printf("\n───────────────────────────────\n");
}

void main() {
	printf("\n│Project 3:: ");
	printf("\n│Linked list를 이용한 Selection Sort \n\n");
	printf("┌─────────────────────────────┐\n");
	printf("│         다음 정수들을 순서대로 입력하세요.               │\n");
	printf("│        11  8  42  24  96  7  15  3  26  49               │\n");
	printf("└─────────────────────────────┘\n");
	
	list_ptr minimum, top, head,temp;
	int i,j, count = 0;
	int array[10];
	printf("입력   :  ");
	for (i = 0; i < 10; i++) {
		scanf_s("%d", &array[i]);
	}
	printf("───────────────────────────────\n");
	
	top = create_list(array);
	printf("정렬 전:");
	print_list(top);


	temp = top;
	while (temp != NULL)
	{
		count++;
		temp = temp->link;
	}

	int buffer;
	head = top;
	temp = head->link;
	for (i = 0; i < count-1; i++) {
		minimum = head;
		for (j = i + 1; j < count; j++) {
			if ( minimum->data > temp->data) {
				buffer = minimum->data;
				minimum->data = temp->data;
				temp->data = buffer;
			}
			else if(temp == NULL)
			{
				break;
			}
			temp = temp->link;
		}
		head = head->link;
		temp = head->link;
	}
	printf("정렬 후:");
	print_list(top);
	printf("Press <Enter> to quit.\n");
	_getch();
}

	
		

		

