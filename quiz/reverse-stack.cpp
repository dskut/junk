// reverse a stack

#include <stack>
#include <iostream>
using namespace std;

class TStack {
private:
    stack<int> Stack;
    
public:
    void Push(int elem) {
        Stack.push(elem);
    }
    
    int Top() const {
        return Stack.top();
    }
    
    void Pop() {
        Stack.pop();
    }
    
    bool IsEmpty() const {
        return Stack.empty();
    }
};

void InsertBottom(TStack& s, int elem) {
    if (s.IsEmpty()) {
        s.Push(elem);
    } else {
        int top = s.Top();
        s.Pop();
        InsertBottom(s, elem);
        s.Push(top);
    }
}

void ReverseStack(TStack& s) {
    if (s.IsEmpty()) {
        return;
    }
    int top = s.Top();
    s.Pop();
    ReverseStack(s);
    InsertBottom(s, top);   
}


void PrintStack(TStack& st) {
    if (st.IsEmpty()) {
        return;
    }
    int top = st.Top();
    st.Pop();
    cout << top << " ";
    PrintStack(st);
    st.Push(top);
}

int main() {
    TStack st;
    st.Push(3);
    st.Push(1);
    st.Push(4);
    st.Push(5);
    st.Push(2);
    cout << "orig: ";
    PrintStack(st);
    cout << endl;
    ReverseStack(st);
    cout << "reverse: ";
    PrintStack(st);
    cout << endl;;
    return 0;
}
