#include <stdio.h>
#include <vector>
#include <stack>

using namespace std;

int N, M;
char map[101][101];


void mark(int startR, int startC, vector<vector<bool>>& visited);

int getConnectedParts() {
  vector<vector<bool>> visited(N, vector<bool>(M));
  int parts = 0;

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      if (!visited[i][j] && map[i][j] == 'W') {
        mark(i, j, visited);
        parts++;
      }
    }
  }
  return parts;
}

void mark(int startR, int startC, vector<vector<bool>>& visited) {
  stack<int> st;
  st.push((startR << 16) | startC);
  while (!st.empty()) {
    int value = st.top();
    st.pop();
    int r = value >> 16;
    int c = value & 0xffff;
    visited[r][c] = true;
    for (int dr = -1; dr <= 1; ++dr) {
      for (int dc = -1; dc <= 1; ++dc) {
        int tr = r + dr;
        int tc = c + dc;
        if (tr < 0 || tr >= N || tc < 0 || tc >= M) {
          continue;
        }
        if (map[tr][tc] == '.' || visited[tr][tc]) {
          continue;
        }
        st.push((tr << 16) | tc);
      }
    }
  }
}

int main() {
  freopen("LakeCounting.in", "r", stdin);
  scanf("%d%d", &N, &M);
  for (int i = 0; i < N; ++i) {
    scanf("%s", map[i]);
  }
  int result = getConnectedParts();
  printf("%d\n", result);
  return 0;
}
