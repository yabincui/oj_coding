
import random

def genRandString(n):
    s = ''
    for i in range(n):
        a = chr(ord('a') + random.randint(0, 25))
        s += a
    return s

def writeTest():
    n1 = random.randint(1, 50)
    n2 = random.randint(1, 50)
    s1 = genRandString(n1)
    s2 = genRandString(n2)
    print '%s;%s' % (s1, s2)


writeTest()
