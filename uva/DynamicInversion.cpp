// UVA 11990
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <vector>
using namespace std;

int N, M;

int s[200000];
int pos[200001];
int remove_s[100000];

int sorted_s[200000];
int tmp_s[200000];

struct SizedTreeEntry {
  int deleted : 1;
  int size : 31;
  int value;
  SizedTreeEntry *left, *right;
};

struct SegmentTreeNode {
  SizedTreeEntry* root;
  vector<SizedTreeEntry> data;
} nodes[1 << 20];

SizedTreeEntry* buildSizedTree(SizedTreeEntry* data, int l, int r) {
  if (l > r) {
    return NULL;
  }
  if (l == r) {
    data[l].left = data[l].right = NULL;
    data[l].size = 1;
    return &data[l];
  }
  int m = (l + r) / 2;
  data[m].left = buildSizedTree(data, l, m - 1);
  data[m].right = buildSizedTree(data, m + 1, r);
  data[m].size = r - l + 1;
  return &data[m];
}

int getCountSmallerThanValue(SizedTreeEntry* root, int value) {
  int result = 0;
  while (root != NULL) {
    //printf("root->value = %d, value = %d\n", root->value, value);
    if (root->value < value) {
      if (root->deleted == 0) {
        //printf("root->value = %d\n", root->value);
        result++;
      }
      if (root->left != NULL) {
        result += root->left->size;
        //printf("add %d\n", root->left->size);
      }
      root = root->right;
    } else {
      root = root->left;
    }
  }
  return result;
}

int getCountBiggerThanValue(SizedTreeEntry* root, int value) {
  int result = 0;
  while (root != NULL) {
    if (root->value < value) {
      root = root->right;
    } else {
      if (root->deleted == 0) {
        result++;
      }
      if (root->right != NULL) {
        result += root->right->size;
      }
      root = root->left;
    }
  }
  return result;
}

void removeValueFromTree(SizedTreeEntry* root, int value) {
  while (root != NULL) {
    root->size--;
    if (root->value == value) {
      root->deleted = 1;
      break;
    } else if (root->value > value) {
      root = root->left;
    } else {
      root = root->right;
    }
  }
}

void merge(int* s, int l, int m, int r) {
  int i = l;
  int j = m + 1;
  int k = 0;
  while (i <= m && j <= r) {
    if (s[i] < s[j]) {
      tmp_s[k++] = s[i++];
    } else {
      tmp_s[k++] = s[j++];
    }
  }
  while (i <= m) {
    tmp_s[k++] = s[i++];
  }
  while (j <= r) {
    tmp_s[k++] = s[j++];
  }
  memcpy(s + l, tmp_s, (r - l + 1) * sizeof(int));
}

void buildSegmentTree(int root, int l, int r) {
  if (l >= N) {
    return;
  }
  if (l == r) {
    nodes[root].data.resize(1);
    SizedTreeEntry* entry = &nodes[root].data[0];
    entry->deleted = 0;
    entry->left = entry->right = NULL;
    entry->size = 1;
    entry->value = s[l];
    nodes[root].root = entry;
    sorted_s[l] = s[l];
    return;
  }
  int m = (l + r) / 2;
  int left = root * 2 + 1;
  int right = root * 2 + 2;
  buildSegmentTree(left, l, m);
  buildSegmentTree(right, m + 1, r);
  int start = l;
  int end = min(r, N - 1);
  //printf("start = %d, end = %d\n", start, end);
  if (m + 1 < N) {
    //printf("m = %d, merge\n", m);
    merge(sorted_s, l, m, end);
  }
  vector<SizedTreeEntry>& data = nodes[root].data;
  data.resize(end - start + 1);
  for (int i = 0, j = start; j <= end; ++i, ++j) {
    data[i].deleted = 0;
    data[i].value = sorted_s[j];
  }
  nodes[root].root = buildSizedTree(data.data(), 0, end - start);
  //printf("nodes[root].root->value = %d\n", nodes[root].root->value);
}

int findReverseCount(int root, int l, int r, int pos, int value) {
  if (l >= N) {
    return 0;
  }
  //printf("l = %d, r = %d, pos = %d, value = %d\n", l, r, pos, value);
  SizedTreeEntry* entry = nodes[root].root;
  if (l == r) {
    if (entry->deleted == 0) {
      if (l < pos && entry->value > value) {
        //printf("t1\n");
        return 1;
      }
      if (l > pos && entry->value < value) {
        //printf("t2\n");
        return 1;
      }
    }
    return 0;
  }
  if (l > pos) {
    int count = getCountSmallerThanValue(entry, value);
    //printf("t3 count = %d\n", count);
    return count;
  }
  if (r < pos) {
    int count = getCountBiggerThanValue(entry, value);
    //printf("t4 count = %d\n", count);
    return count;
  }
  int m = (l + r) / 2;
  return findReverseCount(root * 2 + 1, l, m, pos, value) +
          findReverseCount(root * 2 + 2, m + 1, r, pos, value);
}

void removeValue(int root, int l, int r, int pos, int value) {
  while (true) {
    SizedTreeEntry* entry = nodes[root].root;
    if (l == r) {
      entry->deleted = 1;
      break;
    }
    int m = (l + r) / 2;
    removeValueFromTree(entry, value);
    if (m >= pos) {
      root = root * 2 + 1;
      r = m;
    } else {
      root = root * 2 + 2;
      l = m + 1;
    }
  }
}

void solve() {
  for (int i = 0; i < N; ++i) {
    int t = s[i];
    pos[t] = i;
  }
  int p = 1;
  while (p < N) {
    p *= 2;
  }
  buildSegmentTree(0, 0, p - 1);
  int64_t reverse_sum = 0;
  for (int i = 0; i < N; ++i) {
    int value = s[i];
    int t = pos[value];
    int count = findReverseCount(0, 0, p - 1, t, value);
    //printf("reverse_count for %d at %d is %d\n", value, t, count);
    reverse_sum += count;
  }
  //printf("reverse_sum = %lld\n", reverse_sum);
  reverse_sum /= 2;
  for (int i = 0; i < M; ++i) {
    printf("%lld\n", reverse_sum);
    if (reverse_sum < 0) {
      printf("n = %d, m = %d\n", N, M);
      exit(1);
    }
    int value = remove_s[i];
    int t = pos[value];
    int count = findReverseCount(0, 0, p - 1, t, value);
    reverse_sum -= count;
    removeValue(0, 0, p - 1, t, value);
  }
}

int main() {
  freopen("DynamicInversion.in", "r", stdin);
  while (scanf("%d%d", &N, &M) == 2 && N != 0) {
    for (int i = 0; i < N; ++i) {
      scanf("%d", &s[i]);
    }
    for (int i = 0; i < M; ++i) {
      scanf("%d", &remove_s[i]);
    }
    solve();
  }
  return 0;
}
