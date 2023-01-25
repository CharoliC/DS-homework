#include <cstdio>
#include <stdlib.h>
#include <string.h>

typedef int *UFset;

void Init(UFset &S);
void Union(UFset &S, int rt1, int rt2);
int Find(UFset &S, int x);

int main() {
    int n;
    scanf("%d", &n);

    //s[0] reserved (because computers numbered from 1 to N)
    UFset s = (int*)malloc((n + 1) * sizeof(int));
    memset(s, -1, (n + 1) * sizeof(int));

    int op;
    int c1, c2;
    while((op = getchar()) != 'S') {
        switch(op) {
            case 'I':
                scanf("%d%d", &c1, &c2);
                Union(s, Find(s, c1), Find(s, c2));
                break;

            case 'C':
                scanf("%d%d", &c1, &c2);
                if(Find(s, c1) != Find(s, c2)) {
                    printf("no\n");
                }
                else {
                    printf("yes\n");
                }
                break;
        }
    }

    //count components
    int k = 0;
    for(int i=1; i<=n; i++) {
        if(s[i] < 0) {
            k++;
        }
    }

    if(k == 1) {
        printf("The network is connected.");
    }
    else {
        printf("There are %d components.", k);
    }

    return 0;
}

void Union(UFset &S, int rt1, int rt2) {
    if(rt1 != rt2) {
        //printf("union %d and %d\n", rt1, rt2);
        S[rt2] = rt1;
    }
}

int Find(UFset &S, int x) {
    if(S[x] < 0) {
        return x;
    }
    else {
        return S[x] = Find(S, S[x]);
    }
}