// POJ 1795
#include <stdio.h>
#include <string.h>

#include <algorithm>
using namespace std;

int N;
char s[15][101];
int s_len[15];
char* dp[1 << 15];
int dp_len[1 << 15];
char buffer[2][6500 * 1501]; // C(15, 8) * 1500.
char buffer0[1] = "";

int kmp_prev[1500];

int getCommon(const char* s, const char* t) {
  // preprocessing. kmp_prev[i] shows the biggest value j that s[j] is the prefix of s[i].
  int j = -1;
  kmp_prev[0] = -1;
  for (int i = 1; t[i] != '\0'; ++i) {
    while (j != -1 && t[j + 1] != t[i]) {
      j = kmp_prev[j];
    }
    if (t[j + 1] == t[i]) {
      j++;
    }
    kmp_prev[i] = j;
    //printf("kmp_prev[%d] = %d\n", i, j);
  }

  j = -1;
  for (int i = 0; s[i] != '\0'; ++i) {
    while (j != -1 && t[j + 1] != s[i]) {
      j = kmp_prev[j];
    }
    if (t[j + 1] == s[i]) {
      j++;
      if (t[j + 1] == '\0') {
        return j + 1;
      }
    }
  }
  return j + 1;
}

int permute[1 << 15];
int C[16][16];

bool comparePermute(int a, int b) {
  int bits_a = 0;
  while (a != 0) {
    a &= a - 1;
    bits_a++;
  }
  int bits_b = 0;
  while (b != 0) {
    b &= b - 1;
    bits_b++;
  }
  return bits_a < bits_b;
}

void init() {
  for (int i = 1; i < (1 << 15); ++i) {
    permute[i - 1] = i;
  }
  sort(permute, permute + (1 << 15) - 2, comparePermute);
  C[0][0] = 1;
  for (int i = 1; i <= 15; ++i) {
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      C[i][j] = C[i-1][j] + C[i-1][j-1];
    }
  }
  dp[0] = buffer0;
}
/*
string solve() {
  for (int i = 1; i < (1 << N); ++i) {
    string best;
    for (int j = 0; j < N; ++j) {
      if ((i & (1 << j)) == 0) {
        continue;
      }
      int prev = i & ~(1 << j);
      int common = getCommon(dp[prev].c_str(), s[j]);
      //printf("getCommon(%s, %s) = %d\n", dp[prev].c_str(), s[j], common);
      string t = dp[prev] + (s[j] + common);
      if (best.empty() || best.size() > t.size() || (best.size() == t.size() && best > t)) {
        best = t;
      }
      for (int k = j + 1; k < N; ++k) {
        if (i & (1 << k)) {
          dp[prev & ~(1 << k)].clear();
        }
      }
    }
    dp[i] = best;
  }
  return dp[(1 << N) - 1];
}
*/

char best[1501];

int compareSpecial(char* s, char* t, int t_len, char* t2) {
  int res = memcmp(s, t, t_len);
  if (res != 0) {
    return res;
  }
  return strcmp(s + t_len, t2);
}

char* solve2() {
  for (int i = 0; i < N; ++i) {
    s_len[i] = strlen(s[i]);
  }
  int valid_mask = (1 << N) - 1;
  for (int i = 0; i < N; ++i) {
    dp[1 << i] = s[i];
    dp_len[1 << i] = s_len[i];
  }
  char* cur_buffer = buffer[0];
  char* next_buffer = buffer[1];
  int i = C[15][1];
  for (int level = 2; level <= N; ++level) {
    int ni = i + C[15][level];
    char* p = next_buffer;
    for (; i < ni; ++i) {
      //printf("i = %d, valid_mask = %x\n", i, valid_mask);
      int permute_i = permute[i];
      if (permute_i & ~valid_mask) {
        continue;
      }
      best[0] = '\0';
      int best_len = 1600;
      for (int j = 0; j < N; ++j) {
        if ((permute_i & (1 << j)) == 0) {
          continue;
        }
        int prev = permute_i & ~(1 << j);
        int common = getCommon(dp[prev], s[j]);
        int len = dp_len[prev] + s_len[j] - common;
        if (best_len > len || (best_len == len && compareSpecial(best, dp[prev], dp_len[prev],
                s[j] + common) > 0)) {
          memcpy(best, dp[prev], dp_len[prev]);
          strcpy(best + dp_len[prev], s[j] + common);
          best_len = len;
        }
      }
      dp[permute_i] = p;
      dp_len[permute_i] = best_len;
      strcpy(p, best);
      //printf("dp[%d] = %s\n", permute_i, dp[permute_i]);
      p += best_len + 1;
    }
    swap(cur_buffer, next_buffer);
  }
  return dp[(1 << N) - 1];
}

