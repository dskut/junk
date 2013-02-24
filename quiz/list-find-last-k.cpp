
#include <iostream>
using namespace std;

class TList {
private:
    struct TNode {
        int Data;
        TNode* Next;
        TNode(int data)
            : Data(data)
        {}
    };
    TNode* List;
public:
    ~TList() {
        while (List) {
            TNode* next = List->Next;
            delete List;
            List = next;
        }
    }

    void Push(int val) {
        TNode* cur = List;
        TNode* prev = NULL;
        while (cur) {
            prev = cur;
            cur = cur->Next;
        }
        cur = new TNode(val);
        if (prev) {
            prev->Next = cur;
        } else {
            List = cur;
        }
    }

    int FindLast(int pos) const {
        TNode* fwd = List;
        for (int i = 0; i <= pos; ++i) {
            if (!fwd) {
                return -1;
            }
            fwd = fwd->Next;
        }
        TNode* cur = List;
        while (fwd) {
            cur = cur->Next;
            fwd = fwd->Next;
        }
        return cur->Data;
    }

    void Print() {
        TNode* cur = List;
        cout << "List: ";
        while (cur) {
            cout << cur->Data << " ";
            cur = cur->Next;
        }
        cout << endl;
    }
};

int main() {
    TList list;
    list.Push(1);
    list.Push(2);
    list.Push(3);
    list.Push(4);
    list.Push(5);
    list.Push(6);
    list.Push(7);
    list.Print();
    int res = list.FindLast(2);
    cout << res << endl; // 5
    res = list.FindLast(6);
    cout << res << endl; // 1
    res = list.FindLast(0);
    cout << res << endl; // 7
    res = list.FindLast(7);
    cout << res << endl; // -1
    return 0;
}
