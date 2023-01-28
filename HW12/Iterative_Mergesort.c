#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass(ElementType list[], ElementType sorted[], int N, int length);

void output(ElementType list[], int N)
{
    int i;
    for(i=0; i<N; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

void  merge_sort(ElementType list[],  int N)
{
    ElementType extra[MAXN];  /* the extra space required */
    int length = 1;  /* current length of sublist being merged */
    while(length < N) { 
        merge_pass(list, extra, N, length); /* merge list into extra */
        output(extra, N);
        length *= 2;
        merge_pass(extra, list, N, length); /* merge extra back to list */
        output(list, N);
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for(i=0; i<N; i++) {
        scanf("%d", &A[i]);
    }
    merge_sort(A, N);
    output(A, N);

    return 0;
}

/* Your function will be put here */
void merge_pass(ElementType list[], ElementType sorted[], int N, int length) {
    int lstart, rstart;
    int lpos, rpos;
    int cnt = 0;

    for(lstart=0, rstart=length; lstart<N && rstart<N; lstart+=2*length, rstart+=2*length) {
        for(lpos=lstart, rpos=rstart; lpos<lstart+length && rpos<rstart+length; cnt++) {
            if(list[lpos] < list[rpos]) {
                sorted[cnt] = list[lpos++];
            }
            else {
                sorted[cnt] = list[rpos++];
            }
        }
        while(lpos < lstart+length) {
            sorted[cnt++] = list[lpos++];
        }
        while(rpos < rstart+length) {
            sorted[cnt++] = list[rpos++];
        }
    }

    //when length is large, only left sublist, e.g. length = 4, [2 7 8 9 | 1 3 5 6 | 0 4] -> [1 2 3 5 6 7 8 9 | 0 4]
    lpos = lstart;
    while(lpos < N) {
        sorted[cnt++] = list[lpos++];
    }    
}