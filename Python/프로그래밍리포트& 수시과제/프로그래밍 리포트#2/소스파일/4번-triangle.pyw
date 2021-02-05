# triangle.pyw
from graphics import *

def main():
        # 창을 생성하고 좌표계 크기를 설정
        # 창의 아래쪽에 안내 문구가 나오도록 위치를 정하고 나타냄
        win = GraphWin("Draw a Triangle")
        win.setCoords(0.0, 0.0, 10.0, 10.0)
        message = Text(Point(5, 0.5), "Click on three points")
        message.draw(win)

        # 사용자가 클릭하는 좌표 값을 얻어
        # 꼭지점으로 창에 나타냄
        p1 = win.getMouse()
        p1.draw(win)
        p2 = win.getMouse()
        p2.draw(win)
        p3 = win.getMouse()
        p3.draw(win)

        # Polygon =  세 점으로 삼각형 생성
        # 삼각형 속의 색깔과 바깥선의 색깔 지정하고 draw
        triangle = Polygon(p1,p2,p3)
        triangle.setFill("peachpuff")
        triangle.setOutline("cyan")
        triangle.draw(win)

        # Wait for another click to exit
        # 클릭하면 다음 수행할 문장 없어 종료
        message.setText("Click anywhere to quit.")
        win.getMouse()    

main()
