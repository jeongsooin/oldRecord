// �Ҽ� �˻� ���α׷�
// 1316592 ������ 
#include <iostream>
using namespace std;

class Prime // �Ҽ� Ŭ���� ����
{
public:
	void Is_Prime();
	void Print_prime();
	void Set_number();
private:
	int m_user_num;
};
void Prime::Is_Prime()
{
	//cout << "Test2: " << this->m_user_num << "\n";
	int num = this->m_user_num;  // ���� ���� ��ü�� ������ ��� ������ �ʱ�ȭ
	for (int i = 2; i <= num ; i++) // �Ҽ� �Ǻ� �˰���, 0�� 1�� ���� �Ѵ�.
	{
		if (num == 2 || num ==3) // 2�� 3�� �Ҽ�
		{
			cout << "  �Ҽ��Դϴ�.\n";
			cout << "\n" << " ����������������������������������������������\n  ";
			break;
		}
		else if (num%i == 0) // �ϳ��� ������ �������� ���� ������ �Ҽ��� �ƴϴ�.
		{
			cout << "  �Ҽ��� �ƴմϴ�.\n";
			cout << "\n" << " ����������������������������������������������\n  ";
			break;
		}
		else if (i == num - 1) // ���������� ������ �� ������ �������� ������ �Ҽ� 
		{
			cout << "  �Ҽ��Դϴ�.\n";
			cout << "\n" << " ����������������������������������������������\n  ";
			break;
		}
		else 
			continue;
	}
}

void Prime::Set_number() // ��� ������ �ʱ�ȭ �Ѵ�
{
	int num;
	while (true)
	{
		cout << "  2���� 100������ ���� �� �ϳ��� �Է��ϼ���.\n";
		cout << "  >> ���� �Է� : ";
		cin >> num;
		if (num < 2 || num > 100)
		{
			cout << "�ùٸ� ������ ������ �Է��ϼ���.\n";
			continue;
		}
		this -> m_user_num = num; // �Է¹��� ������ this �����͸� ���� ��� ������ �����Ѵ�
		//cout << "Test : " << this -> m_user_num << "\n";
		break;
	}
}

void Prime::Print_prime() // ���� �� ��� �Ҽ��� ����Ѵ�.
{
	//cout << "Test3 : " << num << "\n";
	int count = 1;  // ����� �� �ٹٲ��� �ϱ� ���� �� �ٲ� �Ǻ� ���ڸ� ������ ����
	int num = this->m_user_num;  // this �����͸� ���� ���� ���� ���� ��ü�� ��� ������ �ʱ�ȭ
	for (int i = 2; i <= num; i++)
	{
		for (int j = 2; j <= i - 1; j++)
		{
			if (i%j == 0) break; //�Ҽ��� �ƴ� ���� ������� �ʴ´�
			else if (j == i - 1 && count % 5 == 0) //���������� �������� �ʰ� �� �ٿ� 5�� ��� �Ǿ����� �� �ٲ�
			{
				cout.width(5);
				cout << i << "\n";
				count++;
			}
			else if (j == i - 1 && count % 5 != 0) //���������� �������� ������ �Ҽ��̹Ƿ� ���
			{
				cout.width(5);
				cout << i << "     ";
				count++;
			}
			else
				continue;
		}
	}
	cout << "\n" << " ����������������������������������������������\n  ";
	//cout << "����Ʈ �׽�Ʈ\n";
}
int main()
{
	char menu;
	Prime p1; // ��ü ����
	cout << "\n  �Ҽ����� �˾ƺ��� ����ϴ� ���α׷�\n";
	cout << " ����������������������������������������������\n";
	p1.Set_number(); // ��ü�� ��� ���� �ʱ�ȭ �Լ� ȣ��
	cout << "\n" << " ����������������������������������������������\n";
	cout << "  1. �Է��� ���� �Ҽ����� �˻�\n";
	cout << "  2. �Է��� ������ �����ϴ� ��� �Ҽ� ���\n";
	cout << "  3. ���α׷� ����\n";
	cout << "  >> �޴� ���� : ";
	cin >> menu;
	cout << " ����������������������������������������������\n";
	switch (menu)
	{
	case '1':
		p1.Is_Prime(); // �Ҽ� �Ǻ� �Լ� ȣ��
		break;
	case '2':
		p1.Print_prime(); // �Ҽ� ��� �Լ� ȣ��
		break;
	case '3':
		break;
	default:
		cout << "  �Է��� �߸��Ǿ����ϴ�.\n";
	}
	return 0;
}