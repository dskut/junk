
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <sstream>
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

class TMinHeap {
private:
    vector<int> Array;

    size_t Parent(size_t i) const {
        return i == 0 ? 0 : (i+1)/2 - 1;
    }

    size_t Left(size_t i) const {
        return 2*(i+1)-1;
    }

    size_t Right(size_t i) const {
        return 2*(i+1);
    }

    size_t Size() const {
        return Array.size();
    }

    void Heapify(size_t i) {
        size_t left = Left(i);
        size_t right = Right(i);
        size_t smallest = i;
        if (left < Size() && Array[left] < Array[i]) {
            smallest = left;
        }
        if (right < Size() && Array[right] < Array[smallest]) {
            smallest = right;
        }
        if (smallest != i) {
            swap(Array[smallest], Array[i]);
            Heapify(smallest);
        }
    }

public:
    void Insert(int x) {
        Array.push_back(x);
        size_t i = Array.size() - 1;
        while (i > 0 && Array[Parent(i)] > Array[i]) {
            swap(Array[i], Array[Parent(i)]);
            i = Parent(i);
        }
    }

    void Pop() {
        Array[0] = Array[Array.size() - 1];
        Array.resize(Array.size() - 1);
        Heapify(0);
    }

    int Min() const {
        return Array[0];
    }

    string ToString() const {
        stringstream stream;
        stream << Array;
        return stream.str();
    }
};

int FindKthLargestInStream(const vector<int>& stream, size_t k) {
    TMinHeap heap;
    for (size_t i = 0; i <= k; ++i) {
        heap.Insert(stream[i]);
    }
    for (size_t i = k+1; i < stream.size(); ++i) {
        int min = heap.Min();
        if (min < stream[i]) {
            heap.Pop();
            heap.Insert(stream[i]);
        }
    }
    return heap.Min();
}

int main() {
    srand(time(NULL));
    vector<int> v;
    v += 0, 1, 2, 2, 3, 4, 4, 6, 8, 8, 8, 9, 10, 
         11, 12, 12, 14, 15, 17, 19, 20;
    random_shuffle(v.begin(), v.end());
    int k = 4;  // in interface count k from 1, but in implementation count k from 0
    cout << v << endl;
    cout << FindKthLargestInStream(v, k - 1) << endl; // 15

    return 0;
}
