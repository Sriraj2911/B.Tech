#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define n 800 // The number of distinct numbers in the entire dataset

#define m1 2000
#define m2 3000
#define m3 4000

int k1 = (m1/n)*0.693;
int k2 = (m2/n)*0.693;
int k3 = (m3/n)*0.693;

int hash[3][2] = {0};

void hash_init(){
    srand(time(NULL));
    
    for(int i=0; i<k3; i++){
        hash[i][0] = rand();
        hash[i][1] = rand();
    }
}

int hash_value(int num, int k, int m){
    return (abs(hash[k][0]*num + hash[k][1]))%m;
}

int total[n] = {0};

int main(){
    int bloomFilter1[m1] = {0};
    int bloomFilter2[m2] = {0};
    int bloomFilter3[m3] = {0};
    hash_init();
    
    FILE *fp = fopen("dataset.txt", "r");
    
    if(!fp){
        perror("File open failed\n");
        return 1;
    }
    
    
    int num;
    while(fscanf(fp, "%d", &num) == 1){
        for(int i=0; i<k1; i++){
            printf("%d\n", hash_value(num, i, m1));
            bloomFilter1[hash_value(num, i, m1)] = 1;
        }
        for(int i=0; i<k2; i++){
            bloomFilter2[hash_value(num, i, m2)] = 1;
        }
        for(int i=0; i<k3; i++){
            bloomFilter3[hash_value(num, i, m3)] = 1;
        }
    }
    fclose(fp);

    // TP[i] stores the true positive count for the bloom filter with m = mi
    int TP[3] = {0};
    int FP[3] = {0};
    int TN[3] = {0};
    int FN[3] = {0};
    
    FILE *pos = fopen("query_positive.txt", "r");
    
    if(!pos){
        perror("File open failed\n");
        return 1;
    }
    int n1;
    while(fscanf(pos, "%d", &n1) == 1){
        for(int i=0; i<k1; i++){
            if(bloomFilter1[hash_value(n1, i, m1)] == 0){
                FN[0]++;
                TP[0]--;
                break;
            } 
        }
        TP[0]++;
        for(int i=0; i<k2; i++){
            if(bloomFilter2[hash_value(n1, i, m2)] == 0){
                FN[1]++;
                TP[1]--;
                break;
            } 
        }
        TP[1]++;
        for(int i=0; i<k3; i++){
            if(bloomFilter3[hash_value(n1, i, m3)] == 0){
                FN[2]++;
                TP[2]--;
                break;
            } 
        }
        TP[2]++;
    }
    fclose(pos);

    FILE *neg = fopen("query_negative.txt", "r");
    
    if(!neg){
        perror("File open failed\n");
        return 1;
    }
    int n2;
    while(fscanf(neg, "%d", &n2) == 1){
        for(int i=0; i<k1; i++){
            if(bloomFilter1[hash_value(n2, i, m1)] == 0){
                TN[0]++;
                FP[0]--;
                break;
            } 
        }
        FP[0]++;
        for(int i=0; i<k2; i++){
            if(bloomFilter2[hash_value(n2, i, m2)] == 0){
                TN[1]++;
                FP[1]--;
                break;
            } 
        }
        FP[1]++;
        for(int i=0; i<k3; i++){
            if(bloomFilter3[hash_value(n2, i, m3)] == 0){
                TN[2]++;
                FP[2]--;
                break;
            } 
        }
        FP[2]++;
    }
    fclose(neg);

    for(int i=0; i<3; i++){
        printf("%d Bloom Filter: \n", (i+2)*1000);
        printf("    True Positive => %d\n", TP[i]);
        printf("    False Positive => %d\n", FP[i]);
        printf("    True Negative => %d\n", TN[i]);
        printf("    False Negative => %d\n\n", FN[i]);
    }

}

