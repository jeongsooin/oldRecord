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
	printf("ã�� ���� ����Ʈ�� �����ϴ�.\n");
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
	printf("\n��Project 5:: ");
	printf("\n��Linked list�� �̿��� Binary Search \n\n");
	printf("��������������������������������������������������������������\n");
	printf("��         ���� �������� ������� �Է��ϼ���.               ��\n");
	printf("��        11  8  42  24  96  7  15  3  26  49               ��\n");
	printf("��������������������������������������������������������������\n");
	printf("�Է�   :  ");
	int i,num;
	treeptr root = NULL;
	treeptr hit;
	for ( i = 0; i < 10; i++)
	{
		scanf_s("%d", &num);
		insert(&root, num);
	}
	printf("\n��������������������������������������������������������������\n\n\t");
	printtree(root);
	printf("\n");
	printf("\n��������������������������������������������������������������\n");
	printf("  ã���� �ϴ� ������ �Է��ϼ���:");
	scanf("%d", &num);
	printf("��������������������������������������������������������������\n");
	search(root, num);
	hit = search(root, num);
	if (hit != NULL) {
		printf("  %d��(��) ã�ҽ��ϴ�.\n", hit->key);
	}
	else printf("  %d ��(��) ã�� ���߽��ϴ�.\n", num);
	printf("��������������������������������������������������������������\n");
	printf("Press <Enter> to quit.\n");
	_getch();
}