
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

string PrintDouble(double d) {
    string res;
    for (size_t i = 0; i < 32 && d != 0; ++i) {
        d *= 2;
        if (d >= 1) {
            res.push_back('1');
            d -= 1;
        } else {
            res.push_back('0');
        }
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

int InsertBits(int n, int m, int i, int j) {
    m <<= i;
    int tail = ~(0xffffffff << i) & n;
    m |= tail;
    n &= (0xffffffff << j);
    return n | m;
}

int main() {
    int n = 1357621;
    cout << "n: " << PrintBits(n) << endl;
    int m = 27;
    cout << "m: " << PrintBits(m) << endl; 
    int i = InsertBits(n, m, 1, 7);
    cout << "i: " << PrintBits(i) << endl;
    int s = SwapOddEvenBits(n);
    cout << "s: " << PrintBits(s) << endl;
    int e = SwapOddEvenBitsEff(n);
    cout << "e: " << PrintBits(e) << endl;
    double d = 0.72;
    cout << "d: " << d << " -> " << PrintDouble(d) << endl;
    return 0;
}
