/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(head==NULL) return NULL;
        ListNode* forward = NULL;
        ListNode* curr=head;
        ListNode* prev=NULL;
        int count=0;

        int nodeCount=0;
        ListNode* temp=head;
        while(temp!=NULL && nodeCount<k){
            temp=temp->next;
            nodeCount++;
        }
        if(nodeCount<k) return head;

        while(curr!=NULL && count<k){
            forward=curr->next;
            curr->next=prev;
            prev=curr;
            curr=forward;
            count++;
        }
        if(forward!=NULL){
            head->next=reverseKGroup(forward,k);
        }
        return prev;
    }
};