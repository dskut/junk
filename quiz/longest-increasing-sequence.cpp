
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

vector<int> GetLis(const vector<int>& nums) {
    size_t N = nums.size();
    vector<int> lengths(N, 1);
    vector<int> prev(N, -1);
    int maxLen = 1;
    int maxEnd = 0;
    for (size_t i = 1; i < N; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (nums[i] > nums[j] && lengths[i] < lengths[j] + 1) {
                lengths[i] = lengths[j] + 1;
                prev[i] = j;
                if (maxLen < lengths[i]) {
                    maxLen = lengths[i];
                    maxEnd = i;
                }
            }
        }
    }

    vector<int> res(maxLen, 0);
    for (int pos = maxLen - 1; pos >= 0; --pos) {
        res[pos] = nums[maxEnd];
        maxEnd = prev[maxEnd];
    }
    return res;
}

size_t CeilIndex(const vector<int>& ends, int num, size_t start, size_t end) {
    if (end == start) {
        return start;
    } else if (end == start + 1) {
        return end;
    }

    size_t mid = start + (end - start) / 2;
    if (ends[mid] > num) {
        return CeilIndex(ends, num, start, mid);
    } else if (ends[mid] < num) {
        return CeilIndex(ends, num, mid, end);
    } else {
        return mid;
    }
}

vector<int> GetLisFast(const vector<int>& nums) {
    size_t N = nums.size();
    vector<int> ends(N, 0);
    vector<int> prev(N+1, -1);
    size_t len = 1;
    ends[0] = nums[0];
    
    for (size_t i = 1; i < N; ++i) {
        if (nums[i] < ends[0]) {
            ends[0] = nums[i];
        } else if (nums[i] > ends[len-1]) {
            prev[i] = ends[len - 1];
            ends[len] = nums[i];
            ++len;
        } else {
            size_t ind = CeilIndex(ends, nums[i], 0, len-1);
            prev[i] = ends[ind-1];
            ends[ind] = nums[i];
        }
    }

    vector<int> res;
    for (int pos = ends[len - 1]; pos >= 0; pos = prev[pos]) {
        res.push_back(nums[pos]);
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    //int arr[] = {10, 22, 9, 33, 21, 50, 41, 60};
    int arr[] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    vector<int> v;
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i) {
        v.push_back(arr[i]);
    }
    cout << v << endl;

    vector<int> lis = GetLis(v);
    cout << lis << endl;

    vector<int> lisFast = GetLisFast(v);
    cout << lisFast << endl;

    return 0;
};
