#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char operators[5] = {'^', '/', '*', '+', '-'};
char operands[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

struct Node{
    char exp;
    struct Node* next;
    struct Node* prev;
};
typedef struct Node Node;

struct Node* createNode(char exp){
    Node* node = (Node*)malloc(sizeof(Node));
    node->exp = exp;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// Push and pop functions for a stack
void push(Node** head, char exp){
    Node* node = createNode(exp);
    if(!(*head)){
        *head = node;
    }
    else{
        node->next = *head;
        (*head)->prev = node;
        *head = node;
    }
}
char pop(Node** head){
    if(!*head) return '0';
    if(!(*head)->next){
        char result = (*head)->exp;
        *head = NULL;
        return result;
    } 

    Node* temp = *head;
    *head = (*head)->next;
    temp->next = NULL;
    (*head)->prev = NULL;
    return temp->exp;
}

// A helper function to check if the char in the given infix expression is an operand or operator
int contains(char *arr, int n, char ele){
    for(int i=0; i<n; i++){
        if(arr[i] == ele){
            return 1;
        }
    }
    return 0;
}

// A helper function to establish the precedence order of the operators
int precedence(char operator){
    switch (operator)
    {
    case '^': return 3;
    case '/':
    case '*': return 2;
    case '+':
    case '-': return 1;
    default: return 0;
    }
}

// Function to convert infix to postfix expression
void inToPost(char *infix){
    // Stack to store the operators
    Node* head = NULL;
    int length = strlen(infix);
    // char array to store the final result
    char* result = (char*)malloc(sizeof(char)*(length+1));
    // An incrementor for the index of the array result
    int j = 0;

    for(int i=0; i<length; i++){
        // Append the operands to the result directly
        if(contains(operands, 26, infix[i]) == 1){
            result[j] = infix[i];
            j++;
        }
        // Push the open bracket onto the stack
        else if(infix[i] == '('){
            push(&head, infix[i]);
        }
        // All the operators in the stack, between the two brackets are appended to the result array
        else if(infix[i] == ')'){
            // Append the elements in the stack to the result array until '(' is found
            while(head && head->exp!='('){
                result[j] = pop(&head);
                j++;
            }
            // Discard '('
            pop(&head);
        }
        // Handle the appending of operators based on their precedence order
        else if(contains(operators, 5, infix[i])){
            // Append the operator in the stack to the result array, if it has a greater precedence than the current operator
            while(head && (precedence(head->exp) >= precedence(infix[i]))){
                result[j++] = pop(&head);
            }
            // Push the current operator onto the stack
            push(&head, infix[i]);
        }
    }
    // Append the remaining operators in the stack to the result array
    while(head){
        result[j] = pop(&head);
        j++;
    }
    // Append the null terminator 
    result[j] = '\0';

    printf("%s", result);
    free(result);
}

int main(){
    int n;
    scanf("%d", &n);
    // Define an array of strings
    char* arrExp[n];

    for(int i=0; i<n; i++){
        arrExp[i] = malloc(1000);
        scanf("%s", arrExp[i]);
    }

    for(int i=0; i<n; i++){
        inToPost(arrExp[i]);
        printf("\n");
    }
}



