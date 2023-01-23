#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
struct Node {
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;

Polynomial Read(); /* details omitted */
void Print(Polynomial p); /* details omitted */
Polynomial Add(Polynomial a, Polynomial b);

int main()
{
    Polynomial a, b, s;
    a = Read();
    b = Read();
    s = Add(a, b);
    Print(s);
    return 0;
}

/* Used for test */
Polynomial Read() {
    Polynomial p = (PtrToNode)malloc(sizeof(struct Node));
    PtrToNode ptr = p;
    ptr->Next = NULL;

    int num;
    scanf("%d", &num);
    while(num--) {
        ptr->Next = (PtrToNode)malloc(sizeof(struct Node));
        ptr = ptr->Next;
        scanf("%d%d", &ptr->Coefficient, &ptr->Exponent);
        ptr->Next = NULL;
    }
    return p;
}

void Print(Polynomial p) {
    PtrToNode ptr = p->Next;
    if(ptr == NULL) {
        printf("0");
        return;
    }
    while(ptr != NULL) {
        printf("%d %d ", ptr->Coefficient, ptr->Exponent);
        ptr = ptr->Next;
    }
}

/* Your function will be put here */
Polynomial Add(Polynomial a, Polynomial b) {
    Polynomial s = (PtrToNode)malloc(sizeof(struct Node));
    PtrToNode ptra = a->Next;
    PtrToNode ptrb = b->Next;
    PtrToNode ptrs = s;
    ptrs->Next = NULL;
    
    while(ptra != NULL && ptrb != NULL) {
        if(ptra->Exponent > ptrb->Exponent) {
            ptrs->Next = (PtrToNode)malloc(sizeof(struct Node));
            ptrs = ptrs->Next;
            ptrs->Coefficient = ptra->Coefficient;
            ptrs->Exponent = ptra->Exponent;
            ptra = ptra->Next;
        }
        else if(ptra->Exponent < ptrb->Exponent) {
            ptrs->Next = (PtrToNode)malloc(sizeof(struct Node));
            ptrs = ptrs->Next;
            ptrs->Coefficient = ptrb->Coefficient;
            ptrs->Exponent = ptrb->Exponent;
            ptrb = ptrb->Next;
        }
        else {
            if(ptra->Coefficient + ptrb->Coefficient == 0) {
                ptra = ptra->Next;
                ptrb = ptrb->Next;
            }
            else {
                ptrs->Next = (PtrToNode)malloc(sizeof(struct Node));
                ptrs = ptrs->Next;
                ptrs->Coefficient = ptra->Coefficient + ptrb->Coefficient;
                ptrs->Exponent = ptra->Exponent;
                ptra = ptra->Next;
                ptrb = ptrb->Next;
            }
        }
        ptrs->Next = NULL;
    }
    if(ptra != NULL) {
        ptrs->Next = ptra;
    }
    if(ptrb != NULL) {
        ptrs->Next = ptrb;
    }

    return s;
}