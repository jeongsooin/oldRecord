// 蠔煎葬 啗骯 Щ煎斜極
// 1316592 薑熱檣
#include <stdio.h>

typedef struct MyInfo // 餌辨濠 薑爾 盪濰й 掘褻羹
{
	char my_name[30];
	int age;
	int basal;
	int height;
	int weight;
	char gender;
}MY;

typedef struct CalorieInfo  // 擠衝婁 遴翕曖 檜葷婁 蠔煎葬蒂 盪濰й 掘褻羹
{
	char item [30];
	int calorie;
}Cal;

MY user_info = { "SI.Jeong",22,1300,160,45,'F' };
Cal food_info[6] = { { "Bread",450 },{ "Noodle",900 },{ "Salad",200 },{ "Rice",500 },{ "Coffe",80 },{ "Cola",150 } };
Cal Excercise_info[5] = { { "Walking",90 },{ "Yoga",60 },{ "Basketball",200 },{ "Swimming",360 },{ "Badmiton",173 } };

void GetIntake(int num, int* intake_cal);
void GetConsumption(int num, int* consumption_cal);
void GetTotal(int* intake_cal, int* consumption_cal, int* total);

int main()
{
	int intake_cal = 0;
	int consumption_cal = 0;
	int total = 0;
	int choice;
	printf("\n  撥鏃и 擠衝婁 模賅 蠔煎葬蒂 啗骯ж朝 Щ煎斜極 殮棲棻.\n");
	printf("  ㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑\n");
	printf("  螃棺 撥鏃и 擠衝擊 埤塭輿撮蹂\n");
	printf("  1. %s\n  2. %s\n  3. %s\n  4. %s\n  5. %s\n  6. %s\n", food_info[0].item, food_info[1].item, food_info[2].item, food_info[3].item, food_info[4].item, food_info[5].item);
	printf("  0. 摹鷗 謙猿\n");
	printf("  式式式式式式式式式式式式式式式式式式式式式式式式式式式\n");
	while (1)
	{
		printf("  Ⅰ");
		scanf("%d", &choice);
		if (choice == 0)
			break;
		else if (choice >= 1 && choice <= 6)
			GetIntake(choice, &intake_cal);
		else
			continue;
	}
	printf("  式式式式式式式式式式式式式式式式式式式式式式式式式式式\n");
	printf("  螃棺 и 遴翕擊 埤塭輿撮蹂\n");
	printf("  1. %s\n  2. %s\n  3. %s\n  4. %s\n  5. %s\n", Excercise_info[0].item, Excercise_info[1].item, Excercise_info[2].item, Excercise_info[3].item, Excercise_info[4].item);
	printf("  0. 摹鷗 謙猿\n");
	printf("  式式式式式式式式式式式式式式式式式式式式式式式式式式式\n");
	while (1)
	{
		printf("  Ⅰ");
		scanf("%d", &choice);
		if (choice == 0)
			break;
		else if (choice >= 1 && choice <= 6)
			GetConsumption(choice, &consumption_cal);
		else
			continue;
	}
	printf("  式式式式式式式式式式式式式式式式式式式式式式式式式式式\n");
	printf("\n  螃棺 撥鏃и 識 蠔煎葬 : %dkcal", intake_cal);
	printf("\n  螃棺 模賅и 識 蠔煎葬 : %dkcal", consumption_cal);
	GetTotal(&intake_cal, &consumption_cal, &total);
	printf("\n  螃棺曖 蠔煎葬 模賅 虜褶紫 : %dkcal\n\n  Ⅰ", total);
	return 0;
}

void GetIntake(int num, int* intake_cal) // 識 撥鏃 蠔煎葬 啗骯
{
	*intake_cal = *intake_cal + food_info[num-1].calorie;
}

void GetConsumption(int num, int* consumption_cal) // 遴翕戲煎 模賅и 蠔煎葬 啗骯
{
	*consumption_cal = *consumption_cal + Excercise_info[num-1].calorie;
}

void GetTotal(int* intake_cal, int* consumption_cal, int* total) // 撥鏃諦 模賅 蠔煎葬 м啗
{
	*total = *intake_cal - (*consumption_cal+user_info.basal);
}