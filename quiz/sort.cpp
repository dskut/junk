
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

ostream& operator<<(ostream& o, const vector<int>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        o << v[i] << " ";
    }
    return o;
}

// O(n^2)
void InsertionSort(vector<int>& v) {
    for (size_t i = 1; i < v.size(); ++i) {
        int key = v[i];
        int j = i - 1;
        while(j >= 0 && v[j] > key) {
            v[j+1] = v[j];
            --j;
        }
        v[j+1] = key;
    }
}

void Merge(vector<int>& v, size_t begin, size_t mid, size_t end) {
    vector<int> left(v.begin() + begin, v.begin() + mid + 1);
    vector<int> right(v.begin() + mid + 1, v.begin() + end + 1);
    size_t leftSize = mid - begin + 1;
    size_t rightSize = end - mid;
    size_t leftInd = 0;
    size_t rightInd = 0;
    for (size_t i = begin; i <= end; ++i) {
        if (leftInd == leftSize && rightInd < rightSize) {
            v[i] == right[rightInd];
            ++rightInd;
        } else if (rightInd == rightSize && leftInd < leftSize) {
            v[i] = left[leftInd];
            ++leftInd;
        } else if (left[leftInd] < right[rightInd]) {
            v[i] = left[leftInd];
            ++leftInd;
        } else {
            v[i] = right[rightInd];
            ++rightInd;
        }
    }
}

void MergeSortImpl(vector<int>& v, size_t begin, size_t end) {
    if (end > begin) {
        size_t mid = (begin + end) / 2;
        MergeSortImpl(v, begin, mid);
        MergeSortImpl(v, mid + 1, end);
        Merge(v, begin, mid, end);
    }
}

// O(n*log(n))
void MergeSort(vector<int>& v) {
    MergeSortImpl(v, 0, v.size() - 1);
}

int Partition(vector<int>& v, int begin, int end) {
    if (begin == end) {
        return begin;
    }
    int pivot = v[end];
    int i = begin - 1;
    for (int j = begin; j < end; ++j) {
        if (v[j] < pivot) {
            ++i;
            ::swap(v[j], v[i]);
        }
    }
    ::swap(v[i+1], v[end]);
    return i+1;
}

void QuickSortImpl(vector<int>& v, int begin, int end) {
    if (end > begin) {
        int mid = Partition(v, begin, end);
        QuickSortImpl(v, begin, mid - 1);
        QuickSortImpl(v, mid + 1, end);
    }
}

// O(n*log(n)), worst case O(n^2)
void QuickSort(vector<int>& v) {
    QuickSortImpl(v, 0, v.size() - 1); 
}

void MaxHeapify(vector<int>& v, size_t ind, size_t heapSize) {
    size_t left = 2*(ind+1) - 1;
    size_t right = 2*(ind+1);
    size_t largest = ind;
    if (left < heapSize && v[left] > v[largest]) {
        largest = left;
    }
    if (right < heapSize && v[right] > v[largest]) {
        largest = right;
    }
    if (largest != ind) {
        ::swap(v[ind], v[largest]);
        MaxHeapify(v, largest, heapSize);
    }
}

void BuildMaxHeap(vector<int>& v) {
    for (int i = v.size()/2 - 1; i >= 0; --i) {
        MaxHeapify(v, i, v.size());
    }
}

// O(n*log(n))
void HeapSort(vector<int>& v) {
    BuildMaxHeap(v);
    size_t heapSize = v.size();
    for (size_t i = v.size() - 1; i > 0; --i) {
        ::swap(v[i], v[0]);
        MaxHeapify(v, 0, --heapSize);
    }
}

// O(n)
void CountSort(vector<int>& v, size_t max) {
    vector<int> counts(max+1, 0);
    vector<int> res(v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        ++counts[v[i]];
    }
    for (size_t i = 1; i < counts.size(); ++i) {
        counts[i] += counts[i - 1];
    }
    for (int i = v.size() - 1; i >= 0; --i) {
        res[counts[v[i]]-1] = v[i];
        --counts[v[i]];
    }
    v = res;
}

int GetByte(int n, size_t byteInd) {
    return (n >> 8*byteInd) & 255;
}

void RadixCountSort(vector<int>& v, size_t byteInd) {
    size_t max = 1<<8;
    vector<int> counts(max+1, 0);
    vector<int> res(v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        ++counts[GetByte(v[i], byteInd)];
    }
    for (size_t i = 1; i < counts.size(); ++i) {
        counts[i] += counts[i - 1];
    }
    for (int i = v.size() - 1; i >= 0; --i) {
        res[counts[GetByte(v[i], byteInd)]-1] = v[i];
        --counts[GetByte(v[i], byteInd)];
    }
    v = res;
}

// O(n)
void RadixSort(vector<int>& v) {
    size_t bytes = sizeof(int);
    for (size_t i = 0; i < bytes; ++i) {
        RadixCountSort(v, i);
    }
}

// O(n)
void BucketSort(vector<int>& v, int max) {
    size_t size = v.size();
    vector<vector<int> > buckets(size);
    for (size_t i = 0; i < v.size(); ++i) {
        size_t bucketInd = v[i] / max;
        buckets[bucketInd].push_back(v[i]);
    }
    vector<int> res;
    for (size_t i = 0; i < buckets.size(); ++i) {
        InsertionSort(buckets[i]);
        res.insert(res.end(), buckets[i].begin(), buckets[i].end());
    }
    v = res;
}

int main() {
    srand(time(0));
    const size_t N = 20;
    vector<int> v(N);
    for (size_t i = 0; i < N; ++i) {
        size_t item = (double)rand() / RAND_MAX * (N+1);
        v[i] = item;
    }
    cout << "origin:         " << v << endl;
    vector<int> orig = v;

    v = orig;
    InsertionSort(v);
    cout << "insertion sort: " << v << endl;

    v = orig;
    MergeSort(v);
    cout << "merge     sort: " << v << endl;

    v = orig;
    QuickSort(v);
    cout << "quick     sort: " << v << endl;

    v = orig;
    HeapSort(v);
    cout << "heap      sort: " << v << endl;

    v = orig;
    CountSort(v, N);
    cout << "count     sort: " << v << endl;

    v = orig;
    RadixSort(v);
    cout << "radix     sort: " << v << endl;

    v = orig;
    BucketSort(v, N);
    cout << "bucket    sort: " << v << endl;

    return 0;
}
