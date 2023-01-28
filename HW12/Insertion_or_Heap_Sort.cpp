#include <cstdio>

void InsertSort(int *a, int n);
void HeapSort(int *a, int n);
void PercolateDown(int *a, int i, int n);
bool Check(int *a, int n);

int checkSeq[100];
bool stopSorting = false;

int main() {
    int n;
    int insertSeq[100], heapSeq[100];

    scanf("%d", &n);
    for(int i=0; i<n; i++) {
        scanf("%d", &insertSeq[i]);
        heapSeq[i] = insertSeq[i];
    }
    for(int i=0; i<n; i++) {
        scanf("%d", &checkSeq[i]);
    }

    InsertSort(insertSeq, n);
    if(!stopSorting) {
        HeapSort(heapSeq, n);    
    }
    return 0;
}

void InsertSort(int *a, int n) {
    int i, j, temp;

    for(i=1; i<n; i++) {
        temp = a[i];
        for(j=i; j>0 && a[j-1] > temp; j--) {
            a[j] = a[j-1];
        }
        a[j] = temp;
        
        if(stopSorting) {
            for(int j=0; j<n-1; j++) {
                printf("%d ", a[j]);
            }
            printf("%d", a[n-1]);
            break;
        }
        if(Check(a, n)) {
            printf("Insertion Sort\n");
            stopSorting= true;
        }
    }
}

void HeapSort(int *a, int n) {
    int temp;

    for(int i=n/2; i>=0; i--) {
        PercolateDown(a, i, n);
    }
    for(int i=n-1; i>0; i--) {
        temp = a[i];
        a[i] = a[0];
        a[0] = temp;
        PercolateDown(a, 0, i);
        if(stopSorting) {
            for(int j=0; j<n-1; j++) {
                printf("%d ", a[j]);
            }
            printf("%d", a[n-1]);
            break;
        }
        if(Check(a, n)) {
            printf("Heap Sort\n");
            stopSorting = true;
        }
    }
}

void PercolateDown(int *a, int i, int n) {
    int child, temp;

    for(temp = a[i]; 2*i+1 < n; i=child) {
        child = 2*i + 1;
        if(child + 1 < n && a[child+1] > a[child]) {
            child++;
        }
        if(temp > a[child]) {
            break;
        }
        a[i] = a[child];
    }
    a[i] = temp;
}

bool Check(int *a, int n) {
    for(int i=0; i<n; i++) {
        if(a[i] != checkSeq[i]) {
            return false;
        }
    }
    return true;
}