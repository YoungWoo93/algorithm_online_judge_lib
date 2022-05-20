#pragma once
#include <functional>
#include <iostream>

#include "linkedList.h"

namespace _DataStructures_
{
	template <typename V>
	class BinaryTreeNode {

	public:
		BinaryTreeNode(V _value, size_t _insertNumber = 0, size_t _height = 0)
		{
			value = _value;
			insertNumber = _insertNumber;
			height = _height;

			parent = nullptr;
			left = nullptr;
			right = nullptr;
		}
		~BinaryTreeNode()
		{
			if (std::is_pointer<V>::value)
				delete (V*&)value;
		}

		bool isLeaf()
		{
			return left == nullptr && right == nullptr;
		}

		bool isRoot()
		{
			return parent == nullptr;
		}

	public:
		V value;
		size_t insertNumber;
		size_t height;

		BinaryTreeNode* parent;
		BinaryTreeNode* left;
		BinaryTreeNode* right;
	};

	template <typename V>
	class  BinaryTree{
	public:
		BinaryTree() {
			compare = [](BinaryTreeNode<V>* a, BinaryTreeNode<V>* b) {return a->value > b->value; };
			//compare = BinaryTree::defaultCompare;
		}

		BinaryTree(std::function<bool(BinaryTreeNode<V>*, BinaryTreeNode<V>*)> _compare) {
			compare = _compare;
		}

		~BinaryTree() {

		}

		bool empty()
		{
			return size() == 0;
		}
		int size()
		{
			return nodeCount;
		}

		bool defaultCompare(BinaryTreeNode<V>* a, BinaryTreeNode<V>* b)
		{
			return a->value > b->value;
		}

		// element access :
		BinaryTreeNode<V>* root()
		{
			return rootNode;
		}


		// modifiers:
		BinaryTreeNode<V>* assign(int n, V value)
		{
			if (n == 0)
				return nullptr;

			BinaryTreeNode<V>* newNode = new BinaryTreeNode<V>(value, nodeCount);
			newNode->insertNumber = nodeCount++;

			BinaryTreeNode<V>* left;
			BinaryTreeNode<V>* right;
			int height = -1;
			
			left = assign((n - 1) / 2, value);
			newNode->left = left;
			if (left != nullptr)
			{
				left->parent = newNode;
				height = max<int>(height, left->height);
			}

			right = assign((n - 1) - (n - 1) / 2, value);
			newNode->right = right;
			if (right != nullptr)
			{
				right->parent = newNode;
				height = max<int>(height, right->height);
			}

			newNode->height = height + 1;
			rootNode = newNode;

			return newNode;
		}

		void insert(V value)
		{
			if (empty())
				rootNode = assign(1, value);
			else
			{
				BinaryTreeNode<V>* newNode = new BinaryTreeNode<V>(value, nodeCount);
				insert(newNode, compare);
			}
		}

		void insert(BinaryTreeNode<V>* _newNode, std::function<bool(BinaryTreeNode<V>*, BinaryTreeNode<V>*)> _compare)
		{
			if (!_newNode->isLeaf() || !_newNode->isRoot())
			{
				std::cout << "insert function works on value or single node, recommend the merge function instead." << endl;
				return;
			}
				

			_newNode->height = 0;
			_newNode->insertNumber = nodeCount+1;


			if (empty())
			{
				rootNode = _newNode;
			}
			else
			{
				if (_compare == nullptr)
					_compare = compare;
				
				BinaryTreeNode<V>* cur = rootNode;

				for(int i=0; cur != nullptr; i++)
				{
					if (_compare(cur, _newNode))
					{
						if (cur->left == nullptr)
						{
							cur->left = _newNode;
							_newNode->parent = cur;
							break;
						}
						else
							cur = cur->left;
					}
					else
					{
						if (cur->right == nullptr)
						{
							cur->right = _newNode;
							_newNode->parent = cur;
							break;
						}
						else
							cur = cur->right;
					}
				}
			}

			for (BinaryTreeNode<V>* ptr = _newNode->parent; ptr != nullptr; ptr = ptr->parent)
			{
				int leftDepth = (ptr->left == nullptr ? -1 : ptr->left->height);
				int rightDepth = (ptr->right == nullptr ? -1 : ptr->right->height);

				int currentDepth = max(leftDepth, rightDepth) + 1;
				
				if (ptr->height == currentDepth)
					break;
				ptr->height = currentDepth;
			}

			nodeCount++;
		}


