#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <cmath>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

vector<int> getVotes(const char* line) {
    vector<int> res;
    int cur = 0;
    for (const char* p = line; *p != '\0'; ++p) {
        if (isdigit(*p)) {
            cur = cur * 10 + *p - '0';
        } else {
            if (cur != 0) {
                res.push_back(cur);
                cur = 0;
            }
        }
    }
    if (cur != 0) {
        res.push_back(cur);
    }
    return res;
}

vector<int> getWinners(int candidates, const vector<vector<int>> votes) {
    //printf("candidates = %d\n", candidates);
    vector<int> pos(votes.size(), 0);
    vector<bool> valid(candidates, true);
    int valid_count = candidates;
    while (true) {
        vector<int> count(candidates, 0);
        for (int i = 0; i < votes.size(); ++i) {
            int vote = votes[i][pos[i]] - 1;
            while (!valid[vote]) {
                pos[i]++;
                vote = votes[i][pos[i]] - 1;
            }
            count[vote]++;
        }
        /*
        printf("new cycle\n");
        for (int i = 0; i < count.size(); ++i) {
            printf("count[%d] = %d\n", i, count[i]);
        }
        */
        int max_value = 0;
        vector<int> max_candidates;
        int min_value = votes.size();
        vector<int> min_candidates;
        for (int i = 0; i < candidates; ++i) {
            if (!valid[i]) continue;
            if (count[i] > max_value) {
                max_value = count[i];
                max_candidates.clear();
                max_candidates.push_back(i);
            } else if (count[i] == max_value) {
                max_candidates.push_back(i);
            }
            if (count[i] < min_value) {
                min_value = count[i];
                min_candidates.clear();
                min_candidates.push_back(i);
            } else if (count[i] == min_value) {
                min_candidates.push_back(i);
            }
        }
        //printf("max_value = %d, votes.size() = %zu\n", max_value, votes.size());
        if (max_value * 2 > votes.size() || max_candidates.size() == valid_count) {
            return max_candidates;
        }
        for (auto i : min_candidates) {
            //printf("remove %d\n", i);
            valid[i] = false;
            valid_count--;
        }
    }
}

int main() {
    freopen("AustralianVoting.in", "r", stdin);
    int cases;
    scanf("%d", &cases);
    char* line = NULL;
    size_t line_size = 0;
    for (int i = 0; i < cases; ++i) {
        int n;
        scanf("%d", &n);
        vector<string> candidates;
        for (int j = 0; j < n; ++j) {
            do {
                getline(&line, &line_size, stdin);
                int n = strlen(line);
                if (line[n - 1] == '\n') {
                    line[n - 1] = '\0';
                }
            } while (line[0] == '\0');
            candidates.push_back(line);
        }
        vector<vector<int>> votes;
        while (true) {
            if (getline(&line, &line_size, stdin) <= 0 || !isdigit(line[0])) {
                break;
            }
            votes.push_back(getVotes(line));
        }
        vector<int> winners = getWinners(candidates.size(), votes);
        if (i > 0) {
            printf("\n");
        }
        for (auto winner : winners) {
            printf("%s\n", candidates[winner].c_str());
        }
    }
}