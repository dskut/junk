
#include <iostream>
using namespace std;

void reverse(char* str) {
    int size = 0;
    char* begin = str;
    char* end = str;
    while (*end) {
        ++end;
        ++size;
    }
    --end;
    for (int i = 0; i < size/2; ++i) {
        char tmp = *begin;
        *begin = *end;
        *end = tmp;
        ++begin;
        --end;
    }
}

int main() {
    char str[] = "qwertyuiop";
    cout << str << endl;
    reverse(str);
    cout << str << endl;

    return 0;
}
