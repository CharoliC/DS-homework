#include <cstdio>
#include <stdlib.h>

typedef struct {
    int data[1000];
    int front; //out
    int rear; //in, out
}Queue;

Queue q;
int inSeq[1000];

void Judge(int *checkSeq, int n);

int main() {
    int checkSeq[1000];
    int n, k;
    scanf("%d%d", &n, &k);

    for(int i=0; i<n; i++) {
        scanf("%d", &inSeq[i]);
    }
    
    while(k--) {
        for(int i=0; i<n; i++) {
            scanf("%d", &checkSeq[i]);
        }
        Judge(checkSeq, n);
    }
}

void Judge(int *checkSeq, int n) {
    int i, j;

    i = j = 0;
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