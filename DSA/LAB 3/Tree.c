#include <stdio.h>
#include <stdlib.h>

int count;

struct node{
    int data;
    struct node* left;
    struct node* right;
};
typedef struct node node;

struct node* createNode(int data){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

struct node* insertLeft(node* root, int data){
    node* leftNode = createNode(data);
    root->left = leftNode;

    return root->left;
}

struct node* insertRight(node* root, int data){
    node* rightNode = createNode(data);
    root->right = rightNode;

    return root->right;
}

struct node* buildTree(node* root, int *arr, int n){
    if(arr[0]==-1){
        return NULL;
    }
    node* a[n];
    a[0] = root;
    for(int i=1; i<n; i++){
        if(arr[i]==-1){
            continue;
        }
        node* parent = a[(i-1)/2];
        if(i%2==0){
            parent->right = insertRight(parent, arr[i]);
            a[i] = parent->right;
        }
        else{
            parent->left = insertLeft(parent, arr[i]);
            a[i] = parent->left;
        }
    }
    return root;
}

void preorder(node* root){
    if(root == NULL){
        return;
    }
    else{
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(node* root){
    if(root==NULL){
        return;
    }
    else{
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void postorder(node* root){
    if(root==NULL){
        return;
    }
    else{
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int main(){
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    node* root = createNode(arr[0]);
    
    // A new array to add extra '-1's to be compatible with the buildTree function 
    int newArr[1000];
    newArr[0] = root->data;
    int j=1;
    for(int i=1; i<n; i++){
        // Add two extra '-1's if the parent node is -1
        if(newArr[(j-1)/2]==-1){
            newArr[j]=-1;
            newArr[j+1]=-1;
            j += 2;
        }
        newArr[j] = arr[i];
        j++;
    }

    // Build the tree with the new array, added with sufficient '-1's
    root = buildTree(root, newArr, j);

    preorder(root);
    printf("\n");
    inorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
}