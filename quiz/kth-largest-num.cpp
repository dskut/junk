
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

ostream& operator<<(ostream& o, const vector<int>& v) {
	for (size_t i = 0; i < v.size(); ++i) {
		o << v[i] << " ";
	}
	return o;
}

vector<int>& operator+=(vector<int>& v, int x) {
    v.push_back(x);
    return v;
}

vector<int>& operator,(vector<int>& v, int x) {
    v.push_back(x);
    return v;
}

// partition descending
int Partition(vector<int>& v, size_t start, size_t end) {
    int i = start;
    for (size_t j = start; j < end; ++j) {
        if (v[j] > v[end]) {
            swap(v[j], v[i]);
            ++i;
        }
    }
    swap(v[i], v[end]);
    return i;
}

int FindKthLargestInArray(vector<int>& v, size_t start, size_t end, int k) {
    if (end <= start) {
        if (k == 0) {
            return v[start];
        } else {
            return -1;
        }
    }

    size_t pivot = Partition(v, start, end);
    size_t pivotRelative = pivot - start; 
    if (pivotRelative > k) {
        return FindKthLargestInArray(v, start, pivot - 1, k);
    } else if (pivotRelative < k) {
        return FindKthLargestInArray(v, pivot + 1, end, k - pivotRelative - 1);
    } else {
        return v[pivot];
    }
}

int main() {
    srand(time(NULL));
    vector<int> v;
    v += 0, 1, 2, 2, 3, 4, 4, 6, 8, 8, 8, 9, 10, 
         11, 12, 12, 14, 15, 17, 19, 20;
    random_shuffle(v.begin(), v.end());
    int k = 4;  // in interface count k from 1, but in implementation count k from 0
    cout << v << endl;
    cout << FindKthLargestInArray(v, 0, v.size() - 1, k - 1) << endl; // 15

    return 0;
}
