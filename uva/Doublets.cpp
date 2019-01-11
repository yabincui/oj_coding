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

#define dprintf printf
//#define dprintf

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

vector<string> splitString(const string &line, const string &delimeters = "") {
    vector<string> strs;
    string s;
    for (const char *p = line.c_str(); *p != '\0'; ++p) {
        bool split_char = (delimeters.empty() ? isspace(*p) : (delimeters.find(*p) != string::npos));
        if (!split_char) {
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

string trimString(const string &s) {
    string res;
    int i = 0;
    while (i < s.size() && isspace(s[i])) {
        i++;
    }
    int j = s.size() - 1;
    while (j >= 0 && isspace(s[j])) {
        j--;
    }
    return s.substr(i, j - i + 1);
}

struct Node {
    string name;
    vector<int> neighbors;
};

class Solution {
public:
    Solution(vector<string>& words) {
        nodes.resize(words.size());
        for (int i = 0; i < words.size(); ++i) {
            word_to_node_id[words[i]] = i;
            nodes[i].name = words[i];
        }
        for (int i = 0; i < words.size(); ++i) {
            for (int j = i + 1; j < words.size(); ++j) {
                if (isNeighbor(words[i], words[j])) {
                    nodes[i].neighbors.push_back(j);
                    nodes[j].neighbors.push_back(i);
                }
            }
        }
    }

    vector<string> getPath(string& from, string& to) {
        vector<int> parent(nodes.size(), -1);
        vector<string> res;
        auto it = word_to_node_id.find(from);
        auto it2 = word_to_node_id.find(to);
        if (it == word_to_node_id.end() || it2 == word_to_node_id.end()) {
            return res;
        }
        int from_id = it->second;
        int to_id = it2->second;
        parent[from_id] = from_id;
        if (to_id == from_id) {
            res.push_back(from);
            return res;
        }
        queue<int> q;
        q.push(from_id);
        while (!q.empty()) {
            int size = q.size();
            while (size-- > 0) {
                int cur = q.front();
                q.pop();
                for (auto n : nodes[cur].neighbors) {
                    if (n == to_id) {
                        res.push_back(nodes[n].name);
                        while (true) {
                            res.push_back(nodes[cur].name);
                            if (cur == from_id) break;
                            cur = parent[cur];
                        }
                        reverse(res.begin(), res.end());
                        return res;
                    }
                    if (parent[n] == -1) {
                        parent[n] = cur;
                        q.push(n);
                    }
                }
            }
        }
        return res;
    }

private:
    bool isNeighbor(const string& a, const string& b) {
        if (a.size() != b.size()) return false;
        int same = 0;
        for (int i = 0; i < a.size(); ++i) {
            if (a[i] == b[i]) same++;
        }
        return same == a.size() - 1;
    }


    vector<Node> nodes;
    unordered_map<string, int> word_to_node_id;
};

int main() {
    freopen("Doublets.in", "r", stdin);
    vector<string> words;
    LineReader reader;
    while (true) {
        string s = reader.getLine();
        if (s == "\n" || s.empty()) {
            break;
        }
        s = trimString(s);
        words.push_back(s);
    }
    Solution solution(words);
    bool first = true;
    while (true) {
        string s = reader.getLine();
        if (s.empty()) break;
        vector<string> strs = splitString(trimString(s));
        if (strs.size() != 2) break;
        vector<string> path = solution.getPath(strs[0], strs[1]);
        if (first) {
            first = false;
        } else {
            printf("\n");
        }
        if (path.empty()) {
            printf("No solution.\n");
        }
        for (auto& p : path) {
            printf("%s\n", p.c_str());
        }
    }
    return 0;    
}