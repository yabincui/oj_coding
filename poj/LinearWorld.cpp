#include <stdio.h>
#include <string.h>

#include <algorithm>
using namespace std;

int N;
double L, V;

struct Ship {
  int dir;
  double pos;
  char name[251];
} ships[32000];

bool comparePos(const Ship& s1, const Ship& s2) {
  if (s1.pos != s2.pos) {
    return s1.pos > s2.pos ? false : true;
  }
  if (s1.dir != s2.dir) {
    return s1.dir == -1 ? true : false;
  }
  return strcmp(s1.name, s2.name) < 0;
}

double best_time;
char best_name[251];

void getResult() {
  best_time = -1;
  int best_no;
  for (int i = 0; i < N; ++i) {
    double t;
    if (ships[i].dir == -1) {
      t = ships[i].pos / V;
    } else {
      t = (L - ships[i].pos) / V;
    }
    if (best_time == -1 || best_time < t) {
      best_time = t;
      best_no = i;
    }
  }
  if (ships[best_no].dir == -1) {
    for (int i = best_no - 1; i >= 0; --i) {
      if (ships[i].dir == 1) {
        best_no--;
      }
    }
  } else {
    for (int i = best_no + 1; i < N; ++i) {
      if (ships[i].dir == -1) {
        best_no++;
      }
    }
  }
  strcpy(best_name, ships[best_no].name);
}

int main() {
  freopen("LinearWorld.in", "r", stdin);
  while (scanf("%d", &N) == 1 && N != 0) {
    scanf("%lf%lf", &L, &V);
    for (int i = 0; i < N; ++i) {
      char d[2];
      scanf("%s%lf%s", d, &ships[i].pos, ships[i].name);
      ships[i].dir = (d[0] == 'p' || d[0] == 'P') ? 1 : -1;
    }
    sort(ships, ships + N, comparePos);
    getResult();
    printf("%13.2f %s\n", (int)(best_time * 100)/100.0, best_name);
  }
  return 0;
}
