/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 class Solution {
    
    ListNode* head;
    int n;
    
public:
    /** @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node. */
    Solution(ListNode* head) {
        this->head = head;
        for (n = 0; head != nullptr; ++n) {
            head = head->next;
        }
    }
    
    /** Returns a random node's value. */
    int getRandom() {
        ListNode* cur = head;
        int move = rand() % n;
        while (move--) {
            cur = cur->next;
        }
        return cur->val;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(head);
 * int param_1 = obj.getRandom();
 */