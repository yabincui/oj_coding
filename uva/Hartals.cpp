#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <cmath>
#include <functional>
#include <numeric>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef long long ll;

int getLostDays(int n, vector<int>& parties) {
    vector<bool> lost(n + 1, false);
    //printf("n = %d\n", n);
    for (auto p : parties) {
        //printf("p = %d\n", p);
        for (int i = p; i <= n; i += p) {
            int day = (i + 5) % 7 + 1;
            if (day != 5 && day != 6) {
                lost[i] = true;
            }
        }
    }
    int count = 0;
    for (int i = 1; i <= n; ++i) {
        if (lost[i]) {
            count++;
        }
    }
    return count;
}

int main() {
    freopen("Hartals.in", "r", stdin);
    int cases;
    scanf("%d", &cases);
    for (int i = 0; i < cases; ++i) {
        int n;
        int p;
        scanf("%d%d", &n, &p);
        vector<int> parties(p);
        for (int j = 0; j < p; ++j) {
            scanf("%d", &parties[j]);
        }
        int lost_days = getLostDays(n, parties);
        printf("%d\n", lost_days);
    }
}