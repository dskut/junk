
#include <stack>
#include <iostream>
#include <cstdlib>
using namespace std;

class TStack {
private:
    stack<int> Impl;
public:
    void Push(int val) {
        Impl.push(val);
    }

    void Pop() {
        Impl.pop();
    }

    int Top() const {
        return Impl.top();
    }

    bool IsEmpty() const {
        return Impl.empty();
    }
};

void Print(TStack& st) {
    if (st.IsEmpty()) {
        cout << endl;
    } else {
        int val = st.Top();
        cout << val << " ";
        st.Pop();
        Print(st);
        st.Push(val);
    }
}

void InsertAsc(TStack& st, int x) {
    if (st.IsEmpty()) {
        st.Push(x);
    } else {
        int top = st.Top();
        if (top >= x) {
            st.Push(x);
        } else {
            st.Pop();
            InsertAsc(st, x);
            st.Push(top);
        }
    }
}

void Sort(TStack& st) {
    TStack res;
    while (!st.IsEmpty()) {
        int x = st.Top();
        st.Pop();
        InsertAsc(res, x);
    }
    st = res;
}

int main() {
    srand(time(NULL));
    TStack st;
    const size_t N = 20;
    for (size_t i = 0; i < N; ++i) {
        int val = (double)rand() / RAND_MAX * (N+1);
        st.Push(val);
    }
    Print(st);
    Sort(st);
    Print(st);
    return 0;
}
