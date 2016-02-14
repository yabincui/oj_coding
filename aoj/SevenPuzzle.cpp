#include <stdio.h>

#include <queue>
#include <unordered_map>
#include <utility>

using namespace std;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int arrayToState(int s[8]) {
  int state = 0;
  for (int i = 0; i < 8; ++i) {
    state = (state << 3) | s[i];
  }
  return state;
}

void stateToArray(int state, int s[8]) {
  for (int i = 7; i >= 0; --i) {
    s[i] = state & 7;
    state >>= 3;
  }
}

unordered_map<int, int> visited;

void buildMinSwap() {
  int s[8];
  for (int i = 0; i < 8; ++i) {
    s[i] = i;
  }
  int startState = arrayToState(s);
  queue<int> q;
  q.push(startState);
  visited.insert(make_pair(startState, 0));
  int swapCount = 0;
  while (!q.empty()) {
    swapCount++;
    int count = q.size();
    while (count-- > 0) {
      int state = q.front();
      q.pop();
      stateToArray(state, s);
      int i;
      for (i = 0; i < 8; ++i) {
        if (s[i] == 0) {
          break;
        }
      }
      int r = i / 4;
      int c = i % 4;
      for (int d = 0; d < 4; ++d) {
        int nr = r + dr[d];
        int nc = c + dc[d];
        if (nr < 0 || nr > 1 || nc < 0 || nc > 3) {
          continue;
        }
        int j = nr * 4 + nc;
        swap(s[i], s[j]);
        int nextState = arrayToState(s);
        if (visited.find(nextState) == visited.end()) {
          q.push(nextState);
          visited.insert(make_pair(nextState, swapCount));
        }
        swap(s[i], s[j]);
      }
    }
  }
}

int main() {
  freopen("SevenPuzzle.in", "r", stdin);
  int s[8];
  buildMinSwap();
  while (true) {
    int i;
    for (i = 0; i < 8; ++i) {
      if (scanf("%d", &s[i]) != 1) {
        break;
      }
    }
    if (i < 8) {
      break;
    }
    int state = arrayToState(s);
    int result = visited[state];
    printf("%d\n", result);
  }
  return 0;
}
