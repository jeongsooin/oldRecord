/* Recursion and Dynamic Programming */
/* 18 May 2017 */
#include <iostream>
#include<string>
#include<time.h>
#include<random>
#include <stdlib.h> 
#include <windows.h>
#define MAX(x,y) (x>y?x:y)
using namespace std;

/* 전역 변수와 함수 선언*/
string str1;
string str2;
const char* string1;
const char* string2;
int m, n;

string RandomString(int len);
int getNumber();
int getMenu();
int RecursionLCS(int i, int j);
int DynamicLCS();
//int DynamicLCS(int** arr);

/* 무작위 문자열을 입력받은 크기로 생성한다. */
string RandomString(int len)
{
	srand(time(0));
	string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	string newstr;
	int pos;
	while (newstr.size() != len) {
		pos = ((rand() % (str.size() - 1)));
		newstr += str.substr(pos, 1);
	}
	return newstr;
}

/* 길이를 정수로 입력받고, 잘못된 입력이 들어올 때는 예외처리 */
int getNumber() {

	int retNum;
	cout << " ──── <Random string generation> ────\n";
	cout << " 문자열의 길이를 입력하세요.     \n" << endl;
	cout << " Enter >> ";
	cin >> retNum;
	cout << " ──────────────────────\n";

	if (cin.fail()) {
		cout << endl;
		cout << "┌──────── Error! ────────┐\n";
		cout << "│ 문자열의 길이를 숫자로 입력해주십시오. │" << endl;
		cout << "└────────────────────┘\n\n";
		cin.clear();
		cin.ignore(256, '\n'); // 입력버퍼를 비움
		return getNumber();
	}

	return retNum;
}

/* 길이를 정수로 입력받고, 잘못된 입력이 들어올 때는 예외처리 */
int getMenu() {

	int retNum;
	cout << " Enter >> ";
	cin >> retNum;

	if (cin.fail()) {
		cout << " 1또는 2만 입력할 수 있습니다.\n" << endl;
		cin.clear();
		cin.ignore(256, '\n'); // 입력버퍼를 비움
		return getMenu();
	}
	return retNum;
}

/* Recursion 방식의 LCS 알고리즘 */
int RecursionLCS(int i, int j)
{

	if (i == m || j == n)
		return 0;
	else if (string1[i] == string2[j])
		return RecursionLCS(i + 1, j + 1) + 1;
	else
		return MAX(RecursionLCS(i + 1, j), RecursionLCS(i, j + 1));

}

