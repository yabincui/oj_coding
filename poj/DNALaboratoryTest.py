import subprocess
import random

def test():
    fh = open('DNALaboratory.in', 'w')
    fh.write('1\n')
    n = random.randint(1, 4)
    fh.write('%d\n' % n)
    names = 'ACGT'
    for i in range(n):
        length = random.randint(1, 6)
        s = []
        for j in range(length):
            k = random.randint(0, 3)
            s.append(names[k])
        fh.write('%s\n' % ''.join(s))
    fh.close()
    print 'call ./DNALaboratory_exe'
    t1 = subprocess.check_output('./DNALaboratory_exe')
    print t1
    print 'call ./DNALaboratory_Correct'
    t2 = subprocess.check_output('./DNALaboratory_Correct')
    print t2
    if t1 != t2:
        raise Exception('not equal!')

def main():
    while True:
        test()

main()
