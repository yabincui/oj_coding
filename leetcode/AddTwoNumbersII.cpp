/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        vector<int> v1, v2;
        while (l1) {
            v1.push_back(l1->val);
            l1 = l1->next;
        }
        while (l2) {
            v2.push_back(l2->val);
            l2 = l2->next;
        }
        ListNode* res = nullptr;
        int add = 0;
        for (int i = v1.size() - 1, j = v2.size() - 1; i >= 0 || j >= 0 || add > 0;) {
            if (i >= 0) add += v1[i--];
            if (j >= 0) add += v2[j--];
            ListNode* temp = new ListNode(add % 10);
            add /= 10;
            temp->next = res;
            res = temp;
        }
        return res;
    }
};
