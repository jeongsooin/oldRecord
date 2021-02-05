# -*- coding: utf-8 -*-
#FILE: chaos.py
#A simple program illustrating chaotic behavior

def main():
	print("This program illustrates a chaotic function")
    #문장을 출력합니다.
	x = eval (input("Enter a between number 0 and 1:"))
    #0과 1사이의 숫자를 입력받습니다.
	for i in range(20):
		x = 3.9*x*(1-x)
		print(x)
        #입력받은 값에 3.9와 1-입력값을 곱하고 다시 입력값으로 대입합니다. 10번 반복합니다.
        #반복하는 동안에 계속 x값이 바뀌게 되므로 출력값을 예상할 수 없게됩니다.
main()