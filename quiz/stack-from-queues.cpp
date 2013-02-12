
#include <iostream>
#include <queue>
using namespace std;

class TQueue {
private:
	queue<int> Impl;

public:
	void Push(int elem) {
		Impl.push(elem);
	}

	int Pop() {
		int top = Impl.front();
		Impl.pop();
		return top;
	}

	size_t Size() {
		return Impl.size();
	}
};

class TFastPushStack {
private:
	TQueue First;
	TQueue Second;

public:
	void Push(int elem) {
		First.Push(elem);
	}

	int Pop() {
		while (First.Size() > 1) {
			Second.Push(First.Pop());
		}
		int res = First.Pop();
		while (Second.Size()) {
			First.Push(Second.Pop());
		}
		return res;
	}

	size_t Size() {
		return First.Size() + Second.Size();
	}
};

class TImprovedFastPushStack {
private:
	TQueue* Pushing;
	TQueue* Popping;

public:
	TImprovedFastPushStack()
		: Pushing(new TQueue)
		, Popping(new TQueue)
	{}

	~TImprovedFastPushStack() {
		delete Pushing;
		delete Popping;
	}

	void Push(int elem) {
		Pushing->Push(elem);
	}

	int Pop() {
		while (Pushing->Size() > 1) {
			Popping->Push(Pushing->Pop());
		}
		swap(Pushing, Popping);
		return Popping->Pop();
	}

	size_t Size() {
		return Pushing->Size() + Popping->Size();
	}
};

class TFastPopStack {
private:
	TQueue First;
	TQueue Second;

public:
	void Push(int elem) {
		First.Push(elem);
		while (Second.Size()) {
			First.Push(Second.Pop());
		}
		while (First.Size()) {
			Second.Push(First.Pop());
		}
	}

	int Pop() {
		return Second.Pop();
	}

	size_t Size() {
		return First.Size() + Second.Size();
	}
};

class TImprovedFastPopStack {
private:
	TQueue* Pushing;
	TQueue* Popping;

public:
	TImprovedFastPopStack()
		: Pushing(new TQueue)
		, Popping(new TQueue)
	{}

	~TImprovedFastPopStack() {
		delete Pushing;
		delete Popping;
	}

	void Push(int elem) {
		Pushing->Push(elem);
		while (Popping->Size()) {
			Pushing->Push(Popping->Pop());
		}
		swap(Pushing, Popping);
	}

	int Pop() {
		return Popping->Pop();
	}

	size_t Size() {
		return Pushing->Size() + Popping->Size();
	}
};

int main() {
	//TFastPushStack s;
	//TFastPopStack s;
	//TImprovedFastPushStack s;
	TImprovedFastPopStack s;

	s.Push(1);
	cout << "push 1" << endl;
	s.Push(2);
	cout << "push 2" << endl;
	s.Push(3);
	cout << "push 3" << endl;
	cout << "pop " << s.Pop() << endl;
	cout << "pop " << s.Pop() << endl;
	s.Push(4);
	cout << "push 4" << endl;
	cout << "pop " << s.Pop() << endl;
	cout << "pop " << s.Pop() << endl;
	s.Push(5);
	cout << "push 5" << endl;
	cout << "pop " << s.Pop() << endl;

	return 0;
}
