// ¼ºÀû °ü¸® ÇÁ·Î±×·¥
// 1316592 Á¤¼öÀÎ
#include <iostream>
#include <fstream>
using namespace std;

struct NODE // ÇÐ»ý Á¤º¸¸¦ ÀúÀåÇÏ´Â ±¸Á¶Ã¼
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

struct List // ±¸Á¶Ã¼ ¸®½ºÆ®
{
	NODE* head;
	NODE* tail;
};
List m_List;

class Grade //Grade Å¬·¡½º Á¤ÀÇ
{
	friend class GradeManage;
public:
	void Set_Info();
	void PrintNode();
	void Get_Sum_and_Average();

protected:
	NODE* AddNode();
};

class GradeManage //GradeManage Å¬·¡½º Á¤ÀÇ
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

	ifstream info; // ÀÐ¾î¿Ã ÆÄÀÏ º¯¼ö ¼±¾ð
	info.open("student_info.txt", ios::in); //ÀÐ±â Àü¿ëÀ¸·Î ÆÄÀÏ ¿­±â
	if (info.is_open() == false) // ÆÄÀÏ ¿­±â¿¡ ½ÇÆÐÇÏ¸é ¼öÇàÇÒ Á¶°Ç¹®
		cout << "ÆÄÀÏÀ» ºÒ·¯¿À´Âµ¥ ½ÇÆÐÇÏ¿´½À´Ï´Ù.\n";
	else
	{
		int num = 0;
		do {
			if (num == 40) break;
			NODE* temp = AddNode(); // ÆÄÀÏ ¿­±â¿¡ ¼º°øÇÏ¸é »õ ³ëµå¸¦ ¸¸µé¾î¼­ µ¥ÀÌÅÍ¸¦ ÀúÀåÇÑ´Ù.
			info >> temp->name >> temp->id_num >> temp->major_name >> temp->major_code >> temp->required1 >> temp->required2 >> temp->chosen1 >> temp->chosen2 >> temp->chosen3;
			num++;

		} while (true);
	}
	info.close(); // ÆÄÀÏÀ» ´Ý¾ÆÁØ´Ù.
}

