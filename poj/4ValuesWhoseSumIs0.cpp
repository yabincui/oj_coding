#include <stdio.h>
#include <stdint.h>

#include <map>
#include <algorithm>
using namespace std;

int n;
int s[4][4000];

int64_t getResult() {
  map<int, int> m;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      m[s[0][i] + s[1][j]]++;
    }
  }
  map<int, int> m2;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      m2[s[2][i] + s[3][j]]++;
    }
  }
  int64_t count = 0;
  for (map<int, int>::iterator it = m.begin(); it != m.end(); ++it) {
    map<int, int>::iterator it2 = m2.find(-it->first);
    if (it2 != m2.end()) {
      count += (int64_t)it->second * it2->second;
    }
  }
  return count;
}

int t[4000*4000];

int64_t getResult2() {
  for (int i = 0, k = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      t[k++] = s[0][i] + s[1][j];
    }
  }
  sort(t, t + n * n);
  int64_t count = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int v = -(s[2][i] + s[3][j]);
      int c = upper_bound(t, t + n * n, v) - lower_bound(t, t + n * n, v);
      count += c;
    }
  }
  return count;
}

int main() {
  freopen("4ValuesWhoseSumIs0.in", "r", stdin);
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 4; ++j) {
      scanf("%d", &s[j][i]);
    }
  }
  int64_t count = getResult2();
  printf("%lld\n", count);
  return 0;
}
