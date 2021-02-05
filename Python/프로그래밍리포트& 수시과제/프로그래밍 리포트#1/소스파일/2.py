print("첫 번째 정수를 입력 하세요:“)
user_num1 = int(input())
print("두 번째 정수를 입력 하세요:“)
user_num2 = int(input())
print("세 번째 정수를 입력 하세요:“)
user_num3 = int(input())
print("---------------------------------------------------")
print("입력받은 정수: %s, %s, %s"%user_num1,user_num2,user_num3))
print("---------------------------------------------------")
if user_num1 > user_num2 :
      user_num1, user_num2 = user_num2, user_num1
      print("STEP1: %s, %s, %s"%(user_num1,user_num2,user_num3))
else:
      print("STEP1: %s, %s, %s"%(user_num1,user_num2,user_num3))
if user_num2 > user_num3 :
      user_num2, user_num3 = user_num3, user_num2
      print("STEP2: %s, %s, %s"%(user_num1,user_num2,user_num3))
else:
      print("STEP2: %s, %s, %s"%(user_num1,user_num2,user_num3))
if user_num3 > user_num1 :
      user_num3, user_num1 = user_num1, user_num3
      print("STEP3: %s, %s, %s"%(user_num1,user_num2,user_num3))
else:
      print("STEP3: %s, %s, %s"%(user_num1,user_num2,user_num3))
      print("---------------------------------------------------")
      print("정렬된 정수: %s, %s, %s"%user_num1,user_num2,user_num3))
      print("---------------------------------------------------")
