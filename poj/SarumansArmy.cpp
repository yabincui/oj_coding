#include <stdio.h>

#include <algorithm>
#include <vector>

using namespace std;

int R;
int n;
vector<int> v;

int getMinPoints() {
  sort(v.begin(), v.end());
  int lastPos = -1;
  int points = 0;
  for (size_t i = 0; i < v.size(); ++i) {
    if (lastPos != -1 && v[i] >= lastPos - R && v[i] <= lastPos + R) {
      continue;
    }
    size_t j = i;
    while (j + 1 < v.size() && v[j + 1] - v[i] <= R) {
      ++j;
    }
    lastPos = v[j];
    points++;
    //printf("lastPos = %d\n", lastPos);
  }
  return points;
}

int getMinPoints2() {
  sort(v.begin(), v.end());
  int i = 0;
  int result = 0;
  while (i < n) {
    int start = v[i++];
    while (i < n && v[i] - start <= R) {
      i++;
    }
    int point = v[i-1];
    result++;
    while (i < n && v[i] <= point + R) {
      i++;
    }
  }
  return result;
}

int main() {
  freopen("SarumansArmy.in", "r", stdin);
  while (true) {
    scanf("%d%d", &R, &n);
    if (R == -1 && n == -1) {
      break;
    }
    v.resize(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &v[i]);
    }
    int result = getMinPoints2();
    printf("%d\n", result);
  }
  return 0;
}
