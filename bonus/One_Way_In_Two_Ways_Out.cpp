#include <cstdio>
#include <stdlib.h>

typedef struct {
    int data[1000];
    int front; //out
    int rear; //in, out
}Queue;

void Judge(int* inSeq, int *checkSeq, int n);

int main() {
    int n, k;
    scanf("%d%d", &n, &k);

    int *inSeq;
    inSeq = (int*)malloc(n * sizeof(int));
    for(int i=0; i<n; i++) {
        scanf("%d", &inSeq[i]);
    }
    
    int *checkSeq;
    checkSeq = (int*)malloc(n * sizeof(int));
    while(k--) {
        for(int i=0; i<n; i++) {
            scanf("%d", &checkSeq[i]);
        }
        Judge(inSeq, checkSeq, n);
    }
}

void Judge(int* inSeq, int *checkSeq, int n) {
    int i = 0, j = 0;
    Queue q;
    q.front = q.rear = 0;
    
    while(i < n) {
        //printf("rear enqueue %d\n", inSeq[i]);
        q.data[q.rear++] = inSeq[i++];

        while(q.data[q.front] == checkSeq[j] || q.data[q.rear - 1] == checkSeq[j]) {
            if(q.data[q.front] == checkSeq[j]) {
                //printf("front dequeue %d\n", q.data[q.front]);
                q.front++;
                j++;
            }
            if(q.data[q.rear - 1] == checkSeq[j]) {
                //printf("rear dequeue %d\n", q.data[q.rear - 1]);
                q.rear--;
                j++;
            }
        }
    }

    if(j == n) {
        printf("yes\n");
    }
    else {
        printf("no\n");
    }
    return;
}