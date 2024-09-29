#include<stdio.h>
#include<stdlib.h>

typedef struct Process{
    int id;
    int at;
    int bt;
    int ct; // compliation time
    int wt; // waiting time
    int st; // starting time
}P;
int main(){
    int n;
    printf("no. of process\t");
    scanf("%d", &n);
    P *p = (P*)malloc(n*sizeof(P));
        P *f = (P*)malloc(sizeof(P));

    for(int i=0; i<n; i++){
        int a, b;    
        printf("Enter at bt \t", n);

        scanf("%d%d",&a,&b);
        p[i].at = a;
        p[i].bt = b;
        p[i].id = i;
    }
   
   // sort based on arrival time 
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(p[i].at > p[j].at){
               f[0] = p[i];
                p[i] = p[j];
                p[j] = f[0];
            }
        }
    }
    int ct=0, i=0; 
    
    // calculate ct, wt for each process
    while(i < n){
        if(p[i].at <= ct){
            p[i].ct = ct + p[i].bt;
            p[i].st = ct;
            p[i].wt = ct - p[i].at;
            ct += p[i].bt;
            i++;
        }
        else ct++;
    }
    for(int i=0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
        p[i].id, p[i].at, p[i].bt, p[i].st, p[i].ct, p[i].wt);
    }
    return 0;
}