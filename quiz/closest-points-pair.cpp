
#include <vector>
#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>
using namespace std;

struct TPoint {
    int X;
    int Y;
    TPoint(int x, int y)
        : X(x)
        , Y(y)
    {}
};

double Dist(const TPoint& first, const TPoint& second) {
    int dx = first.X - second.X;
    int dy = first.Y - second.Y;
    return sqrt(dx*dx + dy*dy);
}

bool CompareX(const TPoint& first, const TPoint& second) {
    return first.X < second.X;
}

bool CompareY(const TPoint& first, const TPoint& second) {
    return first.Y < second.Y;
}

double GetMinDistBrute(const vector<TPoint>& points, size_t start, size_t end) {
    double res = numeric_limits<double>::max();
    for (size_t i = start; i <= end - 1; ++i) {
        for (size_t j = i + 1; j <= end; ++j) {
            double dist = Dist(points[i], points[j]);
            if (dist < res) {
                res = dist;
            }
        }
    }
    return res;
}

double GetMinStripDist(vector<TPoint>& strip, double minDist) {
    sort(strip.begin(), strip.end(), CompareY);
    for (size_t i = 0; i < strip.size() - 1; ++i) {
        for (size_t j = i + 1; j < strip.size() && strip[j].Y - strip[i].Y < minDist; ++j) {
            double dist = Dist(strip[i], strip[j]);
            if (dist < minDist) {
                minDist = dist;
            }
        }
    }
    return minDist;
}

double GetMinDistImpl(const vector<TPoint>& points, size_t start, size_t end) {
    if (end - start <= 2) {
        return GetMinDistBrute(points, start, end);
    }
    size_t mid = start + (end - start)/2;
    double leftMinDist = GetMinDistImpl(points, start, mid);
    double rightMinDist = GetMinDistImpl(points, mid+1, end);
    double minDist = min(leftMinDist, rightMinDist);

    vector<TPoint> strip;
    for (size_t i = start; i <= end; ++i) {
        if (abs(points[i].X - points[mid].X) < minDist) {
            strip.push_back(points[i]);
        }
    }
    minDist = GetMinStripDist(strip, minDist);
    return minDist;
}

double GetMinDist(vector<TPoint>& points) {
    sort(points.begin(), points.end(), CompareX);
    return GetMinDistImpl(points, 0, points.size() - 1);
}

template <typename T>
ostream& operator<<(ostream& o, const vector<T>& v) {
	for (size_t i = 0; i < v.size(); ++i) {
		o << v[i] << " ";
	}
	return o;
}

ostream& operator<<(ostream& o, const TPoint& point) {
    o << "(" << point.X << ", " << point.Y << ")";
    return o;
}

template <typename T>
vector<T>& operator+=(vector<T>& v, T x) {
    v.clear();
    v.push_back(x);
    return v;
}

template <typename T>
vector<T>& operator,(vector<T>& v, T x) {
    v.push_back(x);
    return v;
}

int main() {
    vector<TPoint> points;
    points += TPoint(2, 3), TPoint(12, 30), TPoint(40, 50), 
              TPoint(5, 1), TPoint(12, 10), TPoint(3, 4);
    cout << "points: " << points << endl;
    cout << "min dist = " << GetMinDist(points) << endl;
    return 0;
}
