#include <cstdio>
#include <algorithm>

using namespace std;

int Hash(int *tbl, int key, int n); //return the index of key in hash table

int main() {
    int n;
    scanf("%d", &n);

    int cnt = 0; //number of keys
    int hashTBL[1000], newTBL[1000], isInNewTBL[1000], indexInHashTBL[10000];
    for(int i=0; i<n; i++) {
        scanf("%d", &hashTBL[i]);
        newTBL[i] = -1; //newTBL is empty
        isInNewTBL[i] = 0;
        
        if(hashTBL[i] >= 0) {
            indexInHashTBL[hashTBL[i]] = i;
            cnt++;
        }
    }

    sort(hashTBL, hashTBL + n);

    while(cnt > 0) {
        //try to hash the keys in ascending order into newTBL, so that indexInHashTBL[key] = indexInNewTBL[key]
        for(int i=0; i<n; i++) {
            if(hashTBL[i] >= 0 && isInNewTBL[i] == 0) {
                int pos = Hash(newTBL, hashTBL[i], n);
                if(pos == indexInHashTBL[hashTBL[i]]) {
                    cnt--;
                    newTBL[pos] = hashTBL[i];
                    isInNewTBL[i] = 1;

                    printf("%d", hashTBL[i]);
                    if(cnt != 0) {
                        printf(" ");
                    }
                    break;
                }
            }
        }
    }
}

int Hash(int *tbl, int key, int n) {
    int i = key % n;
    while(tbl[i] >= 0) {
        i = (i + 1) % n;
    }
    return i;
}