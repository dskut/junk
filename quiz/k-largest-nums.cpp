
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

// partition descending
size_t Partition(vector<int>& v, size_t start, size_t end) {
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

vector<int> FindKLargestInArray(vector<int>& v, size_t start, size_t end, int k) {
    if (end <= start) {
        if (k == 0) {
            return vector<int>(1, v[start]);
        } else {
            return vector<int>();
        }
    }

    size_t pivot = Partition(v, start, end);
    size_t pivotRelative = pivot - start; 
    if (pivotRelative > k) {
        return FindKLargestInArray(v, start, pivot - 1, k);
    } else if (pivotRelative < k) {
        vector<int> res(v.begin() + start, v.begin() + pivot + 1);
        vector<int> rightRes = FindKLargestInArray(v, pivot + 1, end, k - pivotRelative - 1);
        res.insert(res.end(), rightRes.begin(), rightRes.end());
        return res;
    } else {
        return vector<int>(v.begin() + start, v.begin() + pivot + 1);
    }
}

/***********************************************/

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

int main() {
    srand(time(NULL));
    vector<int> v;
    v += 0, 1, 2, 2, 3, 4, 4, 6, 8, 8, 8, 9, 10, 
         11, 12, 12, 14, 15, 17, 19, 20;
    random_shuffle(v.begin(), v.end());
    int k = 4;  // in interface count k from 1, but in implementation count k from 0

    cout << v << endl;

    vector<int> largest = FindKLargestInArray(v, 0, v.size() - 1, k - 1);
    sort(largest.begin(), largest.end()); // optional
    cout << largest << endl; // 15, 17, 19, 20

    return 0;
}
