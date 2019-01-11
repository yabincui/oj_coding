#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>

#include <inttypes.h>

using namespace std;

struct Candidate {
    int r, c;
    int64_t cost;

    bool operator<(const Candidate& o) {
        if (cost != o.cost) {
            return cost < o.cost;
        }
        if (r != o.r) {
            return r < o.r;
        }
        return c < o.c;
    }
};

int n, m, a, b;
int s[1000][1000];
int64_t rangeSum[1000][1000];
int rangeMin[1000][1000];
int rangeMinPerC[1000][10][1000];

Candidate candidates[1000000];
bool visited[1000][1000];

int log2(int n) {
    int i = 0;
    for (int t = 1; t * 2 <= n; t *= 2) {
        i++;
    }
    return i;
}

void initRangeMinPerC() {
    int maxJr = log2(n);
    for (int c = 0; c < m; c++) {
        for (int r = 0; r < n; r++) {
            rangeMinPerC[c][0][r] = s[r][c];
        }
        for (int jr = 1; jr <= maxJr; jr++) {
            for (int r = 0; r < n; r++) {
                int t = rangeMinPerC[c][jr-1][r];
                if (r + (1<<(jr-1)) < n) {
                    t = min(t, rangeMinPerC[c][jr-1][r+(1<<(jr-1))]);
                }
                rangeMinPerC[c][jr][r] = t;
            }
        }
    }
}

int getRangeMinPerC(int c, int r1, int r2) {
    int length = r2 - r1 + 1;
    int level = log2(length);
    return min(rangeMinPerC[c][level][r1], rangeMinPerC[c][level][r2 - (1 << level) + 1]);
}

int row[1000];
void preprocessRangeMin() {
    initRangeMinPerC();
    map<int, int> mp;
    for (int i = 0; i <= n - a; i++) {
        for (int j = 0; j < m; j++) {
            row[j] = getRangeMinPerC(j, i, i + a - 1);
        }
        mp.clear();
        for (int j = 0; j < b; j++) {
            mp[row[j]]++;
        }
        for (int j = 0; j <= m - b; j++) {
            rangeMin[i][j] = mp.begin()->first;
            if (j < m - b) {
                mp[row[j + b]]++;
                if (--mp[row[j]] == 0) {
                    mp.erase(row[j]);
                }
            }
        }
    }
}

int64_t getRangeMin(int x1, int y1) {
    return rangeMin[x1][y1];
}

int64_t getRangeSum(int x1, int x2, int y1, int y2) {
    int64_t res = rangeSum[x2][y2];
    if (x1 > 0) {
        res -= rangeSum[x1 - 1][y2];
    }
    if (y1 > 0) {
        res -= rangeSum[x2][y1 - 1];
    }
    if (x1 > 0 && y1 > 0) {
        res += rangeSum[x1 - 1][y1 - 1];
    }
    return res;
}

bool isVisited(Candidate& c) {
    return visited[c.r][c.c] || visited[c.r][c.c + b - 1]
        || visited[c.r + a - 1][c.c] || visited[c.r + a - 1][c.c + b - 1];
}

int main() {
    while (scanf("%d%d%d%d", &n, &m, &a, &b) == 4) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &s[i][j]);
            }
        }
        for (int i = 0; i < n; i++) {
            int64_t prevInLine = 0;
            for (int j = 0; j < m; j++) {
                rangeSum[i][j] = s[i][j] + prevInLine;
                prevInLine += s[i][j];
                if (i > 0) {
                    rangeSum[i][j] += rangeSum[i-1][j];
                }
            }
        }
        preprocessRangeMin();
        int k = 0;
        for (int i = 0; i <= n - a; i++) {
            for (int j = 0; j <= m - b; j++) {
                int64_t sum = getRangeSum(i, i + a - 1, j, j + b - 1);
                int64_t minVal = getRangeMin(i, j);
                //printf("i = %d, j = %d, sum = %lld, minVal = %lld\n", i, j, sum, minVal);
                candidates[k].cost = sum - minVal * a * b;
                candidates[k].r = i;
                candidates[k].c = j;
                k++;
            }
        }
        sort(candidates, &candidates[k]);
        memset(visited, '\0', sizeof(visited));
        vector<Candidate> res;
        for (int t = 0; t < k; t++) {
            if (isVisited(candidates[t])) {
                continue;
            }
            for (int i = 0; i < a; i++) {
                for (int j = 0; j < b; j++) {
                    visited[candidates[t].r + i][candidates[t].c + j] = true;
                }
            }
            res.push_back(candidates[t]);
        }
        printf("%zu\n", res.size());
        for (auto& c : res) {
            printf("%d %d %lld\n", c.r + 1, c.c + 1, c.cost);
        }
    }
}