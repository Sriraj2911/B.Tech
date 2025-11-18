#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define t 2
#define MAX 2*t-1
#define MIN t-1

typedef struct Node {
    int key[MAX+1]; // Extra slot to check node overflow
    int count;
    struct Node* children[MAX+1];
} Node;

Node* createNode(int arr[], int count){
    Node* node = malloc(sizeof(Node));
    for(int i=0; i<count; i++){
        node->key[i] = arr[i];
    }
    for(int i=0; i<=MAX; i++){
        node->children[i] = NULL;
    }
    node->count = count;
    return node;
}

Node* searchNode(Node* root, int key) {
    Node* curr = root;
    while (curr) {
        int i;
        for (i = 0; i < curr->count; i++) {
            if (key == curr->key[i])
                return curr;
            else if (key < curr->key[i]) {
                if (!curr->children[i]) return NULL; // Safety check
                curr = curr->children[i];
                i = 0;
                break;
            }
        }
        if (i == curr->count) {
            if (!curr->children[curr->count]) return NULL; // Safety check
            curr = curr->children[curr->count];
        }
    }
    return NULL;
}


// Check if a node is full
bool nodeFull(Node* node){ 
    return (node->count == MAX); 
}

// Check if a node is a leaf node
bool isLeaf(Node* node){
    for(int i=0; i<=node->count; i++){
        if(node->children[i] != NULL) return false;
    }
    return true;
}

