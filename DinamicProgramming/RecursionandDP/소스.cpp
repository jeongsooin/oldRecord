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

/* ���� ������ �Լ� ����*/
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

/* ������ ���ڿ��� �Է¹��� ũ��� �����Ѵ�. */
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

/* ���̸� ������ �Է¹ް�, �߸��� �Է��� ���� ���� ����ó�� */
int getNumber() {

	int retNum;
	cout << " �������� <Random string generation> ��������\n";
	cout << " ���ڿ��� ���̸� �Է��ϼ���.     \n" << endl;
	cout << " Enter >> ";
	cin >> retNum;
	cout << " ��������������������������������������������\n";

	if (cin.fail()) {
		cout << endl;
		cout << "������������������ Error! ������������������\n";
		cout << "�� ���ڿ��� ���̸� ���ڷ� �Է����ֽʽÿ�. ��" << endl;
		cout << "��������������������������������������������\n\n";
		cin.clear();
		cin.ignore(256, '\n'); // �Է¹��۸� ���
		return getNumber();
	}

	return retNum;
}

/* ���̸� ������ �Է¹ް�, �߸��� �Է��� ���� ���� ����ó�� */
int getMenu() {

	int retNum;
	cout << " Enter >> ";
	cin >> retNum;

	if (cin.fail()) {
		cout << " 1�Ǵ� 2�� �Է��� �� �ֽ��ϴ�.\n" << endl;
		cin.clear();
		cin.ignore(256, '\n'); // �Է¹��۸� ���
		return getMenu();
	}
	return retNum;
}

/* Recursion ����� LCS �˰��� */
int RecursionLCS(int i, int j)
{

	if (i == m || j == n)
		return 0;
	else if (string1[i] == string2[j])
		return RecursionLCS(i + 1, j + 1) + 1;
	else
		return MAX(RecursionLCS(i + 1, j), RecursionLCS(i, j + 1));

}

/* Dynamic Programming ����� LCS �˰��� */
int DynamicLCS()
{

	cout << " ��<Dynamic Programming>                                   ��\n";
	cout << " ��   �� Result ��                                         ��\n";

	str1 = "0" + str1;
	str2 = "0" + str2;

	LARGE_INTEGER StartCounter, EndCounter, liFrequency;// �ð� ������ ����ϱ� ���� ����
	QueryPerformanceFrequency(&liFrequency); // ���ļ�(1�ʴ� �����Ǵ� ī��Ʈ��)�� ���Ѵ�. �ð������� �ʱ�ȭ
	QueryPerformanceCounter(&StartCounter); // �ڵ� ���� �� ī��Ʈ ����

	int LCS_length = 0;
	int MAX;
	int **memo; // 2���� �迭�� �������� �Ҵ��� ���̹Ƿ� ** Ÿ������ ����
	int x = str1.length();
	int y = str2.length();

	memo = new int*[y]; // 2���� �迭�� ���� �Ҵ�

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
	cout << " ��    LCS Length : " << LCS_length << "                                      ��\n";

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
	//cout << " ��    LCS Sequence : "<<LCS << "                                ��\n";

	QueryPerformanceCounter(&EndCounter); // �ڵ� ���� �� ī��Ʈ ����
	double seconds = (double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart;
	cout << " ��    Execution time : " << seconds << " sec" << "                   ��\n";

	return 0;
}
int main()
{
	cout.setf(ios::fixed);
	cout << "\n������������������������������������������������������������������";
	cout << "\n�� <Longest common subsequence problem>                         ��";
	cout << "\n�� LCS �˰����� Recursion ��İ� DP ������� ���α׷����ϰ�   ��";
	cout << "\n�� ������ ���� �ð��� �м��ϴ� ���α׷� �Դϴ�.                 ��";
	cout << "\n������������������������������������������������������������������";
	cout << "\n ���ڿ��� �������� �����ϰų� ���� �Է��� �� �ֽ��ϴ�.\n";
	cout << "\n [1] ���� ���ڿ� �Է�\n [2] ���� ���ڿ� ����\n";

	int string_length = 0;
	int menu = getMenu();
	cout << endl;

	switch (menu)
	{
	case 1:
		cout << " ���������������� <Set String> ����������������\n";
		cout << "   STRING 1 >> ";
		cin >> str1;
		cout << "   STRING 2 >> ";
		cin >> str2;
		cout << " ����������������������������������������������\n";
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
		cout << " �޴��� �߸��Է��ϼ̽��ϴ�.\n";
		return 0;
	}

	string1 = str1.c_str();
	string2 = str2.c_str();
	m = strlen(string1);
	n = strlen(string2);
	cout << " m = " << m << endl;
	cout << " n = " << n << endl;

	cout << " ������������������������������������������������������������\n";

	/* Recurion ����� ���� �ð��� �����Ѵ�. */
	LARGE_INTEGER StartCounter, EndCounter, liFrequency;// �ð� ������ ����ϱ� ���� ����
	QueryPerformanceFrequency(&liFrequency); // ���ļ�(1�ʴ� �����Ǵ� ī��Ʈ��)�� ���Ѵ�. �ð������� �ʱ�ȭ
	QueryPerformanceCounter(&StartCounter); // �ڵ� ���� �� ī��Ʈ ����

	cout << " ��<Recursion>                                             ��\n";
	cout << " ��    �� Result ��                                        ��\n";
	cout << " ��    LCS Length : " << RecursionLCS(0, 0) << "                                      ��\n";

	QueryPerformanceCounter(&EndCounter); // �ڵ� ���� �� ī��Ʈ ����
	double recursion_sec = (double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart;

	cout.precision(10);
	cout << " ��    Execution time : " << recursion_sec << " sec                   ��\n";
	cout << " ������������������������������������������������������������\n";

	/* DynamicLCS ȣ�� */
	DynamicLCS();
	cout << " ������������������������������������������������������������\n";
	
	/* ����� ������ ���������� �˷� ��*/
	for (int i = 0; i < 3; i++) 
		Beep(523, 200);

	return 0;
}