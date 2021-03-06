// 撩瞳 婦葬 Щ煎斜極
// 1316592 薑熱檣
#include <iostream>
#include <fstream>
using namespace std;

struct NODE // з儅 薑爾蒂 盪濰ж朝 掘褻羹
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

struct List // 掘褻羹 葬蝶お
{
	NODE* head;
	NODE* tail;
};
List m_List;

class Grade //Grade 贗楚蝶 薑曖
{
	friend class GradeManage;
public:
	void Set_Info();
	void PrintNode();
	void Get_Sum_and_Average();

protected:
	NODE* AddNode();
};

class GradeManage //GradeManage 贗楚蝶 薑曖
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

	ifstream info; // 檗橫螢 だ橾 滲熱 摹樹
	info.open("student_info.txt", ios::in); //檗晦 瞪辨戲煎 だ橾 翮晦
	if (info.is_open() == false) // だ橾 翮晦縑 褒ぬж賊 熱чй 褻勒僥
		cout << "だ橾擊 碳楝螃朝等 褒ぬж艘蝗棲棻.\n";
	else
	{
		int num = 0;
		do {
			if (num == 40) break;
			NODE* temp = AddNode(); // だ橾 翮晦縑 撩奢ж賊 億 喻萄蒂 虜菟橫憮 等檜攪蒂 盪濰и棻.
			info >> temp->name >> temp->id_num >> temp->major_name >> temp->major_code >> temp->required1 >> temp->required2 >> temp->chosen1 >> temp->chosen2 >> temp->chosen3;
			num++;

		} while (true);
	}
	info.close(); // だ橾擊 殘嬴遽棻.
}

