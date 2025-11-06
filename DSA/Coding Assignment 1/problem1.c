#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node* next;
};
typedef struct Node Node;

Node* createNode(int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = val;
    node->next = NULL;
    return node;
}

void printList(Node* head) {
    while (head) {
        printf("%d, ", head->val);
        head = head->next;
    }
}

int main() {
    int arr[1000];
    int count = 0;
    Node* head = NULL;
    Node* tail = NULL; // to optimize insertion
    
    // Read input and create initial list with tail pointer for O(1) insertion
    for (int i = 0; i < 1000; i++) {
        scanf("%d,", &arr[i]);
        if (arr[i] == -1) {
            break;
        }
        Node* node = createNode(arr[i]);
        if (!head) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        count++;
    }

    // If less than 2 elements, no rearrangement needed
    if (!head || !head->next) {
        printList(head);
        return 0;
    }

    // Split list into odd and even indexed nodes
    Node* oddHead = head;
    Node* evenHead = head->next;
    Node* oddTail = oddHead;
    Node* evenTail = evenHead;

    Node* current = evenHead->next;
    int isOdd = 1; // Flag to alternate between odd and even index
    while (current) {
        if (isOdd) {
            oddTail->next = current;
            oddTail = current;
        } else {
            evenTail->next = current;
            evenTail = current;
        }
        current = current->next;
        isOdd = !isOdd;
    }

    // Merge the two lists
    oddTail->next = evenHead;
    evenTail->next = NULL;

    printList(oddHead);

    return 0;
}
