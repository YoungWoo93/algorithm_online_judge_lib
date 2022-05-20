#pragma once



using namespace std;

namespace _DataStructures_
{
	template <typename V>
	class LinkedListNode
	{
	public:
		LinkedListNode(V _value)
		{
			value = _value;
			prev = nullptr;
			next = nullptr;
		}
		~LinkedListNode()
		{
			if (std::is_pointer<V>::value)
				delete (V*&)value;
		}

		bool isTail()
		{
			return next == nullptr;
		}

		bool isHead()
		{
			return prev == nullptr;
		}

	public:
		V value;

		LinkedListNode<V>* prev;
		LinkedListNode<V>* next;
	};


	template <typename V>
	class LinkedList
	{
		// https://www.cplusplus.com/reference/list/list/
	public:
		LinkedList() {
			head = nullptr;
			tail = nullptr;
			nodeCount = 0;
		}
		LinkedList(int size) {
			V* temp = new V;
			assign(size, *temp);

			delete temp;
		}
		LinkedList(int size, V defaultValue) {
			assign(size, defaultValue);
		}
		~LinkedList() {
			LinkedListNode<V>* node = head;

			while (!node->isTail())
			{
				auto temp = node;
				node = node->next;

				delete temp;
			}
		}


		/// <summary>
		/// 
		/// iterators:
		/// 
		/// begin
		///	end
		///	rbegin
		///	rend
		///	cbegin
		///	cend
		///	crbegin
		///	crend
		/// 
		/// 
		/// </summary>
		/// <typeparam name="V"></typeparam>

			// cpacity:
		bool empty()
		{
			return size() == 0;
		}
		int size()
		{
			return nodeCount;
		}


		// element access :
		V front()
		{
			return head->value;
		}
		V back()
		{
			return tail->value;
		}


		// modifiers:
		void assign(int n, V value)
		{
			if (!empty())
				clear();

			LinkedListNode<V>* newNode = new LinkedListNode<V>(value);
			head = newNode;
			tail = newNode;
			nodeCount = 1;

			for (int i = 1; i < n; i++)
				push_back(value);
		}
		// void emplace_front(V value)
		// https://stackoverflow.com/questions/4303513/push-back-vs-emplace-back

		void push_front(V value)
		{
			if (empty())
				assign(1, value);
			else
			{
				LinkedListNode<V>* newNode = new LinkedListNode<V>(value);
				LinkedListNode<V>* temp = head;

				head = newNode;

				head->next = temp;
				temp->prev = head;

				nodeCount++;
			}
		}
		void pop_front()
		{
			nodeCount--;

			if (empty())
			{
				delete head;
				head = nullptr;
				tail = nullptr;
			}
			else
			{
				auto temp = head;
				head = head->next;
				head->prev = nullptr;

				delete temp;
			}
		}

		void push_back(V value)
		{
			if (empty())
				assign(1, value);
			else
			{
				LinkedListNode<V>* newNode = new LinkedListNode<V>(value);
				LinkedListNode<V>* temp = tail;

				tail = newNode;

				temp->next = tail;
				tail->prev = temp;

				nodeCount++;
			}
		}

		void pop_back()
		{
			nodeCount--;

			if (empty())
			{
				delete tail;
				head = nullptr;
				tail = nullptr;
			}
			else
			{
				auto temp = tail;
				tail = tail->prev;
				tail->next = nullptr;

				delete temp;
			}
		}

		//emplace
		//https://www.cplusplus.com/reference/list/list/emplace/

		void insert(int index, V value)
		{
			if (index < 0 || size() < index)
			{
				// index error check;
				return;
			}

			LinkedListNode<V>* cur = head;
			for (int i = 0; i < index; i++)
				cur = cur->next;

			LinkedListNode<V>* newNode = new LinkedListNode<V>(value);

			newNode->next = cur;
			newNode->prev = cur->prev;
			if (newNode->prev != nullptr)
				newNode->prev->next = newNode;

			cur->prev = newNode;

			nodeCount++;
		}
		void insert(int index, LinkedList<V>& list)
		{
			LinkedListNode<V>* cur = list.head;
			for (int i = 0; i < list.size(); i++)
			{
				insert(index + i, cur->value);
				cur = cur->next;
			}
		}


		void erase(int index)
		{
			if (index < 0 || size() < index)
			{
				// index error check;
				return;
			}

			LinkedListNode<V>* cur = head;
			for (int i = 0; i < index; i++)
				cur = cur->next;

			if (cur->prev != nullptr)
				cur->prev->next = cur->next;
			if (cur->next != nullptr)
				cur->next->prev = cur->prev;

			delete cur;

			nodeCount--;
		}
		void erase(int start, int end)
		{
			for (int i = 0; i < end - start; i++)
				erase(start);

		}

		void swap(LinkedList<V>& list)
		{
			LinkedListNode<V>* nodeTemp;
			int countTemp;

			nodeTemp = this->head;
			this->head = list.head;
			list.head = nodeTemp;

			nodeTemp = this->tail;
			this->tail = list.tail;
			list.tail = nodeTemp;

			countTemp = this->nodeCount;
			this->nodeCount = list.nodeCount;
			list.nodeCount = countTemp;
		}


		void resize(int size)
		{
			V* defaultValue = new V;

			if (empty())
			{
				assign(size, *defaultValue);

				delete defaultValue;
				return;
			}

			if (size == 0)
				clear();

			LinkedListNode<V>* cur = head;
			for (int i = 0; i < size; i++)
			{
				if (!cur->isTail())
					cur = cur->next;
				else
				{
					for (; i < size; i++)
						push_back(*defaultValue);
				}
			}

			for (; !cur->isTail();)
				pop_back();

			delete defaultValue;
		}

		void resize(int size, V defaultValue)
		{
			if (empty())
			{
				assign(size, defaultValue);
				return;
			}

			if (size == 0)
				clear();

			LinkedListNode<V>* cur = head;
			for (int i = 0; i < size; i++)
			{
				if (!cur->isTail())
					cur = cur->next;
				else
				{
					for (; i < size; i++)
						push_back(defaultValue);
				}
			}

			for (; !cur->isTail();)
				pop_back();
		}

		void clear()
		{
			while (!empty())
				pop_back();
		}

	protected:


	private:

	public:
		LinkedListNode<V>* head;
		LinkedListNode<V>* tail;

	protected:
		unsigned int nodeCount;

	private:
	};
}