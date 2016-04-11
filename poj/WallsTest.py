import subprocess
import random

horizon_lines = {}
vertical_lines = {}

def addHorizonLine(line):
    x1 = min(line[0], line[2])
    x2 = max(line[0], line[2])
    y = line[1]
    lines = horizon_lines.get(y)
    if lines is None:
        horizon_lines[y] = [(x1, x2)]
        return True
    for t in lines:
        if t[0] <= x1:
            if t[1] >= x1:
                return False
        elif x2 >= t[0]:
            return False
    lines.append((x1, x2))
    return True

def addVerticalLine(line):
    x = line[0]
    y1 = min(line[1], line[3])
    y2 = max(line[1], line[3])
    lines = vertical_lines.get(x)
    if lines is None:
        vertical_lines[x] = [(y1, y2)]
        return True
    for t in lines:
        if t[0] <= y1:
            if t[1] >= y1:
                return False
        elif y2 >= t[0]:
            return False
    lines.append((y1, y2))
    return True

def isDotOk(x, y):
    lines = horizon_lines.get(y)
    if lines is not None:
        for t in lines:
            if t[0] <= x and t[1] >= x:
                return False
    lines = vertical_lines.get(x)
    if lines is not None:
        for t in lines:
            if t[0] <= y and t[1] >= y:
                return False
    return True

def test():
    horizon_lines = {}
    vertical_lines = {}
    fh = open('Walls.in', 'w')
    N = random.randint(1, 4) + 20
    M = random.randint(1, 1)
    fh.write('%d %d\n' % (N, M))
    MIN_X = 1
    MAX_X = 100
    MIN_Y = 1
    MAX_Y = 100
    fh.write('%d %d %d %d\n' % (MIN_X - 1, MIN_Y - 1, MAX_X + 1, MIN_Y - 1))
    fh.write('%d %d %d %d\n' % (MIN_X - 1, MIN_Y - 1, MIN_X - 1, MAX_Y + 1))
    fh.write('%d %d %d %d\n' % (MIN_X - 1, MAX_Y + 1, MAX_X + 1, MAX_Y + 1))
    fh.write('%d %d %d %d\n' % (MAX_X + 1, MIN_Y - 1, MAX_X + 1, MAX_Y + 1))
    i = 0
    while i < N - 4:
        if random.randint(0, 1) == 0:
            x = random.randint(MIN_X, MAX_X)
            y1 = random.randint(MIN_Y, MAX_Y)
            y2 = random.randint(MIN_Y, MAX_Y)
            line = (x, y1, x, y2)
            if not addVerticalLine(line):
                continue
        else:
            x1 = random.randint(MIN_X, MAX_X)
            x2 = random.randint(MIN_X, MAX_X)
            y = random.randint(MIN_Y, MAX_Y)
            line = (x1, y, x2, y)
            if not addHorizonLine(line):
                continue
        fh.write('%d %d %d %d\n' % line)
        i += 1
    i = 0
    while i < M:
        x = random.randint(MIN_X, MAX_X)
        y = random.randint(MIN_Y, MAX_Y)
        if isDotOk(x, y):
            fh.write('%d %d\n' % (x, y))
            i += 1
    fh.close()
    print 'call ./Walls_exe'
    t1 = subprocess.check_output('./Walls_exe')
    print t1
    print 'call ./Walls_Correct'
    t2 = subprocess.check_output('./Walls_Correct')
    print t2
    if t1 != t2:
        raise Exception('not equal!')

def main():
    while True:
        test()

main()
