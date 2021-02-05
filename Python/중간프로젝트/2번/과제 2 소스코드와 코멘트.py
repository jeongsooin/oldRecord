Python 3.5.1 (v3.5.1:37a07cee5969, Dec  6 2015, 01:38:48) [MSC v.1900 32 bit (Intel)] on win32
Type "copyright", "credits" or "license()" for more information.
>>> def IsLeapYear(year):
    #
    # 4로 나누어 떨어지면서 100으로 나누어 떨어지지 않아야 합니다.
    # 
    if year%4 == 0 and year%100 != 0:
        return True
    #
    # 100으로 나누어 떨어진다면, 400으로도 나누어 떨어져야 합니다. 
    #
    elif year%100 == 0 and year%400 == 0:
        return True
    else:
        return False

while True :
    #
    # 안내 문구를 출력하고 입력을 받습니다. 
    #
    print("정수 연도 값 한 개를 입력 받아 윤년인지 판별 합니다.")
    print("{0:>50}".format("Program name: IsLeapYear"))          # 문자열 포맷팅 함수를 이용하여 오른쪽 정렬
    print("{0:>42}".format(">프로그램 종료: 입력-1"))
    print("{0:>42}".format(">프로그램 시작: 입력 0"))            # -1이 아닌 정수면 되지만, 사용자의 편의를 위하여 0으로 안내 
    menu =int(input())
    print("--------------------------------------------------")
    #
    # -1이 입력되면 루프를 빠져나가 종료 합니다. 
    #
    if menu == -1:
        break
    print("정수 연도 값을 하나 입력하여 주십시오:")
    year=int(input())
    #
    # 입력받은 값이 올바른지 검사합니다. 
    #
    if year <=0 :
        print("잘못 입력하였습니다.\n1이상의 값을 입력하여 주십시오.\a\a\a")
        print("--------------------------------------------------")
        
    else:
            #
            # 함수를 호출하여 결과를 변수에 저장합니다. 
            # 결과를 검사하여 조건에 해당하는 문구를 출력 합니다.
            #
            result = IsLeapYear(year)
            print("입력하신 연도 %s은(는)"%year,end=' ')
            if result == True:
                print("윤년 입니다.")
            else:
                print("윤년이 아닙니다.")
            print("--------------------------------------------------")

      

print("프로그램을 종료 합니다.")
