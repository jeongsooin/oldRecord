// 단계별 별찍기 프로그램
//1316592 정수인
#include <iostream>
using namespace std;

class Star // 클래스 선언
{
public:
	void Print_Starline(int line_num);
	void Set_Starline(int line_num);
private:
	int m_line_num;
};
void Star::Print_Starline(int line_num) //출력 함수 정의
{
	cout << "  ────────────────────────────" << "\n";
	for (int i = 0; i <line_num; i++) // 몇 줄을 출력하는지 조건 
	{
		for (int j = 0; j < line_num; j++) // 각 줄마다 별을 몇 개 출력하는지 조건
		{
			cout << "   *";
			if (i == j) break; // 줄 번호와 별 개수가 같아지면 별 찍기 종료
			else continue;
		}
		cout << " \n";
	}
	cout << "  ────────────────────────────" << "\n";
}

void Star::Set_Starline(int line_num)// 멤버 변수를 멤버 함수를 통해 설정
{
	m_line_num = line_num;  // 인자로 사용자가 입력한 정수 받아 변수 초기화
}
int main()
{
	Star star_1;
	int num;
	int menu;
	cout << "\n  입력한 숫자에 따라 * 모양을 출력하는 프로그램 입니다.\n";
	cout << "  1. 계속\n  2. 종료\n" << "  〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << "\n";
	while (true) // 종료 조건 선택할 때까지 반복
	{
		cout << "  1 - 20 사이의 숫자를 입력하세요 : ";
		cin >> num;
		star_1.Set_Starline(num);
		if (num <= 0 || num > 20)
		{
			cout << "  범위에 맞는 숫자만 입력할 수 있습니다.\n";
			cout << "  프로그램을 계속 하시겠습니까? : ";
			cin >> menu;
			cout << "────────────────────────────" << "\n";
			if (menu == 1) continue;
			else break;
		}
		star_1.Print_Starline(num);
		cout << "  프로그램을 계속 하시겠습니까? : ";
		cin >> menu;
		cout << "  ────────────────────────────" << "\n  ▷";
		if (menu == 1) continue; // 프로그램 종료 조건
		else break; // 루프를 빠져 나간다
	}
	return 0;
}