void sort(int arr[], int n){
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

// Sort the keys in a node
Node* sortNode(Node* node){
    sort(node->key, node->count);
    return node;
}

// Check if a node has a specific key
bool nodeHas(Node* node, int key){
    for(int i=0; i<node->count; i++){
        if(node->key[i] == key) return true;
    }
    return false;
}

// Get the parent of a node
Node* parent(Node* root, Node* node){
    if (!root || !node || root == node) return NULL;
    Node* p = root;
    int key = node->key[0];
    while (p) {
        for (int i = 0; i <= p->count; i++) {
            if (p->children[i] && nodeHas(p->children[i], key))
                return p;
        }
        int found = 0;
        for (int i = 0; i < p->count; i++) {
            if (key < p->key[i]) {
                if (!p->children[i]) return NULL;
                p = p->children[i];
                found = 1;
                break;
            }
        }
        if (!found) {
            if (!p->children[p->count]) return NULL;
            p = p->children[p->count];
        }
    }
    return NULL;
}

// Function to fix the insert, if needed, in case of count > MAX
Node* fixInsert(Node* root, Node* node){
    Node* p = parent(root, node);
    int to_promote = node->key[node->count / 2];
    // node1 and node2 are the result of split of node
    Node* node1 = malloc(sizeof(Node));
    node1->count = 0;
    for(int i=0; i<=MAX; i++) node1->children[i] = NULL;

    Node* node2 = malloc(sizeof(Node));
    node2->count = 0;
    for(int i=0; i<=MAX; i++) node2->children[i] = NULL;
    // If the node to be split is the root
    if(p == NULL){
        for(int i=0; i<(node->count)/2; i++){
            node1->key[i] = node->key[i];
            node1->count++;
            node1->children[i] = node->children[i];
        }
        node1->children[node1->count] = node->children[(node->count)/2];

        for(int i=(node->count)/2 + 1; i<node->count; i++){
            node2->key[i - (node->count)/2 - 1] = node->key[i];
            node2->count++;
            node2->children[i - (node->count)/2 - 1] = node->children[i];
        }

        Node* newRoot = malloc(sizeof(Node));
        newRoot->key[0] = to_promote;
        newRoot->count = 1;
        newRoot->children[0] = node1;
        newRoot->children[1] = node2;
        for(int i=2; i<=MAX; i++) newRoot->children[i] = NULL;
        root = newRoot;
        return root;
    }

    int idx = 0;
    for(idx = 0; idx <= p->count; idx++){
        if(p->children[idx] == node) break;
    }

    for(int i=0; i<(node->count)/2; i++){
        node1->key[i] = node->key[i];
        node1->count++;
        node1->children[i] = node->children[i];
    }
    node1->children[node1->count] = node->children[(node->count)/2];

    for(int i=(node->count)/2 + 1; i<node->count; i++){
        node2->key[i - (node->count)/2 - 1] = node->key[i];
        node2->count++;
        node2->children[i - (node->count)/2 - 1] = node->children[i];
    }

    // Ensure space before insertion
    for(int i = p->count; i > idx; i--){
        p->key[i] = p->key[i-1];
        p->children[i+1] = p->children[i];
    }

    p->key[idx] = to_promote;
    p->children[idx] = node1;
    p->children[idx+1] = node2;
    p->count++;

    if(p->count <= MAX) return root;
    return fixInsert(root, p); // Recursive call
}
// Straight-forward insert
Node* insertNode(Node* root, int key){
    if(!root) return createNode(&key, 1);
    
    Node* curr = root;
    while (curr && !isLeaf(curr)) {
        int i;
        for (i = 0; i < curr->count; i++) {
            if (key < curr->key[i]) {
                curr = curr->children[i];
                i = 0;
                break;
            } else if (key == curr->key[i]) {
                return root;
            }
        }
        if (i == curr->count){
            if(curr->children[curr->count]) curr = curr->children[curr->count];
            else break;
        } 
    }
    // curr is now the leaf node in which key should be inserted
    if(curr->count <= MAX){
        curr->key[curr->count++] = key;
    }
    sortNode(curr);

    if(curr->count <= MAX) return root;
    return fixInsert(root, curr);
}
// Build the BTree using repeated insertNode() calls
Node* buildBTree(int *nodes, int n){
    Node* root = NULL;
    for(int i=0; i<n; i++){
        root = insertNode(root, nodes[i]);
    }
    return root;
}

// Function to fix the insert, if needed, in case of count < MIN
Node* fixDelete(Node* root, Node* node){
    Node* p = parent(root, node);
    if (!p) return root; 

    int idx;
    for(idx=0; idx<=p->count; idx++){
        if(p->children[idx] == node) break;
    }

    Node* left = (idx > 0) ? p->children[idx-1] : NULL;
    // If left has keys which can be taken without making count < MIN
    if(left && left->count > MIN){
        node->key[node->count++] = p->key[idx-1];
        sortNode(node);
        p->key[idx-1] = left->key[--left->count];
        return root;
    }

    // Merging if keys can't be taken from left
    if(left){
        for(int i=0; i<left->count; i++){
            node->key[node->count++] = left->key[i]; // Merge left and node
        }
        node->key[node->count++] = p->key[idx-1]; // Bring down separator node from parent
        p->count--;
        for(int i=idx-1; i<p->count; i++){
            // Adjust keys and children of p after sending one key to node
            p->key[i] = p->key[i+1];
            p->children[i] = p->children[i+1];
        }
        if(p->count < MIN) return fixDelete(root, p); // Recursive call
    }
    return root;
}

Node* deleteNode(Node* root, int key){
    Node* node = searchNode(root, key);
    if(!node) return root;

    int idx;
    for(idx=0; idx<node->count; idx++){
        if(node->key[idx] == key) break;
    }
    // If the node from which key is deleted is a leaf node
    if(isLeaf(node)){
        for(int i=idx; i<node->count-1; i++){
            node->key[i] = node->key[i+1];
        }
        node->count--;
        if(node->count >= MIN) return root;
        return fixDelete(root, node);
    }
    // If the node from which key is deleted is an internal node 
    else {
        Node* left = node->children[idx];
        node->key[idx] = left->key[--left->count];
        if(left->count < MIN) root = fixDelete(root, left);
        return root;
    }
}

void levelOrder(Node* root){
    if (!root) return;
    Node* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        int levelCount = rear - front;
        for (int i = 0; i < levelCount; i++) {
            Node* curr = queue[front++];
            printf("[");
            for (int j = 0; j < curr->count; j++){
                // if(curr->key[i] != 0) 
                printf("%d", curr->key[j]);
                if (j != curr->count - 1) printf(", ");
            }
            printf("] ");
            for (int j = 0; j <= curr->count; j++){
                if (curr->children[j]) queue[rear++] = curr->children[j];
            }
        }
        printf("\n");
    }
}

int main(){
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i=0; i<n; i++) scanf("%d", arr+i);

    Node* root = buildBTree(arr, n);

    int choice = 1, key;
    while(choice != 0){
        scanf("%d", &choice);
        switch (choice){
            case 0:
                printf("Exiting\n");
                break;
            case 1:
                scanf("%d", &key);
                if(searchNode(root, key)) printf("%d present\n", key);
                else printf("%d not present\n", key);
                break;
            case 2:
                scanf("%d", &key);
                if(searchNode(root, key))
                    printf("%d is already present. So no need to insert\n", key);
                else{
                }
                root = insertNode(root, key);
                printf("%d inserted.\n", key);
                break;
            case 3:
                scanf("%d", &key);
                if(!searchNode(root, key))
                    printf("%d not present. So it cannot be deleted\n", key);
                else{
                    root = deleteNode(root, key);
                    printf("%d deleted\n", key);
                }
                break;
            case 4:
                levelOrder(root);
                break;
            default:
                printf("Invalid query\n");
                break;
        }
    }
}
