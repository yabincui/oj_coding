#include <stdio.h>
#include <algorithm>

using namespace std;

struct Cow {
  int T;
  int D;
  double tDivD;
};

int N;
Cow cows[100000];

bool compareCow(const Cow& c1, const Cow& c2) {
  return c1.tDivD < c2.tDivD;
}

int main() {
  freopen("ProtectingTheFlowers.in", "r", stdin);
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    scanf("%d%d", &cows[i].T, &cows[i].D);
    cows[i].tDivD = cows[i].T / (double)cows[i].D;
  }
  sort(cows, &cows[N], compareCow);
  long long curT = 0;
  long long destroyed = 0;
  for (int i = 0; i < N; ++i) {
    destroyed += curT * cows[i].D;
    curT += cows[i].T * 2;
  }
  printf("%lld\n", destroyed);
  return 0;
}
