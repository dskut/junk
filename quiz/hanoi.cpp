
#include <stack>
#include <iostream>
using namespace std;

class TTower {
private:
    stack<int> Disks;
public:
    size_t Num;

    void Push(int disk) {
        Disks.push(disk);
    }

    int Pop() {
        int res = Disks.top();
        Disks.pop();
        return res;
    }

    void Move(TTower& dest, TTower& buffer, size_t count) {
        if (count == 0 || Disks.empty()) {
            return;
        }

        Move(buffer, dest, count - 1);
        MoveTop(dest);
        buffer.Move(dest, *this, count - 1);
    }

    void MoveTop(TTower& dest) {
        int disk = Pop();
        dest.Push(disk);
        cout << "Move disk " << disk << " from tower #" << Num << " to tower #" << dest.Num << endl;
    }
};

int main() {
    const size_t disksNum = 5;
    const size_t towersNum = 3;
    TTower towers[towersNum];
    for (size_t i = 0; i < towersNum; ++i) {
        towers[i].Num = i;
    }

    for (size_t i = 0; i < disksNum; ++i) {
        towers[0].Push(i);
    }
    towers[0].Move(towers[2], towers[1], disksNum);
    return 0;
}
