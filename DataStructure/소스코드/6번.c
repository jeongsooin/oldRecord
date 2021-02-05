#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX 27
typedef struct list_node *list_ptr;
typedef struct list_node {
	char name[10];
	int num;
	list_ptr link;
}node;

struct person {
	char name[10];
	int number;
};

struct person INFO[27] = { { "James",1 },{ "Sally",2 },{ "April",3 },{ "Olivia",4 },{ "Elliot",5 },{ "Chris",6 },{ "Jane",7 },{ "Mark",8 },{ "Robert",9 },{ "Christina",10 },{ "Sebastian",11 },{ "Tom",12 },{ "Eddy",13 },
{ "Lorie",14 },{ "Carol",15 },{ "Anna",16 },{ "Judy",17 },{ "Cathy",18 },{ "Benny",19 },{ "Adams",20 },{ "Jafry",21 },{ "Morin",22 },{ "Shane",23 },{ "Henry",24 },{ "Donald",25 },{ "Abigail",26 },{ "Sam",27 } };

void print_list(list_ptr ptr) {
	int count = 0;
	list_ptr head = ptr;
	do {
		if (count % 5 == 0) {
			printf("\n");
		}
		printf("%d.", ptr->num);
		printf("%-11s",ptr->name);
		ptr = ptr->link;
		count++;
	} while (ptr != head);
}

list_ptr find_node(list_ptr head, int num) {
	list_ptr here = head;
	while (here)
	{
		if (num == here->num) return here;
		here = here->link;
	}
	return NULL;
}

list_ptr detect_node(list_ptr here) {
	int i = 0;
	list_ptr before = here;
	while (i <  4) {
		before = before->link;
		i++;
	}
	return before;
}

list_ptr delete_node(list_ptr head, list_ptr before) {
	if (head == NULL) { printf("There is No list.\n"); }
	list_ptr trail = before->link;
	printf("Number %d %s was eliminated in the list.\n\n", trail->num, trail->name);
	before->link = trail->link;
	if (trail == head) {
		head = trail->link;
	}
	free(trail);
	return head;
}
int getRandnum(list_ptr head) {
	list_ptr temp = head;
	int j = 0;
	int randomnumber, lottery = 0;
	srand((unsigned int)time(NULL));
	randomnumber = rand();
	while (j <randomnumber) {
		temp = temp->link;
		j++;
	}
	lottery = temp->num;
	return lottery;
}
void main() {
	int i = 0;
	int random_number = 0;
	list_ptr here, before, head = NULL;
	list_ptr last_node = (list_ptr)malloc(sizeof(node));
	strncpy_s(last_node->name, 10, INFO[0].name, 10);
	last_node->num = INFO[0].number;
	head = last_node;
	for (i = 1; i < 27; i++) {
		list_ptr newnode = (list_ptr)malloc(sizeof(node));
		strncpy_s(newnode->name, 10, INFO[i].name, 10);
		newnode->num = INFO[i].number;
		newnode->link = head;
		last_node->link = newnode;
		last_node = last_node->link;
	}
	printf("\n式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式\n");
	print_list(head);
	printf("\n式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式\n");
	
	int count = 0;
	while (count < 22) {
		random_number = getRandnum(head);
		printf("Number %d was chosen by drawing lot.", random_number);
		printf("\n\n");
		here = find_node(head, random_number);
		before = detect_node(here);
		head = delete_node(head, before);
		printf("                        << Last survivors >>\n");
		print_list(head);
		printf("\n式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式\n");
		count++;
	}
	printf("\n\n");
	printf("                        << Final survivors >>\n\n\n");
	for (i = 0; i < 5; i++) {
		printf("  %-11s", head->name);
		head = head->link;
	}
	printf("\n\n\n");
	printf("\n式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式\n");
	char enter;
	printf("Press <Enter> to quit.\n");
	scanf_s("%c", &enter, 1);
}