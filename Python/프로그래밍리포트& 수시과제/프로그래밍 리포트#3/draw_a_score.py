import os
import random
from graphics import*

def create_file():

    print("This is a program to drawing a quize score histogram.")
    print("-----------------------------------------------------")

    # 성적 데이터를 쓸 파일을 지정 경로에 생성
    f = open ("C:/score.txt",'w')
    student_num = 1

    # 학생 30명의 성적을 랜덤으로 만들어 파일에 쓴다.
    # write 함수의 인자로 넣기 위해 정수를 문자열로 변환
    while student_num <= 30:
        score_before = random.randint(0,10)
        score_after = str(score_before)
        f.write(score_after)
        f.write("\n")
        student_num = student_num+1
    f.close()

def main():
    # 생성된 파일을 오픈하여 \n문자를 제외하고 문장들을 읽어들인다.
    # 파일 안의 성적은 문자열 형식으로 저장되었으므로
    # 다시 정수로 변환한다.
    f = open ("C:/score.txt",'r')
    score_list0 = f.read().split()
    score_list1 = list(map(int,score_list0))
    howmuchlist = []
    i = 0
    
    # 0부터 10까지의 성적을 가진 학생이 각각 몇명인지 센다.
    # count는 요소의 갯수가 0인 경우에는 값을 써주지 않으므로
    # 없을 경우에는 0이 추가되도록 조건문을 설정한다.
    while i <= 10:
        if i in score_list1:
            howmuchlist.append(score_list1.count(i))
            i = i +1       
        else:
            howmuchlist.append(0)
            i = i+1
        continue

    # 가져온 데이터를 바탕으로 그래프를 그린다.
    # 막대의 높이가 점수에 해당하는 학생 수가 되도록 할 것이므로
    # 좌표계를 설정해주고, 하단에 각 점수 구간을 표시해준다.
    win = GraphWin("Score Chart",600,330)
    win.setBackground("white")
    win.setCoords(0,0,12,20)
    Text(Point(1, 1), '0').draw(win)
    Text(Point(2,1), '1').draw(win)
    Text(Point(3,1), '2').draw(win)
    Text(Point(4,1), '3').draw(win)
    Text(Point(5,1), '4').draw(win)
    Text(Point(6,1), '5').draw(win)
    Text(Point(7,1), '6').draw(win)
    Text(Point(8,1), '7').draw(win)
    Text(Point(9,1), '8').draw(win)
    Text(Point(10,1), '9').draw(win)
    Text(Point(11,1), '10').draw(win)

    # 높이는 학생수를 저장한 리스트에서 인덱스를 이용하여 가져온다.
    # 막대 그래프를 그릴 수 있도록 설정하고 창에 그린다.
    # 그래프를 높이 2 지점부터 그리기 때문에 height+2를 한다. 
    for j in range(0,11):
        height = howmuchlist[j]
        xll = j+1
        bar = Rectangle(Point(xll,2),Point(xll+0.5,height+2))
        bar.setFill("green")
        bar.setWidth(1)
        bar.draw(win)
    # 프로그램이 바로 종료되지 않도록 입력을 받는다.
    # 입력을 받으면 창을 닫는다.
    input("Press <Enter> to quit.")
    win.close()

# 메인 코드에서 각 함수 호출
# 지정 경로에 생성한 파일을 찾아 지울필요 없도록 다시 지워준다. 
create_file()
main()
os.remove("C:/score.txt")
