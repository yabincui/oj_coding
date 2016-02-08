#include <stdio.h>

#include <vector>

using namespace std;

int N;
vector<int> v;

int findRoot(int a) {
  if (v[a] == -1) {
    return a;
  }
  return v[a] = findRoot(v[a]);
}

bool isSameSet(int a, int b) {
  return findRoot(a) == findRoot(b);
}

void unionSet(int a, int b) {
  a = findRoot(a);
  b = findRoot(b);
  if (a != b) {
    v[a] = b;
  }
}

bool isTrue(int D, int X, int Y) {
  if (X > N || Y > N || (X == Y && D == 2)) {
    return false;
  }
  if (X == Y && D == 1) {
    return true;
  }
  if (isSameSet(X, Y + N)) {
    return D == 2;
  }
  if (isSameSet(X, Y)) {
    return D == 1;
  }
  if (isSameSet(X + N, Y)) {
    return false;
  }
  if (D == 1) {
    unionSet(X, Y);
    unionSet(X + N, Y + N);
    unionSet(X + 2 * N, Y + 2 * N);
  } else {
    unionSet(X, Y + N);
    unionSet(X + N, Y + 2 * N);
    unionSet(X + 2 * N, Y);
  }
  return true;
}

int main() {
  freopen("FoodLink.in", "r", stdin);
  int K;
  int fake = 0;
  scanf("%d%d", &N, &K);
  v.resize(3*(N+1) + 1, -1);
  for (int i = 0; i < K; ++i) {
    int D, X, Y;
    scanf("%d%d%d", &D, &X, &Y);
    if(!isTrue(D, X, Y)) {
      fake++;
    }
  }
  printf("%d\n", fake);
}
