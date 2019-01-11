#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>

using namespace std;

typedef long long ll;

ll dp[1000000];

ll getCount(int n) {
    if (dp[n] >= 0) {
        return dp[n];
    }
    int old_n = n;
    int add = 0;
    do {
        if (n & 1) {
            n = 3 * n + 1;
        } else {
            n >>= 1;
        }
        add++;
    } while (n >= 1000000);
    dp[old_n] = getCount(n) + add;
    return dp[old_n];
}

ll getMax(int from, int to) {
    ll maxCount = 0;
    for (int i = from; i <= to; ++i) {
        maxCount = max(maxCount, getCount(i));
    }
    return maxCount;
}

int main() {
    freopen("The3N_1Problem.in", "r", stdin);
    memset(dp, -1, sizeof(dp));
    dp[1] = 1;
    int from, to;
    while (scanf("%d%d", &from, &to) == 2) {
        ll sum = getMax(min(from, to), max(from, to));
        printf("%d %d %lld\n", from, to, sum);
    }
}