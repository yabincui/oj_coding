#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <cmath>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

vector<vector<int>> lcd_map = {
    {0, 1, 2, 4, 5, 6},
    {2, 6},
    {0, 2, 3, 4, 5},
    {0, 2, 3, 5, 6},
    {1, 2, 3, 6},
    {0, 1, 3, 5, 6},
    {0, 1, 3, 4, 5, 6},
    {0, 2, 6},
    {0, 1, 2, 3, 4, 5, 6},
    {0, 1, 2, 3, 5, 6},
};

void addColumn(vector<string>& display, int count=1) {
    for (int i = 0; i < count; ++i) {
        for (auto& line : display) {
            line.push_back(' ');
        }
    }
}

void writeRow(vector<string>& display, int r, int c, int s) {
    for (int i = 0; i < s; ++i) {
        display[r][i + c] = '-';
    }
}

void writeCol(vector<string>& display, int r, int c, int s) {
    for (int i = 0; i < s; ++i) {
        display[r + i][c] = '|';
    }
}

void displayNumber(int s, int n, vector<string>& display) {
    display.resize(3 + 2 * s, "");
    vector<int> digits;
    do {
        digits.push_back(n % 10);
        n /= 10;
    } while (n != 0);
    reverse(digits.begin(), digits.end());
    for (int i = 0; i < digits.size(); ++i) {
        if (i > 0) {
            addColumn(display);
        }
        int start_col = display[0].size();
        addColumn(display, s + 2);
        int d = digits[i];
        //printf("start_col = %d, d = %d\n", start_col, d);
        vector<int>& items = lcd_map[d];
        for (auto item : items) {
            int r, c;
            switch(item) {
            case 0: {
               r = 0;
               c = 1;
               writeRow(display, r, start_col + c, s);
               break;
            }
            case 1: {
                r = 1;
                c = 0;
                writeCol(display, r, start_col + c, s);
                break;
            }
            case 2: {
                r = 1;
                c = s + 1;
                writeCol(display, r, start_col + c, s);
                break;
            }
            case 3: {
                r = s + 1;
                c = 1;
                writeRow(display, r, start_col + c, s);
                break;
            }
            case 4: {
                r = s + 2;
                c = 0;
                writeCol(display, r, start_col + c, s);
                break;
            }
            case 5: {
                r = 2 * s + 2;
                c = 1;
                writeRow(display, r, start_col + c, s);
                break;
            }
            case 6: {
                r = s + 2;
                c = s + 1;
                writeCol(display, r, start_col + c, s);
                break;
            }
            }
        }
    }
}

int main() {
    freopen("LcdDisplay.in", "r", stdin);
    int s, n;
    while (scanf("%d%d", &s, &n) == 2 && s != 0) {
        //printf("s = %d, n = %d\n", s, n);
        vector<string> display;
        displayNumber(s, n, display);
        for (auto& line : display) {
            printf("%s\n", line.c_str());
        }
        printf("\n");
    }
}