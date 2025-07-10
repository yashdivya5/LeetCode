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
    int length(ListNode* head){
        ListNode* temp=head;
        int count=0;
        while(temp!=NULL){
            count++;
            temp=temp->next;
        }
        return count;
    }
    bool isPalindrome(ListNode* head) {
        if(head==NULL || head->next==NULL) return true;
        int len = length(head);
        int middle = len/2;
        ListNode* temp=head;
        int cnt=0;
        while(cnt<middle){
            cnt++;
            temp=temp->next;
        }
        ListNode* prev=temp;
        ListNode*curr=temp->next;
        ListNode* forward=NULL;
        temp->next = NULL;

        while(curr!=NULL){
            forward=curr->next;
            curr->next=prev;
            prev=curr;
            curr=forward;
        }
        ListNode* start=head;
        ListNode* mid=prev;
        for(int i=0; i<middle;i++){
            if(start->val!=mid->val){
                return false;
            }
            start=start->next;
            mid=mid->next;
        }
        return true;


    }
};