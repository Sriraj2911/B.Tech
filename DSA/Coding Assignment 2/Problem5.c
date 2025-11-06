#include <stdio.h>
#include <stdlib.h>

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

Node* insertNode(Node* root, Node* node){
    Node* curr = root;
    while(curr){
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
    node->parent = curr;
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

Node* buildBST(int arr[], int n){
    Node* root = createNode(arr[0]);
    for(int i=1; i<n; i++){
        Node* node = createNode(arr[i]);
        root = insertNode(root, node);
    }

    return root;
}

Node* nodeK(Node* root, Node* u, Node* v, int k){
    Node* curr = root;
    int val1 = u->val;
    int val2 = v->val;
    // After the following loop, curr will contain the node which will have u in its LST and v in its RST, or vice-versa
    // In other words, curr will be the lowest common ancestor of u and v
    while(curr){
        if(val1 < curr->val && val2 < curr->val){
            curr = curr->left;
        }
        else if(val1 > curr->val && val2 > curr->val){
            curr = curr->right;
        }
        else{
            break; // Found least common ancestor
        }
    }


    Node* curr1 = u;
    while(curr1 != curr && k>1){
        curr1 = curr1->parent;
        k--;
    }
    while(curr1 && k>1){
        if(v->val < curr1->val){
            curr1 = curr1->left;
        }
        else{
            curr1 = curr1->right;
        }
        k--;
    }

    return curr1;
}

int main(){
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i=0; i<n; i++){
        scanf("%d", arr+i);
    }
    Node* root = buildBST(arr, n);
    int q;
    scanf("%d", &q);
    int args[3]; // The arrays into which u, v, k are entered
    int results[q]; // Array to store the result of each query
    for(int i=0; i<q; i++){
        for(int j=0; j<3; j++){
            scanf("%d", args+j);
        }
        // Getting the addresses of the nodes in the tree with values args[0] and args[1]
        Node* u = search(root, args[0]);
        Node* v = search(root, args[1]);
        int k = args[2];
        Node* result = nodeK(root, u, v, k);
        if(result){
            if(k == 1){
                printf("1st node value -> %d\n", result->val);
            }
            else if(k == 2){
                printf("2nd node value -> %d\n", result->val);
            }
            else{
                printf("%dth node value -> %d\n", k, result->val);
            }
        }
        else{
            printf("-1\n");
        }
    }
}
