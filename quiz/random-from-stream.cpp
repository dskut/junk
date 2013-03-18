
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

ostream& operator<<(ostream& o, const vector<int>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        o << v[i] << " ";
    }
    return o;
}

int Random(int start, int end) {
    return start + rand() % (end - start + 1);
}

template <typename TIter>
int GetRandomFromStream(TIter begin, TIter end) {
    size_t count = 0;
    int res = -1;
    for (TIter iter = begin; iter != end; ++iter) {
        ++count;
        int r = Random(1, count);
        if (r == 1) {
            res = *iter;
        }
    }
    return res;
}

template <typename TIter>
vector<int> GetRandomFromStream(TIter begin, TIter end, int K) {
    vector<int> res(K, -1);
    TIter iter = begin;
    for (size_t i = 0; i < K && iter != end; ++i, ++iter) {
        res[i] = *iter;
    }
    size_t count = K;
    for (; iter != end; ++iter) {
        ++count;
        int r = Random(1, count);
        if (r <= K) {
            res[r-1] = *iter;
        }
    }
    return res;
}

int main() {
    srand(time(0));
    const int N = 10;
    const int K = 3;
    const int Samples = 5000000;
    vector<int> nums;
    for (size_t i = 0; i < N; ++i) {
        nums.push_back(i);
    }
    random_shuffle(nums.begin(), nums.end());
    vector<int> counts(N, 0);
    cout << GetRandomFromStream(nums.begin(), nums.end()) << endl;
    cout << GetRandomFromStream(nums.begin(), nums.end(), K) << endl;

    for (int i = 0; i < Samples; ++i) {
        int x = GetRandomFromStream(nums.begin(), nums.end());
        ++counts[x];
    }
    cout << "counts: " << counts << endl;

    counts.assign(N,0);
    for (int i = 0; i < Samples; ++i) {
        vector<int> rands = GetRandomFromStream(nums.begin(), nums.end(), K);
        for (size_t j = 0; j < K; ++j) {
            ++counts[rands[j]];
        }
    }
    cout << "counts: " << counts << endl;

    return 0;
}
