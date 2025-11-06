#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct Node{
    int val;
    struct Node *right, *left, *parent;
};
typedef struct Node Node;

Node* createNode(int val){
    Node* node = malloc(sizeof(Node));
    node->val = val;
    node->right = node->left = node->parent = NULL;

    return node;
}

// Array to store the nodes
Node* nodes[1000]; // Assume a maximum of 1000 nodes in the tree
int idx = 0; 

// preorder => root-left-right
// inorder => left-root-right
Node* buildTree(int in[], int pre[], int n) {
    if (n == 0) {
        // nodes[idx++] = NULL;
        return NULL;
    }
    int rootVal = pre[0];

    // Find root in inorder
    int i = 0;
    while (i < n && in[i] != rootVal) i++;
    if (i == n) return NULL; // Root not found in inorder => inconsistent sequences

    Node* root = createNode(rootVal);
    nodes[idx++] = root;

    // Sizes of the left and right subtrees
    int left_size = i;
    int right_size = n - i - 1;

    // Recursively build left and right subtrees
    Node* left = buildTree(in, pre + 1, left_size);
    Node* right = buildTree(in + i + 1, pre + left_size + 1, right_size);

    if (left_size > 0 && left == NULL) return NULL;   // Left subtree inconsistent
    if (right_size > 0 && right == NULL) return NULL; // Right subtree inconsistent

    root->left = left;
    if(left) left->parent = root;
    
    root->right = right;
    if(right) right->parent = root;
    

    return root;
}

// Function to compute height of a binary tree
int height(Node* root) {
    if (root == NULL)
        return 0; // height of empty tree = 0

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}


// The depth of the node will be stored at depths[node->val]
int depths[1000]; // Assuming the maximum value of a node is 1000, minimum is 0, and no two nodes have the same value

void populateDepths(Node* node, int currentDepth){
    if(node == NULL) return;
    depths[node->val] = currentDepth;

    // The children of node are at a depth of 1 + depth(node)
    populateDepths(node->left, currentDepth+1);
    populateDepths(node->right, currentDepth+1);
}

int dist(Node* u, Node* v){
    int d1 = 0;
    int d2 = 0;
    Node* curr1 = u;
    Node* curr2 = v;

    // Bring the two nodes to the same depth
    while(curr1 && curr2 && depths[curr1->val] != depths[curr2->val]){
        if(depths[curr1->val] > depths[curr2->val]){
            curr1 = curr1->parent;
            d1++;
        }
        else{
            curr2 = curr2->parent;
            d2++;
        }
    }

    while(curr1 && curr2 && curr1 != curr2){
        curr1 = curr1->parent;
        d1++;
        curr2 = curr2->parent;
        d2++;
    }
    // d1 = distance between u and LSA(u,v)
    // d2 = distance between v and LSA(u,v)
    return d1 + d2;
}




int mostFreqDist(Node* root){
    populateDepths(root, 0); // This populates the depths[] with depths of all nodes of the tree rooted at root

    int max_distance = 2 * height(root); // Maximum possible distance between two nodes
    int *freq = calloc(max_distance+1, sizeof(int)); // An array which stores the frequency of the distances
    
    for(int i=0; i<idx; i++){
        for(int j=i+1; j<idx; j++){
            if(j == i) continue;
            Node* u = nodes[i];
            Node* v = nodes[j];
            if(u && v) freq[dist(u, v)]++;
            
        }
    }
    int max_freq = 0;
    for(int i=0; i<max_distance+1; i++){
        if(freq[i] > max_freq){
            max_freq = freq[i];
        }
    }
    for(int i=0; i<=max_distance; i++){
        if(max_freq == freq[i]) return i;
    }

}

int main() {
    int n;
    scanf("%d", &n);
    int pre[n];
    int in[n];
    for(int i=0; i<n; i++){
        scanf("%d", pre+i);
    }
    for(int i=0; i<n; i++){
        scanf("%d", in+i);
    }
    
    Node* root = buildTree(in, pre, n);
    if(root){
        int result = mostFreqDist(root);
        printf("%d\n", result);
    }
    else{
        printf("ERROR: The inorder and preorder traversals entered do not give a valid binary tree\n");
    }
}





