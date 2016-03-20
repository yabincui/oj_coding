import subprocess
import random

def test():
  fh = open('MooFest.in', 'w')
  N = random.randint(1, 10000)
  fh.write('%d\n' % N)
  hit_pos = {}
  for i in range(N):
    v = random.randint(1, 10000)
    x = random.randint(1, 10000)
    while hit_pos.has_key(x):
      x = random.randint(1, 10000)
    hit_pos[x] = True
    fh.write('%d %d\n' % (v, x))
  fh.close()
  print 'call ./MooFest_exe'
  t1 = subprocess.check_output('./MooFest_exe')
  print t1
  print
  s = t1.split()
  if s[0] != s[1]:
    raise Excpetion('not equal!')

def main():
  while True:
    test()

main()
