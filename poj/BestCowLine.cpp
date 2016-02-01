#include <stdio.h>

#include <string>
#include <vector>

using namespace std;

int N;
vector<char> v;

string getBestOrder() {
  int start = 0;
  int end = N - 1;
  string s;
  while (s.size() < N) {
    int comp = 0;
    for (int i = start, j = end; i < j; ++i, --j) {
      if (v[i] < v[j]) {
        comp = -1;
        break;
      } else if (v[i] > v[j]) {
        comp = 1;
        break;
      }
    }
    if (comp <= 0) {
      s.push_back(v[start++]);
    } else {
      s.push_back(v[end--]);
    }
  }
  return s;
}

int main() {
  freopen("BestCowLine.in", "r", stdin);
  scanf("%d", &N);
  char buf[100];
  for (int i = 0; i < N; ++i) {
     scanf("%s", buf);
     v.push_back(buf[0]);
  }
  string result = getBestOrder();
  int cur = 0;
  while (cur < result.size()) {
    printf("%c", result[cur]);
    if (cur % 80 == 79) {
      printf("\n");
    }
    cur++;
  }

  return 0;
}
