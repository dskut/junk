
#include <iostream>
#include <stack>
using namespace std;

class TStack {
private:
	stack<int> Impl;

public:
	void Push(int elem) {
		Impl.push(elem);
	}

	int Pop() {
		int top = Impl.top();
		Impl.pop();
		return top;
	}

	size_t Size() const {
		return Impl.size();
	}
};

class TQueue {
private:
	TStack First;
	TStack Second;

public:
	void Push(int elem) {
		First.Push(elem);
	}

	int Pop() {
		if (!Second.Size()) {
			while (First.Size()) {
				Second.Push(First.Pop());
			}
		}
		return Second.Pop();
	}

	size_t Size() const {
		return First.Size() + Second.Size();
	}
};

int main() {
	TQueue q;
	q.Push(1);
	cout << "push 1" << endl;
	q.Push(2);
	cout << "push 2" << endl;
	q.Push(3);
	cout << "push 3" << endl;
	cout << "pop " << q.Pop() << endl;
	cout << "pop " << q.Pop() << endl;
	q.Push(4);
	cout << "push 4" << endl;
	cout << "pop " << q.Pop() << endl;
	cout << "pop " << q.Pop() << endl;
	q.Push(5);
	cout << "push 5" << endl;
	cout << "pop " << q.Pop() << endl;
	return 0;
}
