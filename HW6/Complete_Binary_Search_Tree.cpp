#include <cstdio>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int n;
int i = 1;
int keys[1001];
int levelorder[1001];

void BuildTree(int root);

int main() {
    scanf("%d", &n);
    for(int i=1; i<=n; i++) {
        scanf("%d", &keys[i]);
    }

    //ascending order(same as inorder)
    sort(keys + 1, keys + n + 1);

    BuildTree(1);

    for(int i=1; i<=n; i++) {
        printf("%d", levelorder[i]);
        if(i<n) {
            printf(" ");
        }
    }

    return 0;
}

void BuildTree(int root) {
    if(root > n) {
        return;
    }

    BuildTree(2 * root);
    levelorder[root] = keys[i++];
    BuildTree(2 * root + 1);
}