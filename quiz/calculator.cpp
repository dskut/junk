
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <stack>
using namespace std;

enum ETokenType {
    OPEN,
    CLOSE,
    MUL,
    DIV,
    PLUS,
    MINUS,
    NUM
};

struct TToken {
    ETokenType Type;
    int Value;

    TToken(ETokenType type, int val = 0)
        : Type(type)
        , Value(val)
    {}
};

bool IsOperator(ETokenType type) {
    return type == MUL || type == DIV || type == PLUS || type == MINUS;
}

int Priority(ETokenType type) {
    switch (type) {
    case OPEN:
    case CLOSE:
        return 3;
    case MUL:
    case DIV:
        return 2;
    case PLUS:
    case MINUS:
        return 1;
    case NUM:
    default:
        return 0;
    }
}

ostream& operator<<(ostream& o, const TToken& token) {
    switch (token.Type) {
    case OPEN: o << "OPEN"; break;
    case CLOSE: o << "CLOSE"; break;
    case MUL: o << "MUL"; break;
    case DIV: o << "DIV"; break;
    case PLUS: o << "PLUS"; break;
    case MINUS: o << "MINUS"; break;
    case NUM: o << token.Value; break;
    default: break;
    }
    return o;
}

ostream& operator<<(ostream& o, const vector<TToken>& tokens) {
    for (size_t i = 0; i < tokens.size(); ++i) {
        o << tokens[i] << " ";
    }
    return o;
}

int ParseInt(const string& s) {
    return atoi(s.c_str());
}

vector<TToken> Parse(const string& s) {
    vector<TToken> res;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == ' ') {
            continue;
        } else if (s[i] == '(') {
            res.push_back(TToken(OPEN));
        } else if (s[i] == ')') {
            res.push_back(TToken(CLOSE));
        } else if (s[i] == '*') {
            res.push_back(TToken(MUL));
        } else if (s[i] == '/') {
            res.push_back(TToken(DIV));
        } else if (s[i] == '+') {
            res.push_back(TToken(PLUS));
        } else if (s[i] == '-') {
            int prev;
            for (prev = i-1; prev >= 0; --prev) {
                if (s[prev] != ' ') {
                    break;
                }
            }
            if (i == 0 || s[prev] == ')' || s[prev] == '(' 
                       || s[prev] == '+' || s[prev] == '*' 
                       || s[prev] == '/')
            {
                ++i;
                string strNum(1, s[i]);
                while (isdigit(s[i + 1])) {
                    ++i;
                    if (i == s.size() - 1) {
                        break;
                    } else {
                        strNum += s[i];
                    }
                }
                res.push_back(TToken(NUM, (-1)*ParseInt(strNum)));
            } else {
                res.push_back(TToken(MINUS));
            }
        } else {
            string strNum(1, s[i]);
            if (i == s.size() - 1) {
                res.push_back(TToken(NUM, ParseInt(strNum)));
                continue;
            }
            while (isdigit(s[i+1])) {
                ++i;
                if (i == s.size() - 1) {
                    break;
                } else {
                    strNum += s[i];
                }
            }
            res.push_back(TToken(NUM, ParseInt(strNum)));
        }
    }
    return res;
}

vector<TToken> ToPostfix(const vector<TToken>& tokens) {
    vector<TToken> res;
    stack<TToken> st;
    for (size_t i = 0; i < tokens.size(); ++i) {
        ETokenType type = tokens[i].Type;
        if (type == NUM) {
            res.push_back(tokens[i]);
        } else if (type == OPEN) {
            st.push(tokens[i]);
        } else if (type == CLOSE) {
            while (st.top().Type != OPEN) {
                res.push_back(st.top());
                st.pop();
            }
            st.pop();
        } else {
            while (!st.empty() && IsOperator(st.top().Type) && Priority(st.top().Type) > Priority(type)) {
                res.push_back(st.top());
                st.pop();
            }
            st.push(tokens[i]);
        }
    }
    while (!st.empty()) {
        res.push_back(st.top());
        st.pop();
    }
    return res;
}

TToken Operate(const TToken& op, const TToken& firstTok, const TToken& secondTok) {
    int res = 0;
    int first = firstTok.Value;
    int second = secondTok.Value;
    switch (op.Type) {
    case PLUS:
        res = first + second;
        break;
    case MINUS:
        res = first - second;
        break;
    case MUL:
        res = first * second;
        break;
    case DIV:
        res = first / second;
        break;
    default:
        break;
    }
    return TToken(NUM, res);
}

int EvalTokens(const vector<TToken>& tokens) {
    stack<TToken> st;
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i].Type == NUM) {
            st.push(tokens[i]);
        } else {
            TToken second = st.top();
            st.pop();
            TToken first = st.top();
            st.pop();
            TToken res = Operate(tokens[i], first, second);
            st.push(res);
        }
    }
    return st.top().Value;
}

int Eval(const string& s) {
    vector<TToken> tokens = Parse(s);
    cout << tokens << endl;
    tokens = ToPostfix(tokens);
    cout << tokens << endl;
    int res = EvalTokens(tokens);
    return res;
}

int main() {
    string s = "-3 + 6*10 - (4 + 3)*-3";
    cout << s << endl;
    int res = Eval(s);
    cout << res << endl; 
    return 0;
}
