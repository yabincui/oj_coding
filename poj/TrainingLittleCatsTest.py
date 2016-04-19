import subprocess
import random

def test():
  fh = open('TrainingLittleCats.in', 'w')
  N = random.randint(1, 100)
  M = random.randint(1, 100)
  K = random.randint(1, 100)
  fh.write('%d %d %d\n' % (N, M, K))
  for i in range(K):
    options = 'gse'
    sel = random.randint(3)
    op = options[sel]
    if op == 'g':
        a = random.randint(1, N)
        fh.write('g %d\n' % a)
    elif op == 's':
        a = random.randint(1, N)
        b = random.randint(1, N)
        fh.write('s %d %d\n' % (a, b))
    else:
        a = random.randint(1, N)
        fh.write('e %d\n' % a)
  fh.write("0 0 0\n")
  fh.close()
  print 'call ./TrainingLittleCats_exe'
  t1 = subprocess.check_output('./TrainingLittleCats_exe')
  print t1
  print 'call ./TrainingLittleCats_Correct'
  t2 = subprocess.check_output('./TrainingLittleCats_Correct')
  print t2
  if t1 != t2:
    raise Excpetion('not equal!')

def main():
  while True:
    test()

main()


