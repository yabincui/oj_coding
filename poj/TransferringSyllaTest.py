import subprocess
import random

def test():
    fh = open('TransferringSylla.in', 'w')
    N = random.randint(4, 500)
    M = random.randint(1, min(N * (N - 1) / 2, 20000))
    hit = {}
    fh.write('%d %d\n' % (N, M))
    edge = 0
    while edge < M:
        a = random.randint(0, N - 1)
        b = random.randint(0, N - 1)
        if a == b:
            continue
        if hit.has_key((a, b)) or hit.has_key((b, a)):
            continue
        fh.write('%d %d\n' % (a, b))
        hit[(a, b)] = True
        edge += 1
    fh.write('\n0 0\n')
    fh.close()
    print 'call ./TransferringSylla_exe'
    t1 = subprocess.check_output('./TransferringSylla_exe')
    print t1
    print 'call ./TransferringSylla_Correct'
    t2 = subprocess.check_output('./TransferringSylla_Correct')
    print t2
    if t1 != t2:
        raise Exception('not equal')

def main():
    while True:
        test()

main()
