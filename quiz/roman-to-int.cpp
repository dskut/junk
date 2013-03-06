
#include <iostream>
#include <string>
using namespace std;

struct TRomanSym {
    char Sym;
    int Val;
} chars[] = { {'I', 1}
            , {'V', 5}
            , {'X', 10}
            , {'L', 50}
            , {'C', 100}
            , {'D', 500}
            , {'M', 1000}
            };

int eval(char c) {
    for (int i = 0; i < sizeof(chars)/sizeof(chars[0]); ++i) {
        if (chars[i].Sym == c) {
            return chars[i].Val;
        }
    }
    return 0;
}

int Convert(const string& str) {
    int res = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        int curVal = eval(str[i]);
        int nextVal = (i == str.size() - 1) ? 0 : eval(str[i+1]);
        if (nextVal > curVal) {
            res += nextVal - curVal;
            ++i;
        } else {
            res += curVal;
        }
    }
    return res;
}

int main() {
    string roman = "MCMLXXXIX";
    cout << Convert(roman) << endl; // 1989
}
