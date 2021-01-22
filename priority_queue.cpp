#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<list>

using namespace std;

template<class T>
struct Less
{
	bool operator() { const T& val, const T& va };
	return val < va;
};
template<class T>
struct Greater
{
	bool operator() { const T& val, const T& va };
	return val > va;
};
template<class T, class Container = vector<T>,class Compare = Less<T>>;
class PriorityQueue
{
public:
	void shiftup(int child)
	{
		int parent = (child - 1) / 2;
		while (child > 0)
		{
			if (_com(_c[parent],_c[child]))
			//if (_c[parent] < _c[child])
			{
				swap(_c[parent], _c[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
else
			break;
		}
	}
	void shiftDown(int root)
	{
		int childleft = root * 2 + 1;
		if (childleft > _c.size())
		{
			return;
		}
		else
		{
			if (childleft + 1 > _c.size())
			{
				if (_c[root] < _c[childleft])
					swap(_c[root], _c[childleft]);
				return;
			}else
		{
			int childright = childleft + 1;
			while (childleft < _c.size())
			{
				int ret = _c[childleft] > _c[childright] ? _c[childleft] : _c[childright];
				if (_c[root] < _c[ret])
				{
					swap(_c[root], _c[ret]);
					root = ret;
					childleft = root * 2 + 1;

				}
				else
					break;
			}

		}
	}
	}
	void shiftDown1(int root)
	{
		int parent = root;
		int child = 2 * parent + 1;
		while (child < _c.size())
		{

			if (child + 1 < _c.size() && _com(_c[parent], _c[child]))
			//if (child + 1 < _c.size() && _c[child] <= _c[child + 1])
				++child;

			if (_com(_c[parent], _c[child]))
			{
				swap(_c[parent], _c[child]);
				parent = child;
				child = parent * 2 + 1;
			}
else
			break;
		}
	}
	void pop()
	{
		swap(_c[0], _c[_c.size() - 1]);
		_c.pop_back();
		shiftDown(0);
		//shiftDown1(0);
	}

	void push(const T& val)
	{
		_c.push_back(val);
		shiftup(_c.size() - 1);
	}
	T& top()
	{
		return _c[0];
	}
	bool empty()
	{
		return _c.empty();
	}
	size_t size()
	{
		return _c.size();
	}
private:
	Container _c;
	Compare _com;
};
void test()
{
	PriorityQueue<int,vector<int>,Less<int>> pq;
	pq.push(10);
	pq.push(1);
	pq.push(5);
	pq.push(32);
	pq.push(23);
	pq.pop();
	pq.pop();
	pq.pop();


}

//template<class T,class Container >  开始实现小堆


int main()

{
	test();
	return 0;
}


