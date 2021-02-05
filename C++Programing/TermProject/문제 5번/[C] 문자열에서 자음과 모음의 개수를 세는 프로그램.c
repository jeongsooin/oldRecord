// ������ ������ ���� ����
// 1316592 ������
#include<stdio.h>
#define MAX 200

void SetUpper(char *word); // �빮�ڷ� �ٲٴ� �Լ� ����
void FindVowel(int* c_cons, int* c_vowel, char* word); // ������ ã�� �Լ� ����
 
int main()
{
	int consonant = 0;
	int vowel = 0;
	int* c_consonant = &consonant; // ���� ������ ���� ������
	int* c_vowel = &vowel;  // ���� ������ ���� ������
	char word[MAX];

	printf("\n  �ܾ�� ������ ������ ������ ���� ���α׷� �Դϴ�.\n");
	printf("  ����������������������������\n\n");
	printf("  �ܾ �ϳ� �Է��ϼ��� : ");
	scanf("%s", word);

	SetUpper(word);

	printf("\n  ������������������������������������������������������\n");
	printf("  �ٲ� ���ڿ� : %s\n", word);

	FindVowel(c_consonant, c_vowel, word); 

	printf("  ������������������������������������������������������\n");
	printf("  ������ ���� : %d\n", consonant);
	printf("  ������ ���� : %d\n", vowel);
	printf("  ������������������������������������������������������\n  ��");

	return 0;
}

void SetUpper(char *word) // �Է��� �ܾ��� �迭�� ���� �޾� �ҹ��ڰ� ������ �빮�ڷ� ��ȯ
{
	int i = 0;
	for (i = 0; i < MAX; i++)
	{
		if (97 <= word[i] && word[i] <= 122) // �ҹ����̸�
			word[i] = word[i] - 32; // �빮�ڷ� �ٲٱ�
		else
			continue;
	}
}

void FindVowel(int* c_cons, int* c_vowel, char* word)
{
	int i = 0;
	for (i = 0; i < MAX; i++)
	{
		if (word[i] < 'A' || word[i]>'Z') // �� �迭 ���Ҵ� �ǳʶٱ� 
			continue;
		else if (word[i] == 'A' || word[i] == 'E' || word[i] == 'I' || word[i] == 'O' || word[i] == 'U') // �����̸�
			*c_vowel = *c_vowel + 1; // ���� ������ �����Ͽ� ũ�� ����
		else
			*c_cons = *c_cons + 1; // ������ �ƴϸ� ���� ������ �����Ͽ� ũ�� ����
	}
}