#include <stdio.h>
#include <stdlib.h>

struct Node{
    int val;
    struct Node* next;
};
typedef struct Node Node;

struct Node* createNode(int val){
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = val;
    node->next = NULL;

    return node;
}

// Implement pop and push functions using a singly linked list
void push(Node** head, int val){
    Node* node = createNode(val);
    node->next = *head;
    *head = node;
}

int pop(Node** head){
    if(!(*head)){
        return -1;
    }
    Node* temp = *head; 
    int result = temp->val;
    *head = temp->next;
    free(temp);
    return result;
}

// To insert a number in the stack int the sorted way
// A helper function for the sort() function
void sortedInsert(Node** head, int val){
    // Base case
    if(!(*head) || val > (*head)->val){
        push(head, val);
        return;
    }

    int temp = pop(head);
    sortedInsert(head, val);
    push(head, temp);
}

void sort(Node** head){
    if(!(*head)){
        return;
    }
    int temp = pop(head);
    sort(head);
    sortedInsert(head, temp);
}

void printStack(Node* head){
    while(head){
        printf("%d ", head->val);
        head = head->next;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    if(n == 0){
        printf("Empty stack, nothing to sort\n");
    }
    Node* head = NULL;
    int arr[n];
    for(int i=0; i<n; i++){
        scanf("%d", arr+i);
        push(&head, arr[i]);
    }
    sort(&head);
    printStack(head);
}