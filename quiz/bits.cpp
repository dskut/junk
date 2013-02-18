
#include <iostream>
#include <vector>
#include <string>
using namespace std;

string PrintBits(int n) {
    string res;
    for (size_t i = 0; i < 32; ++i) {
        char bit = (n & 1) + 48;
        res.insert(0, string(1,bit));
        n >>= 1;
    }
    return res;
}

int GetBit(int n, int i) {
    return (n >> i) & 1;
}

int UpdateBit(int n, int i, int b) {
    int mask = ~(1 << i);
    return (n & mask) | (b << i);
}

int SwapOddEvenBits(int n) {
    for (int i = 0; i < 32; i += 2) {
        int oddBit = GetBit(n, i);
        int evenBit = GetBit(n, i+1);
        n = UpdateBit(n, i, evenBit);
        n = UpdateBit(n, i+1, oddBit);
    }
    return n;
}

int SwapOddEvenBitsEff(int n) {
    int evenMask = 0b10101010101010101010101010101010;
    int oddMask  = 0b01010101010101010101010101010101;
    return ((n & evenMask) >> 1) | ((n & oddMask) << 1);
}

int main() {
    int n = 1357620;
    cout << "n: " << PrintBits(n) << endl;
    int s = SwapOddEvenBits(n);
    cout << "s: " << PrintBits(s) << endl;
    int e = SwapOddEvenBitsEff(n);
    cout << "e: " << PrintBits(e) << endl;
    return 0;
}
