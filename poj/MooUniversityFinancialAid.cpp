#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <queue>

using namespace std;

int N, C, F;

struct Cow {
  int score;
  int cost;
} cows[100000];

// frontSum[i] is the minimum cost sum of (N/2) cows before i.
int frontSum[100000];

// backSum[i] is the minimum cost sum of (N/2) cows after i.
int backSum[100000];

bool compareCow(const Cow& c1, const Cow& c2) {
  return c1.score < c2.score;
}

int getMaxMedian() {
  priority_queue<int> q;
  int sum = 0;
  for (int i = 0; i < C; ++i) {
    frontSum[i] = sum;
    sum += cows[i].cost;
    q.push(cows[i].cost);
    if (q.size() > N/2) {
      sum -= q.top();
      q.pop();
    }
  }
  q = priority_queue<int>();
  sum = 0;
  for (int i = C - 1; i >= 0; --i) {
    backSum[i] = sum;
    sum += cows[i].cost;
    q.push(cows[i].cost);
    if (q.size() > N/2) {
      sum -= q.top();
      q.pop();
    }
  }
  int result = -1;
  for (int i = N/2; i < C - N/2; ++i) {
    int cost = frontSum[i] + cows[i].cost + backSum[i];
    if (cost <= F) {
      result = cows[i].score;
    }
  }
  return result;
}

int main() {
  freopen("MooUniversityFinancialAid.in", "r", stdin);
  scanf("%d%d%d", &N, &C, &F);
  for (int i = 0; i < C; ++i) {
    scanf("%d%d", &cows[i].score, &cows[i].cost);
  }
  sort(cows, &cows[C], compareCow);
  int result = getMaxMedian();
  printf("%d\n", result);
  return 0;
}
