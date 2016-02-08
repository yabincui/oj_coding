#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int N;

struct Node {
  int dist;
  int fuel;
};

vector<Node> v;
int L, P;

bool compareNode(const Node& n1, const Node& n2) {
  return n1.dist < n2.dist;
}

int getMinStops() {
  sort(v.begin(), v.end(), compareNode);
  priority_queue<int> lastFuel;
  int curFuel = P;
  int lastPlace = 0;
  int result = 0;
  for (int i = 0; i <= N; ++i) {
    int d = (i == N) ? L : v[i].dist;
    int needFuel = d - lastPlace;
    while (needFuel > curFuel && !lastFuel.empty()) {
      int add = lastFuel.top();
      lastFuel.pop();
      curFuel += add;
      result++;
    }
    if (needFuel > curFuel && lastFuel.empty()) {
      return -1;
    }
    curFuel -= needFuel;
    if (i < N) {
      lastFuel.push(v[i].fuel);
    }
    lastPlace = d;
  }
  return result;
}

int main() {
  freopen("Expedition.in", "r", stdin);
  scanf("%d", &N);
  v.resize(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d%d", &v[i].dist, &v[i].fuel);
  }
  scanf("%d%d", &L, &P);
  for (int i = 0; i < N; ++i) {
    v[i].dist = L - v[i].dist;
  }
  int result = getMinStops();
  printf("%d\n", result);

  return 0;
}
