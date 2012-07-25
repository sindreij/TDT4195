from PIL import Image
import ImageDraw
import ImageFont
from Tkinter import Tk, Canvas, NW, LEFT, BOTH
import ImageTk

font = ImageFont.truetype('ttf-inconsolata.otf', 13)
size = font.getsize('a')
h,w = size

im = Image.new("1", size, 255)
draw = ImageDraw.Draw(im)
draw.text((0, 0), 'a', font=font)
root = Tk()
canvas = Canvas(root, height=h, width=w)
canvas.pack(side=LEFT, fill=BOTH, expand=1)
root.update()

photo = ImageTk.PhotoImage(im)

item = canvas.create_image(0,0,anchor=NW, image=photo)
root.update()