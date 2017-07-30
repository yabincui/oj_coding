class Solution {
    
    bool isWin(string& senate) {
        for (int i = 1; i < senate.size(); ++i) {
            if (senate[i] != senate[0]) {
                return false;
            }
        }
        return true;
    }
    
    void getNext(string& senate) {
        string next;
        
        int silent_r = 0;
        int silent_d = 0;
        for (char c : senate) {
            if (c == 'R') {
                if (silent_r > 0) {
                    --silent_r;
                } else {
                    next.push_back('R');
                    silent_d++;
                }
            } else if (c == 'D') {
                if (silent_d > 0) {
                    silent_d--;
                } else {
                    next.push_back('D');
                    silent_r++;
                }
            }
        }
        senate.clear();
        for (char c : next) {
            if (c == 'R') {
                if (silent_r > 0) {
                    silent_r--;
                } else {
                    senate.push_back(c);
                }
            } else if (c == 'D') {
                if (silent_d > 0) {
                    silent_d--;
                } else {
                    senate.push_back(c);
                }
            }
        }
    }
    
public:
    string predictPartyVictory(string senate) {
        string next;
        
        while (!isWin(senate)) {
            getNext(senate);
        }
        return senate[0] == 'R' ? "Radiant" : "Dire";
    }
};
