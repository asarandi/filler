import sys, os
from Tkinter import *
import tkMessageBox
import random
import time


p1 = ""
p2 = ""

top_margin0 = 3
left_margin = 3
box_width = 12
box_height = 12
spacing = 1

boardsize_x = 0
boardsize_y = 0

p1_score = -1
p2_score = -1

def	init_values():
                global p1
                global p2
                global boardsize_x
                global boardsize_y
                line0 = sys.stdin.readline()
                if   '$$$ exec p1 :' in line0:
                    ptmp = line0.split(" ")[4]
                    ptm = ptmp.split("/")[-1]
                    p1 = ptm.split(".filler")[0]
                elif '$$$ exec p2 :' in line0:
                    ptmp = line0.split(" ")[4]
                    ptm = ptmp.split("/")[-1]
                    p2 = ptm.split(".filler")[0]
                elif 'Plateau ' in line0:
                    line0 = line0.replace(':', ' ')
                    line1 = line0.split(" ")
                    boardsize_x = int(line1[1])
                    boardsize_y = int(line1[2])
                    return
                init_values()
                        
def	read_board():
                global boardsize_y
                global boardsize_x
                global p1_score
                global p2_score
                global board
		line0 = sys.stdin.readline()
                if "<got (O): [" in line0:
                    p1_score += 1
                elif "<got (X): [" in line0:
                    p2_score += 1
                elif "== O fin: " in line0:
                    msg1 = "P1  (red): " + p1 + " " + str(p1_score) + "\n"
                    msg2 = "P2 (blue): " + p2 + " " + str(p2_score)
                    tkMessageBox.showinfo("Game over", msg1 + msg2)
                    sys.exit()
		elif "    0" in line0:
#                    print(boardsize_x)
		    for r in range(0, boardsize_x):
			line1 = sys.stdin.readline()
#                        print(line1)
			lnsplt = line1.split(" ", 2)
			row = int(lnsplt[0]);
			line2 = lnsplt[1] #line1.split(" ", 1)[1]
			for i, c in enumerate(line2):
#                                print(row, i)
			    if (c == '.'):
				board[r][i] = 0
			    elif (c == 'o'):
				board[r][i] = 1
#                                p1_score += 1
			    elif (c == 'O'):
			        board[r][i] = 2
#                               p1_score += 1
			    elif (c == 'x'):
			 	board[r][i] = 3
#                                p2_score += 1
			    elif (c == 'X'):
				board[r][i] = 4
#                                p2_score += 1
			    elif (c == '='):
				board[r][i] = 5
#                    p1_score = 0
#                    p2_score = 0
#                    for y in board:
#                        for x in y:
#                            if (x == 1) or (x == 2):
#                                p1_score += 1
#                            elif (x == 3) or (x == 4):
#                                p2_score += 1
                    return
                else:
    		    read_board()

def update_window():
        global Matrix
        global batrix
        global board
	for x, i in enumerate(board):
		for y, j in enumerate(i):
			if (j == 1) and (batrix[x][y] != 1):
				batrix[x][y] = 1
				canvas.itemconfig(Matrix[x][y], fill="magenta")
			elif (j == 2) and (batrix[x][y] != 2):
				batrix[x][y] = 2
				canvas.itemconfig(Matrix[x][y], fill="red")
			elif (j == 3) and (batrix[x][y] != 3):
				batrix[x][y] = 3
				canvas.itemconfig(Matrix[x][y], fill="cyan")
			elif (j == 4) and (batrix[x][y] != 4):
				batrix[x][y] = 4
				canvas.itemconfig(Matrix[x][y], fill="blue")
			elif (j == 5) and (batrix[x][y] != 5):
				batrix[x][y] = 5;
				canvas.itemconfig(Matrix[x][y], fill="brown")







init_values()
#print("attention:", boardsize_x)
#print("attention:", boardsize_y)

window_width = boardsize_y * box_width
window_height = boardsize_x * box_height

Matrix = [[0 for y in range(boardsize_y)] for x in range(boardsize_x)]
#for i in Matrix:
#    print(i)
batrix = [[0 for y in range(boardsize_y)] for x in range(boardsize_x)]
board = [[0 for y in range(boardsize_y)] for x in range(boardsize_x)]


#print(window_width)
#print(window_height)

root = Tk()
p1_label = Label(root, text="P1: " + p1); p1_label.pack()
p2_label = Label(root, text="P2: " + p2); p2_label.pack()
canvas = Canvas(root, width=window_width, height=window_height)
canvas.pack()


#print(boardsize_y, boardsize_x)
for x, i in enumerate(Matrix):
	top_margin = top_margin0 + (x * box_height)
	for y, j in enumerate(i):
		x0 = left_margin + (y * box_width)
		y0 = top_margin # + (i * box_height)
		x1 = x0 + (box_width - spacing)
		y1 = y0 + (box_height - spacing)
 #               print(x, y)
		Matrix[x][y] = canvas.create_rectangle(x0, y0, x1, y1, fill="beige", outline="red", width=0)

def callback():
	rand_x = random.randrange(0, boardsize_x)
	rand_y = random.randrange(0, boardsize_y)
	canvas.itemconfig(Matrix[rand_x][rand_y], fill="red")



def close(event):
    sys.exit() # if you want to exit the entire thing


def task():
#	print("hello")
#	callback()
	read_board()
	update_window()
        p1_label.config(text="P1  (red): " + p1 + " " + str(p1_score))
        p2_label.config(text="P2 (blue): " + p2 + " " + str(p2_score))     
        canvas.update()
#        time.sleep(0.01)
	root.after(0, task)

#button = Button(root, text='Piush me!', command=callback)
#button.pack()
os.system('''/usr/bin/osascript -e 'tell app "Finder" to set frontmost of process "Python" to true' ''')
root.bind('<Escape>', close)
root.after(0, task)
root.mainloop()
