import subprocess
import random

def test():
  fh = open('CowAcrobats.in', 'w')
  N = random.randint(1, 50000)
  fh.write('%d\n' % N)
  for i in range(N):
    fh.write('%d %d\n' % (random.randint(1, 10000), random.randint(1, 1000000000)))
  fh.close()
  subprocess.check_call('./CowAcrobats_exe')

def main():
  while True:
    test()

main()
