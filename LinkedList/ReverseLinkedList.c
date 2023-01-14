#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
    ElementType Element;
    Position Next;
};

List Read(); /* details omitted */
void Print(List L); /* details omitted */
List Reverse(List L);

int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Reverse(L1);
    Print(L1);
    Print(L2);
    return 0;
}

/* Used for test */
List Read() {
    List L = (PtrToNode)malloc(sizeof(struct Node));
    PtrToNode ptr = L;
    ptr->Next = NULL;

    int num;
    scanf("%d", &num);
    while(num--) {
        ptr->Next = (PtrToNode)malloc(sizeof(struct Node));
        ptr = ptr->Next;
        scanf("%d", &ptr->Element);
        ptr->Next = NULL;
    }
    return L;
}

void Print(List L) {
    PtrToNode ptr = L->Next;
    while(ptr != NULL) {
        printf("%d ", ptr->Element);
        ptr = ptr->Next;
    }
    printf("\n");
}

/* Your function will be put here */
/* Time complexity O(n), constant extra space */
List Reverse(List L) {
    PtrToNode ptr = L->Next;
    PtrToNode next, prev;
    next = prev = NULL;

    while(ptr != NULL) {
        next = ptr->Next;
        ptr->Next = prev;
        prev = ptr;
        ptr = next;
    }
    L->Next = prev;
    return L;
}