void Grade::PrintNode()
{
	NODE* tracer = m_List.head->next; // ¸®½ºÆ®ÀÇ Çìµå¸¦ º¹»ç
	while (tracer != NULL) // ¸®½ºÆ®°¡ ³¡³¯ ¶§±îÁö µû¶ó°£´Ù.
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

NODE* Grade::AddNode() // ¸®½ºÆ®¿¡ ³ëµå¸¦ Ãß°¡ÇÑ´Ù. 
{
	NODE* node = new NODE();
	m_List.tail->next = node;
	node->next = NULL;
	m_List.tail = node;
	return m_List.tail;
}

void Grade::Get_Sum_and_Average() // ¼ºÀûÀÇ ÇÕ°ú Æò±ÕÀ» °è»êÇÏ¿© ¸®½ºÆ®¿¡ °»½ÅÇÑ´Ù.
{
	NODE* temp = m_List.head->next;
	while (temp != NULL)
	{
		temp->sum = temp->chosen1 + temp->chosen2 + temp->chosen3 + temp->required1 + temp->required2;
		temp->average = (temp->chosen1 + temp->chosen2 + temp->chosen3 + temp->required1 + temp->required2) / 5;
		temp = temp->next;
	}
}

void GradeManage::GetStudent() // ÇÐ°ú¿¡ ÇØ´çÇÏ´Â ÇÐ»ý ¼ö¸¦ ±¸ÇÑ´Ù.
{
	m_student_num = 0;
	NODE* temp = m_List.head;
	while (temp != NULL)
	{
		if (temp->major_code == m_major_code) // ÇÐ°ú ÄÚµå°¡ °°ÀºÁö °Ë»çÇÑ´Ù.
		{
			m_student_num++; // °°Àº ÄÚµå¶ó¸é ¸â¹ö º¯¼öÀÇ Å©±â¸¦ Áõ°¡½ÃÅ²´Ù.
			temp = temp->next;
		}
		else
			temp = temp->next;
	}
	cout << "\n";
	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n";
	cout << "¦¢ÃÑ ÇÐ»ý ¼ö ÇöÈ² : " << m_student_num << " ¸í  ¦¢\n";
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n";
}

void GradeManage::SetManager_INFO() //°´Ã¼ÀÇ ¸â¹ö º¯¼ö¸¦ ¼³Á¤ÇÑ´Ù.
{
	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n";
	cout << "¦¢1.¹°¸®ÇÐ°ú" << "        2.°æÁ¦ÇÐ°ú" << "        3.¿µ¹®ÇÐ°ú" << "        4.È­ÇÐ°øÇÐ°ú    ¦¢\n";
	cout << "¦¢5.½Ã°¢µðÀÚÀÎÇÐ°ú" << "  6.»ý¸í°úÇÐ°ú" << "      7.½ÄÇ°¿µ¾çÇÐ°ú" << "    8.IT°øÇÐ°ú      ¦¢\n";
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n  ";
	while (true)
	{
		cout << "¢¹°ü¸® ÇÏ·Á´Â ÇÐ°ú¸¦ ¼±ÅÃÇÏ¼¼¿ä. : ";
		cin >> m_major_code;
		if (m_major_code > 8 || m_major_code < 1)
		{
			cout << "  ¢ºÀß¸ø ÀÔ·ÂÇÏ¼Ì½À´Ï´Ù.\n  ";
			continue;
		}
		else
			break;
	}
	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n";
	cout << "¦¢ ÀÌ¸§À» ÀÔ·ÂÇÏ¼¼¿ä  ¦¢\n";
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n  ¢¹";
	cin >> m_manager_name;
	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n";
	cout << "¦¢ ±³¹øÀ» ÀÔ·ÂÇÏ¼¼¿ä  ¦¢\n";
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n  ¢¹";
	cin >> m_manager_id;
}

void GradeManage::FindBest()
{
	cout << "  ¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë\n";
	for (int i = 1; i < 9; i++)
	{
		NODE* temp = m_List.head->next;
		NODE* tracer = NULL;
		while (temp != NULL)
		{
			if (temp->major_code == i) // ÇÐ°ú ÄÚµå°¡ °°ÀºÁö °Ë»çÇÑ´Ù. 
			{
				//cout << temp->name << "\t" << temp->average<<endl;
				if (tracer == NULL)
					tracer = temp;
				else if (temp->average >= tracer->average)
					tracer = temp;
			}
			temp = temp->next;
		}
		cout << "  ¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡\n";
		cout << "  " << tracer->name << " : " << tracer->major_name << "\n";
		cout << "  Æò±Õ : " << tracer->average << "\n";
		cout << "  °ú¸ñº° ¼ºÀû : " << tracer->required1 << "\t" << tracer->required2 << "\t" << tracer->chosen1 << "\t" << tracer->chosen2 << "\t" << tracer->chosen3 << "\n";
		cout << "  ¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡\n";

	}
	cout << "  ¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë\n";
}
void GradeManage::GetMajorAvg()
{
	NODE* temp = m_List.head->next;
	int major_sum = 0;;
	float major_avg = 0;
	while (temp != NULL)
	{
		if (temp->major_code == m_major_code) // ÇÐ°ú ÄÚµå°¡ °°ÀºÁö °Ë»ç ÇÑ´Ù. 
			major_sum = major_sum + temp->sum;
		temp = temp->next;
	}
	major_avg = major_sum / (m_student_num * 5);
	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n";
	cout << "¦¢ÇÐ°ú ÇÐ»ýµéÀÇ ÃÑ Æò±Õ : " << major_avg << "  ¦¢\n";
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n";
}
void GradeManage::SubjectInfo()
{
	NODE* temp = m_List.head->next;
	NODE* MAX = NULL;
	NODE* min = NULL;
	float average = 0;
	int sum = 0;
	int subject_code = 0;
	cout << " ¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë\n";
	cout << "  °ú¸ñº° ¼ºÀû Åë°è" << endl;
	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n";
	cout << "¦¢ 1. ÇÊ¼ö(1)  2. ÇÊ¼ö(2)  3. ¼±ÅÃ(1)  4. ¼±ÅÃ(2)  5. ¼±ÅÃ(3)   ¦¢\n";
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n";
	cout << "\n  ¢¹°ú¸ñ ¼±ÅÃ : ";
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
			switch (subject_code) // °ú¸ñ ÄÚµå¿¡ µû¶ó ´Ù¸¥ µ¥ÀÌÅÍ¸¦ ÀÐ°Ô ÇÑ´Ù. 
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
	cout << " ¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë\n";
	switch (subject_code) // °ú¸ñ ÄÚµå¿¡ µû¶ó ´Ù¸¥ µ¥ÀÌÅÍ¸¦ ÀÐ°Ô ÇÑ´Ù.
	{
	case 1:
		cout << "  ÃÖ°íÁ¡ : " << MAX->required1 << endl;
		cout << "  ÃÖÇÏÁ¡ : " << min->required1 << endl;
		cout << " ¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡\n";
		cout << "  ÇÊ¼ö 1 ÃÖ¿ì¼ö ÇÐ»ý : " << MAX->name << " ¦¡ " << MAX->required1 << "Á¡" << endl;
		cout << "  ÇÊ¼ö 1 ÃÖÇÏÀ§ ÇÐ»ý : " << min->name << " ¦¡ " << min->required1 << "Á¡" << endl;
		break;
	case 2:
		cout << "  ÃÖ°íÁ¡ : " << MAX->required2 << endl;
		cout << "  ÃÖÇÏÁ¡ : " << min->required2 << endl;
		cout << " ¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡\n";
		cout << "  ÇÊ¼ö 2 ÃÖ¿ì¼ö ÇÐ»ý : " << MAX->name << " ¦¡ " << MAX->required2 << "Á¡" << endl;
		cout << "  ÇÊ¼ö 2 ÃÖÇÏÀ§ ÇÐ»ý : " << min->name << " ¦¡ " << min->required2 << "Á¡" << endl;
		break;
	case 3:
		cout << "  ÃÖ°íÁ¡ : " << MAX->chosen1 << endl;
		cout << "  ÃÖÇÏÁ¡ : " << min->chosen1 << endl;
		cout << " ¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡\n";
		cout << "  ¼±ÅÃ 1 ÃÖ¿ì¼ö ÇÐ»ý : " << MAX->name << " ¦¡ " << MAX->chosen1 << "Á¡" << endl;
		cout << "  ¼±ÅÃ 1 ÃÖÇÏÀ§ ÇÐ»ý : " << min->name << " ¦¡ " << min->chosen1 << "Á¡" << endl;
		break;
	case 4:
		cout << "  ÃÖ°íÁ¡ : " << MAX->chosen2 << endl;
		cout << "  ÃÖÇÏÁ¡ : " << min->chosen2 << endl;
		cout << " ¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡\n";
		cout << "  ¼±ÅÃ 2 ÃÖ¿ì¼ö ÇÐ»ý : " << MAX->name << " ¦¡ " << MAX->chosen2 << "Á¡" << endl;
		cout << "  ¼±ÅÃ 2 ÃÖÇÏÀ§ ÇÐ»ý : " << min->name << " ¦¡ " << min->chosen2 << "Á¡" << endl;
		break;
	case 5:
		cout << "  ÃÖ°íÁ¡ : " << MAX->chosen3 << endl;
		cout << "  ÃÖÇÏÁ¡ : " << min->chosen3 << endl;
		cout << " ¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡\n";
		cout << "  ¼±ÅÃ 3 ÃÖ¿ì¼ö ÇÐ»ý : " << MAX->name << " ¦¡ " << MAX->chosen3 << "Á¡" << endl;
		cout << "  ¼±ÅÃ 3 ÃÖÇÏÀ§ ÇÐ»ý : " << min->name << " ¦¡ " << min->chosen3 << "Á¡" << endl;
		break;
	default:
		break;
	}
	cout << " ¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡\n";
	cout << "  °ú¸ñ Æò±Õ : " << average << endl;
	cout << " ¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë\n";
}
int main()
{
	int menu;
	Grade g1; // °´Ã¼ »ý¼º
	GradeManage GM; // °´Ã¼ »ý¼º
	g1.Set_Info(); // °´Ã¼ÀÇ ¸â¹ö º¯¼ö ÃÊ±âÈ­
	g1.Get_Sum_and_Average(); // °´Ã¼ÀÇ ¸â¹ö º¯¼ö ³»¿ë º¯°æÇÏ´Â ÇÔ¼ö È£Ãâ
	//cout << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡\n";
	//g1.PrintNode();
	//cout << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡\n";
	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n";
	cout << "¦¢¼ºÀû °ü¸® ¸Þ´º¸¦ ¼±ÅÃÇÕ´Ï´Ù.¦¢" << endl;
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n";
	GM.SetManager_INFO(); // °´Ã¼ÀÇ º¯¼ö¸¦ ¼³Á¤ÇÏ´Â ÇÔ¼ö È£Ãâ
	GM.GetStudent(); // °´Ã¼ÀÇ ¸â¹ö º¯¼ö Å©±â¸¦ º¯°æÇÏ´Â ÇÔ¼ö È£Ãâ 
	cout << " ¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë¡ë\n";
	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n";
	cout << "¦¢1. °ú¸ñº° Åë°è º¸±â                         ¦¢\n";
	cout << "¦¢   ¡æ 5°ú¸ñÀÇ °ú¸ñº° ÃÖ°íÁ¡¡¤ÃÖÇÏÁ¡¡¤Æò±Õ   ¦¢\n";
	cout << "¦¢   ¡æ ÃÖ¿ì¼ö¡¤ÃÖÇÏÀ§ ÇÐ»ý Á¤º¸              ¦¢\n";
	cout << "¦¢2. ÇÐ°ú Æò±Õ º¸±â                           ¦¢\n";
	cout << "¦¢   ¡æ ÇØ´ç ÇÐ°úÀÇ Æò±Õ ¼ºÀû                 ¦¢\n";
	cout << "¦¢3. ÇÐ°úº° ÃÖ¿ì¼ö ÇÐ»ý Á¤º¸                  ¦¢\n";
	cout << "¦¢   ¡æ °¢ ÇÐ°úº° ÃÖ¿ì¼ö ÇÐ»ýÀÇ Á¤º¸          ¦¢\n";
	cout << "¦¢4. ÇÁ·Î±×·¥À» Á¾·á ÇÕ´Ï´Ù.                  ¦¢\n";
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n";
	while (true)
	{
		cout << "\n  ¢¹¸Þ´º¸¦ ¼±ÅÃÇÏ¼¼¿ä : ";
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
			cout << "\n  ¢ºÀß¸øÀÔ·ÂÇÏ¼Ì½À´Ï´Ù.\n";
			break;
		}
		cout << "\n  ¢¹°è¼ÓÇÏ½Ã°Ú½À´Ï±î?\n    Á¾·áÇÏ·Á¸é 0À» ÀÔ·ÂÇÏ¼¼¿ä : ";
		cin >> menu;
		if (menu == 0)
			break;
	}

	return 0;
}
