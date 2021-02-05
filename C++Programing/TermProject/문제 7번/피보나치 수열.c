// 피보나치 수열을 출력하는 프로그램
// 1316592 정수인
#include<stdio.h>
#include<limits.h>
void PrintFibo(int num);

int main()
{
	int num;
	printf("\n 〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
	printf("  피보나치 수열을 출력합니다.\n");
	printf("  몇 번째 항까지 출력할 지 입력해 주세요 : ");
	scanf("%d", &num); // 몇 번째 항까지 출력할 것인지 입력 받음
	printf("\n 〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
	PrintFibo(num); // 피보나치 수열을 출력하는 함수 호출
	return 0;
}

void PrintFibo(int num)
{
	int i = 0;
	int count = 1;
	int fibo_0 = 0;
	int fibo_1 = 1;
	int fibo_2;
	int max = INT_MAX; // int형 변수가 나타낼 수 있는 최대값
	//printf("최대 정수값 : %d\n", max);
	for (i = 0; i < num; i++)
	{
		if (i < 2)
		{
			printf(" %d항: %10d\t",i,i); // 0항과 1항은 0,1이므로 그냥 출력
			count++;
		}
		else
		{
			if (fibo_1>max-fibo_0) // 계산한 값이 오버플로우 되면 루프 종료
			{
				printf("\n\n ◇계산 값이 범위를 벗어났습니다.\n");
				break;
			}
			else
			{
				fibo_2 = fibo_0 + fibo_1; // 다음항은 그 전과, 전전 항의 합
				fibo_0 = fibo_1; // 다음 항으로 하나 증가
				fibo_1 = fibo_2; // 다음 항으로 하나 증가
				printf(" %d항: %10d\t",i, fibo_2);
				if (count % 3 == 0) // 한 줄에 3 항씩 출력 하도록 함
					printf("\n ─────────────────────────────────────\n");
				count++;
			}
		}
	}
	printf("\n 〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n ");
}