#include <stdio.h>
#include <string.h>

#include <utility>
using namespace std;

int N;
char cows[5000];

pair<int, int> getResult() {
  int bestK = -1;
  int bestM = -1;
  for (int k = 1; k <= N; ++k) {
    char s[5000];
    memcpy(s, cows, sizeof(cows));
    int i = 0;
    int flip = 0;
    while (i < N) {
      while (i < N && s[i] == 1) {
        i++;
      }
      if (i + k > N) {
        break;
      }
      for (int j = 0; j < k; ++j) {
        s[i + j] = 1 - s[i + j];
      }
      flip++;
    }
    if (i == N && (bestK == -1 || flip < bestM)) {
      bestK = k;
      bestM = flip;
    }
  }
  return make_pair(bestK, bestM);
}

pair<int, int> getResult2() {
  int bestK = -1;
  int bestM = -1;
  for (int k = 1; k <= N; ++k) {
    char flip_stop[5000];
    memset(flip_stop, 0, sizeof(flip_stop));
    int flip_count = 0;
    int is_flip = 0;
    int i = 0;
    for (i = 0; i < N; ++i) {
      if (flip_stop[i]) {
        is_flip = 1 - is_flip;
      }
      if ((cows[i] ^ is_flip) == 1) {
        continue;
      }
      if (i + k > N) {
        break;
      }
      flip_count++;
      is_flip = 1 - is_flip;
      if (i + k < N) {
        flip_stop[i + k] = 1;
      }
    }
    if (i == N && (bestK == -1 || flip_count < bestM)) {
      bestK = k;
      bestM = flip_count;
    }
  }
  return make_pair(bestK, bestM);
}

int main() {
  freopen("FaceTheRightWay.in", "r", stdin);
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    char c;
    do {
      c = getchar();
    } while (c != 'F' && c != 'B');
    cows[i] = (c == 'F') ? 1 : 0;
  }
  pair<int, int> result = getResult2();
  printf("%d %d\n", result.first, result.second);
  return 0;
}
