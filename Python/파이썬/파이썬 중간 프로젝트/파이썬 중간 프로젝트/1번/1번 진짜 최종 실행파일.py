def IsPrime(num):
    if num == 2:
        return True
    if num == 3:
        return True
    if num%2 == 0:
        return False
    i = 3
    while i <= num-1:
        remainder = num % i 
        if remainder == 0:
            return False
        else:
            if i != num-1:
                i = i +1
                continue
            else:
                return True


while True :
    print("       Program name: IsPrime")
    print("          >프로그램 종료: -1\n          >프로그램 시작:  0")
    menu =int(input())
    print("------------------------------------------")
    if menu == -1:
        break
    print("정수를 한 개 입력하여 주십시오:")
    num=int(input())
    
    if num <=0 :
        print("잘못 입력하였습니다.\n2이상의 값을 입력하여 주십시오.\a\a\a")
        print("------------------------------------------")
        
    else:
            result = IsPrime(num)
            print("입력하신 정수 %s은(는)"%num,end=' ')
            if result == True:
                print("소수입니다.")
            else:
                print("소수가 아닙니다.")
            print("------------------------------------------")

      

print("프로그램을 종료 합니다.")
