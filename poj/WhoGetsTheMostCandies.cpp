#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <vector>
using namespace std;

int N, K;

#define MAX_N 500000

int FactorCount[MAX_N + 1];
int BestPos[MAX_N + 1];

struct Child {
  char name[11];
  int next;
} children[MAX_N];

void init() {
  bool valid[1000];
  memset(valid, true, sizeof(valid));
  vector<int> primes;
  primes.push_back(2);
  for (int i = 3; i < 1000; i += 2) {
    if (valid[i]) {
      primes.push_back(i);
      for (int j = i; j < 1000; j += i) {
        valid[j] = false;
      }
    }
  }

  FactorCount[1] = 1;
  for (int cur = 2; cur <= MAX_N; ++cur) {
    int p = cur;
    for (int i = 0; i < primes.size(); ++i) {
      int t = primes[i];
      if (t > cur) {
        break;
      }
      if (cur % t == 0) {
        p = t;
        break;
      }
    }
    int count = 0;
    int left_value = cur;
    while (left_value % p == 0) {
      count++;
      left_value /= p;
    }
    FactorCount[cur] = FactorCount[left_value] * (count + 1);
  }
  BestPos[1] = 1;
  int best = 1;
  int best_pos = 1;
  for (int i = 2; i <= MAX_N; ++i) {
    int cur = FactorCount[i];
    if (cur > best) {
      best = cur;
      best_pos = i;
    }
    BestPos[i] = best_pos;
  }
}

int BIT[MAX_N + 1];

int moveRight(int a, int step) {
  return ((a - 1) + step) % N + 1;
}

int moveLeft(int a, int step) {
  a--;
  if (a >= step) {
    a -= step;
  } else {
    step -= a;
    a = N - step;
  }
  a++;
  return a;
}

void addBitValue(int i, int value) {
  while (i <= N) {
    BIT[i] += value;
    i += i & -i;
  }
}

int getBitSum(int i) {
  int result = 0;
  while (i != 0) {
    result += BIT[i];
    i -= i & -i; 
  }
  return result;
}

int getBitRangeSum(int from, int to) {
  if (from <= to) {
    return getBitSum(to) - getBitSum(from - 1);
  }
  int all = getBitSum(N);
  int miss = getBitSum(from - 1) - getBitSum(to);
  return all - miss;
}

// mark 1 for items that should be omitted.
int findPlace(int t) {
  memset(BIT, 0, sizeof(BIT));
  int selected;
  int next = K;
  for (int i = 1, leftChildren = N-1; i <= t; ++i, --leftChildren) {
    selected = next;
    //printf("selected = %d\n", selected);
    addBitValue(selected, 1);
    if (leftChildren == 0) {
      break;
    }
    int value = children[selected - 1].next;
    //printf("selected = %d, value = %d\n", selected, value);
    if (value > 0) {
      int step = (value - 1) % leftChildren + 1;
      while (step != 0) {
        int new_pos = moveRight(next, step);
        next = moveRight(next, 1);
        step = getBitRangeSum(next, new_pos);
        next = new_pos;
      }
    } else {
      value = -value;
      int step = (value - 1) % leftChildren + 1;
      while (step != 0) {
        int new_pos = moveLeft(next, step);
        //printf("step = %d, next = %d, new_pos = %d\n", step, next, new_pos);
        next = moveLeft(next, 1);
        step = getBitRangeSum(new_pos, next);
        next = new_pos;
      }
    }
  }
  return selected;
}

// make all items go right.
int findPlace2(int t) {
  memset(BIT, 0, sizeof(BIT));
  int selected;
  int next = K;
  for (int i = 1, leftChildren = N-1; i <= t; ++i, --leftChildren) {
    selected = next;
    addBitValue(selected, 1);
    if (leftChildren == 0) {
      break;
    }
    int value = children[selected - 1].next;
    int step;
    if (value > 0) {
      step = (value - 1) % leftChildren + 1;
    } else {
      value = -value;
      step = leftChildren - (value - 1) % leftChildren;
    }
    while (step != 0) {
      int new_pos = moveRight(next, step);
      next = moveRight(next, 1);
      step = getBitRangeSum(next, new_pos);
      next = new_pos;
    }
  }
  return selected;
}

int64_t BIT0[MAX_N + 2];
int64_t BIT1[MAX_N + 2];

void addBitValue(int64_t BIT[], int i, int64_t value) {
  while (i <= MAX_N + 1) {
    BIT[i] += value;
    i += i & -i;
  }
}

int64_t queryBitSum(int64_t BIT[], int i) {
  int64_t sum = 0;
  //fprintf(stderr, "i = %d\n", i);
  while (i != 0) {
    sum += BIT[i];
    i -= i & -i;
  }
  return sum;
}

