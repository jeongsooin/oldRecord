// 대문자, 소문자, 영문자가 아닌 문자의 개수를 세는 프로그램
//1316592 정수인
#include<stdio.h>

int main()
{
	char string[256];
	int i;
	int upper_case = 0;
	int lower_case = 0;
	int non_alphabet = 0;
	printf(" ───────────────────────────────");
	printf("\n  문자열을 입력해주십시오 : ");
	scanf("%s", string);
	for (i = 0; i < 256; i++) //문자열을 저장한 배열의 루프를 돈다
	{
		if (string[i] >= 65 && string[i] <= 90) // 대문자일 때
			upper_case++;
		else if (string[i] >= 97 && string[i] <= 122) // 소문자일 때
			lower_case++;
		else if (string[i] == '\0') // 문자열이 종료되는 널 문자를 만나면 루프 종료
			break;
		else
			non_alphabet++; // 영문자가 아닐 때 
	}
	printf(" ───────────────────────────────");
	printf("\n  대문자 : %d개\n  소문자 : %d개\n  영문자가 아닌 문자 : %d개\n\n  ▷", upper_case, lower_case, non_alphabet);

	return 0;
}