
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

ostream& operator<<(ostream& o, const vector<int>& v) {
	for (size_t i = 0; i < v.size(); ++i) {
		o << v[i] << " ";
	}
	return o;
}

vector<int> findThreeSum(vector<int>& v) {
	if (v.size() < 3) {
		return vector<int>();
	}
	sort(v.begin(), v.end());
	if (*v.begin() > 0 || *v.rbegin() < 0) {
		return vector<int>();
	}

	for (size_t i = 0; i < v.size() - 3; ++i) {
		size_t j = i + 1;
		size_t k = v.size() - 1;
		while (j < k) {
			int sum = v[i] + v[j] + v[k];
			if (sum > 0) {
				--k;
			} else if (sum < 0){
				++j;
			} else {
				vector<int> res;
				res.push_back(v[i]);
				res.push_back(v[j]);
				res.push_back(v[k]);
				return res;
			}
		}
	}
	return vector<int>();
}

int main() {
	vector<int> v;
	v.push_back(-18);
	v.push_back(14);
	v.push_back(8);
	v.push_back(-9);
	v.push_back(7);
	v.push_back(-2);
	v.push_back(3);
	v.push_back(-5);
	v.push_back(3);
	cout << "orig: " << v << endl;
	vector<int> res = findThreeSum(v);
	if (res.empty()) {
		cout << "error!" << endl;
	} else {
		cout << "res: " << res << endl;
	}
	return 0;
}
