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

struct Submition {
    int time;
    bool correct;
};

struct Node {
    int id;
    map<int, vector<Submition>> submitions;
    int success_problems;
    int penalty_time;

    Node() : id(-1), success_problems(0), penalty_time(0) {}

    void calculate() {
        for (auto& pair : submitions) {
            vector<Submition>& v = pair.second;
            for (int i = 0; i < v.size(); ++i) {
                if (v[i].correct) {
                    success_problems++;
                    penalty_time += i * 20 + v[i].time;
                    break;
                }
            }
        }
    }
};

class Solution {
public:
    void addSubmit(int id, int program, int time, char type) {
        nodes[id].id = id;
        if (type != 'I' && type != 'C') {
            return;
        }
        Submition sub;
        sub.time = time;
        sub.correct = type == 'C';
        nodes[id].submitions[program].push_back(sub);
    }

    void printSortedIds() {
        for (auto& pair : nodes) {
            pair.second.calculate();
        }
        vector<Node*> v;
        for (auto& pair : nodes) {
            v.push_back(&pair.second);
        }
        sort(v.begin(), v.end(), [](const Node* n1, const Node* n2) {
            if (n1->success_problems != n2->success_problems) {
                return n1->success_problems > n2->success_problems;
            }
            if (n1->penalty_time != n2->penalty_time) {
                return n1->penalty_time < n2->penalty_time;
            }
            return n1->id < n2->id;
        });
        for (auto n : v) {
            printf("%d %d %d\n", n->id, n->success_problems, n->penalty_time);
        }
    }
    

private:
    map<int, Node> nodes;
};

int main() {
    freopen("ContestScoreboard.in", "r", stdin);
    int cases;
    scanf("%d", &cases);
    LineReader reader;
    reader.getLine();
    reader.getLine();
    for (int c = 1; c <= cases; ++c) {
        Solution solution;
        while (true) {
            string s = reader.getLine();
            if (s.empty() || s.size() == 1 && s[0] == '\n') {
                break;
            }
            int id;
            int problem;
            int time;
            char type[2];
            sscanf(s.c_str(), "%d%d%d%s", &id, &problem, &time, type);
            solution.addSubmit(id, problem, time, type[0]);
            dprintf("c = %d, addSubmit(%d, %d, %d, %s)", c, id, problem, time, type);
        }
        if (c > 1) {
            printf("\n");
        }
        solution.printSortedIds();
    }
}