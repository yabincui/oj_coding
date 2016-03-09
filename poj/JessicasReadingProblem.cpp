#include <stdio.h>

#include <algorithm>
#include <map>
using namespace std;

int P;
int S[1000000];
map<int, int> id_map;
int id_count;

int getMinPages() {
  int min_len = P;
  id_map.clear();
  int start = 0, end = 0;
  while (end < P) {
    while (end < P && id_map.size() < id_count) {
      id_map[S[end++]]++;
    }
    if (id_map.size() < id_count) {
      break;
    }
    while (start < end && id_map.size() == id_count) {
      if (--id_map[S[start]] == 0) {
        id_map.erase(S[start]);
      }
      start++;
    }
    int len = end - start + 1;
    min_len = min(min_len, len);
  }
  return min_len;
}

int main() {
  freopen("JessicasReadingProblem.in", "r", stdin);
  scanf("%d", &P);
  id_map.clear();
  for (int i = 0; i < P; ++i) {
    scanf("%d", &S[i]);
    id_map[S[i]]++;
  }
  id_count = id_map.size();
  int result = getMinPages();
  printf("%d\n", result);
  return 0;
}
