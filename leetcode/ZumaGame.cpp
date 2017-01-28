// 488. Zuma Game
class Solution {
public:
    int min_step;

    int findMinStep(string board, string hand) {
        min_step = INT_MAX;
        sort(hand.begin(), hand.end());
        findMin(board, hand, hand.size());
        if (min_step == INT_MAX) {
            min_step = -1;
        }
        return min_step;
    }
    
    void findMin(const string& board, string& hand, int ball_count) {
        //string new_hand;
        //for (int i = 0; i < hand.size(); ++i) {
        //    if (hand[i] != '\0') {
        //        new_hand.push_back(hand[i]);
        ///    }
        //}
        //printf("findMin(board %s, hand %s, ball_count %d\n", board.c_str(), new_hand.c_str(),
       //         ball_count);
        if (board.size() == 0) {
            int used = hand.size() - ball_count;
            if (min_step > used) {
                min_step = used;
            }
            return;
        }
        if (ball_count == 0 || hand.size() - ball_count > min_step) {
            return;
        }
        char prev_ball = '\0';
        for (auto& ball : hand) {
            if (ball == '\0' || ball == prev_ball) {
                continue;
            }
            char saved = ball;
            ball = '\0';
            hitBall(board, hand, saved, ball_count - 1);
            ball = saved;
        }
    }
    
    void hitBall(const string& board, string& hand, char ball, int ball_count) {
        //printf("hitBall board %s, ball %c\n", board.c_str(), ball);
        char prev_c = '\0';
        for (int i = 0; i < board.size(); ++i) {
            char c = board[i];
            if (c != prev_c && c == ball) {
                // try insert the ball here.
                string new_board;
                new_board.insert(new_board.end(), board.begin(), board.begin() + i);
                new_board.push_back(ball);
                new_board.insert(new_board.end(), board.begin() + i, board.end());
                eraseBoard(new_board, i);
                findMin(new_board, hand, ball_count);
            }
            prev_c = c;
        }
    }
    
    void eraseBoard(string& board, int pos) {
        //printf("erase board %s ", board.c_str());
        int left = pos;
        int right = pos;
        int erased = 0;
        while (left >= 0 && right < board.size() && board[left] == board[right]) {
            int new_left = left;
            while (new_left >= 0 && board[new_left] == board[left]) {
                new_left--;
            }
            int new_right = right;
            while (new_right < board.size() && board[new_right] == board[right]) {
                new_right++;
            }
            if (new_right - new_left - 1 - erased >= 3) {
                erased = new_right - new_left - 1;
            } else {
                break;
            }
            left = new_left;
            right = new_right;
        }
        if (erased > 0) {
            int i = left + 1;
            int j = right;
            while (j < board.size()) {
                board[i++] = board[j++];
            }
            board.resize(board.size() - erased);
        }
        //printf("into %s\n", board.c_str());
    }
    
};
