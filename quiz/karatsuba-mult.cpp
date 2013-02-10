#include <string>
#include <iostream>
using namespace std;

string align(const string& str, size_t size) {
    string res = str;
    string add(size - str.size(), '0');
    res.insert(res.begin(), add.begin(), add.end());
    return res;
}

string shift(const string& str, size_t size) {
    string res = str;
    string add(size, '0');
    res.insert(res.end(), add.begin(), add.end());
    return res;
}

string trim(const string& str) {
	string res = str;
	while (res.size() && res[0] == '0') {
		res.erase(0, 1);
	}
	return res;
}

string plus(string a, string b) {
    size_t size = a.size() > b.size() ? a.size() : b.size();
    a = align(a, size);
    b = align(b, size);

    int m = 0;
    string res(size, '0');
    for (int i = size - 1; i >= 0; --i) {
        int ia = a[i] - 48;
        int ib = b[i] - 48;
        int ires = ia + ib + m;
        if (ires > 9) {
            ires = ires - 10;
            m = 1;
        } else {
            m = 0;
        }
        res[i] = ires + 48;
    }
    if (m) {
    	res.insert(res.begin(), '1');
    }
    return res;
}

string minus(string a, string b) {
    size_t size = a.size() > b.size() ? a.size() : b.size();
    a = align(a, size);
    b = align(b, size);

    int m = 0;
    string res(size, '0');
    for (int i = size - 1; i >= 0; --i) {
        int ia = a[i] - 48;
        int ib = b[i] - 48;
        int ires = ia - ib - m;
        if (ires < 0) {
            ires = ires + 10;
            m = 1;
        } else {
            m = 0;
        }
        res[i] = ires + 48;
    }
    return res;
}

string mult(string a, string b) {
    size_t size = a.size() > b.size() ? a.size() : b.size();
    a = align(a, size);
    b = align(b, size);

    if (size == 1) {
        int ia = a[0] - 48;
        int ib = b[0] - 48;
        int res = ia*ib;
        if (res > 9) {
        	return string(1, res / 10 + 48) + string(1, res % 10 + 48);
        } else {
        	return string(1, res + 48);
        }
    }

    size_t mid = size / 2;
    string a1 = a.substr(0, size - mid);
    string a0 = a.substr(size - mid, mid);

    string b1 = b.substr(0, size - mid);
    string b0 = b.substr(size - mid, mid);

    string x = mult(a0, b0);
    string y = mult(a1, b1);
    string z = mult(::plus(a0, a1), ::plus(b0, b1));

    string yy = shift(y, 2*mid);
    string zz = ::minus(z, ::plus(x, y));
    string zzz = shift(zz, mid);

    string xyy = ::plus(x, yy);
    string res = ::plus(xyy, zzz);
    res = ::trim(res);
    return res;
}

int main() {
    string a = "2937284659837205352351175";
    string b = "13465233452345234502634953204765203453453252";
    string res = mult(a, b);
    cout << a << endl;
    cout << "*" << endl;
    cout << b << endl;
    cout << "=" << endl;
    cout << res << endl;
    return 0;
}
