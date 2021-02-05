// 구구단 출력 프로그램
//1316592 정수인
#include <iostream>
using namespace std;

class Multiplication_tables //구구단 클래스 정의
{
public:
	void Print_table();
	void Print_all();
	void Set_tablenum(int t_num);
private:
	int m_table_number;
};

void Multiplication_tables::Set_tablenum(int t_num) // 멤버 변수 설정
{
	m_table_number = t_num; // 몇 단 까지인지를 나타내는 변수를 입력받아 설정
}
void Multiplication_tables::Print_table() //구구단 출력
{
	int count = 1;
	cout << "\n" << "  ──────────────────────────────────" << "\n";
	for (int i = 1; i < 10; i++)
	{
		cout <<"  " <<m_table_number << "x" << i << "=" << m_table_number*i << " "; // i 단을 출력
		if (count % 3 == 0)
			cout << "\n";
		count++;
	}
}

void Multiplication_tables::Print_all()
{
	int count = 1;
	for (int i = 1; i < 10; i++) // 단을 나타내는 루프
	{
		for (int j = 1; j < 10; j++) //단에 곱할 수를 나타내는 루프 
		{
			cout <<"  "<< i << "x" << j << "=" << i*j << " "; //모든 단에 대해 i*j를 출력
			if (count % 3 == 0)
				cout << "\n";
			count++;
		}
		cout << "  ──────────────────────────────────" << "\n";
	}
}
int main()
{
	int menu;
	int user_num;
	Multiplication_tables table1; //클래스 객체 생성
	cout << "\n  구구단을 출력하는 프로그램 입니다.";
	cout << "\n" << "  〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << "\n";
	while (true) // 종료 조건이 만족될 때까지 계속되는 루프
	{
		cout << "  원하시는 메뉴를 골라주십시오.\n\n  1. 원하는 구구단만 출력\n  2. 전체 구구단 출력\n  3. 프로그램 종료\n";
		cout << "  ──────────────────────────────────" << "\n  ▷ ";
		cin >> menu;
		switch (menu)
		{
		case 1:
			cout << "  출력하고 싶은 단의 숫자를 입력해주십시오.\n  ▷ ";
			cin >> user_num;
			table1.Set_tablenum(user_num); //클래스 객체의 멤버 변수 초기화
			table1.Print_table(); // 원하는 단을 출력하는 함수 호출
			cout <<"\n"<< "  ──────────────────────────────────" << "\n";
			break;
		case 2:
			table1.Print_all(); // 모든 단을 출력하는 함수 호출
			break;
		case 3:
			break;
		default:
			cout << "  메뉴에 있는 숫자를 골라주십시오.\n  ▷ ";
			break;
		}
		if (menu == 3) break; //종료 조건이 만족되면 루프 탈출
		else continue;
	}
	return 0;
}