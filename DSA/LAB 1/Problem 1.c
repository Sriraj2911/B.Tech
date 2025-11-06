#include <stdio.h>
#include <stdbool.h>


int count[1000]={0};

int head(int *q, int n){
    for(int i=0; i<n-1; i++){
        if(count[i]==0 && count[i+1]!=0){
            return i+1;
        }
    }
    return 0;
}

int tail(int *q, int n){
    for(int i=0; i<n-1; i++){
        if((count[i]!=0 && count[i+1]==0) || (count[i]!=0 && count[i+1]!=0 && head(q, n)==i+1)){
            return i;
        }
    }
    return n-1;
}

bool q_empty(int *q, int n){
    int h = head(q, n);
    int t = tail(q, n);
    if(h==0 && t==0){
        return true;
    }
    return false;
}

bool q_full(int *q, int n){
    int h = head(q, n);
    int t = tail(q, n);
    if((h==0 && t==n-1) || (h==t+1)){
        return true;
    }
    return false;
}

void enq(int *q, int item, int n){
    int h = head(q, n);
    int t = tail(q, n);
    if(q_full(q, n)){
        printf("Stack is full: Overflow");
    }
    else{
        t = (t+1)%n;
        q[t] = item;
        count[t]++;
    }
}

int deq(int *q, int n){
    int h = head(q, n);
    int t = tail(q, n);
    if(q_empty(q, n)){
        return -1;
    }
    int temp = q[h];
    count[h]--;
    h = (h+1)%n;
    return temp;
}

void q_rot(int n, int *q, int k){
    int store[n];
    for(int i=0; i<k; i++){
        store[k-1-i]=deq(q, n);
    }
    for(int i=k; i<n; i++){
        store[i]=deq(q, n);
    }
    for(int i=0; i<n; i++){
        enq(q, store[i], n);
        printf("%d", store[i]);
    }
    
}

int main(){
    int n;
    int k;
    scanf("%d", &n);
    int q[n];
    for(int i=0; i<n; i++){
        scanf("%d", q[i]);
    }
    scanf("%d", &k);
    q_rot(n, q, k);
}