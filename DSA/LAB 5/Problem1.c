#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};
typedef struct Node Node;

// int arr[] = {12, 31, 34, 56, 78, 89, 91, 32, 56, 81, 100, 2, 55, 21, 99, 121, 67};

Node* createNode(int data){
    Node* node = malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;

    return node;
}

Node* buildBST(Node* root, int *arr, int n){
    int length = sizeof(arr)/sizeof(int);
    for(int i=1; i<n; i++){
        Node* curr = root;
        while(curr){
            if(arr[i] <= curr->data){
                if(curr->left){
                    curr = curr->left;
                }
                else{
                    curr->left = createNode(arr[i]);
                    break;
                }
            }
            else{
                if(curr->right){
                    curr = curr->right;
                }
                else{
                    curr->right = createNode(arr[i]);
                    break;
                }
            }
        }
    }

    return root;
}

Node* search(Node* root, int key){
    if(!root) return NULL;

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

Node* insert(Node* root, int key){
    if(!root){
        root = createNode(key);
        return root;
    }

    Node* curr = root;
    while(curr){
        if(key < curr->data){
            if(curr->left){
                curr = curr->left;
            }
            else{
                curr->left = createNode(key);
                return root;
            }
        }
        else if(key > curr->data){
            if(curr->right){
                curr = curr->right;
            }
            else{
                curr->right = createNode(key);
                return root;
            }
        }
        else{
            Node* node = createNode(key);
            node->left = curr->left;
            curr->left = node;
            return root;
        }
    }
}

Node* successor(Node* root, int key){
    if(!root) return NULL;
    if(root->right == NULL) return NULL;    // No value is greater than root->data

    Node* curr = root->right;
    while(curr->left){
        curr = curr->left;
    }
    return curr;
}

Node* minimum(Node* root){
    Node* curr = root;
    while(curr->left){
        curr = curr->left;
    }

    return curr;
}

Node* delete(Node* root, int key){
    if(!root) return NULL;

    Node* node = search(root, key); // Pointer to the node to be deleted

    // Case-1: If the node to be deleted is a leaf node
    if(node->left==NULL && node->right==NULL){
        if(root->data == key){
            return NULL;
        }
        Node* curr = root;
        while(curr->left!=node && curr->right!=node){
            if(key > curr->data){
                curr = curr->right;
            }
            else{
                curr = curr->left;
            }
        }
        if(curr->right == node){
            curr->right = NULL;
        }
        else if (curr->left == node){
            curr->left = NULL;
        }
        return root;
    }

    // Case-2: If the node to be deleted has exactly one child
    if((node->left==NULL && node->right!=NULL) || (node->left!=NULL && node->right==NULL)){
        if(root->data == key){
            if(root->left != NULL){
                root = root->left;
                return root;
            }
            if(root->right != NULL){
                root = root->right;
                return root;
            }
        }
        Node* curr = root;
        while(curr->left!=node && curr->right!=node){
            if(key > curr->data){
                curr = curr->right;
            }
            else{
                curr = curr->left;
            }
        }
        // The node to be deleted is the right child of its parent and it has a right child
        if(curr->right==node && node->right!=NULL){
            curr->right = node->right;
            node->right = NULL;
        }
        // The node to be deleted is the right child of its parent and it has a left child
        if(curr->right==node && node->left!=NULL){
            curr->right = node->left;
            node->left = NULL;
        }
        // The node to be deleted is the left child of its parent and it has a right child
        if(curr->left==node && node->right!=NULL){
            curr->left = node->right;
            node->right = NULL;
        }
        // The node to be deleted is the left child of its parent and it has a left child
        if(curr->left==node && node->left!=NULL){
            curr->left = node->left;
            node->left = NULL;
        }
        return root;
    }

    // Case-3: If the node to be deleted has two children
    if(node->left && node->right){
        Node* min = minimum(node);
        int data = min->data;
        root = delete(root, data);
        node->data = data;
        return root;
    }
}

//---------------------------------------------- PRINTING THE TREE ---------------------------------------//
struct QueueNode {
    struct Node* treeNode;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode *front, *rear;
};

struct Queue* createQueue() {
    struct Queue* q = malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(struct Queue* q, struct Node* node) {
    struct QueueNode* temp = malloc(sizeof(struct QueueNode));
    temp->treeNode = node;
    temp->next = NULL;
    if (!q->rear) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

struct Node* dequeue(struct Queue* q) {
    if (!q->front) return NULL;
    struct QueueNode* temp = q->front;
    q->front = q->front->next;
    if (!q->front) q->rear = NULL;
    struct Node* node = temp->treeNode;
    free(temp);
    return node;
}

int isEmpty(struct Queue* q) {
    return q->front == NULL;
}

void printBST(struct Node* root) {
    if (!root) {
        printf("Empty tree\n");
    };
    struct Queue* q = createQueue();
    enqueue(q, root);
    while (!isEmpty(q)) {
        struct Node* node = dequeue(q);
        printf("%d ", node->data);
        if (node->left) enqueue(q, node->left);
        if (node->right) enqueue(q, node->right);
    }
}
// --------------------------------------------------------------------------------------------------------//


int main(){
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i=0; i<n; i++){
        scanf("%d", arr+i);
    }
    Node* root = createNode(arr[0]);
    root = buildBST(root, arr, n);
    printf("Enter your choice:\n");
    printf("1 - Search for an element\n");
    printf("2 - Insert an element\n");
    printf("3 - Find the successor of an element\n");
    printf("4 - Delete an element\n");
    printf("0 - Exit\n");
    while(root){
        int input;
        int key;
        scanf("%d", &input);
        if(input == 0) break;
        if(input == 1){
            scanf("%d", &key);
            Node* node = search(root, key);
            if(!node){
                printf("Key %d not found\n", key);
                continue;
            }
            else{
                printf("Key %d found\n", node->data);
            }
        }
        if(input == 2){
            scanf("%d", &key);
            root = insert(root, key);
            printBST(root);
            printf("\n");
        }
        if(input == 3){
            scanf("%d", &key);
            Node* node = successor(root, key);
            if(!node) {
                printf("The given node has no successor\n");
                continue;
            }
            else{
                printf("The successor node has the key %d\n", node->data);
            }
        }
        if(input == 4){
            scanf("%d", &key);
            Node* node = search(root, key);
            if(!node){
                printf("The node to be deleted is not present in the BST\n");
                continue;
            }
            else{
                root = delete(root, key);
                printBST(root);
                printf("\n");
            }
        }
    }
}



