import subprocess
import random

def test():
  fh = open('InnerVertices.in', 'w')
  N = random.randint(1, 100)
  fh.write('%d\n' % N)
  hit_pos = {}
  for i in range(N):
    x = random.randint(1, 100)
    y = random.randint(1, 100)
    while hit_pos.has_key((x,y)):
      x = random.randint(1, 100)
      y = random.randint(1, 100)
    hit_pos[(x,y)] = True
    fh.write('%d %d\n' % (x, y))
  fh.close()
  print 'call ./InnerVertices_exe'
  t1 = subprocess.check_output('./InnerVertices_exe')
  print t1
  t2 = subprocess.check_output('./InnerVertices_Correct')
  print t2
  if t1 != t2:
    raise Excpetion('not equal!')

def main():
  while True:
    test()

main()

