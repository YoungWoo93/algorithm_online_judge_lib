#pragma once

#include <stdlib.h>
#include <string.h>

namespace _DataStructures_
{
	template <typename V>
	class Vector {
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
					ret++;

				return ret;
			}
			iterator& operator ++() {

				ptr++;

				return *this;
			}
			iterator& operator ++(int) {
				iterator ret(*this);

				ptr++;

				return ret;
			}
			iterator& operator +=(const int n) {

				for (int i = 0; i < n; i++)
					ptr++;

				return *this;
			}


			iterator operator -(const int n) {
				iterator ret(*this);

				for (int i = 0; i < n; i++)
					ret--;

				return ret;
			}
			int operator -(iterator it) {
				
				return (ptr - it.ptr);
			}

			iterator& operator --() {

				ptr--;

				return *this;
			}
			iterator& operator --(int) {
				iterator ret(*this);

				ptr--;

				return ret;
			}
			iterator& operator -=(const int n) {

				for (int i = 0; i < n; i++)
					ptr--;

				return *this;
			}

			V& operator *() {

				return *ptr;
			}

		public:
			V* ptr;
		};

	public:
		Vector()
		{
			ptr = new V[1024];//(V*)malloc(sizeof(V) * 1024);
			itemCount = 0;
			maxSize = 1024;
		}
		Vector(unsigned int count, const V& value)
		{
			ptr = new V[count * 2];//(V*)malloc(sizeof(V) * count * 2);
			for (unsigned int i = 0; i < count; i++)
				memcpy_s(ptr + i, sizeof(V), &value, sizeof(V));

			itemCount = count;
			maxSize = count * 2;
		}
		~Vector()
		{
			delete[] ptr;
		}

		bool empty()
		{
			return itemCount == 0;
		}
		int size()
		{
			return itemCount;
		}
		void push_back(V value)
		{
			if (itemCount >= maxSize)
				resize(maxSize * 2);
			

			*(ptr + itemCount) = value;
			itemCount++;
		}
		void pop_back()
		{
			if(itemCount > 0)
				itemCount--;
		}
		void insert(iterator index, V value)
		{
			if (itemCount + 1 > maxSize)
				resize(maxSize * 2);

			for (iterator it = end(); it != index; it--)
				*it = *(it - 1);

			*index = value;
			itemCount++;
		}

		void insert(iterator index, unsigned int count, V value)
		{
			while (itemCount + count > maxSize)
				resize(maxSize * 2);

			for (iterator it = rbegin() - count; it != index; it--)
				*it = *(it - count);

			for (int i = 0; i < count; i++)
			{
				*index = value;
				index++;
			}

			itemCount += count;
		}

		void insert(iterator index, iterator start, iterator end)
		{
			int count = end - start;

			while (itemCount + count > maxSize)
				resize(maxSize * 2);

			for (iterator it = rbegin() - count; it != index; it--)
				*it = *(it - count);

			for (iterator it = start; it != end; it++)
			{
				*index = *it;
				index++;
			}

			itemCount += count;
		}

		iterator erase(iterator index)
		{
			for (iterator it = index; it != end() - 1; it++)
				*it = *(it + 1);
			
			itemCount--;

			return index;
		}

		iterator erase(iterator _start, iterator _end)
		{
			int count = _end - _start;

			for (iterator it = _start; it != end() - count; it++)
				*it = *(it + count);

			itemCount -= count;

			return _start;
		}

		V& front()
		{
			return ptr[0];
		}
		V& back()
		{
			return ptr[itemCount - 1];
		}

		iterator begin()
		{
			_iterator.ptr = ptr;

			return _iterator;
		}
		iterator end()
		{
			_iterator.ptr = ptr + itemCount;

			return _iterator;
		}

		iterator rbegin()
		{
			_iterator.ptr = ptr + (itemCount - 1);

			return _iterator;
		}
		iterator rend()
		{
			_iterator.ptr = ptr - 1;

			return _iterator;
		}

		V& at(unsigned int index)
		{
			return *(ptr + index);
		}
		V& operator[](unsigned int index)
		{
			return *(ptr + index);
		}

	private:
		void resize(unsigned int size)
		{
			V* temp = new V[size];// (V*)malloc(sizeof(V) * size);

			memcpy_s(temp, sizeof(V) * size, ptr, sizeof(V) * itemCount);
			delete[] ptr;

			ptr = temp;
			maxSize = size;
			if (itemCount > size)
				itemCount = size;
		}
	public:

		unsigned int maxSize;
	protected:

	private:
		V* ptr;
		iterator _iterator;

		unsigned int itemCount;
		
	};
}