// �빮��, �ҹ���, �����ڰ� �ƴ� ������ ������ ���� ���α׷�
//1316592 ������
#include<stdio.h>

int main()
{
	char string[256];
	int i;
	int upper_case = 0;
	int lower_case = 0;
	int non_alphabet = 0;
	printf(" ��������������������������������������������������������������");
	printf("\n  ���ڿ��� �Է����ֽʽÿ� : ");
	scanf("%s", string);
	for (i = 0; i < 256; i++) //���ڿ��� ������ �迭�� ������ ����
	{
		if (string[i] >= 65 && string[i] <= 90) // �빮���� ��
			upper_case++;
		else if (string[i] >= 97 && string[i] <= 122) // �ҹ����� ��
			lower_case++;
		else if (string[i] == '\0') // ���ڿ��� ����Ǵ� �� ���ڸ� ������ ���� ����
			break;
		else
			non_alphabet++; // �����ڰ� �ƴ� �� 
	}
	printf(" ��������������������������������������������������������������");
	printf("\n  �빮�� : %d��\n  �ҹ��� : %d��\n  �����ڰ� �ƴ� ���� : %d��\n\n  ��", upper_case, lower_case, non_alphabet);

	return 0;
}