
#include <iostream>
using namespace std;

int Sum(int a, int b) {
    while (b != 0) {
        int sum = a ^ b;
        b = (a & b) << 1;
        a = sum;
    }
    return a;
}

int main() {
    int a = 136;
    int b = 893;
    cout << a << " + " << b << " = " << Sum(a, b) << endl;
    return 0;
}