/* Dynamic Programming 방식의 LCS 알고리즘 */
int DynamicLCS()
{

	cout << " │<Dynamic Programming>                                   │\n";
	cout << " │   ─ Result ─                                         │\n";

	str1 = "0" + str1;
	str2 = "0" + str2;

	LARGE_INTEGER StartCounter, EndCounter, liFrequency;// 시간 측정에 사용하기 위한 변수
	QueryPerformanceFrequency(&liFrequency); // 주파수(1초당 증가되는 카운트수)를 구한다. 시간측정의 초기화
	QueryPerformanceCounter(&StartCounter); // 코드 수행 전 카운트 저장

	int LCS_length = 0;
	int MAX;
	int **memo; // 2차원 배열을 동적으로 할당할 것이므로 ** 타입으로 선언
	int x = str1.length();
	int y = str2.length();

	memo = new int*[y]; // 2차원 배열의 동적 할당

	for (int i = 0; i < y; i++) {
		memo[i] = new int[x];
	}

	for (int i = 0; i < x; i++) {
		memo[0][i] = 0;
	}
	for (int i = 1; i < y; i++) {
		MAX = 0;
		memo[i][0] = 0;
		for (int j = 1; j < x; j++) {
			if (str2[i] == str1[j]) {
				MAX = memo[i - 1][j - 1] + 1;
				memo[i][j] = MAX;
			}
			else {
				if (memo[i][j - 1] > memo[i - 1][j])
					memo[i][j] = memo[i][j - 1];
				else
					memo[i][j] = memo[i - 1][j];
			}
		}
		if (LCS_length < MAX) LCS_length = MAX;
	}
	cout << " │    LCS Length : " << LCS_length << "                                      │\n";

	int temp0, temp1, for_j;
	temp1 = LCS_length;
	temp0 = temp1 - 1;
	for_j = x - 1;
	string LCS = "";

	for (int i = y - 1; i >0; i--) {
		for (int j = for_j; j > 0; j--) {
			if (memo[i][j] == temp1 && memo[i][j - 1] == temp0 && memo[i - 1][j - 1] == temp0 && memo[i - 1][j] == temp0) {
				temp0--;
				temp1--;
				LCS = str2[i] + LCS;
				for_j = j;
				break;
			}
		}
	}
	//cout << " │    LCS Sequence : "<<LCS << "                                │\n";

	QueryPerformanceCounter(&EndCounter); // 코드 수행 후 카운트 저장
	double seconds = (double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart;
	cout << " │    Execution time : " << seconds << " sec" << "                   │\n";

	return 0;
}
int main()
{
	cout.setf(ios::fixed);
	cout << "\n┌───────────────────────────────┐";
	cout << "\n│ <Longest common subsequence problem>                         │";
	cout << "\n│ LCS 알고리즘을 Recursion 방식과 DP 방식으로 프로그래밍하고   │";
	cout << "\n│ 각각의 수행 시간을 분석하는 프로그램 입니다.                 │";
	cout << "\n└───────────────────────────────┘";
	cout << "\n 문자열을 랜덤으로 생성하거나 직접 입력할 수 있습니다.\n";
	cout << "\n [1] 직접 문자열 입력\n [2] 랜덤 문자열 생성\n";

	int string_length = 0;
	int menu = getMenu();
	cout << endl;

	switch (menu)
	{
	case 1:
		cout << " ──────── <Set String> ────────\n";
		cout << "   STRING 1 >> ";
		cin >> str1;
		cout << "   STRING 2 >> ";
		cin >> str2;
		cout << " ───────────────────────\n";
		break;
	case 2:
		string_length = getNumber();
		str1 = RandomString(string_length);
		cout << " STRING 1 : [ " << str1 << " ]" << endl << endl;
		string_length = getNumber();
		str2 = RandomString(string_length);
		cout << " STRING 2 : [ " << str2 << " ]" << endl << endl;
		break;
	default:
		cout << " 메뉴를 잘못입력하셨습니다.\n";
		return 0;
	}

	string1 = str1.c_str();
	string2 = str2.c_str();
	m = strlen(string1);
	n = strlen(string2);
	cout << " m = " << m << endl;
	cout << " n = " << n << endl;

	cout << " ┌────────────────────────────┐\n";

	/* Recurion 방식의 수행 시간을 측정한다. */
	LARGE_INTEGER StartCounter, EndCounter, liFrequency;// 시간 측정에 사용하기 위한 변수
	QueryPerformanceFrequency(&liFrequency); // 주파수(1초당 증가되는 카운트수)를 구한다. 시간측정의 초기화
	QueryPerformanceCounter(&StartCounter); // 코드 수행 전 카운트 저장

	cout << " │<Recursion>                                             │\n";
	cout << " │    ─ Result ─                                        │\n";
	cout << " │    LCS Length : " << RecursionLCS(0, 0) << "                                      │\n";

	QueryPerformanceCounter(&EndCounter); // 코드 수행 후 카운트 저장
	double recursion_sec = (double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart;

	cout.precision(10);
	cout << " │    Execution time : " << recursion_sec << " sec                   │\n";
	cout << " │────────────────────────────│\n";

	/* DynamicLCS 호출 */
	DynamicLCS();
	cout << " └────────────────────────────┘\n";
	
	/* 결과가 나오면 비프음으로 알려 줌*/
	for (int i = 0; i < 3; i++) 
		Beep(523, 200);

	return 0;
}