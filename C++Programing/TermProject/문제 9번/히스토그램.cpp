// 값의 분포를 히스토그램으로 만들어주는 프로그램
// 1316592 정수인
#include<iostream>
using namespace std;

class Histogram //히스토그램 클래스 선언
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
	for (int i = 0; i < 10 + 1; i++) // 반복문을 돌면서 횟수를 저장하는 멤버 변수를 모두 0으로 초기화 한다.
	{
		m_counter[i] = 0;
	}
}
void Histogram::PrintStar()
{
	cout << "\n 〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n";
	for (int i = 0; i < 10; i++)
	{
		if (m_counter[i] == 0) // 횟수가 0이면 출력하지 말아야 하니까 그냥 개행 문자만 출력한다
		{
			cout << "  " << ((i + 1) * 10) - 9 << " ─ " << (i + 1) * 10 << " : ";
			cout << "\n";
		}
		else
		{
			cout << "  " << ((i + 1) * 10) - 9 << " ─ " << (i + 1) * 10 << " : ";
			for (int j = 0; j < m_counter[i]; j++) // 0이 아닐 때는 존재하는 횟수만큼 반복문을 돌면서 *을 출력한다.
				cout << "*";
			cout << "\n";
		}
	}
	cout << " 〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n";
}
void Histogram::InputNumber(int num) // 사용자가 입력한 정수를 인자로 받는다.
{
	if (num >= 1 && num <= 10) // 들어온 인자를 다음 조건식에 맞는지 검사해서 멤버 변수를 증가시킨다.
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
	Histogram h1; // 객체 생성
	h1.Initialize();  // 객체의 멤버 변수 초기화
	cout << "┌──────────────────────────────┐\n";
	cout << "│입력 값들의 분포를 히스토그램으로 나타내는 프로그램 입니다. │\n";
	cout << "│1부터 100 사이의 정수 10개를 입력하세요                     │\n";
	cout << "└──────────────────────────────┘\n";
	for (int i = 0; i < 10; i++) // 정수를 10개 입력 받는다
	{
		cin >> num;
		cout << "\b";
		h1.InputNumber(num);
	}
	//cout << "test" << endl;
	h1.PrintStar();
	//cout << "test" << endl;
}
