#include <cstdio>
#define MAXN 10000

void Sort(int *a, int low, int high);

int main() {
    int n;
    scanf("%d", &n);

    int hat[MAXN], sorted_hat[MAXN];
    for(int i=0; i<n; i++) {
        scanf("%d", &hat[i]);
        sorted_hat[i] = hat[i];
    }

    int ptaer[MAXN], sorted_ptaer[MAXN];
    for(int i=0; i<n; i++) {
        scanf("%d", &ptaer[i]);
        sorted_ptaer[i] = ptaer[i];
    }

    Sort(sorted_hat, 0, n-1);
    Sort(sorted_ptaer, 0, n-1);

    for(int i=n-1; i>=0; i--) {
        for(int j=0; j<n; j++) {
            if(hat[i] == sorted_hat[j]) {
                for(int k=0; k<n; k++) {
                    if(ptaer[k] == sorted_ptaer[j]) {
                        printf("%d", k+1);
                        if(i != 0) {
                            printf(" ");
                        }
                    }
                }
            }
        }
    }

    return 0;
}

void Sort(int *a, int low, int high) {
    int i, j, pivot, temp;
    if(low < high) {
        pivot = a[low];
        i = low;
        j = high;
        while(i < j) {
            while(i < j && a[j] >= pivot) {
                j--;
            }
            a[i] = a[j];
            while(i < j && a[i] <= pivot) {
                i++;
            }
            a[j] = a[i];
        }
        a[i] = pivot;
        Sort(a, low, i-1);
        Sort(a, i+1, high);
    }
}