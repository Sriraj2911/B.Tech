#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *left;
    struct Node *right;
    int height;
}Node;

Node* createNode(int data){
    Node* node = malloc(sizeof(Node));
    node->data = data;
    node->right = node->left = NULL;
    node->height = 1;
    return node;
}

int height(Node* node){
    if(!node) return 0;
    return node->height;
}

int heightDiff(Node* node){
    if(node == NULL) return 0;
    return height(node->left) - height(node->right);
}

Node* rightRotate(Node* a){
    Node* b = a->left;
    Node* T2 = b->right;

    b->right = a;
    a->left = T2;

    a->height = height(a->right)>height(a->left) ? (1+height(a->right)) : (1+height(a->left));
    b->height = height(b->right)>height(b->left) ? (1+height(b->right)) : (1+height(b->left));

    return b;
}

Node* leftRotate(Node* a){
    Node* b = a->right;
    Node* T2 = b->left;

    b->left = a;
    a->right = T2;

    a->height = height(a->right)>height(a->left) ? (1+height(a->right)) : (1+height(a->left));
    b->height = height(b->right)>height(b->left) ? (1+height(b->right)) : (1+height(b->left));

    return b;
}



Node* searchNode(Node* root, int key){
    Node* curr = root;
    while(curr){
        if(key < curr->data){
            curr = curr->left;
        }
        else if(key > curr->data){
            curr = curr->right;
        }
        else{
            return curr;
        }
    }
    return NULL;
}

Node* insertNode(Node* root, int key){
    if(root==NULL) return createNode(key);
    
    if(key < root->data){
        root->left = insertNode(root->left, key);
    }
    else if(key > root->data){
        root->right = insertNode(root->right, key);
    }
    else{
        return root; // No duplicates
    }

    root->height = height(root->right)>height(root->left) ? (1+height(root->right)) : (1+height(root->left));
    int balance = heightDiff(root);

    if(balance > 1 && key < root->left->data){
        return rightRotate(root);
    }
    if(balance < -1 && key > root->right->data){
        return leftRotate(root);
    }
    if(balance > 1 && key > root->left->data){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance < -1 && key < root->right->data){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

// Build the AVL tree with repeated insertNode calls
Node* buildAVL(int arr[], int n){
    Node* root = NULL;
    for(int i=0; i<n; i++){
        root = insertNode(root, arr[i]);
    }
    return root;
}

Node* minNode(Node* node){
    Node* curr = node;
    while(curr->left){
        curr = curr->left;
    }
    return curr;
}

Node* deleteNode(Node* root, int key){
    if(!root) return NULL;

    if(key < root->data){
        root->left = deleteNode(root->left, key);
    }
    else if(key > root->data){
        root->right = deleteNode(root->right, key);
    }
    else{
        // Found the node to delete
        // Case-1: One or zero children
        if(root->left==NULL || root->right==NULL){
            Node* temp = root->left ? root->left : root->right;

            if(!temp){
                // No children
                temp = root;
                root = NULL;
            }
            else{
                *root = *temp; // Copy the contents of the child
            }
            free(temp);
        }
        // Case-2: Two children
        else{
            Node* temp = minNode(root->right); // Successor node of root
            root->data = temp->data; // Copy the data of the successor node
            root->right = deleteNode(root->right, temp->data); // The successor node has either 1 or 0 children
        }
    }
    // Balancing the resulting tree
    if(!root) return root; // If the original tree had only one node

    root->height = height(root->right)>height(root->left) ? (1+height(root->right)) : (1+height(root->left));

    int balance = heightDiff(root);

    if(balance > 1 && heightDiff(root->left) >= 0){
        return rightRotate(root);
    }
    if(balance > 1 && heightDiff(root->left) < 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance < -1 && heightDiff(root->right) <= 0){
        return leftRotate(root);
    }
    if(balance < -1 && heightDiff(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

// Queue node for BFS
typedef struct QNode {
    Node* node;
    struct QNode* next;
} QNode;

typedef struct {
    QNode* front;
    QNode* rear;
} Queue;

Queue* createQueue() {
    Queue* q = malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue* q, Node* node) {
    QNode* temp = malloc(sizeof(QNode));
    temp->node = node;
    temp->next = NULL;
    if (!q->rear)
        q->front = q->rear = temp;
    else {
        q->rear->next = temp;
        q->rear = temp;
    }
}

Node* dequeue(Queue* q) {
    if (!q->front) return NULL;
    QNode* temp = q->front;
    Node* n = temp->node;
    q->front = temp->next;
    if (!q->front) q->rear = NULL;
    free(temp);
    return n;
}

int isEmpty(Queue* q) {
    return q->front == NULL;
}

void levelOrder(Node* root) {
    if (!root) return;
    Queue* q = createQueue();
    enqueue(q, root);
    enqueue(q, NULL);  // NULL marker for level-end

    while (!isEmpty(q)) {
        Node* node = dequeue(q);
        if (node == NULL) {
            printf("\n");
            if (!isEmpty(q)) enqueue(q, NULL);
        } else {
            printf("%d ", node->data);
            if (node->left) enqueue(q, node->left);
            if (node->right) enqueue(q, node->right);
        }
    }
    free(q);
}

int main(){
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i=0; i<n; i++){
        scanf("%d", arr+i);
    }

    Node* root = buildAVL(arr, n);

    int choice = 1;
    int key;

    while(choice != 0){
        scanf("%d", &choice);
        if(choice>=1 && choice<=3){
            scanf("%d", &key);
        }
        switch (choice)
        {
            case 0:
                printf("Exiting\n");
                break;
            case 1:
                Node* node = searchNode(root, key);
                if(node) printf("%d present\n", key);
                else printf("%d not present\n", key);
                break;
            case 2:
                if(searchNode(root, key)){
                    printf("%d is already present. So no need to insert\n", key);
                }
                else{
                    root = insertNode(root, key);
                    printf("%d inserted.\n", key);
                }
                break;
            case 3:
                if(!searchNode(root, key)){
                    printf("%d not present. So it cannot be deleted\n", key);
                }
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
