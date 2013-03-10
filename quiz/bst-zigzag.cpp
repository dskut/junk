
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include <iostream>
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

void PrintLevelOrder(const TNode* root) {
    if (!root) {
        return;
    }
    queue<const TNode*> q;
    q.push(root);
    while (!q.empty()) {
        const TNode* node = q.front();
        q.pop();
        cout << node->Key << " ";
        if (node->Left) {
            q.push(node->Left);
        }
        if (node->Right) {
            q.push(node->Right);
        }
    }
}

void PrintZigZagOrder(const TNode* root) {
    if (!root) {
        return;
    }

    typedef list<const TNode*> TNodes;
    TNodes nodes;
    nodes.push_back(root);
    for (size_t iter = 0; !nodes.empty(); ++iter) {
        for (TNodes::const_iterator i = nodes.begin(); i != nodes.end(); ++i) {
            cout << (*i)->Key << " ";
        }
        TNodes newNodes;
        for (TNodes::reverse_iterator i = nodes.rbegin(); i != nodes.rend(); ++i) {
            if (iter % 2 != 0) {
                if ((*i)->Left) {
                    newNodes.push_back((*i)->Left);
                }
                if ((*i)->Right) {
                    newNodes.push_back((*i)->Right);
                }
            } else {
                if ((*i)->Right) {
                    newNodes.push_back((*i)->Right);
                }
                if ((*i)->Left) {
                    newNodes.push_back((*i)->Left);
                }
            }
        }
        nodes = newNodes;
    }
}

/*****************************************************/

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

    cout << "level order: ";
    PrintLevelOrder(tree); // 10 5 15 3 8 12 17 1 4 7 11 14 20
    cout << endl;

    cout << "zig-zag order: ";
    PrintZigZagOrder(tree); // 10 15 5 3 8 12 17 20 14 11 7 4 10
    cout << endl;
    
    return 0;
}
