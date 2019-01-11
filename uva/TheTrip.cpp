#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

using namespace std;

typedef long long ll;

int getMinMove(const vector<int>& s) {
    int total = accumulate(s.begin(), s.end(), 0);
    int avg_low;
    int avg_high;
    if (total % s.size() == 0) {
        avg_low = avg_high = total / s.size();
    } else {
        avg_low = total / s.size();
        avg_high = avg_low + 1;
    }
    int add_value = 0;
    int sub_value = 0;
    for (auto n : s) {
        if (n < avg_low) {
            add_value += avg_low - n;
        } else if (n > avg_high) {
            sub_value += n - avg_high;
        }
    }
    return max(add_value, sub_value);
}

int main() {
    freopen("TheTrip.in", "r", stdin);
    int n;
    while (scanf("%d", &n) == 1 && n != 0) {
        vector<int> count;
        for (int i = 0; i < n; ++i) {
            double d;
            scanf("%lf", &d);
            count.push_back((int)round(d * 100));
        }
        int minMove = getMinMove(count);
        printf("$%d.%02d\n", minMove / 100, minMove % 100);
    }
}