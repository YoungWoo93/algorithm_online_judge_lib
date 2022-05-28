#pragma once

#include <stdlib.h>
#include <string.h>

namespace _DataStructures_
{
	template <typename V>
	class Vector {
		
	public:
		Vector()
		{
			ptr = (V*)malloc(sizeof(V) * 1024);
			itemCount = 0;
			maxSize = 1024;
		}
		Vector(unsigned int count, const V& value)
		{
			ptr = (V*)malloc(sizeof(V) * count * 2);
			for (unsigned int i = 0; i < count; i++)
				memcpy_s(ptr + i, sizeof(V), &value, sizeof(V));

			itemCount = count;
			maxSize = count * 2;
		}
		~Vector()
		{
			free(ptr);
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
		V& front()
		{
			return ptr[0];
		}
		V& front()
		{
			return ptr[itemCount - 1];
		}
		V* begin()
		{
			return ptr;
		}
		V* end()
		{
			return ptr + itemCount;
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
			V* temp = (V*)malloc(sizeof(V) * size);

			memcpy_s(temp, sizeof(V) * size, ptr, sizeof(V) * itemCount);
			free(ptr);

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

		unsigned int itemCount;
		
	};
}