
#include <string>
#include <vector>
#include <iostream>
using namespace std;

enum EDirection {
    UNKNOWN,
    UP,
    LEFT,
    UPLEFT,
};

struct TTableElem {
    size_t Length;
    EDirection Dir;

    TTableElem(size_t length, EDirection dir)
        : Length(length)
        , Dir(dir)
    {}
};

ostream& operator<<(ostream& o, const vector<vector<TTableElem> >& table) {
    for (size_t i = 0; i < table.size(); ++i) {
        for (size_t j = 0; j < table[i].size(); ++j) {
            cout << table[i][j].Length << " ";
        }
        cout << endl;
    }
    return o;
}

string GetLcs(const string& first, const string& second) {
    size_t M = first.size();
    size_t N = second.size();
    vector<vector<TTableElem> > table(M+1, vector<TTableElem>(N+1, TTableElem(0, UNKNOWN)));
    for (size_t i = 0; i <= M; ++i) {
        table[i][0] = TTableElem(0, UNKNOWN);
    }
    for (size_t j = 0; j <= N; ++j) {
        table[0][j] = TTableElem(0, UNKNOWN);
    }
    for (size_t i = 1; i <= M; ++i) {
        for (size_t j = 1; j <= N; ++j) {
            if (first[i-1] == second[j-1]) {
                table[i][j] = TTableElem(table[i-1][j-1].Length + 1, UPLEFT);
            } else {
                if (table[i-1][j].Length >= table[i][j-1].Length) {
                    table[i][j] = TTableElem(table[i-1][j].Length, UP);
                } else {
                    table[i][j] = TTableElem(table[i][j-1].Length, LEFT);
                }
            }
        }
    }

    string res(table[M][N].Length, 'X');
    for (int i = M, j = N, pos = res.size() - 1; i > 0 && j > 0;) {
        if (table[i][j].Dir == UPLEFT) {
            res[pos] = first[i-1]; 
            --pos;
            --i;
            --j;
        } else if (table[i][j].Dir == LEFT) {
            --j;
        } else if (table[i][j].Dir == UP) {
            --i;
        }
    }
    return res;
}

int main() {
    string first  = "abcbdab";
    string second = "bdcaba";
    string lcs = GetLcs(first, second);
    cout << first << endl;
    cout << second << endl;
    cout << lcs << endl; // bcba OR bdab
    return 0;
}
