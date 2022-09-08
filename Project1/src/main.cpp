#include <iostream>
#include <string>
#include "../include/data_structure/LinkedList.h"
#include "../include/data_structure/Stack.h"
#include "../include/data_structure/Deque.h"
#include "../include/data_structure/BinaryTree.h"
#include "../include/data_structure/RedBlackTree.h"
#include "../include/data_structure/Vector.h"
#include "../include/data_structure/HashTable.h"

using namespace _DataStructures_;
using namespace std;

void treeTest()
{
	BinaryTree<int> upTree([](int a, int b) {return a > b; });
	BinaryTree<int> downTree([](int a, int b) {return a < b; });

	while (true)
	{
		cout << "cmd 1: insert \t 2: erase" << endl;
		cout << "cmd value >> ";
		int cmd;
		int value;
		cin >> cmd >> value;

		if (cmd == 1)
		{
			upTree.insert(value);
			downTree.insert(value + 100);
		}
		else if (cmd == 2)	
		{ 
			upTree.erase(value);
			downTree.erase(value + 100);
		}

		cout << endl;
		cout << "  upTree" << endl;
		upTree.printTree();
		cout << endl;
		cout << "  downTree" << endl;
		downTree.printTree();
	}
}

void vectorTest()
{
	_DataStructures_::vector<double> v1;
	_DataStructures_::vector<double> v2(100, 10.0);
	for (int i = 0; i < 100; i++)
	{
		v1.push_back((double)i);
		v2.push_back((double)i);

		cout << " " << i << endl;
		cout << "v1 size : " << v1.size() << ", maxSize : " << v1.maxSize << ", last : " << v1[v1.size() - 1] << "\t";
		cout << "v2 size : " << v2.size() << ", maxSize : " << v2.maxSize << ", last : " << v2[v2.size() - 1] << endl;
	}

	for (int i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << "\t";
	}
	cout << endl << endl;
	v1.insert(v1.begin() + 1, 22);
	for (int i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << "\t";
	}
	cout << endl << endl;
	v1.erase(v1.begin() + 4);
	for (int i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << "\t";
	}
	cout << endl << endl;

	v1.erase(v1.begin() + 10, v1.end() - 10);
	for (int i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << "\t";
	}
	cout << endl << endl;

	for (auto it : v1)
	{
		cout << it;
	}


}

void hashTest()
{
	HashMap<string, int> htb;

	cout << sizeof("123") << endl;

	htb.insert("name0", 10);
	cout << htb.size() << endl;
	htb.insert("name1", 11);
	htb.insert("name2", 12);
	cout << htb["name0"] << endl;
	cout << htb["name1"] << endl;
	cout << htb["name2"] << endl;

	//HashMap<string, int> htb2(2);

	//htb2.insert("name0", 10);
	//htb2.insert("name1", 11);
	//htb2.insert("name2", 12);

	//cout << htb2["name0"] << endl;
	//cout << htb2["name1"] << endl;
	//cout << htb2["name2"] << endl;


	//HashMap<int, int> htb;
	//htb.insert(0, 10);
	//htb.insert(1, 11);
	//htb.insert(2, 12);
	//htb[5] = 15;
	//cout << htb[0] << endl;
	//cout << htb[1] << endl;
	//cout << htb[2] << endl;
	//cout << htb[5] << endl;

	//HashMap<int, int> htb2(2);
	//htb2.insert(0, 10);
	//htb2.insert(1, 11);
	//htb2.insert(2, 12);
	//cout << htb2[0] << endl;
	//cout << htb2[1] << endl;
	//cout << htb2[2] << endl;

	
}

void LLtest()
{
	LinkedList<int> tl;

	for (int i = 0; i < 9; i++)
	{
		tl.push_front(i);
		tl.insert(tl.end(), i);
		tl.insert(tl.begin() + 2, i);

	}

	for (auto item : tl)
		cout << " " << item;
	cout << endl;

	LinkedList<int> tl2(10, 9);
	for (auto item : tl2)
		cout << " " << item;
	cout << endl;

	tl.insert(tl.begin(), tl2);

	for (auto item : tl)
		cout << " " << item;
	cout << endl;

	tl.insert(tl.end(), tl2);
	for (auto item : tl)
		cout << " " << item;
	cout << endl;

	cout << endl << endl;

	tl.erase(tl.begin());
	for (auto item : tl)
		cout << " " << item;
	cout << endl;

	tl.erase(tl.begin()+ 10);
	for (auto item : tl)
		cout << " " << item;
	cout << endl;

	tl.erase(tl.begin(), tl.begin() + 20);
	for (auto item : tl)
		cout << " " << item;
	cout << endl;

	cout << endl << endl;

	tl.insert(tl.begin(), tl2.begin() + 1, tl2.begin() + 6);
	for (auto item : tl)
		cout << " " << item;
	cout << endl;
	tl.insert(tl.end(), tl2.begin() + 1, tl2.begin() + 6);
	for (auto item : tl)
		cout << " " << item;
	cout << endl;
}

