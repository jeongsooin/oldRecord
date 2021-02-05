// 자음과 모음의 개수 세기
// 1316592 정수인
#include<stdio.h>
#define MAX 200

void SetUpper(char *word); // 대문자로 바꾸는 함수 선언
void FindVowel(int* c_cons, int* c_vowel, char* word); // 모음을 찾는 함수 선언
 
int main()
{
	int consonant = 0;
	int vowel = 0;
	int* c_consonant = &consonant; // 자음 변수에 대한 포인터
	int* c_vowel = &vowel;  // 모음 변수에 대한 포인터
	char word[MAX];

	printf("\n  단어에서 자음과 모음의 개수를 세는 프로그램 입니다.\n");
	printf("  〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
	printf("  단어를 하나 입력하세요 : ");
	scanf("%s", word);

	SetUpper(word);

	printf("\n  ───────────────────────────\n");
	printf("  바뀐 문자열 : %s\n", word);

	FindVowel(c_consonant, c_vowel, word); 

	printf("  ───────────────────────────\n");
	printf("  자음의 개수 : %d\n", consonant);
	printf("  모음의 개수 : %d\n", vowel);
	printf("  ───────────────────────────\n  ▷");

	return 0;
}

void SetUpper(char *word) // 입력한 단어의 배열을 전달 받아 소문자가 있으면 대문자로 변환
{
	int i = 0;
	for (i = 0; i < MAX; i++)
	{
		if (97 <= word[i] && word[i] <= 122) // 소문자이면
			word[i] = word[i] - 32; // 대문자로 바꾸기
		else
			continue;
	}
}

void FindVowel(int* c_cons, int* c_vowel, char* word)
{
	int i = 0;
	for (i = 0; i < MAX; i++)
	{
		if (word[i] < 'A' || word[i]>'Z') // 빈 배열 원소는 건너뛰기 
			continue;
		else if (word[i] == 'A' || word[i] == 'E' || word[i] == 'I' || word[i] == 'O' || word[i] == 'U') // 모음이면
			*c_vowel = *c_vowel + 1; // 모음 변수에 접근하여 크기 증가
		else
			*c_cons = *c_cons + 1; // 모음이 아니면 자음 변수에 접근하여 크기 증가
	}
}