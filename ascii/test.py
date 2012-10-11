import Image
import ImageDraw
import ImageFont
import math

font = ImageFont.truetype('ttf-inconsolata.otf', 13)

def getCharSize(char):
    size = font.getsize(char)
    im = Image.new("1", size, 255)
    draw = ImageDraw.Draw(im)
    draw.text((0, 0), char, font=font)
    return im.histogram()[0]


all_chars = [chr(i) for i in range(32, 127)]

def compare_char_size(x, y):
    return cmp(getCharSize(x), getCharSize(y))


all_chars.sort(compare_char_size)

sizes = [getCharSize(char) for char in all_chars]

max_size = max(sizes)

chars = {}

for char in all_chars:
    size = getCharSize(char)
    chars[size] = char

char = ' '

for size in range(max_size):
    new_char = chars.get(size)
    if new_char is None:
        chars[size] = char
    else:
        char = new_char

print chars


jpgfile = Image.open('duck2.png')

jpgfile = jpgfile.convert('L')
jpgfile.thumbnail([70, 70])

data = jpgfile.getdata()

size = jpgfile.size

each = int(math.ceil(255.0/len(chars)))

line = []
for i in range(len(data)):
    lineno = i%size[0]
    if lineno == 0:
        print ''.join(line)
        line = []
    line = line + [chars[max_size-data[i]/each]] *2
print ''.join(line)
    #print data[i],