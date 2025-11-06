#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
    int data;
    struct Node *left, *right, *parent;
    bool black; // TRUE => Black
};
typedef struct Node Node;

Node* NIL; // A global node, which is used as an external node
// Initialising NIL
void initNIL(){
    NIL = malloc(sizeof(Node));
    NIL->black = true;
    NIL->left = NIL->right = NIL->parent = NIL;
}

Node* createNode(int data){
    Node* node = malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NIL;
    node->black = false; // The node is red by default
    return node;
}

// a=>parent, b=>child
Node* rotate(Node* a, Node* b){
    Node* a_parent = a->parent;

    if(b->data > a->data){
        Node* T2 = b->left;
        b->left = a;
        a->parent = b;
        a->right = T2;
        T2->parent = a;
        b->parent = a_parent;
    }
    else{
        Node* T2 = b->right;
        b->right = a;
        a->parent = b;
        a->left = T2;
        T2->parent = a;
        b->parent = a_parent;
    }
    // Update parent's child pointer to b
    if(a_parent){
        if(a_parent->left == a){
            a_parent->left = b;
        }
        else{
            a_parent->right = b;
        }
    }
    return b;
}

void inorder(Node* root){
    if(root == NIL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(Node* root){
    if(root == NIL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}


Node* search(Node* root, int data){
    Node* curr = root;
    while(curr != NIL){
        if(data < curr->data){
            curr = curr->left;
        }
        else if(data > curr->data){
            curr = curr->right;
        }
        else{
            return curr;
        }
    }
    return NIL;
}

Node* insert(Node* root, Node* node){
    if(!root){
        node->black = true;
        node->left = node->right = NIL;
        node->parent = NIL;
        return node;   
    }
    node->left = node->right = NIL;
    if(search(root, node->data) != NIL) return root; // Avoid inserting duplicate elements 

    Node* curr = root;
    while(curr != NIL){
        if(node->data < curr->data){
            if(curr->left == NIL){
                curr->left = node;
                node->parent = curr;
                node->black = false;
                break;
            }
            else curr = curr->left;
        }
        else if(node->data > curr->data){
            if(curr->right == NIL){
                curr->right = node;
                node->parent = curr;
                node->black = false;
                break;
            }
            else curr = curr->right;
        }
    }
    // The while loop is for when the root of the subtree after case-2.2 is red
    while(1){
        Node* a = node->parent;
        if(a == NIL) break;
        Node* b = a->parent;
        if(b == NIL) break;
        Node* c = (b->left == a) ? b->right:b->left;
        
        // Case-1: Parent of the inserted node is black
        if(a->black) return root; // No double-red problem if the parent node is black
        
        // Case-2: Parent of the inserted node is red
        else{
            // Case-2.1: Uncle c is black
            if(c->black){
                // For LR/RL there needs to be an extra rotation between inserted node and its parent
                if((b->left==a && a->right==node) || (b->right==a && a->left==node)){
                    node = rotate(a, node);
                    Node* temp = node;
                    node = a;
                    a = temp;
                }
                a = rotate(b, a);
                a->black = true;
                b->black = false;
                // Update the color of the root to black, if changed
                while(root->parent != NIL){
                    root = root->parent;
                }
                root->black = true;
                return root;
            }
            // Case-2.2: Uncle c is red
            else{
                a->black = true;
                b->black = false;
                c->black = true;
                // Stop the propagation if b is the root and change the color of b to black
                if(root == b){
                    b->black = true;
                    return root; 
                }
                node = b; // Consider the subtree rooted at b and repeat the process
            }
        }
    }
    // Ensure the root is black
    while(root->parent != NIL){
        root = root->parent;
    }
    root->black = true;
    return root;
}

Node* buildRBT(int *arr, int n){
    Node* root = NULL;
    for(int i=0; i<n; i++){
        Node* node = createNode(arr[i]);
        root = insert(root, node);
    }
    return root;
}

Node* successor(Node* node){
    if(node == NIL) return NIL;
    if(node->right == NIL) return NIL;    // No value is greater than root->data

    Node* curr = node->right;
    while(curr->left != NIL){
        curr = curr->left;
    }
    return curr;
}

Node* deleteFix(Node* root, Node* node){
    // Trivial case if the deleted node is red
    if(node->black == false) return root;

    // The loop is in cases where propagation is needed
    while(1){    
        Node* a = node->parent;
        if(a == NIL) break;
        // Case-1: Parent of the deleted node is red
        if(!a->black){
            Node* b = (node==a->left) ? a->right:a->left; // b is black
            if(b == NIL) break;
            // Case-1.1: Some child of the b is red
            if((!b->left->black) || (!b->right->black)){
                Node* c = (!b->right->black) ? b->right:b->left; // The red child of b
                if(b == a->left){
                    // Case-1.1.1: a->right=b, b->right=c
                    if(c == b->right){
                        c = rotate(b, c);
                        c->black = false;
                        b->black = true;
                        // Swapping b and c after the rotation and recoloring gives case-1.1.2
                        Node* temp = c;
                        c = b;
                        b = temp;
                    }
                    // Case-1.1.2: a->right=b, b->left=c
                    if(c == b->left){
                        c = rotate(b, c);
                        c = rotate(a, c);
                        a->black = true;
                        // Ensure the root is black
                        while(root->parent != NIL){
                            root = root->parent;
                        }
                        root->black = true;
                        return root;
                    }
                }
                else if(b == a->right){
                    // Case-1.1.3: a->right=b, b->right=c
                    if(c == b->right){
                        c = rotate(b, c);
                        c->black = true;
                        b->black = false;
                        // Swapping b and c after the rotation and recoloring gives case-1.1.3
                        Node* temp = c;
                        c = b;
                        b = temp;
                    }
                    // Case-1.1.4: a->right=b, b->left=c
                    if(c == b->left){
                        c = rotate(b, c);
                        c = rotate(a, c);
                        a->black = true;
                        // Ensure the root is black
                        while(root->parent != NIL){
                            root = root->parent;
                        }
                        root->black = true;
                        return root;
                    }
                }
            }
            // Case-1.2: Both the children of b are black
            else if((b->left->black) && (b->right->black)){
                a->black = true;
                b->black = false;
                while(root->parent != NIL){
                    root = root->parent;
                }
                root->black = true;
                return root;
            }
        }
        // Case-2: Parent of the deleted node is black
        else if(a->black){
            Node* b = (node==a->left) ? a->right:a->left; 
            if(b == NIL) break;
            // Case-2.1: b is red
            if(!b->black){
                // Case-2.1.1: b has no red grandchildren
                if(b->left->left->black && b->right->left->black && b->left->right->black && b->right->right->black){
                    Node* c = (b==a->left) ? b->right:b->left;
                    b = rotate(a, b);
                    b->black = true;
                    c->black = false;
                    while(root->parent != NIL){
                        root = root->parent;
                    }
                    root->black = true;
                    return root;
                }
                // Case-2.1.2: b has a red grandchild
                else{
                    Node* c = b->right;
                    if(c->right->black && c->left->black){
                        c = b->left; // c is the child of b which has a red child
                    }
                    Node* d = (!c->right->black) ? c->right:c->left;
                    // Case-2.1.2.1
                    if((b==a->right && c==b->left && d==c->left) || (b==a->left && c==b->right && d==c->right)){
                        d = rotate(c, d);
                        d->black = true;
                        c->black = false;
                        // Swapping c and d gives case-2.1.2.2
                        Node* temp = c;
                        c = d;
                        d = temp;
                    }
                    // Case-2.1.2.2
                    if((b==a->right && c==b->left && d==c->right) || (b==a->left && c==b->right && d==c->left)){
                        c = rotate(b, c);
                        c = rotate(a, c);
                        d->black = true;
                        while(root->parent != NIL){
                            root = root->parent;
                        }
                        root->black = true;
                        return root;
                    }
                    // Case-2.1.2.3
                    if((b==a->right && c==b->right && d==c->right) || (b==a->left && c==b->left && d==c->left)){
                        d = rotate(c, d);
                        d->black = true;
                        c->black = false;
                        // Swapping c and d gives case-2.1.2.4
                        Node* temp = c;
                        c = d;
                        d = temp;
                    }
                    // Case-2.1.2.4
                    if((b==a->right && c==b->right && d==c->left) || (b==a->left && c==b->left && d==c->right)){
                        b = rotate(a, b);
                        d = rotate(c, d);
                        d = rotate(b, d);
                        b->black = true;
                        while(root->parent != NIL){
                            root = root->parent;
                        }
                        root->black = true;
                        return root;
                    }  
                }
            }
            // Case-2.2: b is black
            else{
                // Case-2.2.1: b has no red children
                if(b->right->black && b->left->black){
                    b->black = false;
                    node = a;
                    continue;
                }
                // Case-2.2.2: b has a red child
                else{
                    Node* c = (!b->right->black) ? b->right:b->left;
                    // Case-2.2.2.1
                    if((b==a->left && c==b->left) || (b==a->right && c==b->right)){
                        c = rotate(b, c);
                        c->black = true;
                        b->black = false;
                        // Swapping b and c gives case-2.2.2.2
                    }
                    // Case-2.2.2.2
                    if((b==a->left && c==b->right) || (b==a->right && c==b->left)){
                        c = rotate(b, c);
                        c = rotate(a, c);
                        c->black = true;
                        while(root->parent != NIL){
                            root = root->parent;
                        }
                        root->black = true;
                        return root;
                    }
                }
            }
        }
        while(root->parent != NIL){
            root = root->parent;
        }
        root->black = true;
        return root;
    }          
}


Node* delete(Node* root, int key){
    if(root == NIL) return NIL;

    Node* node = search(root, key); // Pointer to the node to be deleted
    if(node == NIL) return root; // Return the root as is if key is not present in the RBT

    // Case-1: If the node to be deleted is a leaf node
    if(node->left==NIL && node->right==NIL){
        if(root->data == key){
            return NIL;
        }
        Node* curr = root;
        while(curr->left!=node && curr->right!=node){
            if(key > curr->data){
                curr = curr->right;
            }
            else{
                curr = curr->left;
            }
        }
        if(curr->right == node){
            curr->right = NIL;
            return deleteFix(root, node);
        }
        else if (curr->left == node){
            curr->left = NIL;
            return deleteFix(root, node);
        }
    }

    // Case-2: If the node to be deleted has exactly one child
    if((node->left==NIL && node->right!=NIL) || (node->left!=NIL && node->right==NIL)){
        if(root->data == key){
            if(root->left != NIL){
                root = root->left;
                return deleteFix(root, node);
            }
            else if(root->right != NIL){
                root = root->right;
                return deleteFix(root, node);
            }
        }
        Node* curr = root;
        while(curr->left!=node && curr->right!=node){
            if(key > curr->data){
                curr = curr->right;
            }
            else{
                curr = curr->left;
            }
        }
        // The node to be deleted is the right child of its parent and it has a right child
        if(curr->right==node && node->right!=NIL){
            curr->right = node->right;
            curr->right->parent = curr;
            node->right = NIL;
        }
        // The node to be deleted is the right child of its parent and it has a left child
        if(curr->right==node && node->left!=NIL){
            curr->right = node->left;
            curr->right->parent = curr;
            node->left = NIL;
        }
        // The node to be deleted is the left child of its parent and it has a right child
        if(curr->left==node && node->right!=NIL){
            curr->left = node->right;
            curr->left->parent = curr;
            node->right = NIL;
        }
        // The node to be deleted is the left child of its parent and it has a left child
        if(curr->left==node && node->left!=NIL){
            curr->left = node->left;
            curr->left->parent = curr;
            node->left = NIL;
        }
        return deleteFix(root, node);
    }

    // Case-3: If the node to be deleted has two children
    if(node->left && node->right){
        Node* temp = successor(node);
        int data = temp->data;
        root = delete(root, data);
        node->data = data;
        return deleteFix(root, node);
    }
}


int main(){
    initNIL();
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i=0; i<n; i++){
        scanf("%d", arr+i);
    }
    Node* root = buildRBT(arr, n);
    printf("Inorder traversal -> ");
    inorder(root);
    printf("\n");
    printf("Preorder traversal -> ");
    preorder(root);
    printf("\n");
    int choice = 1;
    int element;
    while(choice != 0){
        printf("Enter your choice:\n");
        printf("1 - Search for an element\n");
        printf("2 - Insert an element\n");
        printf("3 - Delete an element\n");
        printf("0 - Exit\n");
        scanf("%d", &choice);
        if(choice == 0) break;
        switch (choice){
            case 1:
                scanf("%d", &element);
                Node* node = search(root, element);
                if(node!=NIL) printf("Key found\n");
                else printf("Key not found\n");
                break;
            case 2:
                scanf("%d", &element);
                node = createNode(element);
                root = insert(root, node);
                printf("Inorder traversal -> ");
                inorder(root);
                printf("\n");
                printf("Preorder traversal -> ");
                preorder(root);
                printf("\n");
                break;
            case 3:
                scanf("%d", &element);
                if(search(root, element) == NIL) printf("Prompted key is not present in RBT\n");
                else{
                    root = delete(root, element);
                    printf("Inorder traversal -> ");
                    inorder(root);
                    printf("\n");
                    printf("Preorder traversal -> ");
                    preorder(root);
                    printf("\n");
                }
                break;
            default:
                printf("Invalid prompt\n");
                break;
        }
    }
}