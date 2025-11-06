#include <stdio.h>
#include <stdbool.h>

int count[1000]={0};
int n=1000;

int head(int *q){
    if(count[n-1]!=0){
        return n-1;
    }
    if(count[0]==0){
        return -1;
    }
    for(int i=1; i<n; i++){
        if(count[i-1]!=0 && count[i]==0){
            return i-1;
        }
    }
}

bool stack_empty(int *q){
    int h = head(q);
    if(h==-1){
        return true;
    }
    return false;
}

bool stack_full(int *q){
    int h = head(q);
    if(h==n-1){
        return true;
    }
    return false;
}

void push(int *q, int item){
    int h = head(q);
    if(stack_full(q)){
        printf("Stack overflow");
    }
    else{
        h++;
        q[h] = item;
        count[h]++;
    }
}

int pop(int *q){
    int h = head(q);
    if(stack_empty(q)){
        return -1;
    }
    int temp = q[h];
    count[h]--;
    h--;
    return temp;
}

void enq(int *q, int item){
    push(q, item);
}

int deq(int *q1, int *q2){
    int h = head(q1);
    if(h==-1){
        return -1;
    }
    for(int i=0; i<h-1; i++){
        int temp = pop(q1);
        push(q2, temp);
    }
    int result = pop(q1);
    for(int i=0; i<h-1; i++){
        int temp = pop(q2);
        push(q1, temp);
    }
    return result;
}

int main(){
    int item;
    int k;
    int q1[n];
    int q2[n];
    while(true){
        scanf("%d", &k);
        if(k==1){
            scanf("%d", &item);
            enq(q1, item);
        }
        else if(k==2){
            int temp = deq(q1, q2);
            if(temp==-1){
                printf("Queue is empty\n");
            }
            else{
                printf("Dequeued: %d", temp);
            }
        }
        else{
            break;
        }
    }
    
}