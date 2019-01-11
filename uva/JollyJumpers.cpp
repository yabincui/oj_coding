#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <cmath>
#include <numeric>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

typedef long long ll;

vector<int> splitNumbers(const char* line) {
    vector<string> strs;
    string s;
    for (const char* p = line; *p != '\0'; ++p) {
        if (!isspace(*p)) {
            s.push_back(*p);
        } else {
            if (!s.empty()) {
                strs.push_back(s);
                s.clear();
            }
        }
    }
    if (!s.empty()) {
        strs.push_back(s);
    }
    vector<int> res;
    for (auto& s : strs) {
        res.push_back(atoi(s.c_str()));
    }
    return res;
}

bool isJolly(vector<int>& s) {
    int n = s[0];
    unordered_set<int> diff;
    for (int i = 2; i < s.size(); ++i) {
        int d = abs(s[i] - s[i-1]);
        if (d < 1 || d >= n || diff.find(d) != diff.end()) {
            return false;
        }
        diff.insert(d);
    }
    return true;
}

int main() {
    freopen("JollyJumpers.in", "r", stdin);
    char* line = NULL;
    size_t line_size = 0;
    while (getline(&line, &line_size, stdin) > 0 && isdigit(line[0])) {
        vector<int> s = splitNumbers(line);
        if (isJolly(s)) {
            printf("Jolly\n");
        } else {
            printf("Not jolly\n");
        }
    }
}