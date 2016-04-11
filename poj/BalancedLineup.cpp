// POJ 3264
#include <stdio.h>

#include <algorithm>
#include <climits>
#include <utility>
using namespace std;

int N, Q;
int s[50000];

pair<int, int> groups[200000];

struct TreeNode {
  int min_value;
  int max_value;
  TreeNode* left;
  TreeNode* right;

  TreeNode() : min_value(INT_MAX), max_value(INT_MIN), left(NULL), right(NULL) {
  }
};

TreeNode* buildTree(int l, int r) {
  if (l >= N) {
    return NULL;
  }
  if (l == r) {
    TreeNode* root = new TreeNode;
    root->min_value = s[l];
    root->max_value = s[l];
    return root;
  }
  int m = (l + r) / 2;
  TreeNode* left = buildTree(l, m);
  TreeNode* right = buildTree(m + 1, r);
  TreeNode* root = new TreeNode;
  root->min_value = min(left == NULL ? INT_MAX : left->min_value,
                        right == NULL ? INT_MAX : right->min_value);
  root->max_value = max(left == NULL ? INT_MIN : left->max_value,
                        right == NULL ? INT_MIN : right->max_value);
  root->left = left;
  root->right = right;
  return root;
}

pair<int, int> findMinMax(TreeNode* root, int l, int r, int start, int end) {
  if (root == NULL || l > end || r < start) {
    return make_pair(INT_MAX, INT_MIN);
  }
  if (l >= start && r <= end) {
    return make_pair(root->min_value, root->max_value);
  }
  int m = (l + r) / 2;
  pair<int, int> t1 = findMinMax(root->left, l, m, start, end);
  pair<int, int> t2 = findMinMax(root->right, m + 1, r, start, end);
  t1.first = min(t1.first, t2.first);
  t1.second = max(t1.second, t2.second);
  return t1;
}

int findMax(TreeNode* root, int l, int r, int start, int end) {
  if (root == NULL || l > end || r < start) {
    return INT_MIN;
  }
  if (l >= start && r <= end) {
    return root->max_value;
  }
  int m = (l + r) / 2;
  return max(findMax(root->left, l, m, start, end),
             findMax(root->right, m + 1, r, start, end));
}

// Use segment tree.
void solve() {
  int p = 1;
  while (p < N) {
    p *= 2;
  }
  TreeNode* root = buildTree(0, p - 1);
  for (int i = 0; i < Q; ++i) {
    int start = groups[i].first - 1;
    int end = groups[i].second - 1;
    pair<int, int> t = findMinMax(root, 0, p - 1, start, end);
    int diff = t.second - t.first;
    printf("%d\n", diff);
  }
}

int main() {
  freopen("BalancedLineup.in", "r", stdin);
  scanf("%d%d", &N, &Q);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &s[i]);
  }
  for (int i = 0; i < Q; ++i) {
    scanf("%d%d", &groups[i].first, &groups[i].second);
  }
  solve();
  return 0;
}
