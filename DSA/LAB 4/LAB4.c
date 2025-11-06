#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};
typedef struct Node Node;

Node* createNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* insertLeft(Node* root, Node* node){
    if(!root){
        return node;
    }
    root->left = node;
    return root;
}
Node* insertRight(Node* root, Node* node){
    if(!root){
        return node;
    }
    root->right = node;
    return root;
}

void preorder(Node* root){
    if(!root) return;

    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}
void inorder(Node* root){
    if(!root) return;
    
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
void postorder(Node* root){
    if(!root) return;

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

Node* pre_in(int *pre, int *in, int n){
    // Base case
    if(n == 0) return NULL;

    Node* root = createNode(pre[0]);
    // Find the index of the root in inorder
    int i = 0;
    while(in[i] != pre[0]){
        i++;
    }
    int left_size = i; // Size of the left subtree
    int right_size = n-i-1; // Size of the right subtree

    int in_left[left_size]; // Inorder traversal of the left subtree
    int in_right[right_size]; // Inorder traversal of the right subtree

    int pre_left[left_size]; // Preorder traversal of the left subtree
    int pre_right[right_size]; // Preorder traversal of the right subtree

    for(int i=0; i<left_size; i++){
        in_left[i] = in[i];
        pre_left[i] = pre[i+1];
    }

    for(int i=0; i<right_size; i++){
        in_right[i] = in[i+left_size+1];
        pre_right[i] = pre[i+left_size+1];
    }
    // Recursive call
    Node* left = pre_in(pre_left, in_left, left_size);
    Node* right = pre_in(pre_right, in_right, right_size);
    root = insertLeft(root, left);
    root = insertRight(root, right);
    return root;
}

int main(){
    int k;
    scanf("%d", &k);
    int n[k];
    int* pre[k];
    int* in[k];
    for(int i=0; i<k; i++){
        scanf("%d", &n[i]);
        pre[i] = (int*)malloc(n[i]*sizeof(int));
        in[i] = (int*)malloc(n[i]*sizeof(int));
        for(int j=0; j<n[i]; j++){
            scanf("%d", &pre[i][j]);
        }
        for(int j=0; j<n[i]; j++){
            scanf("%d", &in[i][j]);
        }
    }
    for(int i=0; i<k; i++){
        Node* root = pre_in(pre[i], in[i], n[i]);
        printf("\n");
        preorder(root);
        printf("\n");
        postorder(root);
        printf("\n");
        inorder(root);
        printf("\n");

    }
}

