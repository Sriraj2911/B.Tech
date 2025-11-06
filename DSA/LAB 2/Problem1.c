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

struct ListNode* merge2lists(ListNode* head1, ListNode* head2){
    ListNode dummy;
    ListNode* tail = &dummy;
    dummy.next = NULL;
    
    while(head1 && head2){
        int val1 = head1->val;
        int val2 = head2->val;
        if(val1 < val2){
                tail->next = createNode(val1);
                head1 = head1->next;
        }
        else{
            tail->next = createNode(val2);
            head2 = head2->next;
        }
        tail = tail->next;
    }
    tail->next = head1 ? head1 : head2;
    
    return dummy.next;
}

int main(){
    int n1, n2;
    ListNode* head1 = NULL;
    ListNode* head2 = NULL;

    scanf("%d", &n1);
    int a1[n1];
    for(int i=0; i<n1; i++){
        scanf("%d", &a1[i]);
    }
    scanf("%d", &n2);
    int a2[n2];
    for(int i=0; i<n2; i++){
        scanf("%d", &a2[i]);
    }

    for(int i=0; i<n1; i++){
        head1 = insert(head1, a1[i]);
    }
    for(int i=0; i<n2; i++){
        head2 = insert(head2, a2[i]);
    }

    ListNode* head = merge2lists(head1, head2);
    printList(head);
}