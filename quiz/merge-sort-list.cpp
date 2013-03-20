
#include <iostream>
#include <list>
#include <ctime>
#include <cstdlib>
using namespace std;

typedef list<int>::iterator TIter;

ostream& operator<<(ostream& o, const list<int>& seq) {
    for (list<int>::const_iterator iter = seq.begin(); iter != seq.end(); ++iter) {
        o << *iter << " ";
    }
    return o;
}

int Random(int start, int end) {
    return start + rand() % (end - start + 1);
}

TIter FindMid(TIter begin, TIter end) {
    TIter slow = begin;
    TIter fast = begin;
    while (fast != end) {
        ++slow;
        ++fast;
        if (fast == end) {
            break;
        }
        ++fast;
    }
    return slow;
}

void Print(TIter begin, TIter mid, TIter end) {
    for (TIter iter = begin; iter != mid; ++iter) {
        cout << *iter << " ";
    }
    cout << "| ";
    for (TIter iter = mid; iter != end; ++iter) {
        cout << *iter << " ";
    }
    cout << endl;
}

void Merge(list<int>& seq, TIter begin, TIter mid, TIter end) {
    //Print(begin, mid, end);
    TIter firstIter = begin;
    TIter secondIter = mid;
    list<int> newSeq;
    while (firstIter != mid || secondIter != end) {
        if (firstIter == mid) {
            newSeq.push_back(*secondIter);
            ++secondIter;
        } else if (secondIter == end) {
            newSeq.push_back(*firstIter);
            ++firstIter;
        } else {
            if (*firstIter < *secondIter) {
                newSeq.push_back(*firstIter);
                ++firstIter;
            } else {
                newSeq.push_back(*secondIter);
                ++secondIter;
            }
        }
    }
    for (TIter iter = begin, newIter = newSeq.begin(); iter != end; ++iter, ++newIter) {
        *iter = *newIter;
    }
}

void MergeSortImpl(list<int>& seq, TIter begin, TIter end) {
    if (begin == end) {
        return;
    }
    if (++begin == end) {
        return;
    }
    --begin;
    TIter mid = FindMid(begin, end);
    MergeSortImpl(seq, begin, mid);
    MergeSortImpl(seq, mid, end);
    Merge(seq, begin, mid, end);
}

void MergeSort(list<int>& seq) {
    MergeSortImpl(seq, seq.begin(), seq.end());
}

int main() {
    srand(time(0));
    list<int> orig;
    const size_t N = 20;
    for (size_t i = 0; i < N; ++i) {
        int x = Random(0, N);
        orig.push_back(x);
    }
    cout << orig << endl;
    MergeSort(orig);
    cout << orig << endl;
    return 0;
}
