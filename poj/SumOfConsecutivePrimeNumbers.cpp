#include <stdio.h>

#include <cmath>
using namespace std;

int primes[10000];
int prime_count;

void init() {
  int i = 0;
  primes[i++] = 2;
  for (int p = 3; p <= 10000; p += 2) {
    int half = (int)sqrt(p);
    bool ok = true;
    for (int t = 0; t < i && primes[t] <= half; ++t) {
      if (p % primes[t] == 0) {
        ok = false;
        break;
      }
    }
    if (ok) {
      primes[i++] = p;
    }
  }
  prime_count = i;
}

int getCount(int target) {
  int start = 0, end = 0;
  int result = 0;
  int sum = 0;
  while (end < prime_count) {
    bool too_big = false;
    while (end < prime_count && sum < target) {
      if (primes[end] > target) {
        too_big = true;
        break;
      }
      sum += primes[end++];
    }
    if (too_big) {
      break;
    }
    if (sum == target) {
      result++;
    }
    sum -= primes[start++];
  }
  return result;
}

int main() {
  freopen("SumOfConsecutivePrimeNumbers.in", "r", stdin);
  init();
  int k;
  while (scanf("%d", &k) == 1 && k != 0) {
    int result = getCount(k);
    printf("%d\n", result);
  }
  return 0;
}
