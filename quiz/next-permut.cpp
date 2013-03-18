
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void Reverse(int* v, int from, int to) {
    int mid = from + (to - from)/2;
    for (int i = from; i <= mid; ++i) {
        swap(v[i], v[to-i+from]);
    }
}

bool NextPermutation(int* v, int n) {
    int k = -1;
    for (size_t i = 0; i < n - 1; ++i) {
        if (v[i] < v[i+1]) {
            k = i;
        }
    }
    if (k < 0) {
        return false;
    }
    int m = k+1;
    for (size_t i = k+2; i < n; ++i) {
        if (v[i] > v[k]) {
            m = i;
        }
    }
    swap(v[k], v[m]);
    Reverse(v, k+1, n-1);
    return true;
}

int main() {
    int v[] = {2, 3, 1, 4, 5};
    int n = sizeof(v)/sizeof(v[0]);

    sort(v, v+n);
    do {
        for (size_t i = 0; i < n; ++i) {
            cout << v[i] << " ";
        }
        cout << endl;
    } while(next_permutation(v, v+n));

    cout << "----------------------" << endl;
    sort(v, v+n);
    do {
        for (size_t i = 0; i < n; ++i) {
            cout << v[i] << " ";
        }
        cout << endl;
    } while(NextPermutation(v, n));
    return 0;
}
