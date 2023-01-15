#include <cstdio>

typedef struct {
    int data[1000];
    int top;
    int size;
}Stack;
Stack s;

void Judge(int *inSeq, int n);

int main()
{
    int inSeq[1000];
    int m, n, k, i;
    scanf("%d%d%d", &m, &n, &k);
    
    s.size = m;

    while(k--) {
        for(i=0; i<n; i++) {
            scanf("%d", &inSeq[i]);
        }
        Judge(inSeq, n);
    }
}

void Judge(int *inSeq, int n) {
    int i, j;

    i = 1;
    j = 0;
    s.top = -1;
    while(i <= n) {
        if(s.top < s.size - 1) {
            s.data[++s.top] = i;
            //printf("%d pushed, top = %d\n", i, s.top);
            i++;
        }
        while(s.data[s.top] == inSeq[j] && s.top > -1) {
            //printf("%d poped, top = %d\n", s.data[s.top], s.top-1);
            s.top--;
            j++;
        }
        if(s.top == s.size - 1) {
            break;
        }
    }
    if(j == n && s.top == -1) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }
    return;
}