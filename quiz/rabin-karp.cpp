
#include <cstring>
#include <cmath>
#include <iostream>

using namespace std;

size_t Code(const char* str, size_t size, size_t degree, size_t prime) {
    size_t res = 0;
    for (size_t i = 0; i < size; ++i) {
        res = (res * degree + str[i]) % prime;
    }
    return res;
}

bool NaiveMatch(const char* text, const char* pattern) {
    for (; *pattern; ++text, ++pattern) {
        if (*pattern != *text) {
            return false;
        }
    }
    return true;
}

void RabinKarpSearch(const char* text, const char* pattern,
                     size_t degree, size_t prime)
{
    size_t patternSize = strlen(pattern);
    size_t base = (size_t)pow(degree, patternSize - 1) ;
    size_t patternCode = Code(pattern, patternSize, degree, prime);
    size_t curTextCode = Code(text, patternSize, degree, prime);
    for (size_t shift = 0; *(text + patternSize - 1); ++text, ++shift) {
        if (curTextCode == patternCode && NaiveMatch(text, pattern)) {
            cout << shift << endl;
        }
        if (*(text + patternSize)) {
            curTextCode = ((curTextCode - (*(text) * base)) * degree + *(text + patternSize)) % prime;
        }
    }
}

int main() {
    const char* text = "qweb qwenfhai qwexhd qwertrsdhaefd qwedfndhso qwe";
    cout << "text: " << text << endl;
    const char* pattern = "qwe";
    cout << "pattern: " << pattern << endl;
    size_t prime = 67108859;
    size_t degree = 256;
    RabinKarpSearch(text, pattern, degree, prime);
    return 0;
}