		void erase(V value)
		{
			erase(find(value));
		}

		void erase(std::function<int(BinaryTreeNode<V>*)> option)
		{
			erase(rootNode, find(option));
		}





		void eraseLeaf(BinaryTreeNode<V>* _node)
		{
			if (!_node->isRoot())
			{
				if (_node->parent->left == _node)
					_node->parent->left = nullptr;
				else
					_node->parent->right = nullptr;
			}
			else
				rootNode = nullptr;

			for (BinaryTreeNode<V>* ptr = _node->parent; ptr != nullptr; ptr = ptr->parent)
			{
				int leftDepth = (ptr->left == nullptr ? -1 : ptr->left->height);
				int rightDepth = (ptr->right == nullptr ? -1 : ptr->right->height);

				int currentDepth = max(leftDepth, rightDepth) + 1;

				if (ptr->height == currentDepth)
					break;
				ptr->height = currentDepth;
			}

			delete _node;
			nodeCount--;
		}

		void eraseOneChild(BinaryTreeNode<V>* _node)
		{
			if (_node->left != nullptr)
			{
				if (_node->isRoot())
					rootNode = _node->left;
				else
				{
					if (_node->parent->left == _node)
						_node->parent->left = _node->left;
					else
						_node->parent->right = _node->left;

				}
				_node->left->parent = _node->parent;
			}
			else
			{
				if (_node->isRoot())
					rootNode = _node->right;
				else
				{
					if (_node->parent->left == _node)
						_node->parent->left = _node->right;
					else
						_node->parent->right = _node->right;
				}
				_node->right->parent = _node->parent;
			}

			for (BinaryTreeNode<V>* ptr = _node->parent; ptr != nullptr; ptr = ptr->parent)
			{
				int leftDepth = (ptr->left == nullptr ? -1 : ptr->left->height);
				int rightDepth = (ptr->right == nullptr ? -1 : ptr->right->height);

				int currentDepth = max(leftDepth, rightDepth) + 1;

				if (ptr->height == currentDepth)
					break;
				ptr->height = currentDepth;
			}

			delete _node;
			nodeCount--;
		}

		void erase(BinaryTreeNode<V>* _node)
		{
			if (_node->isLeaf())
			{
				eraseLeaf(_node);
			}
			else if(_node->left == nullptr || _node->right == nullptr)
			{
				eraseOneChild(_node);
			}
			else
			{
				BinaryTreeNode<V>* replaceNode;

				if (_node->left->height >= _node->right->height)
				{
					replaceNode = _node->left;
					while (replaceNode->right != nullptr)
						replaceNode = replaceNode->right;
				}
				else
				{
					replaceNode = _node->right;
					while (replaceNode->left != nullptr)
						replaceNode = replaceNode->left;
				}

				swap(_node, replaceNode);

				if (replaceNode->isLeaf())
					eraseLeaf(replaceNode);
				else
					eraseOneChild(replaceNode);
			}
		}

		BinaryTreeNode<V>* find(std::function<int(BinaryTreeNode<V>*)> option)
		{
			BinaryTreeNode<V>* cur = rootNode;

			for (int i = 0; i < rootNode->height; i++)
			{
				if (cur == nullptr)
					break;

				int result = option(cur);

				if (result == 0)
					return cur;
				else if (result < 0)
					cur = cur->left;
				else
					cur = cur->right;
			}

			return cur;
		}

