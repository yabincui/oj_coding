class Twitter {
    
    struct Node {
        int id;
        int no;
        Node(int id, int no) : id(id), no(no) {}
    };
    
    struct User {
        vector<Node> tweets;
        unordered_set<int> followed_users;
    };
    
    int cur_number;
    unordered_map<int, User> user_map;
    
    User* getUser(int userId) {
        auto it = user_map.find(userId);
        if (it == user_map.end()) {
            auto res = user_map.insert(make_pair(userId, User()));
            it = res.first;
        }
        return &it->second;
    }
    
    struct QueueNode {
        Node* node;
        Node* begin;
        
        QueueNode(Node* node, Node* begin) : node(node), begin(begin) {}
    };
    
    static bool compareNode(const QueueNode& n1, const QueueNode& n2) {
        return n1.node->no < n2.node->no;
    }
    
public:
    /** Initialize your data structure here. */
    Twitter() {
        cur_number = 0;
    }
    
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        User* user = getUser(userId);
        user->tweets.push_back(Node(tweetId, cur_number++));
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        priority_queue<QueueNode, vector<QueueNode>, decltype(&compareNode)> q(compareNode);
        User* user = getUser(userId);
        if (!user->tweets.empty()) {
            q.push(QueueNode(&user->tweets.back(), &user->tweets[0]));
        }
        for (int id : user->followed_users) {
            user = getUser(id);
            if (!user->tweets.empty()) {
                q.push(QueueNode(&user->tweets.back(), &user->tweets[0]));
            }
        }
        vector<int> res;
        while (!q.empty() && res.size() < 10) {
            QueueNode cur = q.top(); q.pop();
            res.push_back(cur.node->id);
            if (cur.node != cur.begin) {
                cur.node--;
                q.push(cur);
            }
        }
        return res;
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if (followerId == followeeId) return;
        User* follower = getUser(followerId);
        follower->followed_users.insert(followeeId);
    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        User* follower = getUser(followerId);
        follower->followed_users.erase(followeeId);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter obj = new Twitter();
 * obj.postTweet(userId,tweetId);
 * vector<int> param_2 = obj.getNewsFeed(userId);
 * obj.follow(followerId,followeeId);
 * obj.unfollow(followerId,followeeId);
 */

 