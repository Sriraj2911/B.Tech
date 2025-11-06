#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    int val;
    struct Node *right, *left;
};
typedef struct Node Node;

Node* createNode(char* val){
    if(strcmp(val, "NULL") == 0 || strcmp(val, "null") == 0) return NULL;

    Node* node = malloc(sizeof(Node));
    node->val = atoi(val);
    node->right = node->left = NULL;

    return node;
}

Node* insertNode(Node* root, Node* node){
    Node* curr = root;
    while(1){
        if(node->val < curr->val){
            if(curr->left == NULL){
                curr->left = node;
                break;
            }
            curr = curr->left;
        }
        else{
            if(curr->right == NULL){
                curr->right = node;
                break;
            }
            curr = curr->right;
        }
    }
    return root;
}

Node* search(Node* root, int val){
    Node* curr = root;
    while(curr){
        if(val < curr->val){
            curr = curr->left;
        }
        else if(val > curr->val){
            curr = curr->right;
        }
        else{
            return curr;
        }
    }
    return NULL;
}

Node* buildBST(char* arr[], int n){
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
            }
            if(rightIndex < n){
                nodes[i]->right = nodes[rightIndex];
            }
        }
    }
    Node* root = nodes[0];
    free(nodes);
    return root;
}

int min(Node* root){
    Node* curr = root;
    while(curr->left){
        curr = curr->left;
    }
    return curr->val;
}

int max(Node* root){
    Node* curr = root;
    while(curr->right){
        curr = curr->right;
    }
    return curr->val;
}


int main(){
    char line[500];
    // Assuming a maximum of 100 nodes
    char* arr[100];
    // To store the indices of the two arrays
    int index = 0;
    
    if (!fgets(line, sizeof(line), stdin)) return 0;
    char* token = strtok(line, " \n"); // Splits whenver there is space or a newline
    while (token && index < 100) {
        // Convert char to in and enter into the inorder array
        arr[index++] = token;
        token = strtok(NULL, " \n"); // Stores the next input value
    }
    Node* root = buildBST(arr, index);
    int low;
    int high;
    scanf("%d", &low);
    scanf("%d", &high);
    // Change the values of low and high to reduce the number of iterations
    if(low < min(root)){
        low = min(root);
    }
    if(high > max(root)){
        high = max(root);
    }
    int result = 0;
    for(int i=low; i<=high; i++){
        if(search(root, i)) result += i;
    }
    printf("%d\n", result);
}
