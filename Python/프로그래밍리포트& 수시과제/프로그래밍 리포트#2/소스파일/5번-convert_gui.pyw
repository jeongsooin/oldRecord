# convert_gui.pyw
# Program to convert Celsius to Fahrenheit using a simple
# graphical interface.

from graphics import *


def main():
    # 지정한 크기와 이름의 창을 만들고 좌표계 설정
    win = GraphWin("Celsius Converter", 400, 300)
    win.setCoords(0.0, 0.0, 3.0, 4.0)

    # Draw the interface
    Text(Point(1,3), " Celsius Temperature:").draw(win)
    Text(Point(1,1), "Fahrenheit Temperature:").draw(win)

    # 입력과 출력값이 나타날 지점 설정
    # 입력하는 곳에는 0.0, 출력 부분에는 표시할 값 아직 없음. 
    input = Entry(Point(2,3), 5)
    input.setText("0.0")
    input.draw(win)
    output = Text(Point(2,1),"")
    output.draw(win)

    # 버튼 문구가 표시될 지점 지정하고 텍스트 표시
    # Rectangle = 버튼 문구를 둘러싼 사각형을 그림
    button = Text(Point(1.5,2.0),"Convert It")
    button.draw(win)
    Rectangle(Point(1,1.5), Point(2,2.5)).draw(win) 

    # wait for a mouse click
    win.getMouse()

    # 마우스를 클릭하면 convert input
    celsius = eval(input.getText())
    fahrenheit = 9.0/5.0 * celsius + 32  # fahrenheit로 변환하는 공식

    # display output and change button
    output.setText(fahrenheit)
    button.setText("Quit")

    # wait for click and then quit
    win.getMouse()
    win.close()

main()
        
