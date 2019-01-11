#include <stdio.h>

#include <string>
#include <vector>

using namespace std;

class LineReader {
  public:
    LineReader() : buffer(NULL), buffer_size(0) {}

    ~LineReader() {
        if (buffer)
            free(buffer);
    }

    string getLine() {
        if (getline(&buffer, &buffer_size, stdin) <= 0) {
            return "";
        }
        return string(buffer);
    }

    char *buffer;
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

vector<int> splitNumbers(const string &line) {
    vector<string> strs = splitString(line);
    vector<int> res;
    for (auto &s : strs) {
        res.push_back(atoi(s.c_str()));
    }
    return res;
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
