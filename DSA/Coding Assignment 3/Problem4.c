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

int singleRot = 0;
int doubleRot = 0;

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
        singleRot++;
        return rightRotate(root);
    }
    if(balance < -1 && key > root->right->data){
        singleRot++;
        return leftRotate(root);
    }
    if(balance > 1 && key > root->left->data){
        doubleRot++;
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance < -1 && key < root->right->data){
        doubleRot++;
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

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
        singleRot++;
        return rightRotate(root);
    }
    if(balance > 1 && heightDiff(root->left) < 0){
        doubleRot++;
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance < -1 && heightDiff(root->right) <= 0){
        singleRot++;
        return leftRotate(root);
    }
    if(balance < -1 && heightDiff(root->right) > 0){
        doubleRot++;
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void inorder(Node* root){
    if(!root) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int main(){
    Node* root = NULL;
    char choice = 'a';
    int key;
    int n;
    scanf("%d", &n); // Number of queries
    while(n){
        scanf(" %c", &choice);
        scanf("%d", &key);
        
        switch (choice)
        {
            case 'I':
                if(!searchNode(root, key)){
                    root = insertNode(root, key);
                }
                break;
            case 'D':
                if(searchNode(root, key)){
                    root = deleteNode(root, key);
                }
                break;
            default:
                printf("Invalid query\n");
                n++;
                break;
            }
            n--;
        }
    printf("Inorder: ");
    inorder(root);
    printf("\n");
    printf("Single rotations: %d\n", singleRot);
    printf("Double rotations: %d\n", doubleRot);
}
