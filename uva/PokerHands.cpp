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

vector<int> getRank(vector<string> cards) {
    unordered_map<char, int> value_map;
    for (int i = 2; i <= 9; ++i) {
        value_map[i + '0'] = i;
    }
    value_map['T'] = 10;
    value_map['J'] = 11;
    value_map['Q'] = 12;
    value_map['K'] = 13;
    value_map['A'] = 14;
    vector<int> rank;
    // 9: Same suite with consecutive values.
    auto comp = [&](const string& s1, const string& s2) {
        int v1 = value_map[s1[0]];
        int v2 = value_map[s2[0]];
        if (v1 != v2) {
            return v1 < v2;
        }
        return s1[1] < s2[1];
    };
    sort(cards.begin(), cards.end(), comp);
    bool flag = true;
    for (int i = 1; i <= 4; ++i) {
        if (!(value_map[cards[i][0]] == value_map[cards[0][0]] + i && cards[i][1] == cards[0][1])) {
            flag = false;
        }
    }
    if (flag) {
        rank.push_back(9);
        rank.push_back(value_map[cards[4][0]]);
        return rank;
    }
    // 8: Four of a kind.
    unordered_map<int, int> count_map;
    for (auto& card : cards) {
        count_map[value_map[card[0]]]++;
    }
    vector<pair<int, int>> count_v;
    for (auto& pair : count_map) {
        count_v.push_back(make_pair(pair.second, pair.first));
    }
    sort(count_v.begin(), count_v.end(), greater<pair<int, int>>());
    if (count_v[0].first == 4) {
        rank.push_back(8);
        rank.push_back(count_v[0].second);
        return rank;
    }
    // 7: Full house.
    if (count_v.size() == 2 && count_v[0].first == 3) {
        rank.push_back(7);
        rank.push_back(count_v[0].second);
        return rank;
    }
    // 6: Flush.
    bool same_color = true;
    for (int i = 1; i <= 4; ++i) {
        if (cards[i][1] != cards[0][1]) {
            same_color = false;
        }
    }
    if (same_color) {
        rank.push_back(6);
        for (int i = 4; i >= 0; --i) {
            rank.push_back(value_map[cards[i][0]]);
        }
        return rank;
    }
    // 5: Straight.
    bool consecutive = true;
    for (int i = 1; i <= 4; ++i) {
        if (value_map[cards[i][0]] != value_map[cards[0][0]] + i) {
            consecutive = false;
        }
    }
    if (consecutive) {
        rank.push_back(5);
        rank.push_back(value_map[cards[4][0]]);
    }
    // 4: Three of a kind.
    if (count_v[0].first == 3) {
        rank.push_back(4);
        rank.push_back(count_v[0].second);
        return rank;
    }
    // 3: Two pairs.
    if (count_v.size() == 3 && count_v[0].first == 2 && count_v[1].first == 2) {
        rank.push_back(3);
        rank.push_back(count_v[0].second);
        rank.push_back(count_v[1].second);
        rank.push_back(count_v[2].second);
    }
    // 2: Pair.
    if (count_v[0].first == 2) {
        rank.push_back(2);
        rank.push_back(count_v[0].second);
        for (int i = 1; i < count_v.size(); ++i) {
            rank.push_back(count_v[i].second);
        }
        sort(rank.begin() + 2, rank.end(), greater<int>());
        return rank;
    }
    // 1: High Card.
    rank.push_back(1);
    for (int i = 0; i < count_v.size(); ++i) {
        rank.push_back(count_v[i].second);
    }
    sort(rank.begin() + 1, rank.end(), greater<int>());
    return rank;
}

void showRank(vector<string>& cards, vector<int> rank) {
    return;
    printf("rank of (");
    for (int i = 0; i < cards.size(); ++i) {
        printf("%s ", cards[i].c_str());
    }
    printf(") = ");
    for (auto n : rank) {
        printf("%d ", n);
    }
    printf("\n");
}

int compareCards(const vector<string>& strs) {
    vector<string> player1(strs.begin(), strs.begin() + 5);
    vector<string> player2(strs.begin() + 5, strs.end());
    vector<int> rank1 = getRank(player1);
    vector<int> rank2 = getRank(player2);
    showRank(player1, rank1);
    showRank(player2, rank2);
    for (int i = 0; i < rank1.size(); ++i) {
        if (rank1[i] != rank2[i]) {
            return rank1[i] - rank2[i];
        }
    }
    return 0;
}

int main() {
    freopen("PokerHands.in", "r", stdin);
    char* line = NULL;
    size_t line_size = 0;
    while (getline(&line, &line_size, stdin) > 0 && !isspace(line[0])) {
        vector<string> strs = splitString(line);
        int res = compareCards(strs);
        if (res < 0) {
            printf("White wins.\n");
        } else if (res == 0) {
            printf("Tie.\n");
        } else {
            printf("Black wins.\n");
        }
    }
}