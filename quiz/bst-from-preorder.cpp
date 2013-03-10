
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TNode {
    int Key;
    TNode* Left;
    TNode* Right;

    TNode(int key)
        : Key(key)
        , Left(NULL)
        , Right(NULL)
    {}
};

// O(n) solution
TNode* FromPreOrder(const vector<int>& v) {
    stack<pair<TNode*, int> > st;
    TNode* root = new TNode(v[0]);
    st.push(make_pair(root, v[0]));
    for (size_t i = 1; i < v.size(); ++i) {
        TNode* node = new TNode(v[i]);
        if (v[i] <= st.top().second) {
            st.top().first->Left = node;
        } else {
            TNode* lastPopped = st.top().first;
            while (!st.empty() && st.top().second < v[i]) {
                lastPopped = st.top().first;
                st.pop();
            }
            lastPopped->Right = node;
        }
        st.push(make_pair(node, v[i]));
    }
    return root;
}

void TreeInsert(TNode* root, int key) {
    if (root->Key >= key) {
        if (root->Left) {
            TreeInsert(root->Left, key);
        } else {
            root->Left = new TNode(key);
        }
    } else {
        if (root->Right) {
            TreeInsert(root->Right, key);
        } else {
            root->Right = new TNode(key);
        }
    }
}

// O(n*logn) solution
TNode* FromPreOrderRecursive(const vector<int>& v) {
    TNode* root = new TNode(v[0]);
    for (size_t i = 1; i < v.size(); ++i) {
        TreeInsert(root, v[i]);
    }
    return root;
}

void PrintInOrder(const TNode* root) {
    if (!root) {
        return;
    }
    PrintInOrder(root->Left);
    cout << root->Key << " ";
    PrintInOrder(root->Right);
}

void PrintPreOrder(const TNode* root) {
    if (!root) {
        return;
    }
    cout << root->Key << " ";
    PrintPreOrder(root->Left);
    PrintPreOrder(root->Right);
}

void PrintPostOrder(const TNode* root) {
    if (!root) {
        return;
    }
    PrintPostOrder(root->Left);
    PrintPostOrder(root->Right);
    cout << root->Key << " ";
}

ostream& operator<<(ostream& o, const vector<int>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        o << v[i] << " ";
    }
    return o;
}

int main() {
    vector<int> v;
    v.push_back(10);
    v.push_back(5);
    v.push_back(3);
    v.push_back(1);
    v.push_back(4);
    v.push_back(8);
    v.push_back(7);
    v.push_back(15);
    v.push_back(12);
    v.push_back(11);
    v.push_back(14);
    v.push_back(17);
    v.push_back(20);

    cout << "pre order: " << v << endl;

    TNode* tree = FromPreOrder(v);
    //TNode* tree = FromPreOrderRecursive(v);

    cout << "[built] in order: ";
    PrintInOrder(tree); // should be ordered ascending
    cout << endl;

    cout << "[built] pre order: ";
    PrintPreOrder(tree); // same as v
    cout << endl;

    cout << "[built] post order: ";
    PrintPostOrder(tree); // 1 4 3 7 8 5 11 12 14 20 17 15 10
    cout << endl;
    
    return 0;
}
