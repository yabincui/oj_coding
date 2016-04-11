// POJ 3368
#include <stdio.h>

#include <algorithm>
#include <utility>
using namespace std;

int N, Q;
int s[100000];
pair<int, int> queries[100000];

// For i, range[i].first is the leftmost pos having s[pos] = s[i], range[i].second is the
// right most pos having s[pos] = s[i].
pair<int, int> range[100000];

struct TreeNode {
  int max_freq;
  TreeNode* left;
  TreeNode* right;

  TreeNode() : max_freq(0), left(NULL), right(NULL) {
  }
};

TreeNode nodes[300000];
int node_id = 0;

TreeNode* buildTree(int l, int r) {
  if (l >= N) {
    return NULL;
  }
  if (l == r) {
    TreeNode* root = &nodes[node_id++];
    root->max_freq = 1;
    root->left = root->right = NULL;
    return root;
  }
  int m = (l + r) / 2;
  TreeNode* left = buildTree(l, m);
  TreeNode* right = buildTree(m + 1, r);
  TreeNode* root = &nodes[node_id++];
  root->left = left;
  root->right = right;
  root->max_freq = max(left == NULL ? 0 : left->max_freq,
                       right == NULL ? 0 : right->max_freq);
  if (m+1 < N && s[m] == s[m+1]) {
    int start = max(l, range[m].first);
    int end = min(r, range[m].second);
    root->max_freq = max(root->max_freq, end - start + 1);
  }
  return root;
}

int findMaxFreq(TreeNode* root, int l, int r, int start, int end) {
  if (root == NULL || l > end || r < start) {
    return 0;
  }
  if (l >= start && r <= end) {
    return root->max_freq;
  }
  int m = (l + r) / 2;
  if (end <= m) {
    return findMaxFreq(root->left, l, m, start, end);
  }
  if (start > m) {
    return findMaxFreq(root->right, m + 1, r, start, end);
  }
  int max_freq = max(findMaxFreq(root->left, l, m, start, end),
                     findMaxFreq(root->right, m + 1, r, start, end));
  if (m >= start && m + 1 <= end && s[m] == s[m + 1]) {
    int t_start = max(start, range[m].first);
    int t_end = min(end, range[m].second);
    max_freq = max(max_freq, t_end - t_start + 1);
  }
  return max_freq;
}

// Use segment tree.
void solve() {
  int pos = 0;
  range[0].first = 0;
  for (int i = 1; i < N; ++i) {
    if (s[i] != s[i-1]) {
      pos = i;
    }
    range[i].first = pos;
  }
  pos = N - 1;
  range[N-1].second = N - 1;
  for (int i = N - 2; i >= 0; --i) {
    if (s[i] != s[i+1]) {
      pos = i;
    }
    range[i].second = pos;
  }
  int p = 1;
  while (p < N) {
    p *= 2;
  }
  node_id = 0;
  TreeNode* root = buildTree(0, p - 1);
  for (int i = 0; i < Q; ++i) {
    int start = queries[i].first - 1;
    int end = queries[i].second - 1;
    int max_freq = findMaxFreq(root, 0, p - 1, start, end);
    printf("%d\n", max_freq);
  }
}

int main() {
  freopen("FrequentValues.in", "r", stdin);
  while (true) {
    scanf("%d", &N);
    if (N == 0) {
      break;
    }
    scanf("%d", &Q);
    for (int i = 0; i < N; ++i) {
      scanf("%d", &s[i]);
    }
    for (int i = 0; i < Q; ++i) {
      scanf("%d%d", &queries[i].first, &queries[i].second);
    }
    solve();
  }
  return 0;
}
