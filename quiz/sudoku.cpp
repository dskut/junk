
#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int> > TGrid;

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

const int N = 9;

bool FindEmpty(const TGrid& grid, int& row, int& col) {
    for (row = 0; row < N; ++row) {
        for (col = 0; col < N; ++col) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool HasRowConflict(const TGrid& grid, int row, int col, int num) {
    for (int i = 0; i < N; ++i) {
        if (i != col && grid[row][i] == num) {
            return true;
        }
    }
    return false;
}

bool HasColumnConflict(const TGrid& grid, int row, int col, int num) {
    for (int i = 0; i < N; ++i) {
        if (i != row && grid[i][col] == num) {
            return true;
        }
    }
    return false;
}

void GetSubgrid(int row, int col, int& sx, int& sy) {
    sy = row - row % 3;
    sx = col - col % 3;
}

bool HasSubgridConflict(const TGrid& grid, int row, int col, int num) {
    int sx, sy;
    GetSubgrid(row, col, sx, sy);
    for (int i = sy; i < sy + 3; ++i) {
        for (int j = sx; j < sx+3; ++j) {
            if (i != row && j != col && grid[i][j] == num) {
                return true;
            }
        }
    }
    return false;
}

bool HasConflicts(const TGrid& grid, int row, int col, int num) {
    return HasRowConflict(grid, row, col, num)
        || HasColumnConflict(grid, row, col, num)
        || HasSubgridConflict(grid, row, col, num);
}

bool Solve(TGrid& grid) {
    int row = -1;
    int col = -1;
    if (!FindEmpty(grid, row, col)) {
        return true;
    }
    for (int num = 1; num <= 9; ++num) {
        if (!HasConflicts(grid, row, col, num)) {
            grid[row][col] = num;
            if (Solve(grid)) {
                return true;
            }
            grid[row][col] = 0;
        }
    }
    return false;
}

vector<vector<int> > Sudoku(int grid[N][N]) {
    vector<vector<int> > res(N, vector<int>(N, 0));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            res[i][j] = grid[i][j];
        }
    }
    if (Solve(res)) {
        return res;
    } else {
        return vector<vector<int> >();
    }
}

int main() {
    int grid[N][N] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
                      {5, 2, 0, 0, 0, 0, 0, 0, 0},
                      {0, 8, 7, 0, 0, 0, 0, 3, 1},
                      {0, 0, 3, 0, 1, 0, 0, 8, 0},
                      {9, 0, 0, 8, 6, 3, 0, 0, 5},
                      {0, 5, 0, 0, 9, 0, 6, 0, 0},
                      {1, 3, 0, 0, 0, 0, 2, 5, 0},
                      {0, 0, 0, 0, 0, 0, 0, 7, 4},
                      {0, 0, 5, 2, 0, 6, 3, 0, 0}};
    vector<vector<int> > v = Sudoku(grid);
    cout << v;
    return 0;
}
