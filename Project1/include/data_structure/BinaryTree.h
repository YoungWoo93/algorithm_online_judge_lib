#pragma once
#include <iostream>

#include "linkedList.h"

namespace _DataStructures_
{
	template <typename V>
	class BinaryTreeNode {

	public:
		BinaryTreeNode(V _value)
			:value(_value), parent(nullptr), left(nullptr), right(nullptr){
		}
		~BinaryTreeNode(){
		}

	public:
		V value;

		BinaryTreeNode* parent;
		BinaryTreeNode* left;
		BinaryTreeNode* right;
	};

	template <typename V>
	class  BinaryTree{
	public:
		BinaryTree()
			:compare(&BinaryTree::defaultCompare)
		{
		}

		BinaryTree(bool (*_compare)(V, V))
			:compare(_compare) {
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

		static bool defaultCompare(V a, V b)
		{
			return a > b;
		}

		// element access :
		BinaryTreeNode<V>* root()
		{
			return rootNode;
		}


		BinaryTreeNode<V>* insert(V value)
		{
			BinaryTreeNode<V>* newNode = new BinaryTreeNode<V>(value);

			return insert(newNode);
		}

		BinaryTreeNode<V>* insert(BinaryTreeNode<V>* newNode)
		{
			if (empty())
				rootNode = newNode;
			else
			{
				BinaryTreeNode<V>* cur = rootNode;

				bool leftNode = true;
				BinaryTreeNode<V>* p = rootNode;
				while (cur != nullptr) {
					p = cur;
					if (compare(cur->value, newNode->value)) {
						cur = cur->left;
						leftNode = true;
					}
					else {
						cur = cur->right;
						leftNode = false;
					}
				}

				newNode->parent = p;
				if (leftNode)
					p->left = newNode;
				else
					p->right = newNode;
			}

			nodeCount++;

			return newNode;
		}

		void erase(V value)
		{
			auto target = find(value);

			if (target != nullptr)
				erase(target);
		}

		void erase(BinaryTreeNode<V>* _node)
		{
			BinaryTreeNode<V>* replaceNode;
			BinaryTreeNode<V>** target;

			if (_node->parent != nullptr)
			{
				if (_node->parent->left == _node)
					target = &(_node->parent->left);
				else
					target = &(_node->parent->right);
			}
			else
				target = &rootNode;

			if (_node->left == nullptr && _node->right == nullptr) {
				replaceNode = nullptr;
				*target = replaceNode;

				nodeCount--;
				delete _node;
			}
			else if (_node->left == nullptr) {
				replaceNode = _node->right;
				replaceNode->parent = _node->parent;
				*target = replaceNode;

				nodeCount--;
				delete _node;
			}
			else if (_node->right == nullptr) {
				replaceNode = _node->left;
				replaceNode->parent = _node->parent;
				*target = replaceNode;

				nodeCount--;
				delete _node;
			}
			else {
				replaceNode = leftmost(_node->right);
				_node->value = replaceNode->value;

				erase(replaceNode);
			}
		}

		BinaryTreeNode<V>* find(V _value)
		{
			BinaryTreeNode<V>* cur = rootNode;

			while (cur != nullptr)
			{
				if (cur->value == _value)
					break;

				if (compare(cur->value, _value))
					cur = cur->left;
				else
					cur = cur->right;
			}

			return cur;
		}

		void swap(BinaryTree<V>& tree)
		{
			BinaryTreeNode<V>* rootTemp;
			int numberTemp;
			bool (*compareTemp)(V a, V b);

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

		void DFS(BinaryTreeNode<V>* node, int depth)
		{
			std::cout << node->value;
			std::cout << "\t";

			if (node->left != nullptr)
				DFS(node->left, depth + 1);
			std::cout << std::endl;
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

		bool (*compare)(V a, V b);
	private:
		size_t nodeCount;
	};
}