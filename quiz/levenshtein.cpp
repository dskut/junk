
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int ReplaceCost(char a, char b) {
    return a != b;
}

int min(int a, int b, int c) {
    return min(a, min(b,c));
}

int LevenshteinDist(const string& first, const string& second) {
    const int InsertCost = 1;
    const int DeleteCost = 1;
    size_t M = first.size();
    size_t N = second.size();
    vector<vector<int> > dists(M+1, vector<int>(N+1, 0));
    for (int j = 1; j <= N; ++j) {
        dists[0][j] = dists[0][j-1] + InsertCost;
    }
    for (int i = 1; i <= M; ++i) {
        dists[i][0] = dists[i-1][0] + DeleteCost;
        for (int j = 1; j <= N; ++j) {
            dists[i][j] = min(dists[i-1][j] + DeleteCost,
                              dists[i][j-1] + InsertCost,
                              dists[i-1][j-1] + ReplaceCost(first[i-1], second[j-1]));
        }
    }
    return dists[M][N];
}

int main() {
    string first  = "connect";
    string second = "conehead";
    int dist = LevenshteinDist(first, second);
    cout << first << endl;
    cout << second << endl;
    cout << dist << endl;
    return 0;
}
