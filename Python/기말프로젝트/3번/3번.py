# 3번.py

# 오류가 발생했을 때 프로그램을 종료하는 함수
def safe_exit():
    input(" 종료하시려면 <Enter>를 누르세요.")
    exit(1)

# 오류가 발생했을 때 알맞은 메시지를 출력하는 함수
def print_message(int):
    try:
        if int == 1:
            print(" 수식을 계산할 수 없습니다.")
        elif int == 2:
            print(" 0은 나눌 수 없습니다.")
        else:
            print(" 출력함수 오류")
    except:
        print(" 함수 호출 과정에서 오류가 생겼습니다.")
        input(" 종료하시려면 <Enter>를 누르세요.")
        exit(1)

try:
    import re
except:
    print("모듈 임포트에 실패하였습니다.")
    safe_exit()
    
print("문자열로 입력받은 수식을 계산하는 프로그램 입니다.")

# 항상 참인 while loop
# 입력받는 메뉴가 2일때만 빠져나간다.
while(True):

    # 숫자 1과 2를 입력받아 루프를 조절한다.
    # 1과 2외의 다른 입력이 들어올 시 다시 입력을 받는다.
    try:
        print("────────────────────────────────────")
        menu = int(input("\n1: 계속\n2: 종료\n메뉴를 골라주세요:\n"))
        if (menu == 1 ):
            pass
        elif (menu == 2):
            print("프로그램을 종료합니다.\n")
            break
        else:
            print("1과 2 중에 한 가지만 입력해주십시오.\n")
            continue
    except:
        print("1과 2 중에 한 가지만 입력해주십시오.\n")
        continue
    
    print("┌────────────────────────────────────┐") 
    print("│                            4*2-100/2                                   │")
    print("│        위와 같이 정수와 연산자로 이루어진 수식을 입력해주세요.         │")
    print("│        정수는 최대 4개까지, 연산자는 최대 3개까지 입력할 수 있습니다.  │")
    print("└────────────────────────────────────┘")
    formula = input(" 입력:: ")

    # 입력받은 문자열을 연산자를 기준으로 분리한다.
    # 숫자는 integers 리스트에, 연산자는 operators 리스트에 저장.
    # 연산자의 개수가 0이거나 피연산자의 개수보다 같거나 많으면 다시 입력을 받는다.
    # 숫자는 그대로 사용하기 위해 문자열을 정수로 변환해 준다. 
    try:
        integers = re.split('[*+/-]+',formula)
        operators = []
        for i in formula:
            if ( i =='*' or i =='/' or i =='+' or i == '-' ):
                operators.append(i)
            else:
                pass
        if len(operators) == 0 or len(operators) >= len(integers):
            print(" 수식이 잘못되었습니다.")
            continue
        elif len(operators) >3 or len(integers)>4:
            print(" 숫자는 최대 4개, 연산자는 최대 3개까지 입력할 수 있습니다.")
            continue
        integers = list(map(int,integers))

        # 연산자 우선 순위를 적용하기 위해 우선순위가 높은
        # * 와 /가 수식에 몇개 들어있는지 카운트 한다.
        count = operators.count("*") + operators.count("/")
    except:
        print(" 수식이 잘못되었습니다.")
        continue

    # 문자열로 입력받은 연산자는 사용할 수 없음.
    # 함수를 따로 정의하여 사칙연산 계산을 한다.
    add = lambda a,b:a+b
    div = lambda a,b:a/b
    mul = lambda a,b:a*b
    sub = lambda a,b:a-b

    # * 또는 /가 없을 경우의 수식 계산,
    # 우선순위가 없어서 순서대로 계산하면 된다.
    # 피연산자의 리스트에서 pop으로 꺼내어 계산하려면
    # 피연산자 리스트는 역순으로 배열되어야 연산자와 순서가 맞는다.
    if count == 0:
        integers.reverse()
        for i in operators:
            if i == "+":
                integers.append(add(integers.pop(),integers.pop()))
            else:
                integers.append(sub(integers.pop(),integers.pop()))
        print(" 계산 결과:: ",integers)

    # * 또는 /가 한 개 있을 경우의 수식 계산
    # * 또는 /의 위치에 따라 계산 순서가 달라진다.
    # 연산자의 인덱스를 구해서 각 경우에 알맞는 순서로 수식을 계산한다.
    # 단, 0일 때는 첫번째 경우와 똑같아진다.
    elif count == 1:
        num1 = operators.count("*")
        num2 = operators.count("/")
        if num1 == 1:
            index= operators.index("*")
        elif num2 == 1:
            index = operators.index("/")
        else:
            print("error")
            continue

        # 우선 순위 높은 연산자가 첫번째 연산자일 때.
        if index == 0 :
            integers.reverse()
            for i in operators:
                if i == "*":
                    integers.append(mul(integers.pop(),integers.pop()))
                elif i == "/":                        
                    try:
                        integers.append(div(integers.pop(),integers.pop()))
                    except:
                        print_message(2)
                        break
                    
                elif i == "+":
                    integers.append(add(integers.pop(),integers.pop()))
                else:
                    integers.append(sub(integers.pop(),integers.pop()))

        # 우선 순위 연산자가 두번째 연산자일 때.
        elif index == 1:
            for i in operators:
                if i == "*":
                    temp = mul(integers[1],integers[2])
                    integers[1:3] = []
                    integers.insert(1,temp)
                if i == "/":
                    try:
                        temp = div(integers[1],integers[2])
                        integers[1:3] = []
                        integers.insert(1,temp)
                    except:
                        print_message(2)
                        break
            integers.reverse()
            for i in operators:
                if i == "+":
                    integers.append(add(integers.pop(),integers.pop()))
                elif i == "-":
                    integers.append(sub(integers.pop(),integers.pop()))

        # 우선 순위 연산자가 세번째 연산자일 때.
        elif index == 2 :
            for i in operators:
                if i == "*":
                    temp = mul(integers[2],integers[3])
                    del integers[2]
                    del integers[2]
                    integers.append(temp)
                elif i == "/":
                    try:
                        temp = div(integers[2],integers[3])
                        del integers[2]
                        del integers[2]
                        integers.append(temp)
                    except:
                        print_message(2)
                        safe_exit()

            integers.reverse()
            for i in operators:
                if i == "+":
                    integers.append(add(integers.pop(),integers.pop()))
                elif i == "-":
                    integers.append(sub(integers.pop(),integers.pop()))
        else:
            print_message(1)
            continue
        print(" 계산 결과:: ",integers)

    # 우선 순위 연산자가 수식에 2개 있을 때의 계산.
    # 연속으로 나올때와 연속이 아닐 때의 순서가 다르다.
    elif count == 2:

        # 우선 순위가 낮은 연산자의 위치를 찾는다.
        # 찾은 값을 식별자로 사용해서 계산 순서가 달라지게 한다. 
        if "+" in operators:
            option = operators.index("+")
        elif "-" in operators:
            option = operators.index("-")
        else:
            option = 3

        # 우선 순위 연산자가 연속으로 계산되지 않을 때의 계산.
        if option == 1:
            result = []

            # 우선 순위 높은 연산자를 먼저 계산해야 하므로 먼저 따로 계산.
            # 서로 떨어져 있으므로 계산값이 영향을 주고받지 않는다.
            # 따라서 리스트의 인덱스 값을 이용하여 피연산자에 접근
            for i in range(len(operators)):
                if operators[i] == "*":
                    result.append(mul(integers[i],integers[i+1]))
                elif operators[i] == "/":
                    if integers[i] == 0 or integers[i+1] == 0:
                        print_message(2)
                        safe_exit()
                    result.append(div(integers[i],integers[i+1]))

                else:
                    pass
            # 리스트에서 pop하여 계산할 것이므로 리스트 순서 역전
            # 중간 계산값이 저장된 result 리스트에서 꺼내어 계산한다.
            result.reverse()
            for i in range(len(operators)):
                if operators[i]=="+":
                    result.append(add(result.pop(),result.pop()))
                elif operators[i] == "-":
                    result.append(sub(result.pop(),result.pop()))
                else:
                    pass
            print(" 계산 결과:: ",result)

        # 우선 순위 연산자가 연속으로 계산될 때의 계산.
        elif option == 2 or option == 0:
            temp = []

            # 연속으로 계산되므로 서로 계산 값이 영향을 받는다.
            # 따라서 임시 리스트를 생성하고, 먼저 계산한 연산자의 결과를 저장.
            # 다음 연산자를 계산할 때 꺼내어 계산한다.
            for i in range(len(operators)):
                if operators[i] == "*":
                    if len(temp) != 0:
                        temp.append(mul(temp.pop(),integers[i+1]))
                    else:
                        temp.append(mul(integers[i],integers[i+1]))
                elif operators[i] == "/":
                    try:
                        if len(temp) != 0:
                            temp.append(div(temp.pop(),integers[i+1]))
                        else:
                            temp.append(div(integers[i],integers[i+1]))
                    except:
                        print_message(2)
                        safe_exit()
                else:
                    pass

            # 중간 계산값과 나머지 연산자들의 계산
            # 먼저 계산했던 값을 이어서 사용해야 하므로 temp 리스트에서 pop
            # 저장된 값은 하나밖에 없으므로 인덱스가 필요없다.
            # 단, 첫번째 나오는지 마지막에 나오는지에 따라 값을 꺼내올 순서가
            # 달라지므로, 식별자를 구별해 준다.
            for i in range(len(operators)):
                if operators[i] == "+":
                    if option == 0:
                        result = add(integers[0],temp.pop())
                    else:
                        result = add(temp.pop(),integers[3])
                elif operators[i] == "-":
                    if option == 0:
                        result = sub(integers[0],temp.pop())
                    else:
                        result = sub(temp.pop(),integers[3])
                else:
                    pass
            print(" 계산 결과:: ",result)

        # 우선 순위 연산자가 2개 이상 등장하지만,
        # + - 없이 * / 만 있을때의 계산.
        # 우선 순위가 사라지므로 순차적으로 계산하면 된다.
        elif option == 3:
            integers.reverse()
            for i in operators:
                if i == "*":
                    integers.append(mul(integers.pop(),integers.pop()))
                else:
                    try:
                        integers.append(div(integers.pop(),integers.pop()))
                    except:
                        print_message(2)
                        safe_exit()
            print(" 계산 결과:: ",integers)
        else:
            print_message(1)
            continue

    # 우선 순위가 높은 연산자만 있는 수식의 계산.
    # 순차적으로 계산한다.
    elif count == 3:
        integers.reverse()
        for i in operators:
            if i == "*":
                integers.append(mul(integers.pop(),integers.pop()))
            else:
                try:
                    integers.append(div(integers.pop(),integers.pop()))
                except:
                    print_message(2)
                    safe_exit()
        print(" 계산 결과:: ",integers)
    # 모든 조건문에 해당하지 않을 때.
    else:
        print_message(1)
        continue

            
                   
