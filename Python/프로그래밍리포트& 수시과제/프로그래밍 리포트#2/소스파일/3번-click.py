# click.py
from graphics import *

def main():
    # 이름이 click me인 그래프창을 생성하고
    # 사용자에가 클릭한 좌표 값을  getMouse로 얻고 출력
    # for문을 이용해 10개까지만 출력
    win = GraphWin("Click Me!")  # 크기 지정 안해서 default 크기로 생성
    for i in range(10):
        p = win.getMouse()
        print("You clicked at:", p.getX(), p.getY())
main()
