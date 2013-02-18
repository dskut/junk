
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;

void FindChange(size_t value, const vector<size_t>& coins, string res, size_t maxCoin) {
    if (value == 0) {
        cout << res << endl;
        return;
    }
    for (size_t i = 0; i < coins.size(); ++i) {
        if (value >= coins[i] && coins[i] <= maxCoin) {
            char buffer[256];
            sprintf(buffer, "%u ", coins[i]);
            string newRes = res + string(buffer);
            FindChange(value - coins[i], coins, newRes, coins[i]);
        }
    }
}

int main() {
    const size_t value = 100;
    vector<size_t> coins;
    coins.push_back(1);
    coins.push_back(5);
    coins.push_back(10);
    coins.push_back(25);
    string res;
    FindChange(value, coins, res, *coins.rbegin());
    return 0;
}
