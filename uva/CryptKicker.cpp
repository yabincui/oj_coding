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

// The global logic is a DFS.
// 1. Find words for each length.
// 2. Iteratively guess a word is tranlated to a word.
// 3. If now some words has only one translation, fix them too.
// 3. Check possible conflicts.
// 4. Continue until all possiblities are tried.

class Guesser {
private:
    struct Guess {
        char en[26];  // encrypted to origin
        char oi[26];  // origin to encrypted
        vector<vector<int>> candidates;
    };

public:
    Guesser(vector<string>& words) {
        this->words = words;
        for (int i = 0; i < words.size(); ++i) {
            int n = words[i].size();
            len_map[n].push_back(i);
        }
    }

    vector<string> guess(const vector<string>& input) {
        initInput(input);
        Guess guess = initGuess();
        if (!dfs(guess)) {
            dprintf("dfs failed\n");
            return vector<string>();
        }
        vector<string> res(input.size());
        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[i].size(); ++j) {
                res[i].push_back(guess.en[input[i][j] - 'a']);
            }
            dprintf("res[%d] = %s\n", i, res[i].c_str());
        }
        return res;
    }

    void initInput(const vector<string>& s) {
        input = s;
        sort(input.begin(), input.end(), [](const string& s1, const string& s2) {
            return s1.size() > s2.size();
        });
    }

    Guess initGuess() {
        Guess guess;
        memset(guess.en, 0, sizeof(guess.en));
        memset(guess.oi, 0, sizeof(guess.oi));
        guess.candidates.resize(input.size());
        for (int i = 0; i < input.size(); ++i) {
            vector<int>& v = len_map[input[i].size()];
            guess.candidates[i] = v;
            dprintf("init_guess %s, en_id %d ->", input[i].c_str(), i);
            for (auto n : v) {
                dprintf(" %d", n);
            }
            dprintf("\n");
        }
        return guess;
    }

    bool dfs(Guess& guess) {
        if (!updateGuess(guess)) {
            dprintf("update failed\n");
            return false;
        }
        int guess_id = findOneToGuess(guess);
        dprintf("findGuess %d\n", guess_id);
        if (guess_id == -1) {
            return true;
        }
        vector<int> candidates = guess.candidates[guess_id];
        Guess saved_guess = guess;
        for (int i = 0; i < candidates.size(); ++i) {
            guess.candidates[guess_id].clear();
            bool has_change;
            dprintf("guess en_id %d to %d\n", guess_id, candidates[i]);
            if (assignGuess(guess, guess_id, candidates[i], has_change)) {
                if (dfs(guess)) {
                    return true;
                }
            }
            guess = saved_guess;
        }
        return false;
    }

    bool updateGuess(Guess& guess) {
        bool has_change = true;
        while (has_change) {
            has_change = false;
            for (int i = 0; i < input.size(); ++i) {
                if (guess.candidates[i].empty()) {
                    return true;
                }
                if (!updateCandidate(guess, i, has_change)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool updateCandidate(Guess& guess, int en_id, bool& has_change) {
        int j = 0;
        for (auto or_id : guess.candidates[en_id]) {
            if (isPossible(guess, en_id, or_id)) {
                guess.candidates[en_id][j++] = or_id;
            }
        }
        guess.candidates[en_id].resize(j);
        if (j == 0) {
            return false;
        }
        if (j == 1) {
            dprintf("clear guess[en_id = %d], match to %d\n", en_id, guess.candidates[en_id][0]);
            if (!assignGuess(guess, en_id, guess.candidates[en_id][0], has_change)) {
                return false;
            }
            guess.candidates[en_id].clear();
        }
        return true;
    }

    bool isPossible(Guess& guess, int en_id, int or_id) {
        for (int i = 0; i < input[en_id].size(); ++i) {
            char to = guess.en[input[en_id][i] - 'a'];
            if (to != 0 && to != words[or_id][i]) {
                return false;
            }
        }
        return true;
    }

    int findOneToGuess(Guess& guess) {
        int min_count = INT_MAX;
        int choosen = -1;
        for (int i = 0; i < guess.candidates.size(); ++i) {
            int count = guess.candidates[i].size();
            if (count == 0) continue;
            if (count < min_count || (count == min_count && input[i].size() < input[choosen].size())) {
                choosen = i;
                min_count = count;
            }
        }
        return choosen;
    }

    bool assignGuess(Guess& guess, int en_id, int or_id, bool& has_change) {
        const string& sa = input[en_id];
        const string& sb = words[or_id];
        for (int i = 0; i < sa.size(); ++i) {
            char a = sa[i];
            char b = sb[i];
            if (guess.en[a - 'a'] == b) {
                continue;
            }
            if (guess.en[a - 'a'] != 0 ||
                    guess.oi[b - 'a'] != 0) {
                return false;
            }
            guess.en[a - 'a'] = b;
            guess.oi[b - 'a'] = a;
            dprintf("en[%c] = %c, oi[%c] = %c\n", a, b, b, a);
            has_change = true;
        }
        return true;
    }

private:
    vector<string> words;
    unordered_map<int, vector<int>> len_map;
    vector<string> input;
};

int main() {
    freopen("CryptKicker.in", "r", stdin);
    int n;
    scanf("%d", &n);
    vector<string> words;
    char* line = NULL;
    size_t line_size = 0;
    for (int i = 0; i < n; ++i) {
        while (getline(&line, &line_size, stdin) > 0) {
            if (isalpha(line[0])) break;
        }
        int len = strlen(line);
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        words.push_back(line);
    }
    Guesser guesser(words);
    while (getline(&line, &line_size, stdin) > 0 && line[0] != '*') {
        vector<string> strs = splitString(line);
        vector<string> guess = guesser.guess(strs);
        if (guess.empty()) {
            guess.resize(strs.size());
            for (int i = 0; i < strs.size(); ++i) {
                guess[i].resize(strs[i].size(), '*');
            }
        }
        for (int i = 0; i < guess.size(); ++i) {
            if (i > 0) printf(" ");
            printf("%s", guess[i].c_str());
        }
        printf("\n");
    }
}