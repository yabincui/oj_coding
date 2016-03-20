#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <climits>
#include <cstdlib>
using namespace std;

struct Cow {
  int pos;
  int vol;
} cows[20000];

int N;

void solve() {
  int64_t res = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      res += abs(cows[i].pos - cows[j].pos) * max(cows[i].vol, cows[j].vol);
    }
  }
  printf("%lld\n", res);
}

struct Node {
  int min_vol;
  int max_vol;
  int count;
  int min_pos;
  int max_pos;
  int64_t pos_sum;
  Node *lplv, *lpmv, *mplv, *mpmv;

  Node() {
    min_vol = min_pos = INT_MAX;
    max_vol = max_pos = INT_MIN;
    count = 0;
    pos_sum = 0;
    lplv = lpmv = mplv = mpmv = NULL;
  }

  Node(int vol, int pos) {
    min_vol = max_vol = vol;
    count = 1;
    min_pos = max_pos = pos;
    pos_sum = pos;
  }
};

#define MAX_VOL 20000
#define MAX_POS 20000

int node_count = 0;

Node* insertNode(Node* root, int min_vol, int max_vol, int min_pos, int max_pos, int target_pos,
                 int target_vol) {
  if (min_vol == max_vol && min_pos == max_pos) {
    if (min_vol == target_vol && min_pos == target_pos) {
      root = new Node(target_vol, target_pos);
      //printf("node_count = %d\n", ++node_count);
      return root;
    }
  }
  if (root == NULL) {
    root = new Node;
    //printf("node_count = %d\n", ++node_count);
  }
  int mid_vol = (min_vol + max_vol) / 2;
  int mid_pos = (min_pos + max_pos) / 2;
  if (target_pos <= mid_pos && target_vol <= mid_vol) {
    root->lplv = insertNode(root->lplv, min_vol, mid_vol, min_pos, mid_pos, target_pos, target_vol);
  } else if (target_pos > mid_pos && target_vol <= mid_vol) {
    root->mplv = insertNode(root->mplv, min_vol, mid_vol, mid_pos + 1, max_pos, target_pos, target_vol);
  } else if (target_pos <= mid_pos && target_vol > mid_vol) {
    root->lpmv = insertNode(root->lpmv, mid_vol + 1, max_vol, min_pos, mid_pos, target_pos, target_vol);
  } else {
    root->mpmv = insertNode(root->mpmv, mid_vol + 1, max_vol, mid_pos + 1, max_pos, target_pos, target_vol);
  }
  root->min_vol = min(root->min_vol, target_vol);
  root->max_vol = max(root->max_vol, target_vol);
  root->count++;
  root->min_pos = min(root->min_pos, target_pos);
  root->max_pos = max(root->max_pos, target_pos);
  root->pos_sum += target_pos;
  return root;
}

int query_count;

int64_t querySumLessVol(Node* root, int target_pos, int target_vol) {
  if (root == NULL || root->min_vol >= target_vol) {
    return 0;
  }
  query_count++;
  //printf("root pos[%d-%d], vol[%d-%d], count %d, target_pos %d, target_vol %d\n",
  //       root->min_pos, root->max_pos, root->min_vol, root->max_vol, root->count,
  //       target_pos, target_vol);
  if (root->max_vol < target_vol) {
    if (root->max_pos <= target_pos) {
      return ((int64_t)target_pos * root->count - root->pos_sum) * target_vol;
    }
    if (root->min_pos >= target_pos) {
      return (root->pos_sum - (int64_t)target_pos * root->count) * target_vol;
    }
  }
  int64_t res = 0;
  res += querySumLessVol(root->lplv, target_pos, target_vol);
  res += querySumLessVol(root->lpmv, target_pos, target_vol);
  res += querySumLessVol(root->mplv, target_pos, target_vol);
  res += querySumLessVol(root->mpmv, target_pos, target_vol);
  return res;
}

int64_t querySumEqualVolLessPos(Node* root, int target_pos, int target_vol) {
  if (root == NULL || root->min_vol > target_vol || root->max_vol < target_vol ||
      root->min_pos >= target_pos) {
    return 0;
  }
  if (root->min_vol == root->max_vol && root->min_vol == target_vol && root->max_pos < target_pos) {
    return ((int64_t)target_pos * root->count - root->pos_sum) * target_vol;
  }
  int64_t res = 0;
  res += querySumEqualVolLessPos(root->lplv, target_pos, target_vol);
  res += querySumEqualVolLessPos(root->lpmv, target_pos, target_vol);
  res += querySumEqualVolLessPos(root->mplv, target_pos, target_vol);
  res += querySumEqualVolLessPos(root->mpmv, target_pos, target_vol);
  return res;
}

