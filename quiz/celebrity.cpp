
#include <vector>
#include <queue>
#include <iostream>
#include <cstdlib>
using namespace std;

class TKnowledgeMatrix {
private:
    vector<vector<bool> > Matrix;
public:
    TKnowledgeMatrix(size_t N)
        : Matrix(N, vector<bool>(N, false))
    {}

    void Set(int who, int whom, bool val) {
        Matrix[who][whom] = val;
    }

    bool Knows(int who, int whom) const {
        return Matrix[who][whom];
    }

    size_t Size() const {
        return Matrix.size();
    }
};

TKnowledgeMatrix GenerateMatrix(size_t N, int celebrity) {
    TKnowledgeMatrix res(N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            bool val = ((double)rand() / RAND_MAX) > 0.5;
            res.Set(i, j, val);
        }
    }
    if (0 <= celebrity && celebrity < N) {
        for (int i = 0; i < N; ++i) {
            res.Set(i, celebrity, true);
            res.Set(celebrity, i, false);
        }
    }
    return res;
}

bool TestCelebrity(const TKnowledgeMatrix& m, int person) {
    for (int i = 0; i < m.Size(); ++i) {
        if (i == person) {
            continue;
        }
        if (m.Knows(person, i)) {
            return false;
        }
        if (!m.Knows(i, person)) {
            return false;
        }
    }
    return true;
}

int FindCelebrity(const TKnowledgeMatrix& m) {
    queue<int> testQueue;
    for (int i = 0; i < m.Size(); ++i) {
        testQueue.push(i);
    }
    while (testQueue.size() != 1) {
        int first = testQueue.front();
        testQueue.pop();
        int second = testQueue.front();
        testQueue.pop();
        if (m.Knows(first, second)) {
            testQueue.push(second);
        } else {
            testQueue.push(first);
        }
    }
    int candidate = testQueue.front();
    return TestCelebrity(m, candidate)
        ? candidate
        : -1;
}

int main() {
    srand(time(NULL));
    const size_t N = 100;
    int celebrity = N / 2; 
    TKnowledgeMatrix celebrityMatrix = GenerateMatrix(N, celebrity);
    int actual = FindCelebrity(celebrityMatrix);
    cout << actual << endl; // 50

    TKnowledgeMatrix nocelebrityMatrix = GenerateMatrix(N, -1);
    actual = FindCelebrity(nocelebrityMatrix);
    cout << actual << endl; // -1

    return 0;
}
