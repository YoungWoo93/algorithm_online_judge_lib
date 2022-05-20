#include <iostream>
#include <string>
#include "../include/data_structure/LinkedList.h"
#include "../include/data_structure/Stack.h"
#include "../include/data_structure/Deque.h"
#include "../include/data_structure/BinaryTree.h"


using namespace _DataStructures_;
using namespace std;

void main()
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
			downTree.insert(value);
		}
		else if (cmd == 2)	
		{ 
			upTree.erase(value);
			downTree.erase(value);
		}

		cout << endl;
		cout << "  upTree" << endl;
		upTree.printTree();
		cout << endl;
		cout << "  downTree" << endl;
		downTree.printTree();
	}
}



