import os
import random
from graphics import*

def create_file():
    f = open ("C:/score.txt",'w')
    student_num = 1
    while student_num <= 30:
        score_before = random.randint(0,10)
        score_after = str(score_before)
        f.write(score_after)
        f.write("\n")
        student_num = student_num+1
    f.close()

def main():
    f = open ("C:/score.txt",'r')
    score_list0 = f.read().split()
    score_list1 = list(map(int,score_list0))
    howmuchlist = []
    i = 0
    while i <= 10:
        if i in score_list1:
            howmuchlist.append(score_list1.count(i))
            i = i +1       
        else:
            howmuchlist.append(0)
            i = i+1
        continue

    win = GraphWin("Investment Growth Chart", 320, 240)
    win.setBackground("white")
    Text(Point(20, 230), '0').draw(win)
    Text(Point(20, 200), '5').draw(win)
    Text(Point(20, 170), '10').draw(win)
    Text(Point(20, 140), '15').draw(win)
    Text(Point(20, 110), '20').draw(win)
    Text(Point(20, 80), '25').draw(win)
    Text(Point(20, 60), '30').draw(win)

    height = howmuchlist[i]
    bar = Rectangle(Point(40,230), Point(45, 230-height)) 
    bar.setFill("green")
    bar.setWidth(2)
    bar.draw(win)

    for i in range(0,9):

        xll = i * 5 + 40       
        height = howmuchlist[i]
        bar = Rectangle(Point(xll,230), Point(xll+5, 230-height))
        bar.setFill("green")
        bar.setWidth(2)
        bar.draw(win)


    input("Press <Enter> to quit")
    print("press num1")
    num = int(input())
    if num == 1:
        os.remove("C:/score.txt")
        win.close()
        
create_file()
main()
