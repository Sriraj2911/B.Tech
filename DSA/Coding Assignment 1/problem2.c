#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// If np is taken as an int => It is a 4-bit value
// Addresses are 8-bit values => Type-casting them as int for XOR operations will lead to loss of information and errors
// np is defined as an uintptr_t to avoid the above errors
struct Node{
    int val;
    uintptr_t np;
};
typedef struct Node Node;

Node* createNode(int val){
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = val;
    node->np = (uintptr_t)NULL;
    return node;
}

// Insert node at the start of the linked list
void insert(Node** head, int val){
    Node* node = createNode(val);
    if(!(*head)){
        *head = node;
    }
    else{
        node->np = (uintptr_t)(*head); // node->np = 0 ^ (*head)
        // head->np = next ^ node
        // next = head->np ^ 0;
        (*head)->np ^= (uintptr_t)node;
        *head = node; // Update head
    }
}

void printList(Node *head){
    if(!head){
        printf("Empty list\n");
        return;
    }
    Node* curr = head;
    // Store the prev node
    Node* prev = NULL;
    Node* next;
    while(curr){
        printf("%d ", curr->val);
        next = (Node*)((curr->np) ^ (uintptr_t)prev);
        prev = curr;
        curr = next;
    }
    printf("\n");
}

void search(Node* head, int val){
    Node* curr = head;
    Node* prev = NULL;
    Node* next;
    while(curr){
        if(val == curr->val){
            printf("Element is present\n");
            return;
        }
        next = (Node*)((curr->np)^(uintptr_t)prev);
        prev = curr;
        curr = next;
    }
    printf("Element is not present\n");
}

void delete(Node** head, int val){
    Node* curr = *head;
    Node* prev = NULL;
    Node* next;
    int indicator = 0;
    while(curr){
        next = (Node*)((curr->np)^(uintptr_t)prev);

        if(val == curr->val){
            // Sepaarate cases to avoid errors for prev = NULL and next = NULL
            if(prev){
                prev->np = (prev->np ^ (uintptr_t)curr) ^ (uintptr_t)next;
            }
            else{
                *head = next; // Deleting head
            }

            if(next){
                next->np = (next->np ^ (uintptr_t)curr) ^ (uintptr_t)prev;
            }
            
            free(curr);
            printList(*head);
            return;
        }
        prev = curr;
        curr = next;
    }
    printf("Element is not present\n");

}

int main(){
    Node* head = NULL;
    Node* tail = NULL;
    int k;
    scanf("%d", &k);
    int operations[k]; // Array to store search, insert, delete, and reverse operations
    int ele[k]; // Array to store the values to be searched/inserted/deleted
    int index = 0; // index for the array ele[]
    for(int i=0; i<k; i++){
        scanf("%d", operations+i);
        // For reading the elements to be inserted/searched/deleted
        switch (operations[i])
        {
        case 1:
            scanf("%d", ele+index);
            index++;
            break;
        case 2:
            scanf("%d", ele+index);
            index++;
            break;
        case 3:
            scanf("%d", ele+index);
            index++;
            break;
        // No second input for reversal
        default:
            break;
        }
    }
    int j = 0;
    for(int i=0; i<k; i++){
        switch (operations[i])
        {
        case 1:
            search(head, ele[j]);
            j++;
            break;
        case 2:
            insert(&head, ele[j]);
            printList(head);
            // Assign the tail
            if(head->np == 0){
                tail = head;
            }
            j++;
            break;
        case 3:
            // If the node to be deleted is the tail, then update the tail and then delete
            if(tail->val == ele[j]){
                tail = (Node*)(tail->np);
            }
            delete(&head, ele[j]);
            j++;
            break;
        case 4:
            // Swap head and tail for reversal
            Node* temp = head;
            head = tail;
            tail = temp;
            printList(head);
            break;
        default:
            break;
        }
    }
    
}


