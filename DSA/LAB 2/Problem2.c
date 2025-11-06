#include <stdio.h>
#include <stdlib.h>

struct ListNode{
    int val;
    struct ListNode* next;
};

typedef struct ListNode ListNode;

struct ListNode* createNode(int val){
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

struct ListNode* insert(ListNode* head, int val){
    ListNode* curr = head;
    if(!head){
        curr = createNode(val);
        return curr;
    }

    // ListNode* node = createNode(val);
    
    while(curr->next){
        curr = curr->next;
    }
    curr->next = createNode(val);
    return head;
}

void printList(struct ListNode* head){
    while(head){
        printf("%d ", head->val);
        head = head->next;
    }
}

struct ListNode* reversal(ListNode* head){
    ListNode* next = NULL;
    ListNode* curr = head;
    ListNode* prev = NULL;
    while(curr){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

int main(){
    int n;
    scanf("%d", &n);
    int a[n];
    for(int i=0; i<n; i++){
        scanf("%d", &a[i]);
    }

    ListNode* head = NULL;
    for(int i=0; i<n; i++){
        head = insert(head, a[i]);
    }

    head = reversal(head);
    printList(head);
}