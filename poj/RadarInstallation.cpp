#include <math.h>
#include <stdio.h>

#include <algorithm>

using namespace std;

int N, D;

struct Point {
  int x, y;
};

Point points[1000];

bool compareMaxX(const Point& p1, const Point& p2) {
  double mx1 = p1.x + sqrt((double)D * D - p1.y * p1.y);
  double mx2 = p2.x + sqrt((double)D * D - p2.y * p2.y);
  return mx1 < mx2;
}

int getMinCount() {
  for (int i = 0; i < N; ++i) {
    if (fabs((double)points[i].y) > D) {
      return -1;
    }
  }
  sort(points, &points[N], compareMaxX);
  int count = 0;
  int cur = 0;
  while (cur < N) {
    double x = points[cur].x + sqrt((double)D * D - points[cur].y * points[cur].y);
    count++;
    cur++;
    while (cur < N &&
      sqrt((x - points[cur].x) * (x - points[cur].x) + points[cur].y * points[cur].y) <= D + 1e-6) {
      cur++;
    }
  }
  return count;
}

int main() {
  freopen("RadarInstallation.in", "r", stdin);
  for (int test = 1;; ++test) {
    scanf("%d%d", &N, &D);
    if (N == 0 && D == 0) {
      break;
    }
    for (int i = 0; i < N; ++i) {
      scanf("%d%d", &points[i].x, &points[i].y);
    }
    int result = getMinCount();
    printf("Case %d: %d\n", test, result);
  }
  return 0;
}
