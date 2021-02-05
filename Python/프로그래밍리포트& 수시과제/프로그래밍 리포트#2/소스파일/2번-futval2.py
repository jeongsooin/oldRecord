
from graphics import*

def main():
    # Introduction
    print("This program plots the growth of a 10-year investment.")

    # Get a principal and interest rate
    principal = eval(input("Enter the initial principal: "))
    apr = eval(input("Enter the annualized interest rate: "))

    # Create a grapfics window with labels on left edge
    # 창을 지정한 크기로 만들게 하고, 배경을 흰색으로 설정
    # 창에 좌표계를 설정함.
    # 이제 픽셀이 아닌 좌표계를 이용하여 lable 표시
    win = GraphWin("Investment Growth Chart", 320, 240)
    win.setBackground("white")
    win.setCoords(-1.75, -200, 11.5, 10400)
    Text(Point(-1, 0), ' 0.0K').draw(win)
    Text(Point(-1, 2500), ' 2.5K').draw(win)
    Text(Point(-1, 5000), ' 5.0K').draw(win)
    Text(Point(-1, 7500), ' 7.5K').draw(win)
    Text(Point(-1, 10000), ' 10.0K').draw(win)

    # Draw bar for initial principal
    # 사각형의 왼쪽아래점과 오른쪽 위의 점을 지정하여 bar를 나타냄
    # 막대 안쪽의 색, 너비 설정
    bar = Rectangle(Point(0,0), Point(1, principal))
    bar.setFill("green")
    bar.setWidth(2)
    bar.draw(win)

    # Draw a bar for each subsequent year
    for year in range(1, 11):
        
        # 다음 년도의 principal 계산
        # 좌표계를 이용하므로 year 값을 사용하여 지정 가능
        principal =  principal * ( 1 + apr )
        bar = Rectangle(Point(year,0), Point(year+1,principal))
        bar.setFill("green")
        bar.setWidth(2)
        bar.draw(win)

        
    # Enter를 입력 받으면 종료.
    input("Press <Enter> to quit.")
    win.close()

main()
