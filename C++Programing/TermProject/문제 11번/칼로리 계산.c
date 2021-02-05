// Į�θ� ��� ���α׷�
// 1316592 ������
#include <stdio.h>

typedef struct MyInfo // ����� ���� ������ ����ü
{
	char my_name[30];
	int age;
	int basal;
	int height;
	int weight;
	char gender;
}MY;

typedef struct CalorieInfo  // ���İ� ��� �̸��� Į�θ��� ������ ����ü
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
	printf("\n  ������ ���İ� �Ҹ� Į�θ��� ����ϴ� ���α׷� �Դϴ�.\n");
	printf("  ����������������������������\n");
	printf("  ���� ������ ������ ����ּ���\n");
	printf("  1. %s\n  2. %s\n  3. %s\n  4. %s\n  5. %s\n  6. %s\n", food_info[0].item, food_info[1].item, food_info[2].item, food_info[3].item, food_info[4].item, food_info[5].item);
	printf("  0. ���� ����\n");
	printf("  ������������������������������������������������������\n");
	while (1)
	{
		printf("  ��");
		scanf("%d", &choice);
		if (choice == 0)
			break;
		else if (choice >= 1 && choice <= 6)
			GetIntake(choice, &intake_cal);
		else
			continue;
	}
	printf("  ������������������������������������������������������\n");
	printf("  ���� �� ��� ����ּ���\n");
	printf("  1. %s\n  2. %s\n  3. %s\n  4. %s\n  5. %s\n", Excercise_info[0].item, Excercise_info[1].item, Excercise_info[2].item, Excercise_info[3].item, Excercise_info[4].item);
	printf("  0. ���� ����\n");
	printf("  ������������������������������������������������������\n");
	while (1)
	{
		printf("  ��");
		scanf("%d", &choice);
		if (choice == 0)
			break;
		else if (choice >= 1 && choice <= 6)
			GetConsumption(choice, &consumption_cal);
		else
			continue;
	}
	printf("  ������������������������������������������������������\n");
	printf("\n  ���� ������ �� Į�θ� : %dkcal", intake_cal);
	printf("\n  ���� �Ҹ��� �� Į�θ� : %dkcal", consumption_cal);
	GetTotal(&intake_cal, &consumption_cal, &total);
	printf("\n  ������ Į�θ� �Ҹ� ������ : %dkcal\n\n  ��", total);
	return 0;
}

void GetIntake(int num, int* intake_cal) // �� ���� Į�θ� ���
{
	*intake_cal = *intake_cal + food_info[num-1].calorie;
}

void GetConsumption(int num, int* consumption_cal) // ����� �Ҹ��� Į�θ� ���
{
	*consumption_cal = *consumption_cal + Excercise_info[num-1].calorie;
}

void GetTotal(int* intake_cal, int* consumption_cal, int* total) // ����� �Ҹ� Į�θ� �հ�
{
	*total = *intake_cal - (*consumption_cal+user_info.basal);
}