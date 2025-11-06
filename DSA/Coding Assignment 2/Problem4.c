#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
    int val;
    struct Node *left, *right, *parent;
};
typedef struct Node Node;

Node* createNode(int val){
    Node* node = malloc(sizeof(Node));
    node->val = val;
    node->left = node->right = node->parent = NULL;
    return node;
}

Node* insertLeft(Node* parent, Node* left){
    if(!parent) return NULL;

    parent->left = left;
    if(left) left->parent = parent;
    return parent;
}
Node* insertRight(Node* parent, Node* right){
    if(!parent) return NULL;

    parent->right = right;
    if(right) right->parent = parent;
    return parent;
}

// To maintain the parent-child node values
struct pair{
    int n1;
    int n2;
};
typedef struct pair pair;


// nodes => Array of node pointers
// arr => Array of parent-child pairs
// n => Size of nodes[]
Node* buildTree(Node** nodes, pair arr[], int n) {
    // Array to maintain whether a node is a child of some other node
    // If a node is not a child of any other node, then that node is the root of the binary tree
    bool isChild[n];
    for(int i=0; i<n; i++) isChild[i] = false;

    for(int i=0; i<n-1; i++){
        Node* parent = nodes[arr[i].n1-1];
        Node* child = nodes[arr[i].n2-1];

        // Insert left if empty, else right
        if(parent->left == NULL) insertLeft(parent, child);
        else insertRight(parent, child);

        isChild[arr[i].n2-1] = true; // Mark as child
    }

    // Find root (node which is never a child)
    for(int i=0; i<n; i++){
        if(!isChild[i]) return nodes[i];
    }
    return NULL; // Should not reach here if tree is valid
}


int DFS(Node* root, int* maxLen) {
    if (!root) return 0;

    int left = DFS(root->left, maxLen);
    int right = DFS(root->right, maxLen);

    int leftPath = 0, rightPath = 0;
    if (root->left && root->left->val == root->val) {
        leftPath = left + 1;
    }
    if (root->right && root->right->val == root->val) {
        rightPath = right + 1;
    }

    // Longest path passing through this node
    if (leftPath + rightPath > *maxLen) {
        *maxLen = leftPath + rightPath;
    }

    // Return the longest single direction path to parent
    return (leftPath > rightPath) ? leftPath : rightPath;
}

int longestEqualPath(Node* root) {
    int maxLen = 0;
    DFS(root, &maxLen);

    return maxLen;
}

int main(){
    int n;
    scanf("%d", &n);
    Node* nodes[n]; // n nodes
    for(int i=0; i<n; i++){
        int val;
        scanf("%d", &val);
        nodes[i] = createNode(val);
    }
    pair arr[n-1]; // n-1 parent-child pairs
    for(int i=0; i<n-1; i++){
        scanf("%d %d", &arr[i].n1, &arr[i].n2);
    }

    Node* root = buildTree(nodes, arr, n);

    int maxLen = longestEqualPath(root);

    printf("%d\n", maxLen+1); // +1 because number of nodes, not number of edges

}

