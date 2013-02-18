
#include <string>
#include <iostream>
using namespace std;

void FindCorrectParenImpl(string s, size_t neededCount, 
                          size_t leftCount, size_t rightCount)
{
    if (leftCount == neededCount && rightCount == neededCount) {
        cout << s << endl;
        return;
    }
    if (leftCount < neededCount) {
        FindCorrectParenImpl(s + "(", neededCount, leftCount + 1, rightCount);
    }
    if (rightCount < leftCount) {
        FindCorrectParenImpl(s + ")", neededCount, leftCount, rightCount + 1);
    }
}

void FindCorrectParen(size_t count) {
    string s("(");
    size_t leftCount = 1;
    FindCorrectParenImpl(s, count, leftCount, 0);
}

int main() {
    const size_t count = 4;
    cout << "count = " << count << endl;
    FindCorrectParen(count);
    return 0;
}