		BinaryTreeNode<V>* find(V _value)
		{
			BinaryTreeNode<V>* cur = rootNode;
			BinaryTreeNode<V>* temp = new BinaryTreeNode<V>(_value);

			for (int i = 0; i < rootNode->height; i++) //// height 갱신이 안되서 탐색 자체를 안해버림
			{
				if (cur == nullptr || cur->value == _value)
					break;

				if (compare(cur, temp))
					cur = cur->left;
				else
					cur = cur->right;
			}

			delete temp;

			return cur;
		}

		void swap(BinaryTree<V>& tree)
		{
			BinaryTreeNode<V>* rootTemp;
			int numberTemp;
			std::function<bool(BinaryTreeNode<V>*, BinaryTreeNode<V>*)> compareTemp;

			rootTemp = this->rootNode;
			this->rootNode = tree->rootNode;
			tree->rootNode = rootTemp;

			numberTemp = this->nodeCount;
			this->nodeCount = tree->nodeCount;
			tree->nodeCount = numberTemp;

			compareTemp = this->compare;
			this->compare = tree->compare;
			tree->compare = compareTemp;
		}

		void clear()
		{
			while (!empty())
				erase(rootNode);
		}

		void merge(BinaryTree<V>* newTree, std::function<bool(BinaryTreeNode<V>*, BinaryTreeNode<V>*)> _compare)
		{
			return;
		}

		BinaryTreeNode<V>* leftmost(BinaryTreeNode<V>* _root)
		{
			while (_root->left != nullptr)
				_root = _root->left;

			return _root;
		}

		BinaryTreeNode<V>* rightmost(BinaryTreeNode<V>* _root)
		{
			while (_root->right)
				_root = _root->right;

			return _root;
		}

		void printTree()
		{
			if (!empty())
				DFS(rootNode, 1);
			std::cout << std::endl << "===================================" << std::endl << std::endl;
		}
	protected:
		void syncHeight(BinaryTreeNode<V>* _node)
		{
			if (_node->isRoot)
				return;


			int temp = 0;

			if (_node->left != nullptr && _node - right != nullptr)
				temp = max<int>(_node->left->height, _node->right->height) + 1;
			else if (_node->left != nullptr)
				temp = _node->left->height + 1;
			else if (_node->right != nullptr)
				temp = _node->right->height + 1;
			else
				temp = 0;
			
			if (temp == _node->height)
				return;
			else
			{
				_node->height = temp;
				syncHeight(_node->parent);
			}
		}
	
		void link(BinaryTreeNode<V>* parentNode, BinaryTreeNode<V>* nodePtr, BinaryTreeNode<V>* childNode)
		{
			nodePtr = childNode;

			if (childNode != nullptr)
				childNode->parent = parentNode;
		}

		void swap(BinaryTreeNode<V>* first, BinaryTreeNode<V>* second)
		{
			BinaryTreeNode<V>* temp = new BinaryTreeNode<V>(0, 0);
			
			temp->value = first->value;
			first->value = second->value;
			second->value = temp->value;

			temp->insertNumber = first->insertNumber;
			first->insertNumber = second->insertNumber;
			second->insertNumber = temp->insertNumber;
		}

		void DFS(BinaryTreeNode<V>* node, int depth)
		{
			std::cout << node->value << "(" << node->height << ")";
			std::cout << "\t";

			if (node->left != nullptr)
				DFS(node->left, depth + 1);
			std::cout << endl;
			if (node->right != nullptr)
			{
				for (int i = 0; i < depth; i++)
					std::cout << "\t";
				DFS(node->right, depth + 1);
			}

			return;
		}
		
	private:
		



	public:
		BinaryTreeNode<V>* rootNode;

		std::function<bool(BinaryTreeNode<V>*, BinaryTreeNode<V>*)> compare;
	private:
		size_t nodeCount;
	};
}