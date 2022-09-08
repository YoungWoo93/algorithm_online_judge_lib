#pragma once
#include "BinaryTree.h"

namespace _DataStructures_
{
	template <typename V>
	class RedBlackTreeNode
	{
	public:
		RedBlackTreeNode(V _value)
			:value(_value), parent(nullptr), left(nullptr), right(nullptr), red(true), itIsLeftChild(false) {
		}
		RedBlackTreeNode()
			:value(), parent(nullptr), left(nullptr), right(nullptr), red(false), itIsLeftChild(false) {
		}
		~RedBlackTreeNode() {
		}

		RedBlackTreeNode<V>* brother()
		{
			if (itIsLeftChild)
				return parent->right;

			return parent->left;
		}

		RedBlackTreeNode<V>* uncle()
		{
			if (parent->itIsLeftChild)
				return parent->parent->right;

			return parent->parent->left;
		}

		RedBlackTreeNode<V>* grandParent()
		{
			return parent->parent;
		}
	public:
		V value;

		RedBlackTreeNode* parent;
		RedBlackTreeNode* left;
		RedBlackTreeNode* right;
		bool red;
		bool itIsLeftChild;
	};

	template <typename V>
	class RedBlackTree
	{
	public:
		RedBlackTree()
			:compare(&RedBlackTree::defaultCompare), nullNode(new RedBlackTreeNode<V>()) {
		}

		RedBlackTree(bool (*_compare)(V, V))
			:compare(_compare), nullNode(new RedBlackTreeNode<V>()) {
		}

		~RedBlackTree() {

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
			return a >= b;
		}

		// element access :
		RedBlackTreeNode<V>* root()
		{
			return rootNode;
		}


		RedBlackTreeNode<V>* insert(V value)
		{
			RedBlackTreeNode<V>* newNode = new RedBlackTreeNode<V>(value);
			newNode->parent = nullNode;
			newNode->left = nullNode;
			newNode->right = nullNode;

			newNode = insert(newNode);

			while (newNode != rootNode && newNode->parent->red)
			{
				if (newNode->uncle()->red)
				{
					newNode->grandParent()->red = true;
					newNode->parent->red = false;
					newNode->uncle()->red = false;

					newNode = newNode->grandParent();
					continue;
				}
				else
				{
					if (newNode->itIsLeftChild != newNode->parent->itIsLeftChild)
					{
						newNode = newNode->parent;
						if (newNode->itIsLeftChild)
							rotateLeft(newNode);
						else
							rotateRight(newNode);
					}

					if (newNode->parent->itIsLeftChild)
						rotateRight(newNode->parent->parent);
					else
						rotateLeft(newNode->parent->parent);

					newNode->parent->red = false;
					newNode->parent->left->red = true;
					newNode->parent->right->red = true;
					break;
				}
			}

			if (rootNode->red)
			{
				rootNode->red = false;
				blackDepth++;
			}

			return newNode;
		}



		void erase(V value)
		{
			auto target = find(value);

			if (target != nullptr)
				erase(target);
		}

		void erase(RedBlackTreeNode<V>* _node)
		{
			RedBlackTreeNode<V>* replaceNode;
			RedBlackTreeNode<V>** target;

			if (_node->parent != nullNode)
			{
				if (_node->itIsLeftChild)
					target = &(_node->parent->left);
				else
					target = &(_node->parent->right);
			}
			else
				target = &rootNode;

			if (_node->left == nullNode && _node->right == nullNode) {

				replaceNode = *target;

				if (!replaceNode->red)
				{
					eraseRotate(replaceNode);
				}

				if (replaceNode->itIsLeftChild)
					replaceNode->parent->left = nullNode;
				else
					replaceNode->parent->right = nullNode;
				nodeCount--;
				delete replaceNode;
			}
			else if (_node->left != nullNode) {
				replaceNode = rightmost(_node->left);
				_node->value = replaceNode->value;

				if (!replaceNode->red)
				{
					erase(replaceNode);
					return;
				}

				if (replaceNode->itIsLeftChild)
					replaceNode->parent->left = nullNode;
				else
					replaceNode->parent->right = nullNode;
				nodeCount--;
				delete replaceNode;
			}
			else if (_node->right != nullNode) {
				replaceNode = leftmost(_node->right);
				_node->value = replaceNode->value;

				if (!replaceNode->red)
				{
					erase(replaceNode);
					return;
				}

				if (replaceNode->itIsLeftChild)
					replaceNode->parent->left = nullNode;
				else
					replaceNode->parent->right = nullNode;
				nodeCount--;
				delete replaceNode;
			}

			return;
		}

		void eraseRotate(RedBlackTreeNode<V>* _node)
		{
			if (_node == rootNode) {
				blackDepth--;
				return;
			}
			if (_node->red)
			{
				_node->red = false;
				return;
			}

			if (_node->brother()->red)
			{
				_node->brother()->red = false;
				_node->parent->red = true;

				if (_node->itIsLeftChild)
					rotateLeft(_node->parent);
				else
					rotateRight(_node->parent);
			}

			if (!_node->brother()->left->red && !_node->brother()->right->red)
			{
				_node->brother()->red = true;

				eraseRotate(_node->parent);
			}
			else if (_node->itIsLeftChild && !_node->brother()->right->red)
			{
				_node->brother()->red = true;
				_node->brother()->left->red = false;

				rotateRight(_node->brother());
				eraseRotate(_node);
			}
			else if (!_node->itIsLeftChild && !_node->brother()->left->red)
			{
				_node->brother()->red = true;
				_node->brother()->right->red = false;

				rotateLeft(_node->brother());
				eraseRotate(_node);
			}
			else
			{
				_node->brother()->red = _node->parent->red;
				_node->parent->red = false;
				if (_node->itIsLeftChild)
				{
					_node->brother()->right->red = false;
					rotateLeft(_node->parent);
				}
				else
				{
					_node->brother()->left->red = false;
					rotateRight(_node->parent);
				}
			}
		}

