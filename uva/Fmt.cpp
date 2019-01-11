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

string joinString(const vector<string>& strs, const string& seq="") {
    string s;
    for (int i = 0; i < strs.size(); ++i) {
        if (i > 0) s += seq;
        s += strs[i];
    }
    return s;
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

string getNextWord(string& s, int& s_pos) {
    string res;
    while (s_pos < s.size() && s[s_pos] == ' ') {
        res += s[s_pos++];
    }
    while (s_pos < s.size() && s[s_pos] != '\n' && s[s_pos] != ' ') {
        res += s[s_pos++];
    }
    if (!res.empty()) return res;
    if (s_pos < s.size() && s[s_pos] == '\n') {
        res += s[s_pos++];
    }
    return res;
}

int getSpaceLen(string& s) {
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] != ' ') return i;
    }
    return s.size();
}

void removeEndSpaces(string& s) {
    bool has_newline = false;
    if (s.size() > 0 && s.back() == '\n') {
        has_newline = true;
    }
    int i = (int)s.size() - (has_newline ? 2 : 1);
    while (i >= 0 && s[i] == ' ') {
        i--;
    }
    if (has_newline) {
        s[++i] = '\n';
    }
    s.resize(i + 1);
}

vector<string> formatText(vector<string>& input) {
    vector<string> output;
    for (auto& s : input) {
        removeEndSpaces(s);
    }
    string s = joinString(input);
    //printf("s = '%s'\n", s.c_str());
    bool has_content = false;
    for (int i = 0; i + 1 < s.size(); ++i) {
        if (s[i] == '\n') {
            if (has_content && s[i+1] != '\n' && s[i+1] != ' ') {
                s[i] = ' ';
            } else {
                has_content = false;
            }
        } else {
            has_content = true;
        }
    }
    //printf("s = %s\n", s.c_str());
    int s_pos = 0;
    string next_word;
    string cur_line;
    bool break_newline = false;
    while (true) {
        if (next_word.empty()) {
            next_word = getNextWord(s, s_pos);
        }
        if (next_word.empty()) {
            break;
        }
        //printf("next_word = '%s', cur_line = '%s', break_newline = %d, output size = %zu\n",
        //        next_word.c_str(), cur_line.c_str(), break_newline, output.size());
        if (next_word == "\n") {
            /*
            if (cur_line.empty() && break_newline) {
                next_word.clear();
                break_newline = false;
                continue;
            }
            */
            cur_line += '\n';
            output.push_back(cur_line);
            cur_line.clear();
            next_word.clear();
            break_newline = false;
            continue;
        }
        if (cur_line.empty() && break_newline) {
            next_word = trimString(next_word);
            if (next_word.empty()) {
                continue;
            }
        }
        if (cur_line.size() + next_word.size() <= 72) {
            cur_line += next_word;
            next_word.clear();
        } else if (!cur_line.empty()) {
            cur_line += '\n';
            output.push_back(cur_line);
            cur_line.clear();
            break_newline = true;
        } else if (next_word.size() >= 72) {
            if (next_word[0] == ' ') {
                output.push_back("\n");
            }
            cur_line = trimString(next_word);
            next_word.clear();
        } else {
            cur_line = next_word;
            next_word.clear();
        }
    }
    if (!cur_line.empty()) {
        output.push_back(cur_line + '\n');
    }
    return output;
}

int main() {
    freopen("Fmt.in", "r", stdin);
    LineReader reader;
    vector<string> lines;
    while (true) {
        string s = reader.getLine();
        if (s.empty()) break;
        lines.push_back(s);
    }
    vector<string> res = formatText(lines);
    for (auto& s : res) {
        printf("%s", s.c_str());
    }
    return 0;
}