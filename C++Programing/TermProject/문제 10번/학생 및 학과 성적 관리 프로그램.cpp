// ���� ���� ���α׷�
// 1316592 ������
#include <iostream>
#include <fstream>
using namespace std;

struct NODE // �л� ������ �����ϴ� ����ü
{
	char name[20];
	int id_num;
	int major_code;
	char major_name[20];
	int required1;
	int required2;
	int chosen1;
	int chosen2;
	int chosen3;
	int sum;
	int average;
	NODE* next;
};

struct List // ����ü ����Ʈ
{
	NODE* head;
	NODE* tail;
};
List m_List;

class Grade //Grade Ŭ���� ����
{
	friend class GradeManage;
public:
	void Set_Info();
	void PrintNode();
	void Get_Sum_and_Average();

protected:
	NODE* AddNode();
};

class GradeManage //GradeManage Ŭ���� ����
{
public:
	void GetStudent();
	void SetManager_INFO();
	void FindBest();
	void SubjectInfo();
	void GetMajorAvg();
protected:
	int m_manager_id;
	int m_student_num;
	int m_major_code;
	char m_manager_name[30];
};

void Grade::Set_Info() 
{
	NODE* firstnode = new NODE();
	firstnode->next = NULL;
	m_List.head = firstnode;
	m_List.tail = firstnode;

	ifstream info; // �о�� ���� ���� ����
	info.open("student_info.txt", ios::in); //�б� �������� ���� ����
	if (info.is_open() == false) // ���� ���⿡ �����ϸ� ������ ���ǹ�
		cout << "������ �ҷ����µ� �����Ͽ����ϴ�.\n";
	else
	{
		int num = 0;
		do {
			if (num == 40) break;
			NODE* temp = AddNode(); // ���� ���⿡ �����ϸ� �� ��带 ���� �����͸� �����Ѵ�.
			info >> temp->name >> temp->id_num >> temp->major_name >> temp->major_code >> temp->required1 >> temp->required2 >> temp->chosen1 >> temp->chosen2 >> temp->chosen3;
			num++;

		} while (true);
	}
	info.close(); // ������ �ݾ��ش�.
}

void Grade::PrintNode()
{
	NODE* tracer = m_List.head->next; // ����Ʈ�� ��带 ����
	while (tracer != NULL) // ����Ʈ�� ���� ������ ���󰣴�.
	{
		cout << tracer->name << "\t";
		cout << tracer->id_num << "\t";
		cout << tracer->major_name << "\t";
		cout << tracer->major_code << "\t";
		cout << tracer->required1 << "\t";
		cout << tracer->required2 << "\t";
		cout << tracer->chosen1 << "\t";
		cout << tracer->chosen2 << "\t";
		cout << tracer->chosen3 << "\n";
		tracer = tracer->next;
	}
}

NODE* Grade::AddNode() // ����Ʈ�� ��带 �߰��Ѵ�. 
{
	NODE* node = new NODE();
	m_List.tail->next = node;
	node->next = NULL;
	m_List.tail = node;
	return m_List.tail;
}

void Grade::Get_Sum_and_Average() // ������ �հ� ����� ����Ͽ� ����Ʈ�� �����Ѵ�.
{
	NODE* temp = m_List.head->next;
	while (temp != NULL)
	{
		temp->sum = temp->chosen1 + temp->chosen2 + temp->chosen3 + temp->required1 + temp->required2;
		temp->average = (temp->chosen1 + temp->chosen2 + temp->chosen3 + temp->required1 + temp->required2) / 5;
		temp = temp->next;
	}
}

void GradeManage::GetStudent() // �а��� �ش��ϴ� �л� ���� ���Ѵ�.
{
	m_student_num = 0;
	NODE* temp = m_List.head;
	while (temp != NULL)
	{
		if (temp->major_code == m_major_code) // �а� �ڵ尡 ������ �˻��Ѵ�.
		{
			m_student_num++; // ���� �ڵ��� ��� ������ ũ�⸦ ������Ų��.
			temp = temp->next;
		}
		else
			temp = temp->next;
	}
	cout << "\n";
	cout << "����������������������������\n";
	cout << "���� �л� �� ��Ȳ : " << m_student_num << " ��  ��\n";
	cout << "����������������������������\n";
}

