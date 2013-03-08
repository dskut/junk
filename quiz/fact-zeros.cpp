
#include <iostream>
#include <cstdlib>
using namespace std;

int GetFactorsNum(int n, int div) {
    int res = 0;
    while (n % div == 0) {
        ++res;
        n /= div;
    }
    return res;
}

int GetFactZeros(int n) {
    int fives = 0;
    for (int i = 1; i <= n; ++i) {
        fives += GetFactorsNum(i, 5);
    }
    return fives;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "usage: " << argv[0] << " <X>" << endl;
        return 1;
    }
    int n = atoi(argv[1]);
    cout << GetFactZeros(n) << endl;
    return 0;
}
