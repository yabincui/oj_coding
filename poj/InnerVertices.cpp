#include <stdio.h>
#include <string.h>
#include <limits.h>

#include <algorithm>
#include <map>
#include <vector>
using namespace std;

int N;

struct Pos {
  int col, row;
} positions[100000];

struct Row {
  int min_col, max_col;
  
  Row(int min_col = INT_MAX, int max_col = INT_MIN) : min_col(min_col), max_col(max_col) {
  }
};

struct Col {
  int min_row, max_row;

  Col(int min_row = INT_MAX, int max_row = INT_MIN) : min_row(min_row), max_row(max_row) {
  }
};

// leaf_size = power_of_2_no_less_than(100000) = 1 << 17
// 2 * (leaf_size) = 1 << 18
int segment_tree[1 << 18];

void segmentTreeAddValue(int root, int left, int right, int id, int value) {
  if (left == right) {
    if (left == id) {
      segment_tree[root] += value;
    }
    return;
  }
  if (left <= id && right >= id) {
    segment_tree[root] += value;
    int mid = (left + right) / 2;
    segmentTreeAddValue(root * 2 + 1, left, mid, id, value);
    segmentTreeAddValue(root * 2 + 2, mid + 1, right, id, value);
  }
}

int segmentTreeQuery(int root, int left, int right, int min_id, int max_id) {
  if (left > max_id || right < min_id) {
    return 0;
  }
  if (left >= min_id && right <= max_id) {
    return segment_tree[root];
  }
  int mid = (left + right) / 2;
  int result = 0;
  result += segmentTreeQuery(root * 2 + 1, left, mid, min_id, max_id);
  result += segmentTreeQuery(root * 2 + 2, mid + 1, right, min_id, max_id);
  return result;
}

// O(nlogn) use segment tree, still timeout.
void solve() {
  // For each row, the [min_col, max_col] range.
  map<int, Row> row_map;
  for (int i = 0; i < N; ++i) {
    Row& tmp = row_map[positions[i].row];
    tmp.min_col = min(tmp.min_col, positions[i].col);
    tmp.max_col = max(tmp.max_col, positions[i].col);
  }
  // We want to go through each column from left to right, some rows are added
  // as they have intersection with current column, and some rows are removed
  // as they have no intersection with current column. So here calculate which
  // rows we should remove/add at each column.
  map<int, vector<int> > add_rows_at_col_map;
  map<int, vector<int> > del_rows_at_col_map;
  for (std::map<int, Row>::iterator it = row_map.begin(); it != row_map.end(); ++it) {
    add_rows_at_col_map[it->second.min_col].push_back(it->first);
    del_rows_at_col_map[it->second.max_col].push_back(it->first);
  }
  // For each col, the [min_row, max_row] range.
  map<int, Col> col_map;
  for (int i = 0; i < N; ++i) {
    Col& tmp = col_map[positions[i].col];
    tmp.min_row = min(tmp.min_row, positions[i].row);
    tmp.max_row = max(tmp.max_row, positions[i].row);
  }
  // Convert to row to sorted row id.
  vector<int> rows;
  for (int i = 0; i < N; ++i) {
    rows.push_back(positions[i].row);
  }
  sort(rows.begin(), rows.end());
  map<int, int> row_to_id_map;
  int row_count = 0;
  for (int i = 0; i < rows.size(); ++i) {
    if (i == 0 || rows[i] != rows[i-1]) {
      row_to_id_map[rows[i]] = row_count++;
    }
  }
  
  memset(segment_tree, 0, sizeof(segment_tree));

  long long result = 0;
  map<int, Col>::iterator it;
  // Go through columns from left to right.
  for (it = col_map.begin(); it != col_map.end(); ++it) {
    int col = it->first;
    // Add rows having intersection with current column.
    map<int, vector<int> >::iterator add_it = add_rows_at_col_map.find(col);
    if (add_it != add_rows_at_col_map.end()) {
      vector<int>& v = add_it->second;
      for (int i = 0; i < v.size(); ++i) {
        int id = row_to_id_map[v[i]];
        //printf("add row %d\n", v[i]);
        segmentTreeAddValue(0, 0, row_count - 1, id, 1);
      }
    }
    int min_row = it->second.min_row;
    int max_row = it->second.max_row;
    int min_id = row_to_id_map[min_row];
    int max_id = row_to_id_map[max_row];
    int sum = segmentTreeQuery(0, 0, row_count - 1, min_id, max_id);
    result += sum;
    //printf("for column %d, sum = %d, result = %lld\n", col, sum, result);
    // Remove rows having no intersection with current column.
    map<int, vector<int> >::iterator del_it = del_rows_at_col_map.find(col);
    if (del_it != del_rows_at_col_map.end()) {
      vector<int>& v = del_it->second;
      for (int i = 0; i < v.size(); ++i) {
        int id = row_to_id_map[v[i]];
        //printf("rm row %d\n", v[i]);
        segmentTreeAddValue(0, 0, row_count - 1, id, -1);
      }
    }
  }
  printf("%lld\n", result);
}

