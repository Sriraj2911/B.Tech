#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    int val;
    struct Node *left, *right, *parent;
};
typedef struct Node Node;

Node* createNode(char* val){
    if(strcmp(val, "NULL") == 0 || strcmp(val, "null") == 0) return NULL;

    int data = atoi(val);
    Node* node = malloc(sizeof(Node));
    node->val = data;
    node->left = node->right = node->parent = NULL;

    return node;
}

Node* buildTree(char* arr[], int n){
    if(n == 0) return NULL;

    // Array of node pointers
    Node** nodes = malloc(n * sizeof(Node*));
    for(int i=0; i<n; i++){
        nodes[i] = createNode(arr[i]); // NULL is handled in createNode()
    }

    for(int i=0; i<n; i++){
        if(nodes[i] != NULL){
            int leftIndex = 2*i+1;
            int rightIndex = 2*i+2;

            if(leftIndex < n){
                nodes[i]->left = nodes[leftIndex];
                if(nodes[leftIndex]) nodes[leftIndex]->parent = nodes[i];
            }
            if(rightIndex < n){
                nodes[i]->right = nodes[rightIndex];
                if(nodes[rightIndex]) nodes[rightIndex]->parent = nodes[i];
            }
        }
    }
    Node* root = nodes[0];
    free(nodes);
    return root;
}

// left->root->right
void inorder(Node* root){
    Node* prev = NULL;
    Node* curr = root;

    while(curr){
        Node* next;
        if(prev == curr->parent){
            if(curr->left){
                next = curr->left;
            }
            else{
                printf("%d ", curr->val);
                next = (curr->right) ? curr->right:curr->parent;
            }
        }
        else if(prev == curr->left){
            printf("%d ", curr->val);
            next = (curr->right) ? curr->right:curr->parent;
        }
        else if(prev == curr->right){
            next = curr->parent;
        }
        prev = curr;
        curr = next;
    }
}

// root->left->right
void preorder(Node* root){
    Node* prev = NULL;
    Node* curr = root;

    while(curr){
        Node* next;
        if(prev == curr->parent){
            printf("%d ", curr->val);
            if(curr->left){
                next = curr->left;
            }
            else if(curr->right){
                next = curr->right;
            }
            else if(curr->parent){
                next = curr->parent;
            }
        }
        else if(prev == curr->left){
            next = (curr->right) ? curr->right:curr->parent;

        }
        else if(prev == curr->right){
            next = curr->parent;
        }
        prev = curr;
        curr = next;
    }
}

// left->right->root
void postorder(Node* root){
    Node* prev = NULL;
    Node* curr = root;

    while(curr){
        Node* next;
        if(prev == curr->parent){
            if(curr->left){
                next = curr->left;
            }
            else if(curr->right){
                next = curr->right;
            }
            else if(curr->parent){
                printf("%d ", curr->val);
                next = curr->parent;
            }
        }
        else if(prev == curr->left){
            if(curr->right){
                next = curr->right;
            }
            else{
                printf("%d ", curr->val);
                next = curr->parent;
            }

        }
        else if(prev == curr->right){
            printf("%d ", curr->val);
            next = curr->parent;
        }
        prev = curr;
        curr = next;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    getchar(); // Consume leftover newline

    for (int i=0; i<n; i++) {
        char line[500];
        // Assuming a maximum of 100 nodes
        char* arr[100];
        // To store the indices of the array
        int index = 0;

        // Read the array
        if (!fgets(line, sizeof(line), stdin)) break;
        char* token = strtok(line, " \n"); // Splits whenver there is space or a newline
        while (token && index < 100) {
            // Convert char to int and enter into the array
            arr[index++] = token;
            token = strtok(NULL, " \n"); // Stores the next input value
        }

        printf("Output: \n");
        Node* root = buildTree(arr, index);
        inorder(root);
        printf("\n");
        preorder(root);
        printf("\n");
        postorder(root);
        printf("\n");
    }
}
