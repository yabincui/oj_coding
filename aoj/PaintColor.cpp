#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

int W, H;

struct Tape {
  int x1, y1;
  int x2, y2;
} tapes[1000];

int N;

void compressBoard(vector<vector<bool>>& board) {
  for (int i = 0; i < N; ++i) {
    tapes[i].x1 *= 2;
    tapes[i].y1 *= 2;
    tapes[i].x2 *= 2;
    tapes[i].y2 *= 2;
    //printf("x1 %d, y1 %d, x2 %d, y2 %d\n", tapes[i].x1, tapes[i].y1, tapes[i].x2, tapes[i].y2);
  }
  vector<int> xs, ys;
  for (int i = 0; i < N; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if (tapes[i].x1 + j >= 0 && tapes[i].x1 + j <= W * 2) {
        xs.push_back(tapes[i].x1 + j);
      }
      if (tapes[i].x2 + j >= 0 && tapes[i].x2 + j <= W * 2) {
        xs.push_back(tapes[i].x2 + j);
      }
      if (tapes[i].y1 + j >= 0 && tapes[i].y1 + j <= H * 2) {
        ys.push_back(tapes[i].y1 + j);
      }
      if (tapes[i].y2 + j >= 0 && tapes[i].y2 + j <= H * 2) {
        ys.push_back(tapes[i].y2 + j);
      }
    }
  }
  sort(xs.begin(), xs.end());
  xs.erase(unique(xs.begin(), xs.end()), xs.end());
  sort(ys.begin(), ys.end());
  ys.erase(unique(ys.begin(), ys.end()), ys.end());
  /*
  printf("xs:");
  for (int i = 0; i < xs.size(); ++i) {
    printf(" %d", xs[i]);
  }
  printf("\n");
  printf("ys:");
  for (int i = 0; i < ys.size(); ++i) {
    printf(" %d", ys[i]);
  }
  printf("\n");
  */
  board.clear();
  board.resize(ys.size(), vector<bool>(xs.size(), true));
  for (int i = 0; i < N; ++i) {
    int x1 = lower_bound(xs.begin(), xs.end(), tapes[i].x1) - xs.begin();
    int x2 = lower_bound(xs.begin(), xs.end(), tapes[i].x2) - xs.begin();
    int y1 = lower_bound(ys.begin(), ys.end(), tapes[i].y1) - ys.begin();
    int y2 = lower_bound(ys.begin(), ys.end(), tapes[i].y2) - ys.begin();
    //printf("fill [%d,%d] - [%d,%d]\n", x1, y1, x2, y2);
    for (int x = x1; x <= x2; ++x) {
      for (int y = y1; y <= y2; ++y) {
        board[y][x] = false;
      }
    }
  }
  for (int i = 0; i < board.size(); ++i) {
    for (int j = 0; j < board[0].size(); ++j) {
      //printf("%d%c", (int)board[i][j], (j == board[0].size() - 1) ? '\n' : ' ');
    }
  }
}

int countAreas(vector<vector<bool>>& board) {
  int count = 0;
  int dr[4] = {-1, 1, 0, 0};
  int dc[4] = {0, 0, -1, 1};

  for (int i = 0; i < board.size(); ++i) {
    for (int j = 0; j < board[0].size(); ++j) {
      if (board[i][j]) {
        count++;
        board[i][j] = false;
        queue<pair<int, int>> q;
        q.push(make_pair(i, j));
        while (!q.empty()) {
          pair<int, int> value = q.front(); q.pop();
          for (int t = 0; t < 4; ++t) {
            int r = dr[t] + value.first;
            int c = dc[t] + value.second;
            if (r >= 0 && r < board.size() && c >= 0 && c < board[0].size() && board[r][c]) {
              board[r][c] = false;
              q.push(make_pair(r, c));
            }
          }
        }
      }
    }
  }
  return count;
}

int main() {
  freopen("PaintColor.in", "r", stdin);
  while (scanf("%d%d", &W, &H) == 2 && !(W == 0 && H == 0)) {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
      scanf("%d%d%d%d", &tapes[i].x1, &tapes[i].y1, &tapes[i].x2, &tapes[i].y2);
    }
    vector<vector<bool>> board;
    compressBoard(board);
    int count = countAreas(board);
    printf("%d\n", count);
  }
  return 0;
}
