// 502. IPO
class Solution {
public:
    struct Node {
      int profit;
      int capital;
      Node(int p, int c) : profit(p), capital(c) {}
    };

    static bool CompareNodeByProfit(Node* n1, Node* n2) {
        if (n1->profit < n2->profit) {
            return true;
        }
        return false;
    }

    static bool CompareNodeByCapital(Node* n1, Node* n2) {
        if (n1->capital < n2->capital) {
            return true;
        }
        return false;
    }


    static int* Profits;
    static int* Capital;

    static bool CompareNodeByProfit1(int n1, int n2) {
        if (Profits[n1] < Profits[n2]) {
            return true;
        }
        return false;
    }

    static bool CompareNodeByCapital1(int n1, int n2) {
        if (Capital[n1] < Capital[n2]) {
            return true;
        }
        return false;
    }

    int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital) {
    	class Solution {
    	public:
    	    struct Node {
    	      int profit;
    	      int capital;
    	      Node(int p, int c) : profit(p), capital(c) {}
    	    };

    	    static bool CompareNodeByProfit(Node* n1, Node* n2) {
    	        if (n1->profit < n2->profit) {
    	            return true;
    	        }
    	        return false;
    	    }

    	    static bool CompareNodeByCapital(Node* n1, Node* n2) {
    	        if (n1->capital < n2->capital) {
    	            return true;
    	        }
    	        return false;
    	    }


    	    static int* Profits;
    	    static int* Capital;

    	    static bool CompareNodeByProfit1(int n1, int n2) {
    	        if (Profits[n1] < Profits[n2]) {
    	            return true;
    	        }
    	        return false;
    	    }

    	    static bool CompareNodeByCapital1(int n1, int n2) {
    	        if (Capital[n1] < Capital[n2]) {
    	            return true;
    	        }
    	        return false;
    	    }

    	    int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital) {
    	        this->Profits = Profits.data();
    	        this->Capital = Capital.data();
    	        vector<int> v(Profits.size());
    	        for (int i = 0; i < Profits.size(); ++i) {
    	            v[i] = i;
    	        }
    	        sort(v.begin(), v.end(), CompareNodeByCapital1);
    	        if (k >= Profits.size() && (v.size() == 0 || W >= v.back())) {
    	            int sum = W;
    	            for (auto& p : Profits) {
    	                sum += p;
    	            }
    	            return sum;
    	        }
    	        priority_queue<int> q;
    	        //priority_queue<int, vector<int>, decltype(&CompareNodeByProfit1)> q(CompareNodeByProfit1);
    	        int w = W;
    	        int node_id = 0;
    	        //return 0;
    	        while (k > 0) {
    	            while (node_id < v.size() && Capital[v[node_id]] <= w) {
    	                q.push(Profits[v[node_id++]]);
    	            }
    	            if (q.empty()) {
    	                break;
    	            }
    	            if (!q.empty()) {
    	                int cur = q.top(); q.pop();
    	                w += cur;
    	                k--;
    	            }
    	        }
    	        return w;
    	    }
    	};

    	    int* Solution::Profits;
    	    int* Solution::Capital;

        this->Profits = Profits.data();
        this->Capital = Capital.data();
        vector<int> v(Profits.size());
        for (int i = 0; i < Profits.size(); ++i) {
            v[i] = i;
        }
        sort(v.begin(), v.end(), CompareNodeByCapital1);
        priority_queue<int> q;
        //priority_queue<int, vector<int>, decltype(&CompareNodeByProfit1)> q(CompareNodeByProfit1);
        int w = W;
        int node_id = 0;
        //return 0;
        while (k > 0) {
            while (node_id < v.size() && Capital[v[node_id]] <= w) {
                q.push(Profits[v[node_id++]]);
            }
            if (q.empty()) {
                break;
            }
            if (!q.empty()) {
                int cur = q.top(); q.pop();
                w += cur;
                k--;
            }
        }
        return w;
    }
};

    int* Solution::Profits;
    int* Solution::Capital;
