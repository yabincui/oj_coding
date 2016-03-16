#include <stdio.h>
#include <algorithm>
#include <cmath>
using namespace std;

int N, H, R, T;

double loc[100];

void getResult() {
  double g = 10.0;
  for (int i = 0; i < N; ++i) {
    double h = H;
    double t0 = i;
    double t = sqrt(2*h/g);
    if ( T <= t0) {
      loc[i] = h;
      continue;
    }
    int d = (int)((T - t0) / (2 * t));
    double rem_t = T - t0 - d * 2 * t;
    if (rem_t <= t) {
      loc[i] = h - 0.5 * g * rem_t * rem_t;
    } else {
      rem_t -= t;
      double v = g * t;
      loc[i] = v * rem_t - 0.5 * g * rem_t * rem_t;
    }
  }
  sort(loc, loc + N);
  for (int i = 0; i < N; ++i) {
    loc[i] += 2 * 0.01 * R * i;
  }
}

int main() {
  freopen("PhysicsExperiment.in", "r", stdin);
  int test;
  scanf("%d", &test);
  for (int t = 0; t < test; ++t) {
    scanf("%d%d%d%d", &N, &H, &R, &T);
    getResult();
    for (int i = 0; i < N; ++i) {
      printf("%.2f%c", loc[i], (i != N - 1) ? ' ' : '\n');
    }
  }
  return 0;
}
