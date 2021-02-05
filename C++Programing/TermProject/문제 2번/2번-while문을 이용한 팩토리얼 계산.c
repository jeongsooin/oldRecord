// while 문을 이용한 팩토리얼 계산 프로그램
//1316592 정수인
#include <stdio.h>
int main()
{
	int factorial_num = 0;
	int result = 1;
	int init_num = 1;
	printf("팩토리얼 계산을 하는 프로그램 입니다.\n");
	printf("────────────────────\n");
	while (1) //알맞는 범위의 숫자를 입력할 때까지 입력을 받는다.
	{
		printf("정수를 하나 입력해 주세요. : ");
		scanf("%d", &factorial_num);
		if (factorial_num <= 0) //0이하의 숫자를 입력하면 다시 입력 받는다.
		{
			printf("계산할 수 없습니다.\n양의 정수를 입력해 주십시오.\n\n");
			continue;
		}
		else break;//올바른 입력값이 들어오면 빠져나가 계산을 한다.
	}
	printf("────────────────────\n");
	while (init_num <= factorial_num)//while문을 이용하여 계산한다.
	{
		result *= init_num;
		init_num++;
	}

	printf("%d의 팩토리얼 계산 값은 %d 입니다.\n",factorial_num, result);
	printf("────────────────────\n");

	return 0;
}