int common_table[15][15];

void buildCommonTable() {
  for (int i = 0; i < N; ++i) {
    s_len[i] = strlen(s[i]);
  }
  bool valid[15];
  memset(valid, true, sizeof(valid));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (i == j) {
        continue;
      }
      int common = getCommon(s[i], s[j]);
      if (common == s_len[i] && common == s_len[j]) {
        valid[max(i, j)] = false;
      } else if (common == s_len[j]) {
        valid[j] = false;
      }
      common_table[i][j] = common;
    }
  }
  int j = 0;
  for (int i = 0; i < N; ++i) {
    if (valid[i]) {
      strcpy(s[j], s[i]);
      for (int k = 0; k < N; ++k) {
        common_table[j][k] = common_table[i][k];
        common_table[k][j] = common_table[k][i];
      }
      j++;
    }
  }
  N = j;
}

// dp2[i][j] is the cost to get string union of i, using s[j] as the start.
int dp2[1 << 15][15];
int cmp_table[15][15];

char* solve3() {
  buildCommonTable();
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      int res = strcmp(s[i], s[j]);
      cmp_table[i][j] = res;
      cmp_table[j][i] = -res;
    }
  }
  memset(dp2, -1, sizeof(dp2));
  for (int i = 0; i < N; ++i) {
    dp2[1 << i][i] = s_len[i];
    //printf("dp2[%d][%d] = %d\n", 1 << i, i, dp2[1 << i][i]);
  }
  //printf("next\n");
  for (int i = 1; i < (1 << N); ++i) {
    for (int bit0 = 0; bit0 < N; ++bit0) {
      if ((i & (1 << bit0)) == 0) {
        continue;
      }
      int prev = i & ~(1 << bit0);
      if (prev == 0) {
        continue;
      }
      //printf("i = %d, bit0 = %d, prev = %d\n", i, bit0, prev);
      int best = 1600;
      for (int bit1 = 0; bit1 < N; ++bit1) {
        if ((prev & (1 << bit1)) == 0) {
          continue;
        }
        int add = s_len[bit0] - common_table[bit0][bit1];
        int value = add + dp2[prev][bit1];
        if (best > value) {
          best = value;
        }
      }
      dp2[i][bit0] = best;
      //printf("dp2[%d][%d] = %d\n", i, bit0, best);
    }
  }
  char* p = buffer[0];
  int bits = (1 << N) - 1;
  int prev = -1;
  for (int i = 0; i < N; ++i) {
    int sel = -1;
    for (int j = 0; j < N; ++j) {
      if (dp2[bits][j] != -1) {
        if (sel == -1) {
          sel = j;
          continue;
        }
        int l1 = (prev == -1) ? dp2[bits][sel] : dp2[bits][sel] - common_table[prev][sel];
        int l2 = (prev == -1) ? dp2[bits][j] : dp2[bits][j] - common_table[prev][j];
        if (l1 > l2) {
          sel = j;
        } else if (l1 == l2) {
          char* s1 = (prev == -1) ? s[sel] : s[sel] + common_table[prev][sel];
          char* s2 = (prev == -1) ? s[j] : s[j] + common_table[prev][j];
          //printf("bits = %d, j = %d, dp[%d][%d] = %d, s1 = %s, s2 = %s\n",
          //    bits, j, bits, j, dp2[bits][j], s1, s2);
          if (strcmp(s1, s2) > 0) {
            sel = j;
          }
        }
      }
    }
    //printf("dp2[%d][%d] = %d\n", bits, sel, dp2[bits][sel]);
    char* q = s[sel];
    if (prev != -1) {
      q += common_table[prev][sel];
    }
    //printf("buffer[0] = %s, q = %s\n", buffer[0], q);
    strcpy(p, q);
    p += strlen(p);
    prev = sel;
    bits &= ~(1 << sel);
  }
  return buffer[0];
}

int main() {
  init();
  freopen("DNALaboratory.in", "r", stdin);
  int test;
  scanf("%d", &test);
  for (int t = 1; t <= test; ++t) {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
      scanf("%s", s[i]);
    }
    char* result = solve3();
    printf("Scenario #%d:\n%s\n\n", t, result);
  }
  return 0;
}
