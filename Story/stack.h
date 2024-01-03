#pragma once
template<typename T>
class stack {
	T* elem;
	int tp;
	int maxsize;
public:
	stack(int size = 10);
	int top();
	void pop();
	void push(T e);
	bool empty();
	~stack();
};

template<typename T>
stack<T>::stack(int size) {
	maxsize = size;
	elem = new T[maxsize];
	tp = 0;
}

template<typename T>
int stack<T>::top() {
	return elem[tp - 1];
}

template<typename T>
void stack<T>::pop()
{
	tp--;
}

template<typename T>
bool stack<T>::empty()
{
	return tp == 0;
}

template<typename T>
stack<T>::~stack()
{
	delete[]elem;
}


template<typename T>
void stack<T>::push(T e)
{
	elem[tp++] = e;
	if (tp >= maxsize)
	{
		T* tmp = new T[maxsize * 2];
		for (int i = 0; i < tp; i++)
			tmp[i] = elem[i];
		delete[]elem;
		elem = tmp;
	}
}