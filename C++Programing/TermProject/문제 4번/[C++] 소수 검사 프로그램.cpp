// 소수 검사 프로그램
// 1316592 정수인 
#include <iostream>
using namespace std;

class Prime // 소수 클래스 정의
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
	int num = this->m_user_num;  // 실행 중인 객체의 변수를 멤버 변수로 초기화
	for (int i = 2; i <= num ; i++) // 소수 판별 알고리즘, 0과 1은 제외 한다.
	{
		if (num == 2 || num ==3) // 2나 3은 소수
		{
			cout << "  소수입니다.\n";
			cout << "\n" << " ───────────────────────\n  ";
			break;
		}
		else if (num%i == 0) // 하나라도 나누어 떨어지는 수가 있으면 소수가 아니다.
		{
			cout << "  소수가 아닙니다.\n";
			cout << "\n" << " ───────────────────────\n  ";
			break;
		}
		else if (i == num - 1) // 마지막까지 나눴을 때 나누어 떨어지지 않으면 소수 
		{
			cout << "  소수입니다.\n";
			cout << "\n" << " ───────────────────────\n  ";
			break;
		}
		else 
			continue;
	}
}

void Prime::Set_number() // 멤버 변수를 초기화 한다
{
	int num;
	while (true)
	{
		cout << "  2부터 100까지의 정수 중 하나를 입력하세요.\n";
		cout << "  >> 정수 입력 : ";
		cin >> num;
		if (num < 2 || num > 100)
		{
			cout << "올바른 범위의 정수를 입력하세요.\n";
			continue;
		}
		this -> m_user_num = num; // 입력받은 변수를 this 포인터를 통해 멤버 변수에 대입한다
		//cout << "Test : " << this -> m_user_num << "\n";
		break;
	}
}

void Prime::Print_prime() // 범위 내 모든 소수를 출력한다.
{
	//cout << "Test3 : " << num << "\n";
	int count = 1;  // 출력할 때 줄바꿈을 하기 위해 줄 바꿈 판별 숫자를 저장할 변수
	int num = this->m_user_num;  // this 포인터를 통해 현재 실행 중인 객체의 멤버 변수로 초기화
	for (int i = 2; i <= num; i++)
	{
		for (int j = 2; j <= i - 1; j++)
		{
			if (i%j == 0) break; //소수가 아닌 수는 출력하지 않는다
			else if (j == i - 1 && count % 5 == 0) //마지막까지 나눠지지 않고 한 줄에 5개 출력 되었으면 줄 바꿈
			{
				cout.width(5);
				cout << i << "\n";
				count++;
			}
			else if (j == i - 1 && count % 5 != 0) //마지막까지 나눠지지 않으면 소수이므로 출력
			{
				cout.width(5);
				cout << i << "     ";
				count++;
			}
			else
				continue;
		}
	}
	cout << "\n" << " ───────────────────────\n  ";
	//cout << "프린트 테스트\n";
}
int main()
{
	char menu;
	Prime p1; // 객체 생성
	cout << "\n  소수인지 알아보고 출력하는 프로그램\n";
	cout << " ───────────────────────\n";
	p1.Set_number(); // 객체의 멤버 변수 초기화 함수 호출
	cout << "\n" << " ───────────────────────\n";
	cout << "  1. 입력한 수가 소수인지 검사\n";
	cout << "  2. 입력한 범위에 존재하는 모든 소수 출력\n";
	cout << "  3. 프로그램 종료\n";
	cout << "  >> 메뉴 선택 : ";
	cin >> menu;
	cout << " ───────────────────────\n";
	switch (menu)
	{
	case '1':
		p1.Is_Prime(); // 소수 판별 함수 호출
		break;
	case '2':
		p1.Print_prime(); // 소수 출력 함수 호출
		break;
	case '3':
		break;
	default:
		cout << "  입력이 잘못되었습니다.\n";
	}
	return 0;
}