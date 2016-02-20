#include <stdio.h>
#include <string.h>

#include <utility>

using namespace std;

int N, Q;
pair<char, int> S[100000];
int parent[100001];
int mark[100001];
int set[100001];

int findRoot(int p) {
  int root = p;
  while (set[root] != -1) {
    root = set[root];
  }
  while (p != root) {
    int t = set[p];
    set[p] = root;
    p = t;
  }
  return root;
}

void unionSet(int p, int q) {
  int root1 = findRoot(p);
  int root2 = findRoot(q);
  if (root1 != root2) {
    set[root1] = root2;
  }
}

int main() {
  freopen("MarkedAncestor.in", "r", stdin);
  //freopen("2170-input.txt", "r", stdin);
  while (scanf("%d%d", &N, &Q) == 2 && !(N == 0 && Q == 0)) {
    parent[1] = 1;
    for (int i = 2; i <= N; ++i) {
      scanf("%d", &parent[i]);
    }
    set[1] = -1;
    for (int i = 2; i <= N; ++i) {
      set[i] = parent[i];
    }
    memset(mark, 0, sizeof(mark));
    mark[1] = 1;
    for (int i = 0; i < Q; ++i) {
      char buf[10];
      scanf("%s%d", buf, &S[i].second);
      S[i].first = buf[0];
      if (S[i].first == 'M') {
        set[S[i].second] = -1;
        mark[S[i].second]++;
      }
    }
    long long sum = 0;
    // From back to front.
    for (int i = Q - 1; i >= 0; --i) {
      if (S[i].first == 'M') {
        if (--mark[S[i].second] == 0) {
          unionSet(S[i].second, parent[S[i].second]);
        }
      } else if (S[i].first == 'Q') {
        int v = findRoot(S[i].second);
        //printf("findRoot(%d) = %d\n", S[i].second, v);
        sum += v;
      }
    }
    printf("%lld\n", sum);
  }
  return 0;
}
