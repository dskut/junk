
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class TFsm {
public:
    vector<vector<size_t> > States;

public:
    TFsm(size_t patternSize)
        : States(patternSize + 1, vector<size_t>(256, 0))
        , FinalState(patternSize)
    {}

    size_t FinalState;

    void Set(size_t state, char sym, size_t nextState) {
        States[state][sym+127] = nextState;
    }

    size_t Step(size_t state, char sym) const {
        return States[state][sym+127];
    }
};

bool IsSuffix(const string& suffix, const string& str) {
    return suffix == str.substr(str.size() - suffix.size());
}

TFsm BuildFsm(const string& pattern, const string& alphabet) {
    TFsm fsm(pattern.size());
    for (size_t i = 0; i <= pattern.size(); ++i) {
        for (size_t j = 0; j < alphabet.size(); ++j) {
            string addedPattern = pattern.substr(0, i) + alphabet[j];
            for (size_t k = ::min(pattern.size(), i+1); true; --k) {
                string prefix = pattern.substr(0, k);
                if (IsSuffix(prefix, addedPattern)) {
                    fsm.Set(i, alphabet[j], k);
                    break;
                }
            }
        }
    }
    return fsm;
}

void FsmSearch(const string& text, const string& pattern, const string& alphabet) {
    TFsm fsm = BuildFsm(pattern, alphabet);
    cout << "fsm built" << endl;
    size_t state = 0;
    for (size_t i = 0; i < text.size(); ++i) {
        state = fsm.Step(state, text[i]);
        if (state == fsm.FinalState) {
            cout << i + 1 - pattern.size()<< endl;
        }
    }
}

int main() {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string text = "qwerfasioaysf qwqweqwersdfp qwerbf qwehapdf qwer";
    cout << "text: " << text << endl;
    string pattern = "qwer";
    cout << "pattern: " << pattern << endl;
    FsmSearch(text, pattern, alphabet);
    return 0;
}
