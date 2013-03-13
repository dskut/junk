
#include <vector>
#include <iostream>
#include <cstdio>
using namespace std;

ostream& operator<<(ostream& o, const vector<int>& v) {
	for (size_t i = 0; i < v.size(); ++i) {
		o << v[i] << " ";
	}
	return o;
}

ostream& operator<<(ostream& o, const vector<vector<int> >& v) {
	for (size_t i = 0; i < v.size(); ++i) {
		o << v[i] << endl;
	}
	return o;
}

vector<int>& operator+=(vector<int>& v, int x) {
    v.clear();
    v.push_back(x);
    return v;
}

vector<int>& operator,(vector<int>& v, int x) {
    v.push_back(x);
    return v;
}

struct TSubarrayRes {
    size_t Pos;
    size_t End;
    int Sum;
};

struct TSubmatrixRes {
    size_t Top;
    size_t Bottom;
    size_t Left;
    size_t Right;
    int Sum;
};

TSubarrayRes FindLargestSubarray(const vector<int>& v) {
    TSubarrayRes res = {0, 0, v[0]};
    int localMax = v[0];
    int localMaxInd = 0;
    for (size_t i = 1; i < v.size(); ++i) {
        if (localMax + v[i] < 0) {
            localMaxInd = i+1;
            localMax = 0;
        } else {
            localMax += v[i];
        }
        if (localMax > res.Sum) {
            res.Pos = localMaxInd;
            res.Sum = localMax;
            res.End = i;
        }
    }
    return res;
}

int Sum(const vector<vector<int> >& matrix, size_t i1, size_t j1, size_t i2, size_t j2) {
    int sum = 0;
    for (size_t i = i1; i <= i2; ++i) {
        for (size_t j = j1; j <= j2; ++j) {
            sum += matrix[i][j];
        }
    }
    return sum;
}

TSubmatrixRes FindLargestSubmatrixBrute(const vector<vector<int> >& matrix) {
    size_t n = matrix.size();
    TSubmatrixRes res = {0,0,0,0,0};
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            for (size_t k = i; k < n; ++k) {
                for (size_t m = j; m < n; ++m) {
                    int sum = Sum(matrix, i, j, k, m);
                    if (sum > res.Sum) {
                        res.Sum = sum;
                        res.Top = i;
                        res.Left = j;
                        res.Bottom = k;
                        res.Right = m;
                    }
                }
            }
        }
    }
    return res;
}

TSubmatrixRes FindLargestSubmatrixQuad(const vector<vector<int> >& matrix) {
    size_t n = matrix.size();
    vector<vector<int> > precomp(n, vector<int>(n, 0));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            precomp[i][j] = matrix[i][j];
            if (i > 0) {
                precomp[i][j] += precomp[i-1][j];
            }
            if (j > 0) {
                precomp[i][j] += precomp[i][j-1];
            }
            if (i > 0 && j > 0) {
                precomp[i][j] -= precomp[i-1][j-1];
            }
        }
    }

    TSubmatrixRes res = {0,0,0,0,0};
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            for (size_t k = i; k < n; ++k) {
                for (size_t m = j; m < n; ++m) {
                    int Skm = precomp[k][m];
                    int Sij = (i == 0 || j == 0) ? 0 : precomp[i-1][j-1];
                    int Sim = (i == 0) ? 0 : precomp[i-1][m];
                    int Skj = (j == 0) ? 0 :precomp[k][j-1];

                    int sum = Skm + Sij - Sim - Skj;
                    if (sum > res.Sum) {
                        res.Sum = sum;
                        res.Top = i;
                        res.Left = j;
                        res.Bottom = k;
                        res.Right = m;
                    }
                }
            }
        }
    }
    return res;
}


TSubmatrixRes FindLargestSubmatrixFast(const vector<vector<int> >& matrix) {
    size_t n = matrix.size();

    vector<vector<vector<int> > > columnSums(n, vector<vector<int> >(n, vector<int>(n, 0)));
    for (size_t j = 0; j < n; ++j) {
        for (size_t i = 0; i < n; ++i) {
            int sum = 0;
            for (size_t k = i; k < n; ++k) {
                sum += matrix[k][j];
                columnSums[i][k][j] = sum;
            }
        }
    }

    TSubmatrixRes res = {0,0,0,0,0};
    for (size_t i = 0; i < n; ++i) {
        for (size_t k = i; k < n; ++k) {
            int localMax = columnSums[i][k][0];
            int localMaxInd = 0;
            for (size_t j = 1; j < n; ++j) {
                if (localMax + columnSums[i][k][j] < 0) {
                    localMaxInd = j+1;
                    localMax = 0;
                } else {
                    localMax += columnSums[i][k][j];
                }
                if (localMax > res.Sum) {
                    res.Sum = localMax;
                    res.Top = i;
                    res.Left = localMaxInd;
                    res.Bottom = k;
                    res.Right = j;
                }
            }
        }
    }
    return res;
}


int main() {
    vector<int> v;
    v += 3, -4, -1, 5, -2, 4, -8, 3, 3, -2;
    TSubarrayRes res = FindLargestSubarray(v);
    cout << v << endl;
    cout << "[" << res.Pos << "," << res.End << "]=" << res.Sum << endl; // [3,5] = 7

    vector<vector<int> > matrix(10);
    matrix[0] +=  5, -2,  4,  2, -2,  0,  3, -7,  4, -1;
    matrix[1] += -6,  4, -7,  5, -9,  2, -8,  9, -6, -3;
    matrix[2] +=  7, -2, -4, -8, -9, -6,  1,  0, -5,  7;
    matrix[3] += -5,  4,  3, -9,  7,  6,  8,  4,  9, -1;
    matrix[4] += -1, -2, -8, -4,  4,  6, -3,  4, -5, -2;
    matrix[5] += -9,  5, -3,  6,  9,  1,  0,  4, -7, -2;
    matrix[6] += -3, -1,  2, -8, -4, -3, -5, -7,  4,  9;
    matrix[7] += -8,  4, -7,  8,  0,  1,  4, -2, -9, -6; 
    matrix[8] += -7, -4,  5, -9, -1, -3,  0,  4, -6, -8;
    matrix[9] +=  6,  8,  2, -3, -4,  1,  0, -9,  5,  5;
    cout << matrix;
    TSubmatrixRes mres;
    mres = FindLargestSubmatrixBrute(matrix);
    printf("[(%lu, %lu), (%lu, %lu)] = %d\n", mres.Top, mres.Left, mres.Bottom, mres.Right, mres.Sum);
    mres = FindLargestSubmatrixQuad(matrix);
    printf("[(%lu, %lu), (%lu, %lu)] = %d\n", mres.Top, mres.Left, mres.Bottom, mres.Right, mres.Sum);
    mres = FindLargestSubmatrixFast(matrix);
    printf("[(%lu, %lu), (%lu, %lu)] = %d\n", mres.Top, mres.Left, mres.Bottom, mres.Right, mres.Sum);
    return 0;
}
