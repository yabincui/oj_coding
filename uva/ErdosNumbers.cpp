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

vector<string> splitString(const string& line, const string& delimeters = "") {
    vector<string> strs;
    string s;
    for (const char* p = line.c_str(); *p != '\0'; ++p) {
        bool split_char = (delimeters.empty() ? isspace(*p) : (delimeters.find(*p) != string::npos));
        if (!split_char) {
            s.push_back(*p);
        } else {
            if (!s.empty()) {
                strs.push_back(s);
                dprintf("push back %s\n", s.c_str());
                s.clear();
            }
        }
    }
    if (!s.empty()) {
        dprintf("push back %s\n", s.c_str());
        strs.push_back(s);
    }
    return strs;
}

string trimString(const string& s) {
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

vector<string> parsePaper(const string& line) {
    string s = splitString(line, ":")[0];
    vector<string> res;
    int i = 0;
    while (i < s.size()) {
        auto j = s.find("., ", i);
        if (j == s.npos) {
            res.push_back(s.substr(i));
            dprintf("parsePaper %s\n", res.back().c_str());
            break;
        }
        res.push_back(s.substr(i, j + 1 - i));
        dprintf("parsePaper %s\n", res.back().c_str());
        i = j + 3;
    }
    for (auto& name : res) {
        name = trimString(name);
    }
    return res;
}

struct Node {
    vector<int> neighbors;
};

vector<int> getLinkNumbers(const vector<vector<string>>& names, const vector<string> questions) {
    unordered_map<string, int> name_map;
    vector<Node> nodes;
    for (auto& v : names) {
        vector<int> ids;
        for (auto& name : v) {
            auto it = name_map.find(name);
            if (it == name_map.end()) {
                ids.push_back(nodes.size());
                name_map[name] = nodes.size();
                nodes.resize(nodes.size() + 1);
            } else {
                ids.push_back(it->second);
            }
        }
        for (int i = 0; i < ids.size(); ++i) {
            for (int j = 0; j < ids.size(); ++j) {
                if (i == j) continue;
                nodes[ids[i]].neighbors.push_back(ids[j]);
            }
        }
    }
    vector<int> dist(nodes.size(), -1);
    queue<int> q;
    string start = "Erdos, P.";
    auto it = name_map.find(start);
    if (it != name_map.end()) {
        dist[it->second] = 0;
        q.push(it->second);
        dprintf("dist[%d] = %d\n", it->second, 0);
    }
    for (int d = 1; !q.empty(); d++) {
        int size = q.size();
        while (size--) {
            int cur = q.front();
            q.pop();
            for (int n : nodes[cur].neighbors) {
                if (dist[n] == -1) {
                    dist[n] = d;
                    dprintf("dist[%d] = %d\n", n, d);
                    q.push(n);
                }
            }
        }
    }
    vector<int> result(questions.size(), -1);
    for (int i = 0; i < questions.size(); ++i) {
        auto it = name_map.find(questions[i]);
        if (it != name_map.end()) {
            result[i] = dist[it->second]; 
        }
    }
    return result;
}

void printResult(const vector<string>& questions, const vector<int>& result) {
    for (int i = 0; i < questions.size(); ++i) {
        if (result[i] == -1) {
            printf("%s infinity\n", questions[i].c_str());
        } else {
            printf("%s %d\n", questions[i].c_str(), result[i]);
        }
    }
}

int main() {
    freopen("ErdosNumbers.in", "r", stdin);
    int cases;
    scanf("%d", &cases);
    LineReader reader;
    for (int c = 1; c <= cases; ++c) {
        int P, N;
        scanf("%d%d", &P, &N);
        reader.getLine();
        vector<vector<string>> names;
        for (int i = 0; i < P; ++i) {
            names.push_back(parsePaper(reader.getLine()));
        }
        vector<string> questions;
        for (int i = 0; i < N; ++i) {
            questions.push_back(parsePaper(reader.getLine())[0]);
        }
        dprintf("getLinkNumbers\n");
        vector<int> result = getLinkNumbers(names, questions);
        printf("Scenario %d\n", c);
        printResult(questions, result);   
    }
}