int row_count;
int col_count;

void compressPositions() {
  vector<int> v(N);
  for (int i = 0; i < N; ++i) {
    v[i] = positions[i].col;
  }
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
  /*
  for (int i = 0; i < v.size(); ++i) {
    printf("v[%d] = %d\n", i, v[i]);
  }
  */
  col_count = v.size();
  for (int i = 0; i < N; ++i) {
    positions[i].col = lower_bound(v.begin(), v.end(), positions[i].col) - v.begin();
  }
  v.resize(N);
  for (int i = 0; i < N; ++i) {
    v[i] = positions[i].row;
  }
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
  for (int i = 0; i < N; ++i) {
    positions[i].row = lower_bound(v.begin(), v.end(), positions[i].row) - v.begin();
  }
  row_count = v.size();
  /*
  for (int i = 0; i < N; ++i) {
    fprintf(stderr, "p[%d] r %d, c %d\n", i, positions[i].row, positions[i].col);
  }
  */
}

Row row_map[100000];
Col col_map[100000];

int BIT[1 << 18];
int BIT_N;

void addBITValue(int i, int value) {
  //fprintf(stderr, "addBITValue\n");
  i++;
  while (i <= BIT_N) {
    BIT[i] += value;
    i += i & -i;
  }
  //fprintf(stderr, "addBITValue end\n");
}

int queryBIT(int i) {
  //fprintf(stderr, "queryBIT, i = %d\n", i);
  i++;
  int result = 0;
  while (i != 0) {
    result += BIT[i];
    i -= i & -i;
  }
  //fprintf(stderr, "queryBIT end\n");
  return result;
}

// First compress Positions, then make map operations into O(1) operations.
void solve2() {
  compressPositions();
  //fprintf(stderr, "after compress\n");
  for (int i = 0; i < N; ++i) {
    Row& tmp = row_map[positions[i].row];
    tmp.min_col = min(tmp.min_col, positions[i].col);
    tmp.max_col = max(tmp.max_col, positions[i].col);
  }
  for (int i = 0; i < N; ++i) {
    Col& tmp = col_map[positions[i].col];
    tmp.min_row = min(tmp.min_row, positions[i].row);
    tmp.max_row = max(tmp.max_row, positions[i].row);
  }
  // pair<col, row>
  vector<pair<int, int> > add_rows_at_col;
  vector<pair<int, int> > del_rows_at_col;
  for (int i = 0; i < row_count; ++i) {
    add_rows_at_col.push_back(make_pair(row_map[i].min_col, i));
    del_rows_at_col.push_back(make_pair(row_map[i].max_col, i));
  }
  sort(add_rows_at_col.begin(), add_rows_at_col.end());
  sort(del_rows_at_col.begin(), del_rows_at_col.end());
  //fprintf(stderr, "before loop\n");
  int add_index = 0;
  int del_index = 0;
  long long result = 0;

  BIT_N = row_count;
  for (int i = 0; i < col_count; ++i) {
    while (add_index < add_rows_at_col.size() && add_rows_at_col[add_index].first <= i) {
      addBITValue(add_rows_at_col[add_index].second, 1);
      //printf("add row %d\n", add_rows_at_col[add_index].second);
      add_index++;
    }

    //fprintf(stderr, "col %d, min_row %d, max_row %d\n", i, col_map[i].min_row, col_map[i].max_row);
    int value = queryBIT(col_map[i].max_row);
    //printf("query %d = %d\n", col_map[i].max_row, value);
    if (col_map[i].min_row > 0) {
      int value2 = queryBIT(col_map[i].min_row - 1);
      //printf("query %d = %d\n", col_map[i].min_row - 1, value2);
      value -= value2;
    }
    result += value;
    //printf("after col %d, value = %d, result = %lld\n", i, value, result);

    while (del_index < del_rows_at_col.size() && del_rows_at_col[del_index].first <= i) {
      addBITValue(del_rows_at_col[del_index].second, -1);
      //printf("rm row %d\n", del_rows_at_col[del_index].second);
      del_index++;
    }
  }
  printf("%lld\n", result);
}

int main() {
  freopen("InnerVertices.in", "r", stdin);
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    scanf("%d%d", &positions[i].col, &positions[i].row);
  }
  solve2();
  return 0;
}