		RedBlackTreeNode<V>* find(V _value)
		{
			RedBlackTreeNode<V>* cur = rootNode;

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

		void swap(RedBlackTree<V>& tree)
		{
			RedBlackTreeNode<V>* rootTemp;
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

		RedBlackTreeNode<V>* leftmost(RedBlackTreeNode<V>* _root)
		{
			while (_root->left != nullNode)
				_root = _root->left;

			return _root;
		}

		RedBlackTreeNode<V>* rightmost(RedBlackTreeNode<V>* _root)
		{
			while (_root->right != nullNode)
				_root = _root->right;

			return _root;
		}

		void printTree()
		{
			if (!empty())
				DFSprint(rootNode, 1);
			std::cout << std::endl << "===================================" << std::endl << std::endl;
		}
		bool proveTree()
		{
			bool ret;
			if (!empty())
			{
				proveValue = rightmost(rootNode)->value;
				ret = DFSprove(rootNode, blackDepth);
				if (ret)
					std::cout << std::endl << "Red Black legal" << std::endl;
				else
					std::cout << std::endl << "Red Black not legal" << std::endl;
			}
			std::cout << std::endl << "===================================" << std::endl << std::endl;

			return ret;
		}
	protected:
		void rotateLeft(RedBlackTreeNode<V>* node)
		{
			RedBlackTreeNode<V>* a = node;
			RedBlackTreeNode<V>* b = node->right;
			RedBlackTreeNode<V>* c = node->right->left;

			if (a == rootNode)
				rootNode = b;

			b->parent = a->parent;
			if (a->itIsLeftChild)
				a->parent->left = b;
			else
				a->parent->right = b;

			a->parent = b;
			b->left = a;

			c->parent = a;
			a->right = c;

			b->itIsLeftChild = a->itIsLeftChild;
			a->itIsLeftChild = true;
			c->itIsLeftChild = false;

			nullNode->parent = nullptr;
			nullNode->left = nullptr;
			nullNode->right = nullptr;
		}
		void rotateRight(RedBlackTreeNode<V>* node)
		{
			RedBlackTreeNode<V>* a = node;
			RedBlackTreeNode<V>* b = node->left;
			RedBlackTreeNode<V>* c = node->left->right;

			if (a == rootNode)
			{
				rootNode = b;
			}

			b->parent = a->parent;
			if (a->itIsLeftChild)
				a->parent->left = b;
			else
				a->parent->right = b;

			a->parent = b;
			b->right = a;

			c->parent = a;
			a->left = c;

			b->itIsLeftChild = a->itIsLeftChild;
			a->itIsLeftChild = false;
			c->itIsLeftChild = true;

			nullNode->parent = nullNode;
			nullNode->right = nullNode;
			nullNode->left = nullNode;
		}




		RedBlackTreeNode<V>* insert(RedBlackTreeNode<V>* newNode)
		{
			if (empty())
				rootNode = newNode;
			else
			{
				RedBlackTreeNode<V>* cur = rootNode;

				newNode->itIsLeftChild = true;
				RedBlackTreeNode<V>* p = rootNode;
				while (cur != nullNode) {
					p = cur;
					if (compare(cur->value, newNode->value)) {
						cur = cur->left;
						newNode->itIsLeftChild = true;
					}
					else {
						cur = cur->right;
						newNode->itIsLeftChild = false;
					}
				}

				newNode->parent = p;
				if (newNode->itIsLeftChild)
					p->left = newNode;
				else
					p->right = newNode;
			}

			nodeCount++;

			return newNode;
		}

		void DFSprint(RedBlackTreeNode<V>* node, int depth)
		{
			if (node->red)
				std::cout << "*";
			std::cout << node->value;
			std::cout << "\t";

			if (node->left != nullNode)
				DFSprint(node->left, depth + 1);
			std::cout << std::endl;
			if (node->right != nullNode)
			{
				for (int i = 0; i < depth; i++)
					std::cout << "\t";
				DFSprint(node->right, depth + 1);
			}

			return;
		}

		bool DFSprove(RedBlackTreeNode<V>* node, int blackCount)
		{
			if (node->red && node->parent->red)
			{
				std::cout << "Red Red error at " << node->parent->value << " -> " << node->value << std::endl;
				return false;
			}

			if (!node->red)
				blackCount--;

			if (node->left == nullNode && node->right == nullNode)
			{
				if (blackCount != 0)
				{
					std::cout << "Black Count error at " << node->value << std::endl;
					return false;
				}

				if (!compare(proveValue, node->value))
				{
					std::cout << "sort error at " << node->value << std::endl;
					return false;
				}

				return true;
			}

			if (node->left != nullNode)
			{
				if (!DFSprove(node->left, blackCount))
					return false;
			}

			if (!compare(proveValue, node->value))
			{
				std::cout << "sort error at " << node->value << std::endl;
				return false;
			}

			if (node->right != nullNode)
			{
				if (!DFSprove(node->right, blackCount))
					return false;
			}

			return true;
		}
	private:
		V proveValue;



	public:
		RedBlackTreeNode<V>* rootNode;

		bool (*compare)(V a, V b);
	private:
		size_t nodeCount;

	public:
		int blackDepth;
		RedBlackTreeNode<V>* nullNode;
	};



}