void Grade::PrintNode()
{
	NODE* tracer = m_List.head->next; // 葬蝶お曖 ④萄蒂 犒餌
	while (tracer != NULL) // 葬蝶お陛 部陳 陽梱雖 評塭除棻.
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

NODE* Grade::AddNode() // 葬蝶お縑 喻萄蒂 蹺陛и棻. 
{
	NODE* node = new NODE();
	m_List.tail->next = node;
	node->next = NULL;
	m_List.tail = node;
	return m_List.tail;
}

void Grade::Get_Sum_and_Average() // 撩瞳曖 м婁 ゎ敕擊 啗骯ж罹 葬蝶お縑 偵褐и棻.
{
	NODE* temp = m_List.head->next;
	while (temp != NULL)
	{
		temp->sum = temp->chosen1 + temp->chosen2 + temp->chosen3 + temp->required1 + temp->required2;
		temp->average = (temp->chosen1 + temp->chosen2 + temp->chosen3 + temp->required1 + temp->required2) / 5;
		temp = temp->next;
	}
}

void GradeManage::GetStudent() // з婁縑 п渡ж朝 з儅 熱蒂 掘и棻.
{
	m_student_num = 0;
	NODE* temp = m_List.head;
	while (temp != NULL)
	{
		if (temp->major_code == m_major_code) // з婁 囀萄陛 偽擎雖 匐餌и棻.
		{
			m_student_num++; // 偽擎 囀萄塭賊 詹幗 滲熱曖 觼晦蒂 隸陛衛鑑棻.
			temp = temp->next;
		}
		else
			temp = temp->next;
	}
	cout << "\n";
	cout << "忙式式式式式式式式式式式式忖\n";
	cout << "弛識 з儅 熱 ⑷�� : " << m_student_num << " 貲  弛\n";
	cout << "戌式式式式式式式式式式式式戎\n";
}

void GradeManage::SetManager_INFO() //偌羹曖 詹幗 滲熱蒂 撲薑и棻.
{
	cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n";
	cout << "弛1.僭葬з婁" << "        2.唳薯з婁" << "        3.艙僥з婁" << "        4.�倆訄醾訄�    弛\n";
	cout << "弛5.衛陝蛤濠檣з婁" << "  6.儅貲婁з婁" << "      7.衝ヶ艙曄з婁" << "    8.IT奢з婁      弛\n";
	cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n  ";
	while (true)
	{
		cout << "Ⅰ婦葬 ж溥朝 з婁蒂 摹鷗ж撮蹂. : ";
		cin >> m_major_code;
		if (m_major_code > 8 || m_major_code < 1)
		{
			cout << "  Ⅱ澀跤 殮溘ж樟蝗棲棻.\n  ";
			continue;
		}
		else
			break;
	}
	cout << "忙式式式式式式式式式式忖\n";
	cout << "弛 檜葷擊 殮溘ж撮蹂  弛\n";
	cout << "戌式式式式式式式式式式戎\n  Ⅰ";
	cin >> m_manager_name;
	cout << "忙式式式式式式式式式式忖\n";
	cout << "弛 掖廓擊 殮溘ж撮蹂  弛\n";
	cout << "戌式式式式式式式式式式戎\n  Ⅰ";
	cin >> m_manager_id;
}

void GradeManage::FindBest()
{
	cout << "  ㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑\n";
	for (int i = 1; i < 9; i++)
	{
		NODE* temp = m_List.head->next;
		NODE* tracer = NULL;
		while (temp != NULL)
		{
			if (temp->major_code == i) // з婁 囀萄陛 偽擎雖 匐餌и棻. 
			{
				//cout << temp->name << "\t" << temp->average<<endl;
				if (tracer == NULL)
					tracer = temp;
				else if (temp->average >= tracer->average)
					tracer = temp;
			}
			temp = temp->next;
		}
		cout << "  式式式式式式式式式式式式式式式式式式式式式式式式式式\n";
		cout << "  " << tracer->name << " : " << tracer->major_name << "\n";
		cout << "  ゎ敕 : " << tracer->average << "\n";
		cout << "  婁跡滌 撩瞳 : " << tracer->required1 << "\t" << tracer->required2 << "\t" << tracer->chosen1 << "\t" << tracer->chosen2 << "\t" << tracer->chosen3 << "\n";
		cout << "  式式式式式式式式式式式式式式式式式式式式式式式式式式\n";

	}
	cout << "  ㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑\n";
}
void GradeManage::GetMajorAvg()
{
	NODE* temp = m_List.head->next;
	int major_sum = 0;;
	float major_avg = 0;
	while (temp != NULL)
	{
		if (temp->major_code == m_major_code) // з婁 囀萄陛 偽擎雖 匐餌 и棻. 
			major_sum = major_sum + temp->sum;
		temp = temp->next;
	}
	major_avg = major_sum / (m_student_num * 5);
	cout << "忙式式式式式式式式式式式式式式忖\n";
	cout << "弛з婁 з儅菟曖 識 ゎ敕 : " << major_avg << "  弛\n";
	cout << "戌式式式式式式式式式式式式式式戎\n";
}
void GradeManage::SubjectInfo()
{
	NODE* temp = m_List.head->next;
	NODE* MAX = NULL;
	NODE* min = NULL;
	float average = 0;
	int sum = 0;
	int subject_code = 0;
	cout << " ㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑\n";
	cout << "  婁跡滌 撩瞳 鱔啗" << endl;
	cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n";
	cout << "弛 1. в熱(1)  2. в熱(2)  3. 摹鷗(1)  4. 摹鷗(2)  5. 摹鷗(3)   弛\n";
	cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n";
	cout << "\n  Ⅰ婁跡 摹鷗 : ";
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
			switch (subject_code) // 婁跡 囀萄縑 評塭 棻艇 等檜攪蒂 檗啪 и棻. 
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
	cout << " ㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑\n";
	switch (subject_code) // 婁跡 囀萄縑 評塭 棻艇 等檜攪蒂 檗啪 и棻.
	{
	case 1:
		cout << "  譆堅薄 : " << MAX->required1 << endl;
		cout << "  譆ж薄 : " << min->required1 << endl;
		cout << " 式式式式式式式式式式式式式式式式式式式式式式式式\n";
		cout << "  в熱 1 譆辦熱 з儅 : " << MAX->name << " 式 " << MAX->required1 << "薄" << endl;
		cout << "  в熱 1 譆ж嬪 з儅 : " << min->name << " 式 " << min->required1 << "薄" << endl;
		break;
	case 2:
		cout << "  譆堅薄 : " << MAX->required2 << endl;
		cout << "  譆ж薄 : " << min->required2 << endl;
		cout << " 式式式式式式式式式式式式式式式式式式式式式式式式\n";
		cout << "  в熱 2 譆辦熱 з儅 : " << MAX->name << " 式 " << MAX->required2 << "薄" << endl;
		cout << "  в熱 2 譆ж嬪 з儅 : " << min->name << " 式 " << min->required2 << "薄" << endl;
		break;
	case 3:
		cout << "  譆堅薄 : " << MAX->chosen1 << endl;
		cout << "  譆ж薄 : " << min->chosen1 << endl;
		cout << " 式式式式式式式式式式式式式式式式式式式式式式式式\n";
		cout << "  摹鷗 1 譆辦熱 з儅 : " << MAX->name << " 式 " << MAX->chosen1 << "薄" << endl;
		cout << "  摹鷗 1 譆ж嬪 з儅 : " << min->name << " 式 " << min->chosen1 << "薄" << endl;
		break;
	case 4:
		cout << "  譆堅薄 : " << MAX->chosen2 << endl;
		cout << "  譆ж薄 : " << min->chosen2 << endl;
		cout << " 式式式式式式式式式式式式式式式式式式式式式式式式\n";
		cout << "  摹鷗 2 譆辦熱 з儅 : " << MAX->name << " 式 " << MAX->chosen2 << "薄" << endl;
		cout << "  摹鷗 2 譆ж嬪 з儅 : " << min->name << " 式 " << min->chosen2 << "薄" << endl;
		break;
	case 5:
		cout << "  譆堅薄 : " << MAX->chosen3 << endl;
		cout << "  譆ж薄 : " << min->chosen3 << endl;
		cout << " 式式式式式式式式式式式式式式式式式式式式式式式式\n";
		cout << "  摹鷗 3 譆辦熱 з儅 : " << MAX->name << " 式 " << MAX->chosen3 << "薄" << endl;
		cout << "  摹鷗 3 譆ж嬪 з儅 : " << min->name << " 式 " << min->chosen3 << "薄" << endl;
		break;
	default:
		break;
	}
	cout << " 式式式式式式式式式式式式式式式式式式式式式式式式\n";
	cout << "  婁跡 ゎ敕 : " << average << endl;
	cout << " ㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑\n";
}
int main()
{
	int menu;
	Grade g1; // 偌羹 儅撩
	GradeManage GM; // 偌羹 儅撩
	g1.Set_Info(); // 偌羹曖 詹幗 滲熱 蟾晦��
	g1.Get_Sum_and_Average(); // 偌羹曖 詹幗 滲熱 頂辨 滲唳ж朝 л熱 ��轎
	//cout << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式\n";
	//g1.PrintNode();
	//cout << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式\n";
	cout << "忙式式式式式式式式式式式式式式忖\n";
	cout << "弛撩瞳 婦葬 詭景蒂 摹鷗м棲棻.弛" << endl;
	cout << "戌式式式式式式式式式式式式式式戎\n";
	GM.SetManager_INFO(); // 偌羹曖 滲熱蒂 撲薑ж朝 л熱 ��轎
	GM.GetStudent(); // 偌羹曖 詹幗 滲熱 觼晦蒂 滲唳ж朝 л熱 ��轎 
	cout << " ㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑\n";
	cout << "忙式式式式式式式式式式式式式式式式式式式式式式忖\n";
	cout << "弛1. 婁跡滌 鱔啗 爾晦                         弛\n";
	cout << "弛   ⊥ 5婁跡曖 婁跡滌 譆堅薄﹞譆ж薄﹞ゎ敕   弛\n";
	cout << "弛   ⊥ 譆辦熱﹞譆ж嬪 з儅 薑爾              弛\n";
	cout << "弛2. з婁 ゎ敕 爾晦                           弛\n";
	cout << "弛   ⊥ п渡 з婁曖 ゎ敕 撩瞳                 弛\n";
	cout << "弛3. з婁滌 譆辦熱 з儅 薑爾                  弛\n";
	cout << "弛   ⊥ 陝 з婁滌 譆辦熱 з儅曖 薑爾          弛\n";
	cout << "弛4. Щ煎斜極擊 謙猿 м棲棻.                  弛\n";
	cout << "戌式式式式式式式式式式式式式式式式式式式式式式戎\n";
	while (true)
	{
		cout << "\n  Ⅰ詭景蒂 摹鷗ж撮蹂 : ";
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
			cout << "\n  Ⅱ澀跤殮溘ж樟蝗棲棻.\n";
			break;
		}
		cout << "\n  Ⅰ啗樓ж衛啊蝗棲梱?\n    謙猿ж溥賊 0擊 殮溘ж撮蹂 : ";
		cin >> menu;
		if (menu == 0)
			break;
	}

	return 0;
}
