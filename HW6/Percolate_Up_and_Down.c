#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
#define MinData -1

typedef struct HeapStruct *PriorityQueue;
struct HeapStruct {
    ElementType *Elements;
    int Capacity;
    int Size;
};

PriorityQueue Initialize(int MaxElements); /* details omitted */

void PercolateUp(int p, PriorityQueue H);
void PercolateDown(int p, PriorityQueue H);

void Insert(ElementType X, PriorityQueue H) 
{
    int p = ++H->Size;
    H->Elements[p] = X;
    PercolateUp(p, H);
}

ElementType DeleteMin(PriorityQueue H)
{ 
    ElementType MinElement; 
    MinElement = H->Elements[1];
    H->Elements[1] = H->Elements[H->Size--];
    PercolateDown(1, H);
    return MinElement; 
}

int main()
{
    int n, i, op, X;
    PriorityQueue H;

    scanf("%d", &n);
    H = Initialize(n);
    for(i=0; i<n; i++) {
        scanf("%d", &op);
        switch(op) {
        case 1:
            scanf("%d", &X);
            Insert(X, H);
            break;
        case 0:
            printf("%d ", DeleteMin(H));
            break;
        }
    }
    printf("\nInside H:");
    for (i=1; i<=H->Size; i++)
        printf(" %d", H->Elements[i]);
    return 0;
}

/* Used for test */
PriorityQueue Initialize(int MaxElements) {
    PriorityQueue H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
    H->Elements = (int*)malloc((MaxElements + 1) * sizeof(int));
    H->Elements[0] = MinData;
    H->Capacity = MaxElements;
    H->Size = 0;
    return H;
}

/* Your function will be put here */
void PercolateUp(int p, PriorityQueue H) {
    int i;
    int temp = H->Elements[p];

    for(i=p; H->Elements[i/2] > temp; i /= 2) {
        H->Elements[i] = H->Elements[i/2];
    }
    H->Elements[i] = temp;
}

void PercolateDown(int p, PriorityQueue H) {
    int i;
    int child;
    int temp = H->Elements[p];

    for(i=p; 2*i<=H->Size; i=child) {
        child = 2*i;
        if(child + 1 <= H->Size && H->Elements[child] > H->Elements[child+1]) {
            child++;
        }
        if(temp < H->Elements[child]) {
            break;
        }
        H->Elements[i] = H->Elements[child];
    }
    H->Elements[i] = temp;
}