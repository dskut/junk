
#include <iostream>
using namespace std;

int FindFixedPoint(const int* arr, int start, int end) {
    if (start > end) {
        return -1;
    }
    int mid = start + (end - start)/2;
    int item = arr[mid];
    if (item < mid) {
        return FindFixedPoint(arr, mid+1, end);
    } else if (item > mid) {
        return FindFixedPoint(arr, start, mid-1);
    } else {
        return mid;
    }
}

int FindFixedPointNonUniq(const int* arr, int start, int end) {
    if (start > end) {
        return -1;
    }
    int mid = start + (end - start)/2;
    int item = arr[mid];

    if (mid == item) {
        return mid;
    }

    int leftInd = min(item, mid-1);
    int leftRes = FindFixedPointNonUniq(arr, start, leftInd);
    if (leftRes != -1) {
        return leftRes;
    }

    int rightInd = max(item, mid+1);
    return FindFixedPointNonUniq(arr, rightInd, end);
    
}

int main() {
    int arr[10];
    arr[0] = -6;
    arr[1] = -4;
    arr[2] = -1;
    arr[3] = 0;
    arr[4] = 3;
    arr[5] = 4;
    arr[6] = 6;
    arr[7] = 9;
    arr[8] = 11;
    arr[9] = 14;
    int fp = FindFixedPoint(arr, 0, 9);
    cout << fp << endl; // 6

    int arrNonUniq[10];
    arr[0] = -1;
    arr[1] = 0;
    arr[2] = 1;
    arr[3] = 1;
    arr[4] = 3;
    arr[5] = 4;
    arr[6] = 5;
    arr[7] = 5;
    arr[8] = 8;
    arr[9] = 12;
    fp = FindFixedPointNonUniq(arr, 0, 19);
    cout << fp << endl; // 8
    return 0;
}
