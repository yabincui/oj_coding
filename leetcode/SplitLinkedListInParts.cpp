/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    
    int getLen(ListNode* root) {
        int n = 0;
        while (root) {
            root = root->next;
            n++;
        }
        return n;
    }
    
public:
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        int n = getLen(root);
        vector<ListNode*> res;
        int each = n / k;
        int rem = n % k;
        ListNode* curHead = root;
        for (int i = 0; i < k; ++i) {
            ListNode** p = &curHead;
            int items = each;
            if (rem) {
                rem--;
                items++;
            }
            //printf("i = %d, rem = %d, each = %d, items = %d\n", i, rem, each, items);
            while (items--) {
                p = &(*p)->next;
            }
            ListNode* next = *p;
            *p = nullptr;
            //printf("curHead = %d, next = %d\n", (curHead ? curHead->val : -1), (next ? next->val : -1));
            res.push_back(curHead);
            curHead = next;
        }
        return res;
    }
};
