
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct TBox {
    // width <= height
    int Width;
    int Depth;
    int Height;

    vector<TBox> GetRotations() const {
        vector<TBox> res(3);
        res[0] = *this;
        TBox d = {min(Width, Height), max(Width, Height), Depth};
        res[1] = d;
        TBox w = {min(Height, Depth), max(Height, Depth), Width};
        res[2] = w;
        return res;
    }

    int GetSquare() const {
        return Width * Depth;
    }

    bool DoesFit(const TBox& greater) const {
        return Width < greater.Width && Depth < greater.Depth;
    }
};

bool CompareSquare(const TBox& first, const TBox& second) {
    return first.GetSquare() > second.GetSquare();
}

ostream& operator<<(ostream& o, const vector<TBox>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        const TBox& b = v[i];
        o << "(" << b.Width << "," << b.Depth << "," << b.Height << ") ";
    }
    return o;
}

vector<TBox> RotateAndSort(const vector<TBox>& v) {
    vector<TBox> orig;
    orig.reserve(v.size() * 3);
    for (size_t i = 0; i < v.size(); ++i) {
        vector<TBox> rotations = v[i].GetRotations();
        orig.insert(orig.end(), rotations.begin(), rotations.end());
    }
    sort(orig.begin(), orig.end(), CompareSquare);
    return orig;
}

vector<TBox> MaxBoxStack(const vector<TBox>& v) {
    vector<TBox> orig = RotateAndSort(v);

    vector<int> heights(orig.size());
    for (size_t i = 0; i < orig.size(); ++i) {
        heights[i] = orig[i].Height;
    }

    vector<int> prev(orig.size(), -1);
    for (size_t i = 0; i < orig.size(); ++i) {
        for (size_t j = i + 1; j < orig.size(); ++j) {
            if (orig[j].DoesFit(orig[i]) && heights[i] + orig[j].Height > heights[j]) {
                heights[j] = heights[i] + orig[j].Height;
                prev[j] = i;
            }
        }
    }

    int maxHeight = 0;
    int winner = 0;
    for (size_t i = 0; i < orig.size(); ++i) {
        if (heights[winner] < heights[i]) {
            winner = i;
        }
    }

    vector<TBox> res;
    while (winner >= 0) {
        res.push_back(orig[winner]);
        winner = prev[winner];
    }
    return res;
}

int main() {
    TBox boxes[] = { {4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32} };
    vector<TBox> v;
    for (int i = 0; i < sizeof(boxes)/sizeof(boxes[0]); ++i) {
        v.push_back(boxes[i]);
    }
    cout << v << endl;
    vector<TBox> optimal = MaxBoxStack(v);
    cout << optimal << endl;
    return 0;
}
