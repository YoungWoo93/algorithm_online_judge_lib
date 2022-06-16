#pragma once

#include <stdlib.h>
#include <string.h>
#include <iterator>
namespace _DataStructures_
{
	template <typename V>
	class Vector {
	public:
		class myIterator : public std::iterator<std::random_access_iterator_tag, V>{


		public:
			myIterator() :ptr(nullptr) {}
			myIterator(const myIterator& it) :ptr(it.ptr) {}
			~myIterator() {}


			bool operator ==(const myIterator& it) {

				return ptr == it.ptr;
			}

			bool operator !=(const myIterator& it) {

				return ptr != it.ptr;
			}

			myIterator& operator =(const myIterator& it) {

				ptr = it.ptr;

				return *this;
			}

			myIterator operator +(const int n) {
				myIterator ret(*this);

				for (int i = 0; i < n; i++)
					ret++;

				return ret;
			}
			myIterator& operator ++() {

				ptr++;

				return *this;
			}
			myIterator& operator ++(int) {
				myIterator ret(*this);

				ptr++;

				return ret;
			}
			myIterator& operator +=(const int n) {

				for (int i = 0; i < n; i++)
					ptr++;

				return *this;
			}


			myIterator operator -(const int n) {
				myIterator ret(*this);

				for (int i = 0; i < n; i++)
					ret--;

				return ret;
			}
			int operator -(myIterator it) {

				return (ptr - it.ptr);
			}

			myIterator& operator --() {

				ptr--;

				return *this;
			}
			myIterator& operator --(int) {
				myIterator ret(*this);

				ptr--;

				return ret;
			}
			myIterator& operator -=(const int n) {

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
		Vector(unsigned int count, const V& value = V())
		{
			ptr = new V[count * 2]; //(V*)malloc(sizeof(V) * count * 2);
			
			for (size_t i = 0; i < count; i++)
				ptr[i] = value;
		

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

		void assign(size_t _size, V& value)
		{
			delete[] ptr;
			Vector temp(_size, value);

			ptr = temp.ptr;
			maxSize = temp.maxSize;
			itemCount = temp.itemCount;
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
			if (itemCount > 0)
				itemCount--;
		}
		void insert(myIterator index, V value)
		{
			if (itemCount + 1 > maxSize)
				resize(maxSize * 2);

			for (myIterator it = end(); it != index; it--)
				*it = *(it - 1);

			*index = value;
			itemCount++;
		}

		void insert(myIterator index, unsigned int count, V value)
		{
			while (itemCount + count > maxSize)
				resize(maxSize * 2);

			for (myIterator it = rbegin() - count; it != index; it--)
				*it = *(it - count);

			for (int i = 0; i < count; i++)
			{
				*index = value;
				index++;
			}

			itemCount += count;
		}

		void insert(myIterator index, myIterator start, myIterator end)
		{
			int count = end - start;

			while (itemCount + count > maxSize)
				resize(maxSize * 2);

			for (myIterator it = rbegin() - count; it != index; it--)
				*it = *(it - count);

			for (myIterator it = start; it != end; it++)
			{
				*index = *it;
				index++;
			}

			itemCount += count;
		}

		myIterator erase(myIterator index)
		{
			for (myIterator it = index; it != end() - 1; it++)
				*it = *(it + 1);

			itemCount--;

			return index;
		}

		myIterator erase(myIterator _start, myIterator _end)
		{
			int count = _end - _start;

			for (myIterator it = _start; it != end() - count; it++)
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

		myIterator begin()
		{
			_myIterator.ptr = ptr;

			return _myIterator;
		}
		myIterator end()
		{
			_myIterator.ptr = ptr + itemCount;

			return _myIterator;
		}

		myIterator rbegin()
		{
			_myIterator.ptr = ptr + (itemCount - 1);

			return _myIterator;
		}
		myIterator rend()
		{
			_myIterator.ptr = ptr - 1;

			return _myIterator;
		}

		V& at(unsigned int index)
		{
			return *(ptr + index);
		}
		V& operator[](unsigned int index)
		{
			return *(ptr + index);
		}

		Vector<V>& operator=(const Vector<V>& v)
		{
			V* temp = new V[v.maxSize];
			itemCount = v.itemCount;
			maxSize = v.maxSize;

			for (int i = 0; i < v.itemCount; i++)
				temp[i] = *(v.ptr + i);

			delete ptr;

			ptr = temp;

			return *this;
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
		myIterator _myIterator;

		unsigned int itemCount;

	};
}