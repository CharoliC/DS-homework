#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree  Left;
    Tree  Right;
};

int Isomorphic(Tree T1, Tree T2) {
    if(T1 == NULL && T2 == NULL)
        return 1;

    else if(T1 != NULL && T2 != NULL) {
        if(T1->Element == T2->Element) {
            if(T1->Left == NULL && T2->Left == NULL)
                return Isomorphic(T1->Right, T2->Right);
            else if(T1->Left != NULL && T2->Left != NULL && T1->Left->Element == T2->Left->Element)
                return Isomorphic(T1->Left, T2->Left) && Isomorphic(T1->Right, T2->Right);
            else
                return Isomorphic(T1->Left, T2->Right) && Isomorphic(T1->Right, T2->Left);
        }
        else
            return 0;
    }
    
    else
        return 0;
}