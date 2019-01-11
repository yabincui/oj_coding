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

bool readBoard(vector<string>& board) {
    for (int i = 0; i < 8; ++i) {
        char buf[40];
        scanf("%s", buf);
        board.push_back(buf);
    }
    for (auto& line : board) {
        for (auto c : line) {
            if (c != '.') {
                return true;
            }
        }
    }
    return false;
}

bool isValidPos(const vector<string>& board, int r, int c) {
    return r >= 0 && r < board.size() && c >= 0 && c < board[r].size();
}

bool checkMove(const vector<string>& board, int r, int c, char king) {
    char item = board[r][c];
    vector<int> dr;
    vector<int> dc;
    bool oneshot = false;
    if (item == 'p') {
        dr = {1, 1};
        dc = {-1, 1};
        oneshot = true;
    } else if (item == 'P') {
        dr = {-1, -1};
        dc = {-1, 1};
        oneshot = true;
    } else if (item == 'n' || item == 'N') {
        dr = {-2, -2, -1, -1, 1, 1, 2, 2};
        dc = {-1, 1, -2, 2, -2, 2, -1, 1};
        oneshot = true;
    } else if (item == 'b' || item == 'B') {
        dr = {-1, -1, 1, 1};
        dc = {-1, 1, -1, 1};
    } else if (item == 'r' || item == 'R') {
        dr = {-1, 1, 0, 0};
        dc = {0, 0, -1, 1};
    } else if (item == 'q' || item == 'Q') {
        dr = {-1, -1, -1, 0, 0, 1, 1, 1};
        dc = {-1, 0, 1, -1, 1, -1, 0, 1};
    } else if (item == 'k' || item == 'K') {
        dr = {-1, -1, -1, 0, 0, 1, 1, 1};
        dc = {-1, 0, 1, -1, 1, -1, 0, 1};
        oneshot = true;
    }
    for (int d = 0; d < dr.size(); ++d) {
        int nr = r;
        int nc = c;
        for (int i = 0;; ++i) {
            nr += dr[d];
            nc += dc[d];
            if (!isValidPos(board, nr, nc)) {
                break;
            }
            if (board[nr][nc] == king) {
                return true;
            }
            if (board[nr][nc] != '.') {
                break;
            }
            if (oneshot) break;
        }
    }
    return false;
}

bool isChecked(const vector<string>& board, char king) {
    bool check_white = king == 'K';
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (board[i][j] == '.') continue;
            if (check_white) {
                if (isupper(board[i][j])) continue;
            } else {
                if (islower(board[i][j])) continue;
            }
            if (checkMove(board, i, j, king)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    freopen("CheckTheCheck.in", "r", stdin);
    int game = 1;
    while (true) {
        vector<string> board;
        if (!readBoard(board)) {
            break;
        }
        if (isChecked(board, 'K')) {
            printf("Game #%d: white king is in check.\n", game++);
        } else if (isChecked(board, 'k')) {
            printf("Game #%d: black king is in check.\n", game++);
        } else {
            printf("Game #%d: no king is in check.\n", game++);
        }
    }
}