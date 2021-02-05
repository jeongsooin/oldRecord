// ������ ��� ���α׷�
//1316592 ������
#include <iostream>
using namespace std;

class Multiplication_tables //������ Ŭ���� ����
{
public:
	void Print_table();
	void Print_all();
	void Set_tablenum(int t_num);
private:
	int m_table_number;
};

void Multiplication_tables::Set_tablenum(int t_num) // ��� ���� ����
{
	m_table_number = t_num; // �� �� ���������� ��Ÿ���� ������ �Է¹޾� ����
}
void Multiplication_tables::Print_table() //������ ���
{
	int count = 1;
	cout << "\n" << "  ��������������������������������������������������������������������" << "\n";
	for (int i = 1; i < 10; i++)
	{
		cout <<"  " <<m_table_number << "x" << i << "=" << m_table_number*i << " "; // i ���� ���
		if (count % 3 == 0)
			cout << "\n";
		count++;
	}
}

void Multiplication_tables::Print_all()
{
	int count = 1;
	for (int i = 1; i < 10; i++) // ���� ��Ÿ���� ����
	{
		for (int j = 1; j < 10; j++) //�ܿ� ���� ���� ��Ÿ���� ���� 
		{
			cout <<"  "<< i << "x" << j << "=" << i*j << " "; //��� �ܿ� ���� i*j�� ���
			if (count % 3 == 0)
				cout << "\n";
			count++;
		}
		cout << "  ��������������������������������������������������������������������" << "\n";
	}
}
int main()
{
	int menu;
	int user_num;
	Multiplication_tables table1; //Ŭ���� ��ü ����
	cout << "\n  �������� ����ϴ� ���α׷� �Դϴ�.";
	cout << "\n" << "  �����������������������������������" << "\n";
	while (true) // ���� ������ ������ ������ ��ӵǴ� ����
	{
		cout << "  ���Ͻô� �޴��� ����ֽʽÿ�.\n\n  1. ���ϴ� �����ܸ� ���\n  2. ��ü ������ ���\n  3. ���α׷� ����\n";
		cout << "  ��������������������������������������������������������������������" << "\n  �� ";
		cin >> menu;
		switch (menu)
		{
		case 1:
			cout << "  ����ϰ� ���� ���� ���ڸ� �Է����ֽʽÿ�.\n  �� ";
			cin >> user_num;
			table1.Set_tablenum(user_num); //Ŭ���� ��ü�� ��� ���� �ʱ�ȭ
			table1.Print_table(); // ���ϴ� ���� ����ϴ� �Լ� ȣ��
			cout <<"\n"<< "  ��������������������������������������������������������������������" << "\n";
			break;
		case 2:
			table1.Print_all(); // ��� ���� ����ϴ� �Լ� ȣ��
			break;
		case 3:
			break;
		default:
			cout << "  �޴��� �ִ� ���ڸ� ����ֽʽÿ�.\n  �� ";
			break;
		}
		if (menu == 3) break; //���� ������ �����Ǹ� ���� Ż��
		else continue;
	}
	return 0;
}