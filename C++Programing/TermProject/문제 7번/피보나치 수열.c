// �Ǻ���ġ ������ ����ϴ� ���α׷�
// 1316592 ������
#include<stdio.h>
#include<limits.h>
void PrintFibo(int num);

int main()
{
	int num;
	printf("\n ��������������������������������������\n");
	printf("  �Ǻ���ġ ������ ����մϴ�.\n");
	printf("  �� ��° �ױ��� ����� �� �Է��� �ּ��� : ");
	scanf("%d", &num); // �� ��° �ױ��� ����� ������ �Է� ����
	printf("\n ��������������������������������������\n");
	PrintFibo(num); // �Ǻ���ġ ������ ����ϴ� �Լ� ȣ��
	return 0;
}

void PrintFibo(int num)
{
	int i = 0;
	int count = 1;
	int fibo_0 = 0;
	int fibo_1 = 1;
	int fibo_2;
	int max = INT_MAX; // int�� ������ ��Ÿ�� �� �ִ� �ִ밪
	//printf("�ִ� ������ : %d\n", max);
	for (i = 0; i < num; i++)
	{
		if (i < 2)
		{
			printf(" %d��: %10d\t",i,i); // 0�װ� 1���� 0,1�̹Ƿ� �׳� ���
			count++;
		}
		else
		{
			if (fibo_1>max-fibo_0) // ����� ���� �����÷ο� �Ǹ� ���� ����
			{
				printf("\n\n �ް�� ���� ������ ������ϴ�.\n");
				break;
			}
			else
			{
				fibo_2 = fibo_0 + fibo_1; // �������� �� ����, ���� ���� ��
				fibo_0 = fibo_1; // ���� ������ �ϳ� ����
				fibo_1 = fibo_2; // ���� ������ �ϳ� ����
				printf(" %d��: %10d\t",i, fibo_2);
				if (count % 3 == 0) // �� �ٿ� 3 �׾� ��� �ϵ��� ��
					printf("\n ��������������������������������������������������������������������������\n");
				count++;
			}
		}
	}
	printf("\n ��������������������������������������\n ");
}