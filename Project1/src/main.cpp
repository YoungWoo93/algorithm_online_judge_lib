#include <iostream>
#include <string>
#include "../include/data_structure/LinkedList.h"
#include "../include/data_structure/Stack.h"
#include "../include/data_structure/Deque.h"
#include "../include/data_structure/BinaryTree.h"
#include "../include/data_structure/Vector.h"
#include "../include/data_structure/HashTable.h"

using namespace _DataStructures_;
using namespace std;

void treeTest()
{
	BinaryTree<int> upTree([](BinaryTreeNode<int>* a, BinaryTreeNode<int>* b) {return a->value > b->value; });
	BinaryTree<int> downTree([](BinaryTreeNode<int>* a, BinaryTreeNode<int>* b) {return a->value < b->value; });

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
		else if (cmd == 3)
		{
			upTree.merge(&downTree, upTree.compare);
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
	Vector<double> v1;
	Vector<double> v2(100, 10.0);
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
	HashTable<string, int> htb;

	cout << sizeof("123") << endl;

	htb.insert("name0", 10);
	cout << htb.size() << endl;
	htb.insert("name1", 11);
	htb.insert("name2", 12);
	cout << htb["name0"] << endl;
	cout << htb["name1"] << endl;
	cout << htb["name2"] << endl;

	//HashTable<string, int> htb2(2);

	//htb2.insert("name0", 10);
	//htb2.insert("name1", 11);
	//htb2.insert("name2", 12);

	//cout << htb2["name0"] << endl;
	//cout << htb2["name1"] << endl;
	//cout << htb2["name2"] << endl;


	//HashTable<int, int> htb;
	//htb.insert(0, 10);
	//htb.insert(1, 11);
	//htb.insert(2, 12);
	//htb[5] = 15;
	//cout << htb[0] << endl;
	//cout << htb[1] << endl;
	//cout << htb[2] << endl;
	//cout << htb[5] << endl;

	//HashTable<int, int> htb2(2);
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

void main()
{
	vector<int> test;

	test.push_back(1);
	test.push_back(2);
	test.push_back(3);

	//LLtest();
	//treeTest();
	vectorTest();
	//hashTest();
}
