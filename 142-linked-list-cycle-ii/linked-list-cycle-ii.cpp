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
    ListNode* isCycle(ListNode* head){
        ListNode* fast=head;
        ListNode* slow=head;
        if(fast==NULL || fast->next==NULL) return NULL;
        while(fast!=NULL && fast->next!=NULL){
            fast=fast->next->next;
            slow=slow->next;
            if(fast==slow){
                return slow;
            }
        }
        return NULL;
    }
    ListNode *detectCycle(ListNode *head) {
        if(head==NULL) return NULL;
        ListNode* intersection = isCycle(head);
        ListNode* slow=head;
        if(intersection==NULL) return NULL;
        while(slow!=intersection){
            slow=slow->next;
            intersection=intersection->next;
        }
        return slow;
    }
};