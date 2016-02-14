#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <queue>

using namespace std;

struct Hit {
  int x, y, t;
};

int M;
Hit hits[50000];

bool unsafe_map[302][302];
bool destroyed_map[302][302];
bool visited_map[302][302];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool compareHit(const Hit& h1, const Hit& h2) {
  return h1.t < h2.t;
}

int goSafeTime() {
  queue<int> q;
  q.push(0);
  int hit_index = 0;
  int time = 0;
  
  if (unsafe_map[0][0] == false) {
    return 0;
  }
  visited_map[0][0] = true;
  while (!q.empty()) {
    time++;
    while (hit_index < M && hits[hit_index].t <= time) {
      int x = hits[hit_index].x;
      int y = hits[hit_index].y;
      destroyed_map[x][y] = true;
      for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx <= 301 && ny >= 0 && ny <= 301) {
          destroyed_map[nx][ny] = true;
        }
      }
      hit_index++;
    }
    int count = q.size();
    while (count-- > 0) {
      int node = q.front();
      q.pop();
      int x = node >> 16;
      int y = node & 0xffff;
      for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || ny < 0) {
          continue;
        }
        if (nx <= 301 && ny <= 301) {
          if (destroyed_map[nx][ny]) {
            continue;
          }
          if (unsafe_map[nx][ny] == false) {
            return time;
          }
          if (visited_map[nx][ny]) {
            continue;
          }
          visited_map[nx][ny] = true;
          q.push((nx << 16) | ny);
        } else {
          return time;
        }
      }
    }
  }
  return -1;
}

int main() {
  freopen("MeteorShower.in", "r", stdin);
  scanf("%d", &M);
  for (int i = 0; i < M; ++i) {
    scanf("%d%d%d", &hits[i].x, &hits[i].y, &hits[i].t);
  }
  sort(hits, hits + M, compareHit);
  memset(unsafe_map, false, sizeof(unsafe_map));
  memset(destroyed_map, false, sizeof(destroyed_map));
  memset(visited_map, false, sizeof(visited_map));
  for (int i = 0; i < M; ++i) {
    int x = hits[i].x;
    int y = hits[i].y;
    unsafe_map[x][y] = true;
    for (int d = 0; d < 4; ++d) {
      int nx = x + dx[d];
      int ny = y + dy[d];
      if (nx >= 0 && nx <= 301 && ny >= 0 && ny <= 301) {
        unsafe_map[nx][ny] = true;
      }
    }
  }
  int result = goSafeTime();
  printf("%d\n", result);
}
