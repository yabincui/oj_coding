#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <cmath>

using namespace std;

bool isPrime(int p) {
  if (p % 2 == 0) {
    return p == 2;
  }
  int limit = (int)sqrt(p);
  for (int i = 3; i <= limit; i += 2) {
    if (p % i == 0) {
      return false;
    }
  }
  return true;
}

int modularMul(int a, int b, int n) {
  uint64_t res = 1;
  uint64_t base = a;
  while (b != 0) {
    if (b & 1) {
      res = res * base % n; 
    }
    base = base * base % n;
    b >>= 1;
  }
  return (int)res;
}

int main() {
  freopen("PseudoprimeNumbers.in", "r", stdin);
  int p, a;
  while (scanf("%d%d", &p, &a) == 2 && p != 0 && a != 0) {
    bool result = false;
    if (!isPrime(p)) {
      int v = modularMul(a, p, p);
      if (v == a) {
        result = true;
      }
    }
    printf("%s\n", result ? "yes" : "no");
  }
  return 0;
}
