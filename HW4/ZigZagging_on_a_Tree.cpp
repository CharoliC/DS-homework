#include <cstdio>
#include <stdlib.h>

typedef struct TreeNode *Tree;
struct TreeNode{
    int data;
    Tree left;
    Tree right;
};

typedef struct {
    Tree data[30];
    int top;
}Stack;

Tree BuildTree(int *inorder, int *postorder, int n);
void ZigZag(Tree T);
bool IsEmpty(Stack &S);
bool Push(Stack &S, Tree x);
bool Pop(Stack &S, Tree &x);

int main() {
    int inorder[30], postorder[30];
    int n;

    scanf("%d", &n);
    for(int i=0; i<n; i++) {
        scanf("%d", &inorder[i]);
    }
    for(int i=0; i<n; i++) {
        scanf("%d", &postorder[i]);
    }

    Tree T = BuildTree(inorder, postorder, n);
    ZigZag(T);

    return 0;
}

Tree BuildTree(int *inorder, int *postorder, int n) {
    if(n == 0) {
        return NULL;
    }

    Tree T = (Tree)malloc(sizeof(struct TreeNode));
    T->data = postorder[n-1];

    int rootIndex = 0;
    while(inorder[rootIndex] != postorder[n-1]) {
        rootIndex++;
    }

    T->left = BuildTree(inorder, postorder, rootIndex);
    T->right = BuildTree(inorder + rootIndex + 1, postorder + rootIndex, n - rootIndex - 1);
    return T;
}

void ZigZag(Tree T) {
    if(T == NULL) {
        return;
    }

    Tree p;
    Stack S1, S2;
    int level = 1;
    
    S1.top = S2.top = -1;

    Push(S1, T);

    while(!(IsEmpty(S1) && IsEmpty(S2))) {
        //odd level, p<-S1, right->S2, left->S2
        if(level % 2 == 1) {
            if(IsEmpty(S1)) {
                level++;
                continue;
            }
            Pop(S1, p);
            printf("%d ", p->data);
            if(p->right != NULL) {
                Push(S2, p->right);
            }
            if(p->left != NULL) {
                Push(S2, p->left);
            }
        }
        //even level, p<-S2, left->S1, right->S1
        if(level % 2 == 0) {
            if(IsEmpty(S2)) {
                level++;
                continue;
            }
            Pop(S2, p);
            printf("%d ", p->data);
            if(p->left != NULL) {
                Push(S1, p->left);
            }
            if(p->right != NULL) {
                Push(S1, p->right);
            }
        }
    }
    return;
}

bool IsEmpty(Stack &S) {
    return S.top == -1;
}

bool Push(Stack &S, Tree x) {
    if(S.top == 30 - 1) {
        return false;
    }
    S.data[++S.top] = x;
    return true;
}

bool Pop(Stack &S, Tree &x) {
    if(IsEmpty(S)) {
        return false;
    }
    x = S.data[S.top--];
    return true;
}