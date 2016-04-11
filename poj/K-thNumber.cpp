// POJ 2104
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <climits>
#include <cmath>
#include <vector>
using namespace std;

int n, m;
int s[100000];
int sorted_s[100000];

struct Question {
  int start;
  int end;
  int kth;
} questions[5000];

struct Segment {
  int data[1000];
  int count;
};

Segment segments[1000];
Segment start_segment;
Segment end_segment;

int findKth(int k, int start_seg, int end_seg) {
  int low = 0;
  int high = n - 1;
  while (low < high) {
    int mid = (low + high) / 2;
    int target = sorted_s[mid];
    int less_equal_count = 0;
    for (int i = start_seg; i <= end_seg; ++i) {
      int* p = upper_bound(segments[i].data, segments[i].data + segments[i].count, target);
      less_equal_count += p - segments[i].data;
    }
    if (start_segment.count > 0) {
      int* p = upper_bound(start_segment.data, start_segment.data + start_segment.count, target);
      less_equal_count += p - start_segment.data;
    }
    if (end_segment.count > 0) {
      int* p = upper_bound(end_segment.data, end_segment.data + end_segment.count, target);
      less_equal_count += p - end_segment.data;
    }
    if (less_equal_count >= k) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }
  return sorted_s[low];
}

void solve() {
  memcpy(sorted_s, s, sizeof(s));
  sort(sorted_s, sorted_s + n);
  int size_per_segment = (int)sqrt(n);
  size_per_segment = 1000;
  int segment_count = n / size_per_segment;
  if (n % size_per_segment != 0) {
    segment_count++;
  }
  for (int i = 0, k = 0; i < segment_count; ++i) {
    int count = std::min(size_per_segment, n - k);
    segments[i].count = count;
    for (int j = 0; j < count; ++j) {
      segments[i].data[j] = s[k++];
    }
    sort(segments[i].data, segments[i].data + count);
  }

  for (int i = 0; i < m; ++i) {
    int start = questions[i].start - 1;
    int end = questions[i].end - 1;
    int start_seg = start / size_per_segment;
    int end_seg = end / size_per_segment;
    int start1;
    if (start % size_per_segment == 0) {
      //printf("a0\n");
      start_segment.count = 0;
      start1 = start;
    } else {
      //printf("a1\n");
      start1 = std::min((start / size_per_segment + 1) * size_per_segment, end + 1);
      int k = 0;
      for (int j = start; j < start1; ++j) {
        start_segment.data[k++] = s[j];
      }
      start_segment.count = k;
      //printf("start_segment.count = %d\n", k);
      sort(start_segment.data, start_segment.data + k);
    }
    int start1_seg = start1 / size_per_segment;
    int end1;
    int end1_seg;
    if (end >= (start1_seg + 1) * size_per_segment) {
      end1 = end - end % size_per_segment - 1;
      end1_seg = end1 / size_per_segment;
    } else {
      end1 = start1 - 1;
      end1_seg = start1_seg - 1;
    }
    int k = 0;
    for (int j = end1 + 1; j <= end; ++j) {
      end_segment.data[k++] = s[j];
    }
    sort(end_segment.data, end_segment.data + k);
    end_segment.count = k;
    int value = findKth(questions[i].kth, start1_seg, end1_seg);
    /*
    printf("t1\n");
    printf("start1_seg = %d, end1_seg = %d, start1 = %d, end1 = %d, start = %d, end = %d\n",
            start1_seg, end1_seg, start1, end1,
            start, end);
    printf("start_seg:");
    for (int j = 0; j < start_segment.count; ++j) {
      printf(" %d", start_segment.data[j]);
    }
    printf("\n");
    printf("end_seg:");
    for (int j = 0; j < end_segment.count; ++j) {
      printf(" %d", end_segment.data[j]);
    }
    printf("\n");
    */
    printf("%d\n", value);
  }
}

struct TreeNode {
  vector<int> sorted_data;
  TreeNode *left, *right;

  TreeNode() : left(NULL), right(NULL) {
  }
};

TreeNode* buildTree(int l, int r) {
  //printf("buildTree(%d, %d)\n", l, r);
  if (l > r || l >= n) {
    return NULL;
  }
  if (l == r) {
    TreeNode* root = new TreeNode;
    root->sorted_data.push_back(s[l]);
    return root;
  }
  int mid = (l + r) / 2;
  TreeNode* left = buildTree(l, mid);
  TreeNode* right = buildTree(mid + 1, r);
  TreeNode* root = new TreeNode;
  root->left = left;
  root->right = right;
  int j = 0, k = 0;
  int left_size = (left == NULL) ? 0 : left->sorted_data.size();
  int right_size = (right == NULL) ? 0 : right->sorted_data.size();
  while (j != left_size && k != right_size) {
    if (left->sorted_data[j] <= right->sorted_data[k]) {
      root->sorted_data.push_back(left->sorted_data[j++]);
    } else {
      root->sorted_data.push_back(right->sorted_data[k++]);
    }
  }
  while (j != left_size) {
    root->sorted_data.push_back(left->sorted_data[j++]);
  }
  while (k != right_size) {
    root->sorted_data.push_back(right->sorted_data[k++]);
  }
  return root;
}

int findLessEqualCount(TreeNode* root, int l, int r, int start, int end, int target) {
  if (root == NULL || l > end || r < start) {
    return 0;
  }
  if (l >= start && r <= end) {
    return upper_bound(root->sorted_data.begin(), root->sorted_data.end(), target) -
              root->sorted_data.begin();
  }
  int m = (l + r) / 2;
  int result = 0;
  result += findLessEqualCount(root->left, l, m, start, end, target);
  result += findLessEqualCount(root->right, m + 1, r, start, end, target);
  return result;
}

// Use segment tree.
void solve2() {
  int p = 1;
  while (p < n) {
    p *= 2;
  }
  TreeNode* root = buildTree(0, p - 1);
  //printf("buildTree, root = %p\n", root);
  for (int i = 0; i < m; ++i) {
    int low = 0;
    int high = n - 1;
    int start = questions[i].start - 1;
    int end = questions[i].end - 1;
    int k = questions[i].kth;
    while (low < high) {
      int mid = (low + high) / 2;
      int target = root->sorted_data[mid];
      int less_equal_count = findLessEqualCount(root, 0, p - 1, start, end, target);
      if (less_equal_count >= k) {
        high = mid;
      } else {
        low = mid + 1;
      }
    }
    printf("%d\n", root->sorted_data[low]);
  }
}

int main() {
  freopen("K-thNumber.in", "r", stdin);
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &s[i]);
  }
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", &questions[i].start, &questions[i].end, &questions[i].kth);
  }
  solve();
  return 0;
}
