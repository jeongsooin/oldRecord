def IsLeapYear(year):
    if year%4 == 0 and year%100 != 0:
        return True
    elif year%100 == 0 and year%400 == 0:
        return True
    else:
        return False

while True :
  
    print("정수 연도 값 한 개를 입력 받아 윤년인지 판별 합니다.")
    print("{0:>50}".format("Program name: IsLeapYear"))
    print("{0:>42}".format(">프로그램 종료: 입력-1"))
    print("{0:>42}".format(">프로그램 시작: 입력 0"))
    menu =int(input())
    print("--------------------------------------------------")
    if menu == -1:
        break
    print("정수 연도 값을 하나 입력하여 주십시오:")
    year=int(input())
    
    if year <=0 :
        print("잘못 입력하였습니다.\n1이상의 값을 입력하여 주십시오.\a\a\a")
        print("--------------------------------------------------")
        
    else:
            result = IsLeapYear(year)
            print("입력하신 연도 %s은(는)"%year,end=' ')
            if result == True:
                print("윤년 입니다.")
            else:
                print("윤년이 아닙니다.")
            print("--------------------------------------------------")

      

print("프로그램을 종료 합니다.")
