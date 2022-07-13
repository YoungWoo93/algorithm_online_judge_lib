#pragma once



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
		class iterator {


		public:
			iterator() :ptr(nullptr) {}
			iterator(const iterator& it) :ptr(it.ptr) {}
			~iterator() {}


			bool operator ==(const iterator& it) {

				return ptr == it.ptr;
			}

			bool operator !=(const iterator& it) {

				return ptr != it.ptr;
			}

			iterator& operator =(const iterator& it) {

				ptr = it.ptr;

				return *this;
			}

			iterator operator +(const int n) {
				iterator ret(*this);

				for (int i = 0; i < n; i++)
					ret.ptr = ret.ptr->next;

				return ret;
			}
			iterator& operator ++() {

				ptr = ptr->next;

				return *this;
			}
			const iterator operator ++(int) {
				iterator ret(*this);

				ptr = ptr->next;

				return ret;
			}
			iterator& operator +=(const int n) {

				for (int i = 0; i < n; i++)
					ptr = ptr->next;

				return *this;
			}


			iterator operator -(const int n) {
				iterator ret(*this);

				for (int i = 0; i < n; i++)
					ret.ptr = ret.ptr->prev;

				return ret;
			}
			iterator& operator --() {

				ptr = ptr->prev;

				return *this;
			}
			const iterator operator --(int) {
				iterator ret(*this);

				ptr = ptr->prev;

				return ret;
			}
			iterator& operator -=(const int n) {

				for (int i = 0; i < n; i++)
					ptr = ptr->prev;

				return *this;
			}

			V& operator *() {
				return ptr->value;
			}

		public:
			LinkedListNode<V>* ptr;
		};



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
		iterator begin()
		{
			_iterator.ptr = head;

			return _iterator;
		}
		iterator end()
		{
			_iterator.ptr = tail->next;

			return _iterator;
		}

		iterator rbegin()
		{
			_iterator.ptr = tail;

			return _iterator;
		}
		iterator rend()
		{
			_iterator.ptr = head->prev;

			return _iterator;
		}
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

		void insert(iterator index, V value)
		{
			LinkedListNode<V>* cur = index.ptr;
			LinkedListNode<V>* newNode = new LinkedListNode<V>(value);

			if (cur == nullptr)		// 근데 여기가 end로서의 null 인지, 개발자 실수로 인한 null인지 알 방법이 있나?
			{
				push_back(value);
			}
			else
			{
				newNode->next = cur;
				newNode->prev = cur->prev;
				if (newNode->prev != nullptr)
					newNode->prev->next = newNode;

				if (cur->prev == nullptr)
					head = newNode;
				cur->prev = newNode;

				nodeCount++;
			}

		}
		void insert(iterator index, LinkedList<V>& list)
		{
			LinkedListNode<V>* cur = index.ptr;

			if (cur == nullptr)
			{
				for (iterator it = list.begin(); it != list.end(); it++)
					push_back(*it);
			}
			else
			{
				for (iterator it = list.begin(); it != list.end(); it++)
					insert(index, *it);
			}
		}
		void insert(iterator index, iterator start, iterator end)
		{
			LinkedListNode<V>* cur = index.ptr;

			if (cur == nullptr)
			{
				for (iterator it = start; it != end; it++)
					push_back(*it);
			}
			else
			{
				for (iterator it = start; it != end; it++)
					insert(index, *it);
			}
		}

		iterator erase(iterator index)
		{
			LinkedListNode<V>* cur = index.ptr;
			iterator ret = index + 1;

			if (cur->prev == nullptr)
				pop_front();
			else if (cur->next == nullptr)
				pop_back();
			else
			{
				nodeCount--;

				cur->prev->next = cur->next;
				cur->next->prev = cur->prev;

				delete cur;
			}

			return ret;
		}

		iterator erase(iterator start, iterator end)
		{
			while (start != end)
				start = erase(start);

			return start;
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

		iterator _iterator;
	};


}