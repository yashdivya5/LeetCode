/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    void insertAtTail(Node* &head, Node* &tail, int d){
        Node* newNode=new Node(d);
        if(head==NULL){
            head=newNode;
            tail=newNode;
            return;
        }
        else{
            tail->next=newNode;
            tail=newNode;
        }
    }
    Node* copyRandomList(Node* head) {
        //step1: clone the LL with next
        Node* cloneHead=NULL;
        Node* cloneTail=NULL;
        Node* temp=head;
        while(temp!=NULL){
            insertAtTail(cloneHead,cloneTail,temp->val);
            temp=temp->next;
        }
        //Step2: create a map
        unordered_map<Node*,Node*>oldToNewNode;
        Node* originalNode=head;
        Node* cloneNode=cloneHead;

        while(originalNode!=NULL && cloneNode!=NULL){
            oldToNewNode[originalNode]=cloneNode;
            originalNode=originalNode->next;
            cloneNode=cloneNode->next;
        }
        originalNode=head;
        cloneNode=cloneHead;

        while(originalNode!=NULL){
            cloneNode->random=oldToNewNode[originalNode->random];
            cloneNode=cloneNode->next;
            originalNode=originalNode->next;
        }
        return cloneHead;
    }
};