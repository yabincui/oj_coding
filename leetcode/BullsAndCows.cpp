// 299. Bulls and Cows
class Solution {
public:
    string getHint(string secret, string guess) {
        int bull = 0;
        int digitA[10];
        int digitB[10];
        memset(digitA, 0, sizeof(digitA));
        memset(digitB, 0, sizeof(digitB));
        for (int i = 0; i < secret.size(); ++i) {
            if (secret[i] == guess[i]) {
                bull++;
            }
            digitA[secret[i]-'0']++;
            digitB[guess[i]-'0']++;
        }
        int cow = 0;
        for (int i = 0; i < 10; ++i) {
            cow += min(digitA[i], digitB[i]);
        }
        cow -= bull;
        char buf[40];
        snprintf(buf, sizeof(buf), "%dA%dB", bull, cow);
        return buf;
    }
};