void GradeManage::SetManager_INFO() //��ü�� ��� ������ �����Ѵ�.
{
	cout << "��������������������������������������������������������������������������\n";
	cout << "��1.�����а�" << "        2.�����а�" << "        3.�����а�" << "        4.ȭ�а��а�    ��\n";
	cout << "��5.�ð��������а�" << "  6.������а�" << "      7.��ǰ�����а�" << "    8.IT���а�      ��\n";
	cout << "��������������������������������������������������������������������������\n  ";
	while (true)
	{
		cout << "������ �Ϸ��� �а��� �����ϼ���. : ";
		cin >> m_major_code;
		if (m_major_code > 8 || m_major_code < 1)
		{
			cout << "  ���߸� �Է��ϼ̽��ϴ�.\n  ";
			continue;
		}
		else
			break;
	}
	cout << "������������������������\n";
	cout << "�� �̸��� �Է��ϼ���  ��\n";
	cout << "������������������������\n  ��";
	cin >> m_manager_name;
	cout << "������������������������\n";
	cout << "�� ������ �Է��ϼ���  ��\n";
	cout << "������������������������\n  ��";
	cin >> m_manager_id;
}

void GradeManage::FindBest()
{
	cout << "  ���������������������������\n";
	for (int i = 1; i < 9; i++)
	{
		NODE* temp = m_List.head->next;
		NODE* tracer = NULL;
		while (temp != NULL)
		{
			if (temp->major_code == i) // �а� �ڵ尡 ������ �˻��Ѵ�. 
			{
				//cout << temp->name << "\t" << temp->average<<endl;
				if (tracer == NULL)
					tracer = temp;
				else if (temp->average >= tracer->average)
					tracer = temp;
			}
			temp = temp->next;
		}
		cout << "  ����������������������������������������������������\n";
		cout << "  " << tracer->name << " : " << tracer->major_name << "\n";
		cout << "  ��� : " << tracer->average << "\n";
		cout << "  ���� ���� : " << tracer->required1 << "\t" << tracer->required2 << "\t" << tracer->chosen1 << "\t" << tracer->chosen2 << "\t" << tracer->chosen3 << "\n";
		cout << "  ����������������������������������������������������\n";

	}
	cout << "  ���������������������������\n";
}
void GradeManage::GetMajorAvg()
{
	NODE* temp = m_List.head->next;
	int major_sum = 0;;
	float major_avg = 0;
	while (temp != NULL)
	{
		if (temp->major_code == m_major_code) // �а� �ڵ尡 ������ �˻� �Ѵ�. 
			major_sum = major_sum + temp->sum;
		temp = temp->next;
	}
	major_avg = major_sum / (m_student_num * 5);
	cout << "��������������������������������\n";
	cout << "���а� �л����� �� ��� : " << major_avg << "  ��\n";
	cout << "��������������������������������\n";
}
void GradeManage::SubjectInfo()
{
	NODE* temp = m_List.head->next;
	NODE* MAX = NULL;
	NODE* min = NULL;
	float average = 0;
	int sum = 0;
	int subject_code = 0;
	cout << " �������������������������\n";
	cout << "  ���� ���� ���" << endl;
	cout << "������������������������������������������������������������������\n";
	cout << "�� 1. �ʼ�(1)  2. �ʼ�(2)  3. ����(1)  4. ����(2)  5. ����(3)   ��\n";
	cout << "������������������������������������������������������������������\n";
	cout << "\n  ������ ���� : ";
	cin >> subject_code;
	while (temp != NULL)
	{
		if (temp->major_code == m_major_code)
		{
			if (MAX == NULL && min == NULL)
			{
				MAX = temp;
				min = temp;
			}
			switch (subject_code) // ���� �ڵ忡 ���� �ٸ� �����͸� �а� �Ѵ�. 
			{
			case 1:
				if (temp->required1 > MAX->required1)
					MAX = temp;
				else if (temp->required1 < min->required1)
					min = temp;
				sum = sum + temp->required1;
				break;
			case 2:
				if (temp->required2 > MAX->required2)
					MAX = temp;
				else if (temp->required2 < min->required2)
					min = temp;
				sum = sum + temp->required2;
				break;
			case 3:
				if (temp->chosen1 > MAX->chosen1)
					MAX = temp;
				else if (temp->chosen1 < min->chosen1)
					min = temp;
				sum = sum + temp->chosen1;
				break;
			case 4:
				if (temp->chosen2 > MAX->chosen2)
					MAX = temp;
				else if (temp->chosen2 < min->chosen2)
					min = temp;
				sum += temp->chosen2;
				break;
			case 5:
				if (temp->chosen3 > MAX->chosen3)
					MAX = temp;
				else if (temp->chosen3 < min->chosen3)
					min = temp;
				sum += temp->chosen3;
				break;
			default:
				break;
			}
		}
		temp = temp->next;
	}
	average = sum / m_student_num;
	cout << " �������������������������\n";
	switch (subject_code) // ���� �ڵ忡 ���� �ٸ� �����͸� �а� �Ѵ�.
	{
	case 1:
		cout << "  �ְ��� : " << MAX->required1 << endl;
		cout << "  ������ : " << min->required1 << endl;
		cout << " ������������������������������������������������\n";
		cout << "  �ʼ� 1 �ֿ�� �л� : " << MAX->name << " �� " << MAX->required1 << "��" << endl;
		cout << "  �ʼ� 1 ������ �л� : " << min->name << " �� " << min->required1 << "��" << endl;
		break;
	case 2:
		cout << "  �ְ��� : " << MAX->required2 << endl;
		cout << "  ������ : " << min->required2 << endl;
		cout << " ������������������������������������������������\n";
		cout << "  �ʼ� 2 �ֿ�� �л� : " << MAX->name << " �� " << MAX->required2 << "��" << endl;
		cout << "  �ʼ� 2 ������ �л� : " << min->name << " �� " << min->required2 << "��" << endl;
		break;
	case 3:
		cout << "  �ְ��� : " << MAX->chosen1 << endl;
		cout << "  ������ : " << min->chosen1 << endl;
		cout << " ������������������������������������������������\n";
		cout << "  ���� 1 �ֿ�� �л� : " << MAX->name << " �� " << MAX->chosen1 << "��" << endl;
		cout << "  ���� 1 ������ �л� : " << min->name << " �� " << min->chosen1 << "��" << endl;
		break;
	case 4:
		cout << "  �ְ��� : " << MAX->chosen2 << endl;
		cout << "  ������ : " << min->chosen2 << endl;
		cout << " ������������������������������������������������\n";
		cout << "  ���� 2 �ֿ�� �л� : " << MAX->name << " �� " << MAX->chosen2 << "��" << endl;
		cout << "  ���� 2 ������ �л� : " << min->name << " �� " << min->chosen2 << "��" << endl;
		break;
	case 5:
		cout << "  �ְ��� : " << MAX->chosen3 << endl;
		cout << "  ������ : " << min->chosen3 << endl;
		cout << " ������������������������������������������������\n";
		cout << "  ���� 3 �ֿ�� �л� : " << MAX->name << " �� " << MAX->chosen3 << "��" << endl;
		cout << "  ���� 3 ������ �л� : " << min->name << " �� " << min->chosen3 << "��" << endl;
		break;
	default:
		break;
	}
	cout << " ������������������������������������������������\n";
	cout << "  ���� ��� : " << average << endl;
	cout << " �������������������������\n";
}
int main()
{
	int menu;
	Grade g1; // ��ü ����
	GradeManage GM; // ��ü ����
	g1.Set_Info(); // ��ü�� ��� ���� �ʱ�ȭ
	g1.Get_Sum_and_Average(); // ��ü�� ��� ���� ���� �����ϴ� �Լ� ȣ��
	//cout << "��������������������������������������������������������������������������������\n";
	//g1.PrintNode();
	//cout << "��������������������������������������������������������������������������������\n";
	cout << "��������������������������������\n";
	cout << "������ ���� �޴��� �����մϴ�.��" << endl;
	cout << "��������������������������������\n";
	GM.SetManager_INFO(); // ��ü�� ������ �����ϴ� �Լ� ȣ��
	GM.GetStudent(); // ��ü�� ��� ���� ũ�⸦ �����ϴ� �Լ� ȣ�� 
	cout << " �������������������������\n";
	cout << "������������������������������������������������\n";
	cout << "��1. ���� ��� ����                         ��\n";
	cout << "��   �� 5������ ���� �ְ����������������   ��\n";
	cout << "��   �� �ֿ���������� �л� ����              ��\n";
	cout << "��2. �а� ��� ����                           ��\n";
	cout << "��   �� �ش� �а��� ��� ����                 ��\n";
	cout << "��3. �а��� �ֿ�� �л� ����                  ��\n";
	cout << "��   �� �� �а��� �ֿ�� �л��� ����          ��\n";
	cout << "��4. ���α׷��� ���� �մϴ�.                  ��\n";
	cout << "������������������������������������������������\n";
	while (true)
	{
		cout << "\n  ���޴��� �����ϼ��� : ";
		cin >> menu;
		switch (menu)
		{
		case 1:
			GM.SubjectInfo();
			break;
		case 2:
			GM.GetMajorAvg();
			break;
		case 3:
			GM.FindBest();
		case 4:
			break;
		default:
			cout << "\n  ���߸��Է��ϼ̽��ϴ�.\n";
			break;
		}
		cout << "\n  ������Ͻðڽ��ϱ�?\n    �����Ϸ��� 0�� �Է��ϼ��� : ";
		cin >> menu;
		if (menu == 0)
			break;
	}

	return 0;
}
