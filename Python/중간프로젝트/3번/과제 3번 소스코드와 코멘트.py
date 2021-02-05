Python 3.5.1 (v3.5.1:37a07cee5969, Dec  6 2015, 01:38:48) [MSC v.1900 32 bit (Intel)] on win32
Type "copyright", "credits" or "license()" for more information.
>>> def IsLeapYear(year):
    #
    # 윤년을 검사하는 조건문 입니다.
    # 4로 나누어 떨어지고 100으로 나누어 떨어지지 않거나
    # 100과 400으로 나누어 떨어지면 윤년 입니다.
    #
    if year%4 == 0 and year%100 != 0:
        return True
    elif year%100 == 0 and year%400 == 0:
        return True
    else:
        return False

def GetDayOfMonth(year,month):
    
    #
    # 7월 이하에서는 홀수 달이 31일
    # 짝수 달이 30일 입니다.
    # 그 중 2월이 윤년의 달인지 검사합니다.
    #
    if month<=7:
        if month ==2 and result1 == True:
            return 29
        if month == 2 and result1 == False:
            return 28
        if month%2 == 1:
            return 31
        else: 
            return 30
    #
    # 7월 이상에서는 짝수 달이 31일 입니다.
    #
    if 7 <month:
        if month%2 == 1:
            return 30
        else:
            return 31
#
# 프로그램 실행시 자동 종료가 되는 문제 때문에 루프를 넣었습니다.
#
while True:
    # 안내 문구를 출력하고 입력을 받습니다.
    #
    print("Program name: GetDayOfMonth")
    print("입력하신 연월에 해당하는 날짜 수를 알려드립니다.")
    print("------------------------------------------------")
    print("연도를 입력하세요:")
    year = int(input())
    #
    # 함수가 두 개 이므로 입력 인자 전달이 정확해야 합니다.
    # 입력을 받자마자 해당 함수를 호출합니다.
    #
    result1 = IsLeapYear(year)
    print("몇 월인지 입력하세요.:")
    month = int(input())
    #
    # 두 번째 함수를 호출 합니다.
    #
    result2 = GetDayOfMonth(year,month)
    print("------------------------------------------------")
    print("%s년 %s월은 %s일 입니다."%(year,month,result2))
    print("계속하시겠습니까?")
    print("YES: 입력 1\nNO:입력0")
    menu = int(input())
    #
    # 결과를 출력한 뒤 종료할 것인지 입력 받습니다.
    #
    if menu == 0:
        break
    if menu == 1:
        continue

