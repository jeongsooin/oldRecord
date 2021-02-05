#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX 27
typedef struct list_node *list_ptr;
typedef struct list_node {
	char name[10];
	int num;
	list_ptr before;
	list_ptr after;
}node;

struct person {
	char name[10];
	int number;
};

struct person INFO[27] = { { "James",1 },{ "Sally",2 },{ "April",3 },{ "Olivia",4 },{ "Elliot",5 },{ "Chris",6 },{ "Jane",7 },{ "Mark",8 },{ "Robert",9 },{ "Christina",10 },
{ "Sebastian",11 },{ "Tom",12 },{ "Eddy",13 },{ "Lorie",14 },{ "Carol",15 },{ "Anna",16 },{ "Judy",17 },{ "Cathy",18 },{ "Benny",19 },{ "Adams",20 },{ "Jafry",21 },{ "Morin",22 },
{ "Shane",23 },{ "Henry",24 },{ "Donald",25 },{ "Abigail",26 },{ "Sam",27 } };

void insert(list_ptr node, list_ptr newnode) {
	newnode->before = node;
	newnode->after = node->after;
	node->after->before = newnode;
	node->after = newnode;
}

void print_list(list_ptr HEAD) {
	int count = 0;
	list_ptr trail = HEAD->before;
	while (trail != HEAD)
	{
		if (count % 5 == 0) printf("\n");
		printf("%d.%-11s", trail->num, trail->name);
		trail = trail->before;
		count++;
	}
	printf("\n式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式\n");
}

int getRandnum(list_ptr HEAD) {
	list_ptr temp = HEAD->before;
	int j = 0;
	int randomnumber, lottery = 0;
	srand((unsigned int)time(NULL));
	randomnumber = rand();
	while (j <randomnumber) {
		temp = temp->before;
		j++;
	}
	if (temp == HEAD) { temp = temp->before; }
	lottery = temp->num;
	return lottery;
}
list_ptr find_node(list_ptr head, int num) {
	list_ptr here = head->before;
	while (here)
	{
		if (num == here->num) return here;
		here = here->before;
	}
	return NULL;
}
list_ptr detect_nodeR(list_ptr HEAD, list_ptr here) {
	int i = 0;
	list_ptr prev = here;
	while (i <  4) {
		if (prev == HEAD) prev = prev->before;
		prev = prev->before;
		i++;
	}
	return prev;
}

list_ptr detect_nodeL(list_ptr HEAD, list_ptr here) {
	int i = 0;
	list_ptr prev = here;
	while (i <  5) {
		if (prev == HEAD) prev = prev->after;
		prev = prev->after;
		i++;
	}
	return prev;
}

void main() {
	int i, rand_num;
	list_ptr founded = NULL;
	list_ptr HEAD = (list_ptr)malloc(sizeof(node));
	HEAD->after = HEAD;
	HEAD->before = HEAD;
	HEAD->num = 0;
	strncpy_s(HEAD->name, 10, "HEAD", 10);
	list_ptr newnode[27];
	for (i = 0; i < 27; i++) {
		newnode[i] = (list_ptr)malloc(sizeof(node));
		newnode[i]->num = INFO[i].number;
		strncpy_s(newnode[i]->name, 10, INFO[i].name, 10);
		insert(HEAD, newnode[i]);
	}
	print_list(HEAD);
	//rand_num = getRandnum(HEAD);
	//printf("%d\n", rand_num);
	//founded = find_node(HEAD, rand_num);
	//printf("Number %d %s chosen.\n", founded->num, founded->name);
	//list_ptr previous_node = detect_nodeR(founded);
	//printf("%s\n", previous_node->name);
	//previous_node = detect_nodeL(founded);
	//printf("%s\n", previous_node->name);
	int count = 1;
	while (count < 23) {
		rand_num = getRandnum(HEAD);
		//printf("%d\n", rand_num);
		founded = find_node(HEAD, rand_num);
		printf("Number %d %s was chosen by a drawing lot.\n", founded->num, founded->name);
		list_ptr prevR = detect_nodeR(HEAD, founded);
		list_ptr prevL = detect_nodeL(HEAD, founded);
		if (count % 2 == 1) {
			printf("Right Turn\n");
			list_ptr temp = prevR->before;
			//printf("%s\n", prevR->name);
			if (HEAD == temp) temp = temp->before;
			printf("Number %d %s was eliminated in the list.\n", temp->num, temp->name);
			temp->before->after = temp->after;
			temp->after->before = temp->before;
			free(temp);
		}
		else if (count % 2 == 0) {
			printf("Left Turn\n");
			list_ptr temp = prevL->after;
			//printf("%s\n", prevL->name);
			if (HEAD == temp)  temp = temp->after;
			printf("Number %d %s was eliminated in the list.\n", temp->num, temp->name);
			temp->before->after = temp->after;
			temp->after->before = temp->before;
			free(temp);
		}
		printf("                     << Last survivors >>\n");
		print_list(HEAD);
		count = count + 1;
	}

	printf("                     << Final survivors >>\n\n\n");
	print_list(HEAD);
	char enter;
	printf("Press <Enter> to quit.\n");
	scanf_s("%c", &enter,1);

}