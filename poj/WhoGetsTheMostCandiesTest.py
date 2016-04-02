import subprocess
import random

def test():
  fh = open('WhoGetsTheMostCandies.in', 'w')
  N = random.randint(1, 500000)
  K = random.randint(1, N)
  fh.write('%d %d\n' % (N, K))
  hit_pos = {}
  TN = 2 * N
  for i in range(N):
    x = random.randint(-TN, TN)
    while x == 0:
      x = random.randint(-TN, TN)
    fh.write('C%d %d\n' % (i, x))
  fh.close()
  print 'call ./WhoGetsTheMostCandies_exe'
  t1 = subprocess.check_output('./WhoGetsTheMostCandies_exe')
  print t1
  print 'call ./WhoGetsTheMostCandies_Correct'
  t2 = subprocess.check_output('./WhoGetsTheMostCandies_Correct')
  print t2
  if t1 != t2:
    raise Excpetion('not equal!')

def main():
  while True:
    test()

main()


