#pragma once

#include <stdlib.h>
#include <string.h>
#include <iterator>

namespace _DataStructures_
{
	template <typename V>
	class vector {
	public:
		class myIterator : public std::iterator<std::random_access_iterator_tag, V> {


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
			const myIterator operator ++(int) {
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
			const myIterator operator --(int) {
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
		vector()
		{
			ptr = new V[1];
			itemCount = 0;
			maxSize = 1;
		}
		vector(const vector& v)
		{
			ptr = new V[v.maxSize];

			for (int i = 0; i < v.itemCount; i++)
			{
				auto test = V(*(v.ptr + i));
				*(ptr + i) = test;
			}

			itemCount = v.itemCount;
			maxSize = v.maxSize;
		}
		vector(unsigned int count, const V& value = V())
		{
			ptr = new V[count * 2];

			for (int i = 0; i < count; i++)
			{
				auto test = value;
				auto testv = V(test);
				*(ptr + i) = testv;
			}

			itemCount = count;
			maxSize = count * 2;
		}
		~vector()
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

		void assign(size_t _size, const V& value = V())
		{
			if (ptr != nullptr)
				delete[] ptr;

			ptr = new V[_size * 2]; //(V*)malloc(sizeof(V) * count * 2);

			for (size_t i = 0; i < _size; i++)
				ptr[i] = value;


			itemCount = _size;
			maxSize = _size * 2;
		}
		void reserve(const size_t _size)
		{
			V* temp = new V[_size];

			memmove(temp, ptr, sizeof(V) * itemCount);
			maxSize = _size;
			delete[] ptr;
			ptr = temp;
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
	
		void clear()
		{
			delete[] ptr;
			itemCount = 0;
			_myIterator.ptr = nullptr;

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

		vector<V>& operator=(const vector<V>& v)
		{
			if (ptr != nullptr)
				delete[] ptr;

			ptr = new V[v.maxSize];
			itemCount = v.itemCount;
			maxSize = v.maxSize;

			for (int i = 0; i < v.itemCount; i++)
				ptr[i] = *(v.ptr + i);

			return *this;
		}

	private:
		void resize(unsigned int size)
		{
			V* temp = new V[size];// (V*)malloc(sizeof(V) * size);
			for (size_t i = 0; i < itemCount; i++)
				temp[i] = ptr[i];

			delete[] ptr;
			ptr = temp;
			maxSize = size;
		}
	public:

		unsigned int maxSize;
		V* ptr;
		myIterator _myIterator;
		unsigned int itemCount;

	protected:

	private:

	};
}