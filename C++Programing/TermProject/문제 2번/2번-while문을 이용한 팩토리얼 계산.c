// while ���� �̿��� ���丮�� ��� ���α׷�
//1316592 ������
#include <stdio.h>
int main()
{
	int factorial_num = 0;
	int result = 1;
	int init_num = 1;
	printf("���丮�� ����� �ϴ� ���α׷� �Դϴ�.\n");
	printf("����������������������������������������\n");
	while (1) //�˸´� ������ ���ڸ� �Է��� ������ �Է��� �޴´�.
	{
		printf("������ �ϳ� �Է��� �ּ���. : ");
		scanf("%d", &factorial_num);
		if (factorial_num <= 0) //0������ ���ڸ� �Է��ϸ� �ٽ� �Է� �޴´�.
		{
			printf("����� �� �����ϴ�.\n���� ������ �Է��� �ֽʽÿ�.\n\n");
			continue;
		}
		else break;//�ùٸ� �Է°��� ������ �������� ����� �Ѵ�.
	}
	printf("����������������������������������������\n");
	while (init_num <= factorial_num)//while���� �̿��Ͽ� ����Ѵ�.
	{
		result *= init_num;
		init_num++;
	}

	printf("%d�� ���丮�� ��� ���� %d �Դϴ�.\n",factorial_num, result);
	printf("����������������������������������������\n");

	return 0;
}