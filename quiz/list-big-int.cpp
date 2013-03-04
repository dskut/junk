
#include <iostream>
#include <sstream>
#include <assert.h>
using namespace std;

class TBigIntBase {
protected:
    struct TNode {
        int Value;
        TNode* Next;
        
        TNode(int value, TNode* next = NULL)
            : Value(value)
            , Next(next)
        {}
    };

    TNode* ListHead;

    void Swap(TBigIntBase& other) {
        TNode* tmp = other.ListHead;
        other.ListHead = ListHead;
        ListHead = tmp;
    }

public:
    TBigIntBase()
        : ListHead(NULL)
    {}

    TBigIntBase(const TBigIntBase& other) 
        : ListHead(NULL)
    {
        TNode* iter = other.ListHead;
        TNode* current = NULL;
        if (iter) {
            ListHead = new TNode(iter->Value);
            current = ListHead;
            iter = iter->Next;
        }
        while (iter) {
            TNode* node = new TNode(iter->Value);
            current->Next = node;
            current = node;
            iter = iter->Next;
        }
    }

    ~TBigIntBase() {
        Clear();
    }

    void Clear() {
        TNode* iter = ListHead;
        while (iter) {
            TNode* next = iter->Next;
            delete iter;
            iter = next;
        }
        ListHead = NULL;
    }

    void PushFront(int x) {
        TNode* node = new TNode(x, ListHead);
        ListHead = node;
    }

    string ToString() const {
        stringstream stream;
        TNode* iter = ListHead;
        if (iter) {
            stream << iter->Value;
            iter = iter->Next;
        }
        while (iter) {
            stream << "->" << iter->Value; 
            iter = iter->Next;
        }
        return stream.str();
    }

    size_t Size() const {
        size_t res = 0;
        for (TNode* iter = ListHead; iter; iter = iter->Next) {
            ++res;
        }
        return res;
    }
};

class TBigInt: public TBigIntBase {
public:
    TBigInt()
    {}

    TBigInt(const TBigInt& other) 
        : TBigIntBase(other)
    {}

    TBigInt& operator=(const TBigInt& other) {
        TBigInt tmp(other);
        tmp.Swap(*this);
        return *this;
    }

    TBigInt& operator+=(const TBigInt& other) {
        TNode* iter = ListHead;
        TNode* otherIter = other.ListHead;
        TNode* prev = NULL;
        TNode* otherPrev = NULL;
        bool carry = false;
        for (; iter && otherIter; iter = iter->Next, otherIter = otherIter->Next) {
            iter->Value += otherIter->Value + carry;
            if (iter->Value >= 10) {
                iter->Value -= 10;
                carry = true;
            } else {
                carry = false;
            }
            prev = iter;
            otherPrev = otherIter;
        }
        if (!iter) {
            prev = otherPrev;
            iter = otherIter;
        }
        for (; iter; iter = iter->Next) {
            iter->Value += carry;
            if (iter->Value >= 10) {
                iter->Value -= 10;
                carry = true;
            } else {
                carry = false;
            }
            prev = iter;
        }
        if (carry) {
            TNode* node = new TNode(1);
            prev->Next = node;
        }
        return *this;
    }

    TBigInt operator+(const TBigInt& other) const {
        TBigInt res = *this;
        res += other;
        return res;
    }
};

class TBigDirectInt: public TBigIntBase {
private:
    bool DoAdd(TNode* iter, TNode* otherIter) {
        if (!iter) {
            return false;
        }
        bool carry = DoAdd(iter->Next, otherIter->Next);
        iter->Value += otherIter->Value + carry;
        if (iter->Value >= 10) {
            iter->Value -= 10;
            return true;
        } else {
            return false;
        }
    }
    
    void Pad(size_t size) {
        for (size_t i = 0; i < size; ++i) {
            PushFront(0);
        }
    }

public:
    TBigDirectInt()
    {}

    TBigDirectInt(const TBigInt& other) 
        : TBigIntBase(other)
    {}

    TBigDirectInt& operator=(const TBigDirectInt& other) {
        TBigDirectInt tmp(other);
        tmp.Swap(*this);
        return *this;
    }

    TBigDirectInt& operator+=(TBigDirectInt other) {
        size_t size = Size();
        size_t otherSize = other.Size();
        if (size > otherSize) {
            other.Pad(size - otherSize);
        } else if (size < otherSize) {
            Pad(otherSize - size);
        }
        assert(Size() == other.Size());
        bool carry = DoAdd(ListHead, other.ListHead);
        if (carry) {
            PushFront(1);
        }
        return *this;
    }

    TBigDirectInt operator+(const TBigDirectInt& other) const {
        TBigDirectInt res = *this;
        res += other;
        return res;
    }
};

int main() {
    TBigInt x;
    TBigInt y;
    TBigInt z;

    // x = 617
    x.Clear();
    x.PushFront(6);
    x.PushFront(1);
    x.PushFront(7);
    cout << "x = " << x.ToString() << endl; // 7->1->6
    // y = 295
    y.Clear();
    y.PushFront(2);
    y.PushFront(9);
    y.PushFront(5);
    cout << "y = " << y.ToString() << endl; // 5->9->2

    z = x + y;
    cout << "z = " << z.ToString() << endl; // 2->1->9

    x.Clear();
    x.PushFront(1);
    x.PushFront(9);
    x.PushFront(9);
    x.PushFront(9);
    cout << "x = " << x.ToString() << endl; // 9->9->9->1

    y.Clear();
    y.PushFront(5);
    cout << "y = " << y.ToString() << endl; // 5

    z = x + y;
    cout << "z = " << z.ToString() << endl; // 4->0->0->2


    TBigDirectInt a;
    TBigDirectInt b;
    TBigDirectInt c;

    // a = 98923 
    a.Clear();
    a.PushFront(3);
    a.PushFront(2);
    a.PushFront(9);
    a.PushFront(8);
    a.PushFront(9);
    cout << "a = " << a.ToString() << endl; // 9->8->9->2->3
    // y = 2647
    b.Clear();
    b.PushFront(7);
    b.PushFront(4);
    b.PushFront(6);
    b.PushFront(2);
    cout << "b = " << b.ToString() << endl; // 2->6->4->7

    c = a + b;
    cout << "c = " << c.ToString() << endl; // 1->0->1->5->7->0

    return 0;
}
