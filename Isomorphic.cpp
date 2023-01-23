#include <cstdio>
#include <stdlib.h>

typedef struct TreeNode *Tree;
struct TreeNode {
    char data;
    Tree left;
    Tree right;
};

int Isomorphic(Tree T1, Tree T2) {
    if(T1 == NULL && T2 == NULL) {
        return 1;
    }
    else if(T1 != NULL && T2 != NULL) {
        if(T1->data == T2->data) {
            if(T1->left == NULL && T2->left == NULL)
                return Isomorphic(T1->right, T2->right);
            else if(T1->left != NULL && T2->left != NULL && T1->left->data == T2->left->data)
                return Isomorphic(T1->left, T2->left) && Isomorphic(T1->right, T2->right);
            else
                return Isomorphic(T1->left, T2->right) && Isomorphic(T1->right, T2->left);
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}