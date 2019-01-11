#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;

void readBoard(vector<vector<char>>& board, int n, int m) {
    board.resize(n);
    for (int i = 0; i < n; ++i) {
        vector<char>& line = board[i];
        line.resize(m);
        for (int j = 0; j < m; ++j) {
            do {
                line[j] = getchar();
            } while (line[j] != '*' && line[j] != '.');
        }
    }
}

void changeBoard(vector<vector<char>>& board) {
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (board[i][j] == '*') continue;
            int count = 0;
            for (int ni = i-1; ni <= i+1; ++ni) {
                for (int nj = j-1; nj <= j+1; ++nj) {
                    if (ni < 0 || ni >= board.size() || nj < 0 || nj >= board[i].size()) {
                        continue;
                    }
                    if (board[ni][nj] == '*') {
                        count++;
                    }
                }
            }
            board[i][j] = '0' + count;
        }
    }
}

void printBoard(const vector<vector<char>>& board) {
    for (auto& line : board) {
        for (auto c : line) {
            printf("%c", c);
        }
        printf("\n");
    }
}

int main() {
    freopen("Minesweeper.in", "r", stdin);
    int n, m;
    int field = 1;
    while (scanf("%d%d", &n, &m) == 2) {
        if (n == 0 || m == 0) break;
        vector<vector<char>> board;
        readBoard(board, n, m);
        changeBoard(board);
        if (field > 1) {
            printf("\n");
        }
        printf("Field #%d:\n", field++);
        printBoard(board);
    }
}