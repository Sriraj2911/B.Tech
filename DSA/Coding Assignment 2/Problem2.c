#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    int val;
    struct Node *right, *left;
};
typedef struct Node Node;

Node* createNode(int val){
    Node* node = malloc(sizeof(Node));
    node->val = val;
    node->right = node->left = NULL;

    return node;
}

// Queue structure
struct Queue {
    struct Node** arr; // Array of node pointers
    int front, rear, size, capacity;
};
typedef struct Queue Queue;

// Initialising the queue data structure
Queue* createQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->arr = (Node**)malloc(capacity * sizeof(Node*));
    q->front = q->size = 0;
    q->rear = capacity - 1;
    q->capacity = capacity;
    return q;
}

int isEmpty(Queue* q) {
    return (q->size == 0);
}

void enqueue(Queue* q, Node* node) {
    q->rear = (q->rear + 1) % q->capacity;
    q->arr[q->rear] = node;
    q->size++;
}

Node* dequeue(Queue* q) {
    struct Node* node = q->arr[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return node;
}

// Level order traversal
void levelOrder(struct Node* root) {
    if (root == NULL) {
        printf("NULL\n");
        return;
    }

    struct Queue* q = createQueue(100); // Assuming a maximum of 100 nodes
    enqueue(q, root);

    while (!isEmpty(q)) {
        struct Node* current = dequeue(q);

        if (current == NULL) {
            printf("NULL ");
            continue; // Don't enqueue children of a NULL
        }

        printf("%d ", current->val);

        // Only enqueue the children of internal nodes
        if (current->left != NULL || current->right != NULL) {
            enqueue(q, current->left);   // Can be NULL
            enqueue(q, current->right);  // Can be NULL
        }
    }

    printf("\n");
}

// preorder => root-left-right
// inorder => left-root-right
Node* buildTree(int in[], int pre[], int n) {
    if (n == 0) return NULL;

    int rootVal = pre[0];

    // Find root in inorder
    int i = 0;
    while (i < n && in[i] != rootVal) i++;
    if (i == n) return NULL; // Root not found in inorder => inconsistent sequences

    Node* root = createNode(rootVal);

    // Sizes of the left and right subtrees
    int left_size = i;
    int right_size = n - i - 1;

    // Recursively build left and right subtrees
    Node* left = buildTree(in, pre + 1, left_size);
    Node* right = buildTree(in + i + 1, pre + left_size + 1, right_size);

    if (left_size > 0 && left == NULL) return NULL;   // Left subtree inconsistent
    if (right_size > 0 && right == NULL) return NULL; // Right subtree inconsistent

    root->left = left;
    root->right = right;

    return root;
}



int main() {
    int n;
    scanf("%d", &n);
    getchar(); // Consume leftover newline

    for (int i=0; i<n; i++) {
        char line[500];
        // Assuming a maximum of 100 nodes
        int in[100], pre[100];
        // To store the indices of the two arrays
        int inCount = 0, preCount = 0;

        // Read inorder sequence
        if (!fgets(line, sizeof(line), stdin)) break;
        char* token = strtok(line, " \n"); // Splits whenver there is space or a newline
        while (token && inCount < 100) {
            // Convert char to in and enter into the inorder array
            in[inCount++] = atoi(token);
            token = strtok(NULL, " \n"); // Stores the next input value
        }

        // Read preorder sequence
        if (!fgets(line, sizeof(line), stdin)) break;
        token = strtok(line, " \n");
        while (token && preCount < 100) {
            pre[preCount++] = atoi(token);
            token = strtok(NULL, " \n");
        }

        Node* root = buildTree(in, pre, inCount);
        printf("Output -> ");
        if(inCount != preCount) printf("ERROR\n"); // Unequal sizes of inorder and preorder arrays is handled here
        else {
            if (root) levelOrder(root);
            else printf("ERROR\n");
        }
    }
}





