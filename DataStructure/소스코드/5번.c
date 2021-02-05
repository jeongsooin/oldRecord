#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
typedef struct treenode *treeptr;
typedef struct treenode {
	int key;
	treeptr left, right;
}treenode;

void insert(treeptr *root, int key) {
	treeptr p, t; 
	treeptr n;

	t = *root;
	p = NULL;
	while (t!=NULL)
	{
		if (key == t->key) return; 
		p = t;
		if (key < p->key) t = p->left;
		else t = p->right;
	}
	n = (treeptr)malloc(sizeof(treenode));
	if (n == NULL) return;
	n->key = key;
	n->left = n->right = NULL;
	if (p != NULL) {
		if (key < p->key) p->left = n;
		else p->right = n;
	}
	else *root = n;
}

treeptr search(treeptr node, int key) {
	while (node != NULL) {
		if (key == node->key) return node;
		else if (key < node->key) node = node->left;
		else node = node->right;
	}
	printf("찾는 수가 리스트에 없습니다.\n");
	return NULL;
}
void printtree(treeptr root)
{
	if (root != NULL)
	{
		printtree(root->left);
		printf("%-5d", root->key);
		printtree(root->right);
	}
}
void main() {
	printf("\n│Project 5:: ");
	printf("\n│Linked list를 이용한 Binary Search \n\n");
	printf("┌─────────────────────────────┐\n");
	printf("│         다음 정수들을 순서대로 입력하세요.               │\n");
	printf("│        11  8  42  24  96  7  15  3  26  49               │\n");
	printf("└─────────────────────────────┘\n");
	printf("입력   :  ");
	int i,num;
	treeptr root = NULL;
	treeptr hit;
	for ( i = 0; i < 10; i++)
	{
		scanf_s("%d", &num);
		insert(&root, num);
	}
	printf("\n───────────────────────────────\n\n\t");
	printtree(root);
	printf("\n");
	printf("\n───────────────────────────────\n");
	printf("  찾고자 하는 정수를 입력하세요:");
	scanf("%d", &num);
	printf("───────────────────────────────\n");
	search(root, num);
	hit = search(root, num);
	if (hit != NULL) {
		printf("  %d을(를) 찾았습니다.\n", hit->key);
	}
	else printf("  %d 을(를) 찾지 못했습니다.\n", num);
	printf("───────────────────────────────\n");
	printf("Press <Enter> to quit.\n");
	_getch();
}