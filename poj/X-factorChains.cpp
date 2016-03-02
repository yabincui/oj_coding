#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <cmath>
#include <vector>

using namespace std;

uint64_t C[21][21];

void init() {
  for (int i = 0; i <= 20; ++i) {
    for (int j = 0; j <= i; ++j) {
      if (j == 0 || j == i) {
        C[i][j] = 1;
      } else {
        C[i][j] = C[i-1][j] + C[i-1][j-1];
      }
    }
  }
}

vector<int> getFactors(int X) {
  vector<int> v;
  if (X == 1) {
    v.push_back(1);
    return v;
  }
  int limit = (int)sqrt(X);
  for (int i = 2; i <= limit; ++i) {
    if (X % i == 0) {
      int t = 0;
      while (X % i == 0) {
        t++;
        X /= i;
      }
      v.push_back(t);
    }
  }
  if (X != 1) {
    v.push_back(1);
  }
  return v;
}

int main() {
  freopen("X-factorChains.in", "r", stdin);
  int X;
  init();
  while (scanf("%d", &X) == 1) {
    vector<int> v = getFactors(X);
    int sum = 0;
    for (int i = 0; i < v.size(); ++i) {
      sum += v[i];
    }
    uint64_t ways = 1;
    int last = sum;
    for (int i = 0; i < v.size(); ++i) {
      ways *= C[last][v[i]];
      last -= v[i];
    }
    printf("%d %llu\n", sum, ways);
  }
  return 0;
}
