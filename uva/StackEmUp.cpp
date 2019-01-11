#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <functional>
#include <map>
#include <numeric>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef long long ll;

//#define dprintf printf
#define dprintf

class LineReader {
public:
    LineReader() : buffer(NULL), buffer_size(0) {}

    ~LineReader() {
        if (buffer) free(buffer);
    }

    string getLine() {
        if (getline(&buffer, &buffer_size, stdin) <= 0) {
            return "";
        }
        return string(buffer);
    }

    char* buffer;
    size_t buffer_size;
};

vector<string> splitString(const char* line) {
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
    return strs;
}

vector<int> splitNumbers(const char* line) {
    vector<string> strs = splitString(line);
    vector<int> res;
    for (auto& s : strs) {
        res.push_back(atoi(s.c_str()));
    }
    return res;
}

vector<int> getOrder(const vector<vector<int>>& shuffles, const vector<int> applies) {
    vector<int> current(53);
    for (int i = 1; i <= 52; ++i) {
        current[i] = i;
    }
    for (int apply : applies) {
        vector<int> next(53);
        for (int i = 0; i < 52; ++i) {
            int pos = i + 1;
            int from = shuffles[apply-1][i];
            next[pos] = current[from];
        }
        current = next;
    }
    return current;
}

void printOrder(const vector<int>& order) {
    const char* names[] = {
        "Jack", "Queen", "King", "Ace"
    };
    const char* suites[] = {
        "Clubs", "Diamonds", "Hearts", "Spades",
    };
    for (int i = 1; i <= 52; ++i) {
        int n = order[i] - 1;
        int name_i = n % 13;
        int suite_i = n / 13;
        string name;
        if (name_i <= 8) {
            name = to_string(name_i + 2);
        } else {
            name = names[name_i - 9];
        }
        printf("%s of %s\n", name.c_str(), suites[suite_i]);
    }
}

int main() {
    freopen("StackEmUp.in", "r", stdin);
    int cases;
    scanf("%d", &cases);
    LineReader reader;
    for (int c = 0; c < cases; ++c) {
        int n;
        scanf("%d", &n);
        vector<vector<int>> shuffles;
        for (int i = 0; i < n; ++i) {
            vector<int> v(52);
            for (int j = 0; j < 52; ++j) {
                scanf("%d", &v[j]);
            }
            shuffles.push_back(v);
        }
        reader.getLine();
        vector<int> applies;
        while (true) {
            string s = reader.getLine();
            dprintf("s = %s, size = %zu\n", s.c_str(), s.size());
            if (s.empty() || (s.size() == 1 && s[0] == '\n')) {
                break;
            }
            int v;
            sscanf(s.c_str(), "%d", &v);
            applies.push_back(v);
            dprintf("applies add %d\n", v);
        }
        dprintf("applies.size() = %zu\n", applies.size());
        vector<int> order = getOrder(shuffles, applies);
        if (c > 0) {
            printf("\n");
        }
        printOrder(order);
    }
}