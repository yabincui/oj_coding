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
    ListNode* oddEvenList(ListNode* head) {
        ListNode* odd;
        ListNode* even = nullptr;
        ListNode** podd = &odd;
        ListNode** peven = &even;
        while (head != nullptr) {
            *podd = head;
            podd = &head->next;
            head = head->next;
            if (head != nullptr) {
                *peven = head;
                peven = &head->next;
                head = head->next;
            }
        }
        *podd = even;
        *peven = nullptr;
        return odd;
    }
};