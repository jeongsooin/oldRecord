def IsLeapYear(year):
    if year%4 == 0 and year%100 != 0:
        return True
    elif year%100 == 0 and year%400 == 0:
        return True
    else:
        return False

def GetDayOfMonth(year,month):
    
    
    if month<=7:
        if month ==2 and result1 == True:
            return 29
        if month == 2 and result1 == False:
            return 28
        if month%2 == 1:
            return 31
        else: 
            return 30
    if 7 <month:
        if month%2 == 1:
            return 30
        else:
            return 31

while True:

    print("Program name: GetDayOfMonth")
    print("입력하신 연월에 해당하는 날짜 수를 알려드립니다.")
    print("------------------------------------------------")
    print("연도를 입력하세요:")
    year = int(input())
    result1 = IsLeapYear(year)
    print("몇 월인지 입력하세요.:")
    month = int(input())
    result2 = GetDayOfMonth(year,month)
    print("------------------------------------------------")
    print("%s년 %s월은 %s일 입니다."%(year,month,result2))
    print("계속하시겠습니까?")
    print("YES: 입력 1\nNO:입력0")
    menu = int(input())
    if menu == 0:
        break
    if menu == 1:
        continue
