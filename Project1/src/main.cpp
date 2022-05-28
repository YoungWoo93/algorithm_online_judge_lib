#include <iostream>
#include <string>
#include "../include/data_structure/LinkedList.h"
#include "../include/data_structure/Stack.h"
#include "../include/data_structure/Deque.h"
#include "../include/data_structure/BinaryTree.h"
#include "../include/data_structure/Vector.h"

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
	for (int i = 0; i < 100000; i++)
	{
		v1.push_back((double)i);
		v2.push_back((double)i);

		cout << " " << i << endl;
		cout << "v1 size : " << v1.size() << ", maxSize : " << v1.maxSize << ", last : " << v1[v1.size() - 1] << "\t";
		cout << "v2 size : " << v2.size() << ", maxSize : " << v2.maxSize << ", last : " << v2[v2.size() - 1] << endl;
	}
}


void main()
{
	//treeTest();

	vectorTest();
}