#include <vector>
#include <string>

void printV(_DataStructures_::vector<_DataStructures_::vector<int>>& test)
{
	for (int i = 0; i < test.size(); i++)
	{
		for (int j = 0; j < test[i].size(); j++)
			cout << test[i][j] << " ";
		cout << endl;
	}
}

class testClass {
public:
	testClass()
	{
	}
	testClass(int i)
	{
		data = i;

		//cout << "new Class ! " << data << endl;
	}
	~testClass()
	{
		cout << "delete Class ! " << data << endl;
	}

	int data;
	char dummy[1024];
};


#include <queue>
#include "../include/data_structure/Heap.h"
void heapTest()
{
	_DataStructures_::Heap<int> mypq([](const int& a, const int& b) {return a < b; });

	int input = 0;
	while (true)
	{

		cin >> input;
		if (input == -1)
			break;

		mypq.push(input);
		
		cout << "==================" << endl;
		for (int i = 1; i < mypq.container.size(); i++)
			cout << "\t" << mypq.container[i];
		cout << endl << "==================" << endl;
	}

	while (!mypq.empty())
	{
		mypq.pop();
		cout << "==================" << endl;
		for (int i = 1; i < mypq.container.size(); i++)
			cout << "\t" << mypq.container[i];
		cout << endl << "==================" << endl;
	}
}


void autoHeapTest()
{
	std::priority_queue<int, std::vector<int>, greater<int>> stdpq;
	_DataStructures_::Heap<int> myqp([](const int& a, const int& b) {return a < b; });

	int targetSize = 10;

	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 1000; j++)
		{
			
			if (stdpq.empty() || rand() % stdpq.size() < targetSize)
			{
				int v = rand() % 100;
				stdpq.push(v);
				myqp.push(v);
			}

			if (stdpq.top() != myqp.top())
			{
				cout << "???" << endl;
			}
			
			if (!stdpq.empty() && rand() % stdpq.size() > targetSize)
			{
				stdpq.pop();
				myqp.pop();
			}

			if (stdpq.top() != myqp.top())
			{
				cout << "???" << endl;
			}
		}
	}


	targetSize = 100;

	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 1000; j++)
		{

			if (stdpq.empty() || rand() % stdpq.size() < targetSize)
			{
				int v = rand() % 100;
				stdpq.push(v);
				myqp.push(v);
			}

			if (stdpq.top() != myqp.top())
			{
				cout << "???" << endl;
			}

			if (!stdpq.empty() && rand() % stdpq.size() > targetSize)
			{
				stdpq.pop();
				myqp.pop();
			}

			if (stdpq.top() != myqp.top())
			{
				cout << "???" << endl;
			}
		}
	}
}



void RBtreeTest()
{
	RedBlackTree<int> rbt;


	while (true)
	{
		cout << "cmd 1: insert \t 2: erase" << endl;
		cout << "cmd value >> ";
		int cmd;
		int value;
		cin >> cmd >> value;

		if (cmd == 1)
		{
			rbt.insert(value);
		}
		else if (cmd == 2)
		{
			rbt.erase(value);
		}

		cout << endl;
		cout << " Tree" << endl;
		rbt.printTree();
		if (!rbt.proveTree()) {
			cout << " ???";
		}
	}
}

void RBtreeTestAuto()
{
	RedBlackTree<int> rbt;
	std::vector<int> pool;
	int temp;

	int treeWeight = 10;

	int push = 0;
	int pop = 0;
	int sizeSum = 0;

	int cycle = 1000;
	for(int count = 0; count < cycle; count++)
	{
		cout << rbt.blackDepth << endl;

		sizeSum += pool.size();
		if ((rand() % (pool.size() / 2 + 1)) < (treeWeight / 4) + 1)
		{
			push++;
			temp = rand() % 1000;
			cout << "\tinsert " << temp << endl;
			rbt.insert(temp);
			pool.push_back(temp);
		}
		else if(!pool.empty())
		{
			pop++;
			temp = rand() % pool.size();
			cout << "\terase " << pool[temp] << endl;
			rbt.erase(pool[temp]);
			pool.erase(pool.begin() + temp);
		}

		cout << endl;
		cout << " Tree" << endl;
		rbt.printTree();
		if (!rbt.proveTree()) {
			cout << " ??? " << count;
		}
	}

	cout << "push : " << push << "\t pop : " << pop << endl;
	cout << "size aver : " << sizeSum / cycle << endl;
}


void main()
{
	//RBtreeTest();
	RBtreeTestAuto();
}
