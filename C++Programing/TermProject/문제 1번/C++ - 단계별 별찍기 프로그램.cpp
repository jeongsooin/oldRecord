// �ܰ躰 ����� ���α׷�
//1316592 ������
#include <iostream>
using namespace std;

class Star // Ŭ���� ����
{
public:
	void Print_Starline(int line_num);
	void Set_Starline(int line_num);
private:
	int m_line_num;
};
void Star::Print_Starline(int line_num) //��� �Լ� ����
{
	cout << "  ��������������������������������������������������������" << "\n";
	for (int i = 0; i <line_num; i++) // �� ���� ����ϴ��� ���� 
	{
		for (int j = 0; j < line_num; j++) // �� �ٸ��� ���� �� �� ����ϴ��� ����
		{
			cout << "   *";
			if (i == j) break; // �� ��ȣ�� �� ������ �������� �� ��� ����
			else continue;
		}
		cout << " \n";
	}
	cout << "  ��������������������������������������������������������" << "\n";
}

void Star::Set_Starline(int line_num)// ��� ������ ��� �Լ��� ���� ����
{
	m_line_num = line_num;  // ���ڷ� ����ڰ� �Է��� ���� �޾� ���� �ʱ�ȭ
}
int main()
{
	Star star_1;
	int num;
	int menu;
	cout << "\n  �Է��� ���ڿ� ���� * ����� ����ϴ� ���α׷� �Դϴ�.\n";
	cout << "  1. ���\n  2. ����\n" << "  �����������������������������" << "\n";
	while (true) // ���� ���� ������ ������ �ݺ�
	{
		cout << "  1 - 20 ������ ���ڸ� �Է��ϼ��� : ";
		cin >> num;
		star_1.Set_Starline(num);
		if (num <= 0 || num > 20)
		{
			cout << "  ������ �´� ���ڸ� �Է��� �� �ֽ��ϴ�.\n";
			cout << "  ���α׷��� ��� �Ͻðڽ��ϱ�? : ";
			cin >> menu;
			cout << "��������������������������������������������������������" << "\n";
			if (menu == 1) continue;
			else break;
		}
		star_1.Print_Starline(num);
		cout << "  ���α׷��� ��� �Ͻðڽ��ϱ�? : ";
		cin >> menu;
		cout << "  ��������������������������������������������������������" << "\n  ��";
		if (menu == 1) continue; // ���α׷� ���� ����
		else break; // ������ ���� ������
	}
	return 0;
}