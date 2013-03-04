
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

ostream& operator<<(ostream& o, const vector<string>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        o << v[i] << " ";
    }
    return o;
}

struct TAnagram {
    string Orig;
    string Sorted;

    TAnagram(const string& orig, const string& sorted)
        : Orig(orig)
        , Sorted(sorted)
    {}

    bool operator<(const TAnagram& other) {
        if (Sorted != other.Sorted) {
            return Sorted < other.Sorted;
        }
        return Orig < other.Orig;
    }
};

int PartitionAnagrams(vector<TAnagram>& v, int start, int end) {
    TAnagram& part = v[end];
    int i = start;
    for (int j = start; j < end; ++j) {
        if (v[j] < part) {
            swap(v[i], v[j]);
            ++i;
        }
    }
    swap(v[end], v[i]);
    return i;
}

void QuickSortAnagrams(vector<TAnagram>& v, int start, int end) {
    if (end > start) {
        int p = PartitionAnagrams(v, start, end);
        QuickSortAnagrams(v, start, p - 1);
        QuickSortAnagrams(v, p + 1, end);
    }
}

void SortAnagrams(vector<string>& v) {
    vector<TAnagram> anagrams;
    anagrams.reserve(v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        string sorted = v[i];
        sort(sorted.begin(), sorted.end());
        TAnagram a(v[i], sorted); 
        anagrams.push_back(a);
    }

    QuickSortAnagrams(anagrams, 0, anagrams.size() - 1);

    vector<string> sorted;
    sorted.reserve(v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        sorted.push_back(anagrams[i].Orig);
    }
    v = sorted;
}


int main() {
    vector<string> v;
    v.push_back("fruit");
    v.push_back("apple");
    v.push_back("juice");
    v.push_back("pine");
    v.push_back("rtfui");
    v.push_back("iucej");
    v.push_back("ejicu");
    v.push_back("cherry");
    v.push_back("ipne");
    v.push_back("papel");
    cout << v << endl;
    SortAnagrams(v);
    cout << v << endl;
}
