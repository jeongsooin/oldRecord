# 1번.py

try:
    from graphics import*
    import re
    import operator
except:
    print("모듈을 import하지 못했습니다.")
    input("Press Enter to quit.")
    exit(1)

# input으로 사용할 파일을 읽어들인다.
# 단어를 추출하기 위해 공백을 기준으로 나눈다.
try:
    f=open("input.txt",'r')
    text = f.read()
    text = re.split('[ \n]+',text)
except:
    print("파일을 열어 읽어들이는데에 실패했습니다.")
    
# 나눈 단어들이 저장된 리스트를 읽어서
# 없는 단어면 딕셔너리에 추가하고
# 있는 단어면 갯수를 추가한다.
dic={}
for i in text:
    if i not in dic:
        dic[i] = 1
    else:
        dic[i]=dic[i]+1

# 단어가 들어온 갯수가 큰 순서대로 정렬한다.
# 정렬한 값을 key와 value의 리스트로 따로 만든다.
data = (sorted(dic.items(),key=operator.itemgetter(1),reverse=True))
keylist = [x[0] for x in data]
valuelist = [x[1] for x in data]

# 그래프에 빈도 횟수 상위 10개를 출력할건데,
# 추출한 단어가 10개도 안될 수 있다.
# 그럴 경우 key와 value의 리스트를 null과 0으로 채워
# 오류를 방지한다. 
if len(keylist) < 10 :
    for i in range(11-len(keylist)):
        keylist.append('Null')
if len(valuelist) < 10 :
    for i in range(11-len(valuelist)):
        valuelist.append(0)
        
# 그래프를 그린다.
# x 축의 구분자로 key 값의 리스트에서 순서대로 참조하여
# 그래프에 나타낸다. 
win = GraphWin("Text Input 분석",800,500)
win.setBackground("white")
win.setCoords(0,0,58,60)
Text(Point(6,5),keylist[0]).draw(win)
Text(Point(11,5),keylist[1]).draw(win)
Text(Point(16,5),keylist[2]).draw(win)
Text(Point(21,5),keylist[3]).draw(win)
Text(Point(26,5),keylist[4]).draw(win)
Text(Point(31,5),keylist[5]).draw(win)
Text(Point(36,5),keylist[6]).draw(win)
Text(Point(41,5),keylist[7]).draw(win)
Text(Point(46,5),keylist[8]).draw(win)
Text(Point(51,5),keylist[9]).draw(win)
Text(Point(3,7),'0- - - - -').draw(win)
Text(Point(3,12),'5- - - - -').draw(win)
Text(Point(3,17),'10- - - - -').draw(win)
Text(Point(3,22),'15- - - - -').draw(win)
Text(Point(3,27),'20- - - - -').draw(win)
Text(Point(3,32),'25- - - - -').draw(win)
Text(Point(3,37),'30- - - - -').draw(win)
Text(Point(3,42),'35- - - - -').draw(win)
Text(Point(3,47),'40- - - - -').draw(win)
Text(Point(3,52),'45- - - - -').draw(win)
Text(Point(3,57),'50- - - - -').draw(win)

# 출력할 10개의 단어의 등장 횟수를 막대로 그린다.
# 그래프를 읽기 쉽도록 높이가 곧 횟수가 되게 한다.
# 단, 등장 횟수가 그래프로 그릴 수 있는 최고 높이를 초과할 수도 있는데
# 그럴 경우 값을 강제로 그래프의 한도치로 잡아준다.
for j in range (0,10):
    height = valuelist[j]
    if height >= 53 :
        height = 53
        print("%s의 크기가 최고 한도(53)를 초과해 MAX 값으로 설정됩니다."%keylist[j])
        print("실제 크기는 %d 입니다."%valuelist[j])
    else:
        pass
    xll=(j+1)*5
    bar = Rectangle(Point(xll,7),Point(xll+2,height+7))
    bar.setFill("pink")
    bar.setWidth(1)
    bar.draw(win)

print("──────────────────────────────────")
input("\n종료 하려면 <Enter>를 누르세요.\n")
win.close()