void addRangeValue(int l, int r, int64_t value) {
  addBitValue(BIT0, l, -(l - 1) * value);
  addBitValue(BIT1, l, value);
  addBitValue(BIT0, r + 1, r * value);
  addBitValue(BIT1, r + 1, -value);
}

int64_t queryPosValue(int i) {
  if (i == 0) {
    return 0;
  }
  int64_t value0 = queryBitSum(BIT0, i) + queryBitSum(BIT1, i) * i;
  int64_t value1 = queryBitSum(BIT0, i-1) + queryBitSum(BIT1, i - 1) * (i - 1);
  return value0 - value1;
}

// add value t for range [l, r].
// S'(x) = S(x) if x < l
// S'(x) = S(x) + (x - l + 1) * t for l <= x <= r
// S'(x) = S(x) + (r - l + 1) * t for x > r

// S(x) = T0 + T1*x
// at pos l, T0 - (l-1)*t, T1 + t
// at pos r + 1, T0 + r*t, T1 - t

// How to jump to location directly? Give a rank number for each child.
// when remove a child, subtract the rank number of child after it by 1.
// Then it becomes a binary search? I need two BITs to do range subtraction.
int findPlace3(int t) {
  memset(BIT0, 0, sizeof(BIT0));
  memset(BIT1, 0, sizeof(BIT1));
  
  for (int i = 1; i <= N; ++i) {
    addBitValue(BIT0, i, i);
  }
  int selected;
  int next = K;
  for (int i = 1, leftChildren = N - 1; i < t; ++i, leftChildren--) {
    //printf("i = %d, selected = %d\n", i, selected);
    selected = next;
    int curRank = queryPosValue(selected);
    // 1 - leftChildren ranks
    int nextRank;
    int value = children[selected - 1].next;
    if (value > 0) {
      value = (value - 1) % leftChildren;
      if (curRank + value <= leftChildren) {
        nextRank = curRank + value;
      } else {
        nextRank = curRank + value - leftChildren;
      }
    } else {
      value = -value;
      value = (leftChildren - value % leftChildren) % leftChildren;
      if (curRank + value <= leftChildren) {
        nextRank = curRank + value;
      } else {
        nextRank = curRank + value - leftChildren;
      }
    }

    // Sub rank value by one for [selected, N]
    addRangeValue(selected, N, -1);

    // search for the first pos having nextRank.
    int low = 1, high = N;
    while (low + 1 < high) {
      int mid = (low + high) / 2;
      int rank = queryPosValue(mid);
      if (rank < nextRank) {
        low = mid + 1;
      } else if (rank == nextRank) {
        high = mid;
      } else {
        high = mid - 1;
      }
    }
    if (low != high && queryPosValue(low) == nextRank) {
      next = low;
    } else {
      next = high;
    }
  }
  return next;
}

// Make the rank value at pos i by S(i), thun downgrade two dimentional BIT
// to one dimentional BIT.
int findPlace4(int t) {
  memset(BIT0, 0, sizeof(BIT0));
  for (int i = 1; i <= N; ++i) {
    addBitValue(BIT0, i, 1);
  }

  int next = K;
  for (int i = 1, leftChildren = N - 1; i < t; ++i, --leftChildren) {
    int selected = next;
    int curRank = queryBitSum(BIT0, selected);
    int value = children[selected - 1].next;
    int nextRank;
    if (value > 0) {
      value = (value - 1) % leftChildren;
      if (curRank + value <= leftChildren) {
        nextRank = curRank + value;
      } else {
        nextRank = curRank + value - leftChildren;
      }
    } else {
      value = -value;
      value = (leftChildren - value % leftChildren) % leftChildren;
      if (curRank + value <= leftChildren) {
        nextRank = curRank + value;
      } else {
        nextRank = curRank + value - leftChildren;
      }
    }
    addBitValue(BIT0, selected, -1);
    int low = 1, high = N;
    while (low + 1 < high) {
      int mid = (low + high) / 2;
      int rank = queryBitSum(BIT0, mid);
      if (rank < nextRank) {
        low = mid + 1;
      } else if (rank == nextRank) {
        high = mid;
      } else {
        high = mid - 1;
      }
    }
    if (low != high && queryBitSum(BIT0, low) == nextRank) {
      next = low;
    } else {
      next = high;
    }
  }
  return next;
}

int main() {
  freopen("WhoGetsTheMostCandies.in", "r", stdin);
  init(); 
  while (scanf("%d%d", &N, &K) == 2 && N != 0) {
    for (int i = 0; i < N; ++i) {
      scanf("%s%d", children[i].name, &children[i].next);
    }
    int t = BestPos[N];
    int index = findPlace4(t);
    //printf("index = %d, t = %d\n", index, t);
    printf("%s %d\n", children[index-1].name, FactorCount[t]);
  }
  return 0;
}