// Use 2 dimentional segment tree. Still timeout, seems because it needs more than O(logN) to
// access a 2 dimentional range.
void solve2() {
  Node* root = NULL;
  //printf("start insert Node\n");
  for (int i = 0; i < N; ++i) {
    root = insertNode(root, 1, MAX_VOL, 1, MAX_POS, cows[i].pos, cows[i].vol);
  }
  int64_t res = 0;
  for (int i = 0; i < N; ++i) {
    query_count = 0;
    res += querySumLessVol(root, cows[i].pos, cows[i].vol);
    //printf("query_count for %d is %d\n", i, query_count);
    //exit(0);
    res += querySumEqualVolLessPos(root, cows[i].pos, cows[i].vol);
  }
  printf("%lld\n", res);
}

bool compareVol(const Cow& c1, const Cow& c2) {
  return c1.vol < c2.vol;
}

Node* insertNode(Node* root, int min_pos, int max_pos, int target_pos) {
  if (min_pos == max_pos) {
    if (min_pos == target_pos) {
      return new Node(0, target_pos);
    }
  }
  if (min_pos > target_pos || max_pos < target_pos) {
    return root;
  }
  int mid_pos = (min_pos + max_pos) / 2;
  if (root == NULL) {
    root = new Node;
  }
  root->lplv = insertNode(root->lplv, min_pos, mid_pos, target_pos);
  root->mplv = insertNode(root->mplv, mid_pos + 1, max_pos, target_pos);
  root->min_pos = min(root->min_pos, target_pos);
  root->max_pos = max(root->max_pos, target_pos);
  root->count++;
  root->pos_sum += target_pos;
  return root;
}

int64_t querySum(Node* root, int target_pos) {
  if (root == NULL) {
    return 0;
  }
  if (root->max_pos <= target_pos) {
    return (int64_t)target_pos * root->count - root->pos_sum;
  }
  if (root->min_pos >= target_pos) {
    return root->pos_sum - (int64_t)target_pos * root->count;
  }
  int64_t res = 0;
  res += querySum(root->lplv, target_pos);
  res += querySum(root->mplv, target_pos);
  return res;
}

// Insert cows into the segment tree by volume order, so we only need one dimentional now,
// and access time can be limited to O(logN).
void solve3() {
  sort(cows, cows + N, compareVol);
  Node* root = NULL;
  int64_t res = 0;
  for (int i = 0; i < N; ++i) {
    res += querySum(root, cows[i].pos) * cows[i].vol;
    root = insertNode(root, 1, MAX_POS, cows[i].pos);
  }
  printf("%lld\n", res);
}

int64_t cow_positions[20001];
int64_t cow_position_nums[20001];

int64_t getSum(int64_t s[], int i) {
  int64_t res = 0;
  while (i != 0) {
    res += s[i];
    i -= i & -i;
  }
  return res;
}

void insertValue(int64_t s[], int i, int64_t value) {
  while (i <= MAX_POS) {
    s[i] += value;
    i += i & -i;
  }
}

// Use binary index tree.
void solve4() {
  sort(cows, cows + N, compareVol);
  memset(cow_positions, 0, sizeof(cow_positions));
  int64_t pos_sum = 0;
  int64_t res = 0;
  for (int i = 0; i < N; ++i) {
    int64_t prev_pos_num = getSum(cow_position_nums, cows[i].pos - 1);
    int64_t prev_pos_sum = getSum(cow_positions, cows[i].pos - 1);
    int64_t post_pos_num = i - prev_pos_num;
    int64_t post_pos_sum = pos_sum - prev_pos_sum;
    res += (prev_pos_num * (int64_t)cows[i].pos - prev_pos_sum) * cows[i].vol;
    res += (post_pos_sum - post_pos_num * (int64_t)cows[i].pos) * cows[i].vol;
    pos_sum += cows[i].pos;
    insertValue(cow_positions, cows[i].pos, cows[i].pos);
    insertValue(cow_position_nums, cows[i].pos, 1);
  }
  printf("%lld\n", res);
}

int main() {
  freopen("MooFest.in", "r", stdin);
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    scanf("%d%d", &cows[i].vol, &cows[i].pos);
  }
  //solve3();
  solve4();
  return 0;
}
