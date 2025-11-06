#include <stdio.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    bool black;
    struct Node *left, *right;
}Node;

void rb_enumerate(Node* root, int a, int b){
    if(!root) return;
    // If the root value is greater than both a and b, then function call with root->left, as all the nodes in root->right are not [a, b]
    if(root->data > b){
        rb_enumerate(root->left, a, b);
    }
    // Root value is in the range [a, b]
    else if(root->data>=a && root->data<=b){
        // This logic is similar to that of inorder traversal, except here all the nodes are not visited, only the ones in the range
        if(root->data > a){
            rb_enumerate(root->left, a, b);
        }
        printf("%d ", root->data);
        if(root->data < b){
            rb_enumerate(root->right, a, b);
        }
    }
    // If the root value is less than both a and b, then function call with root->right, as all the nodes in root->left are not in [a, b]
    else if(root->data < a){
        rb_enumerate(root->right, a, b);
    }
}