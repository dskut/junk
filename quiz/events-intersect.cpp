
#include <iostream>
#include <vector>
using namespace std;

struct TMeeting {
    int Start;
    int End;
    
    TMeeting(int start, int end)
        : Start(start)
        , End(end)
    {}
};

struct TEvent {
    bool Start;
    int Time;

    TEvent()
    {}

    TEvent(bool start, int time)
        : Start(start)
        , Time(time)
    {}
};

template <typename T>
ostream& operator<<(ostream& o, const vector<T>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        o << v[i] << " ";
    }
    return o;
}

ostream& operator<<(ostream& o, const TMeeting& m) {
    o << "[" << m.Start << "," << m.End << "]";
}

template <typename T>
vector<T>& operator+=(vector<T>& v, const T& t) {
    v.push_back(t);
    return v;
}

template <typename T>
vector<T>& operator,(vector<T>& v, const T& t) {
    v.push_back(t);
    return v;
}

void FindBounds(const vector<TMeeting>& meetings, int& minTime, int& maxTime) {
    minTime = meetings[0].Start;
    maxTime = meetings[0].End;
    for (size_t i = 1; i < meetings.size(); ++i) {
        minTime = min(minTime, meetings[i].Start);
        maxTime = max(maxTime, meetings[i].End);
    }
}

vector<TEvent> SortEvents(const vector<TMeeting>& meetings) {
    int minTime, maxTime;
    FindBounds(meetings, minTime, maxTime);

    int periods = maxTime - minTime + 1;
    vector<int> counts(2*periods, 0);

    for (size_t i = 0; i < meetings.size(); ++i) {
        int indexStart = meetings[i].Start + 1;
        int indexEnd = meetings[i].End;
        ++counts[indexStart];
        ++counts[indexEnd];
    }

    for (size_t i = 0; i < counts.size() - 1; ++i) {
        counts[i+1] += counts[i];
    }

    vector<TEvent> events(2*meetings.size());
    for (size_t i = 0; i < meetings.size(); ++i) {
        int indexStart = meetings[i].Start + 1;
        int indexEnd = meetings[i].End;

        events[counts[indexStart]] = TEvent(true, meetings[i].Start);
        --counts[indexStart];

        events[counts[indexEnd]] = TEvent(false, meetings[i].End);
        --counts[indexEnd];
    }
    return events;
}

size_t GetBooking(const vector<TMeeting>& meetings) {
    vector<TEvent> events = SortEvents(meetings);
    size_t count = 0;
    size_t maxCount = 0;
    for (size_t i = 0; i < events.size(); ++i) {
        if (events[i].Start) {
            ++count;
            maxCount = max(maxCount, count);
        } else {
            --count;
        }
    }
    return maxCount;
}

int main() {
    vector<TMeeting> meetings;
    meetings += TMeeting(11,13), TMeeting(16,20), TMeeting(13,17),
                TMeeting(14,17), TMeeting(12,18), TMeeting(12,15),
                TMeeting(10,15), TMeeting(18,20), TMeeting(15,19);
    cout << meetings << endl;
    cout << GetBooking(meetings) << endl;

    return 0;
}
