#include <stdio.h>
#include <stdlib.h>



struct Node{
    int val;
    struct Node* next;
    struct Node* prev;
};
typedef struct Node Node;

struct Node* createNode(int val){
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = val;
    node->next = NULL;
    node->prev = NULL;
    
    return node;
}

int length = 0;
// Build a linked list where head->prev=tail and tail->next=middle
struct Node* insertNode(Node* head, int val){
    Node* node = createNode(val);
    if(!head){
        head = node;
        length++;
        return head;
    }
    if(!(head->next)){
        head->next = node;
        node->prev = head;
        // head->prev = tail
        head->prev = node;
        // tail->next = middle
        node->next = head;
        length++;
        return head;
    }
    Node* tail = head->prev;
    // Define a new node and initialise it to the middle node of the list before inserting a new node 
    Node* midBefore = tail->next;
    tail->next = NULL;
    // Insert the new node at the end, and update tail
    tail->next = node;
    node->prev = tail;
    tail = node;
    head->prev = tail;
    length++;
    // The middle node of the new list changes based on the length of the list
    if(length%2==1){
        tail->next = midBefore->next;
    }
    else{
        tail->next = midBefore;
    }
    return head;
}

struct Node* push(Node* head, int ele){
    head = insertNode(head, ele); // The insertNode() function will handle everything
    return head;
}

int pop(Node** head0){
    Node* head = *head0;
    if(length == 0){
        return -1;
    }
    if(length == 1){
        Node* temp = head;
        head = NULL;
        length--;
        return temp->val;
    }
    if(length == 2){
        // The list after pop will have only the head
        Node* node = createNode(head->val);
        length--;
        return node->val;
    }
    Node* tail = head->prev;
    Node* midBefore = tail->next; // The middle node before popping
    tail->next = NULL;
    head->prev = tail->prev; // Update the tail
    tail->prev->next = NULL;
    tail->prev = NULL;
    length--;
    // The new middle node depends on the length of the list
    if(length%2==1){
        head->prev->next = midBefore;
    }
    else{
        head->prev->next = midBefore->prev;
    }
    *head0 = head;
    return tail->val;
}

int findMiddle(Node* head){
    if(length==0){
        // Returns -2 to avoid overlap with the -1 in pop() function
        return -2;
    }
    if(length==1){
        return head->val;
    }
    Node* middle = head->prev->next;
    return middle->val;
}

int deleteMiddle(Node** head0){
    Node* head = *head0;
    if(length==0){
        // Returns -2 to avoid overlap with the -1 in pop() function
        return -2;
    }
    if(length==1){
        Node* temp = head;
        head = NULL;
        length--;
        return temp->val;
    }
    if(length==2){
        // Only the tail will remain
        Node* node = createNode(head->next->val);
        int result = head->val;
        // Update the remainging node to be the head
        head = node;
        length--;
        return result;
    }
    Node* midBefore = head->prev->next; // Middle element in the stack before deletion
    Node* prev = midBefore->prev;
    Node* next = midBefore->next;
    Node* tail = head->prev;
    int result = midBefore->val;
    // Delete the middle node
    prev->next = next;
    next->prev = prev;
    midBefore->next = NULL;
    midBefore->prev = NULL;
    length--;
    // Link the tail and the latest middle node 
    if(length%2==1){
        tail->next = next;
    }
    else{
        tail->next = prev;
    }
    *head0 = head;
    return result;
}

int main(){
    int n; // A variable for number of operations
    scanf("%d", &n);
    int index = 0; // A variable to keep track of the indices of the outputs
    int results[n]; // An array to store the outputs in 
    for(int i=0; i<n; i++){
        // Set the value which is less likely to be an input
        results[i] = -1000;
    }
    int operation; // Variable for operations
    Node* head = NULL;
    while(n){
        scanf("%d", &operation);
        switch (operation)
        {
        case 1:
            int ele;
            scanf("%d", &ele);
            head = push(head, ele);
            // No increment in 'input' as there there is no output for pop
            break;
        case 2:
            results[index] = pop(&head);
            index++;
            break;
        case 3:
            results[index] = findMiddle(head);
            index++;
            break;
        case 4:
            results[index] = deleteMiddle(&head);
            index++;
            break;
        default:
            break;
        }
        n--;
    }
    for(int i=0; i<index; i++){
        // Output for popping an empty stack
        if(results[i]==-1){
            printf("Stack Underflow\n");
        }
        // Output for finding/deleting middle value of an empty stack
        else if(results[i]==-2){
            printf("Stack Empty\n");
        }
        else{
            printf("%d\n", results[i]);
        }
    }
}