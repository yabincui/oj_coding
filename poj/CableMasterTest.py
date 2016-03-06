#!/usr/bin/python

import random
import subprocess

## write test cases for CableMaster
def writeTest():
  N = random.randint(1, 10000)
  K = random.randint(1, 10000)
  fh = open('CableMaster.in', 'w')
  fh.write("%d %d\n" % (N, K))
  for i in range(N):
    v = random.uniform(1.0, 100000.0)
    fh.write("%.2lf\n" % v)

def main():
  random.seed()
  while True:
    writeTest()
    subprocess.check_call('./CableMaster_exe')

if __name__ == '__main__':
  main()
