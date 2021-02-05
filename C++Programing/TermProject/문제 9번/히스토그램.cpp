// ���� ������ ������׷����� ������ִ� ���α׷�
// 1316592 ������
#include<iostream>
using namespace std;

class Histogram //������׷� Ŭ���� ����
{
public:
	void InputNumber(int num);
	void Initialize();
	void PrintStar();
protected:
	int m_counter[11];
};
void Histogram::Initialize()
{
	for (int i = 0; i < 10 + 1; i++) // �ݺ����� ���鼭 Ƚ���� �����ϴ� ��� ������ ��� 0���� �ʱ�ȭ �Ѵ�.
	{
		m_counter[i] = 0;
	}
}
void Histogram::PrintStar()
{
	cout << "\n �������������������������������\n";
	for (int i = 0; i < 10; i++)
	{
		if (m_counter[i] == 0) // Ƚ���� 0�̸� ������� ���ƾ� �ϴϱ� �׳� ���� ���ڸ� ����Ѵ�
		{
			cout << "  " << ((i + 1) * 10) - 9 << " �� " << (i + 1) * 10 << " : ";
			cout << "\n";
		}
		else
		{
			cout << "  " << ((i + 1) * 10) - 9 << " �� " << (i + 1) * 10 << " : ";
			for (int j = 0; j < m_counter[i]; j++) // 0�� �ƴ� ���� �����ϴ� Ƚ����ŭ �ݺ����� ���鼭 *�� ����Ѵ�.
				cout << "*";
			cout << "\n";
		}
	}
	cout << " �������������������������������\n";
}
void Histogram::InputNumber(int num) // ����ڰ� �Է��� ������ ���ڷ� �޴´�.
{
	if (num >= 1 && num <= 10) // ���� ���ڸ� ���� ���ǽĿ� �´��� �˻��ؼ� ��� ������ ������Ų��.
		m_counter[0]++;
	else if (num >= 11 && num <= 20)
		m_counter[1]++;
	else if (num >= 21 && num <= 30)
		m_counter[2]++;
	else if (num >= 31 && num <= 40)
		m_counter[3]++;
	else if (num >= 41 && num <= 50)
		m_counter[4]++;
	else if (num >= 51 && num <= 60)
		m_counter[5]++;
	else if (num >= 61 && num <= 70)
		m_counter[6]++;
	else if (num >= 71 && num <= 80)
		m_counter[7]++;
	else if (num >= 81 && num <= 90)
		m_counter[8]++;
	else if (num >= 91 && num <= 100)
		m_counter[9]++;
	else
		m_counter[10];
}
int main()
{
	int num;
	Histogram h1; // ��ü ����
	h1.Initialize();  // ��ü�� ��� ���� �ʱ�ȭ
	cout << "����������������������������������������������������������������\n";
	cout << "���Է� ������ ������ ������׷����� ��Ÿ���� ���α׷� �Դϴ�. ��\n";
	cout << "��1���� 100 ������ ���� 10���� �Է��ϼ���                     ��\n";
	cout << "����������������������������������������������������������������\n";
	for (int i = 0; i < 10; i++) // ������ 10�� �Է� �޴´�
	{
		cin >> num;
		cout << "\b";
		h1.InputNumber(num);
	}
	//cout << "test" << endl;
	h1.PrintStar();
	//cout << "test" << endl;
}
