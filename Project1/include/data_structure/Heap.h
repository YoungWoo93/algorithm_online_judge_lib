#pragma once

#pragma once

#include "Vector.h"

template <typename V>
bool compareFunc(const V& first, const V& second)
{
	return first > second;
}

namespace _DataStructures_
{
	template <typename V>
	class Heap {
	public:
		Heap()
			:container(1)
		{
			container.reserve(2);
			compare = compareFunc;
		}
		Heap(bool (*_cmp)(const V& first, const V& second))
			:container(1)
		{
			container.reserve(2);
			compare = _cmp;
		}
		~Heap()
		{

		}
		

		bool empty()
		{
			return container.size() <= 1;
		}
		int size()
		{
			return container.size() - 1;
		}
		V top()
		{
			return container[1];
		}
		void push(V value)
		{
			if (container.maxSize <= container.itemCount)
				container.reserve(container.maxSize * 2);

			this->container.push_back(value);

			int index = container.size() - 1;
			while (index / 2 > 0)
			{
				if (compare(container[index], container[index / 2]))
				{
					std::swap(container[index], container[index / 2]);
					index /= 2;
				}
				else
					break;
			}
		}
		void pop()
		{
			container[1] = container.back();
			container.pop_back();

			int index = 1;

			while (true)
			{
				if (index * 2 > container.itemCount)
					break;
				else if (index * 2 + 1 > container.itemCount)
				{
					if (compare(container[index * 2], container[index]))
						std::swap(container[index], container[index * 2]);

					break;
				}
				else
				{
					if (compare(container[index * 2], container[index * 2 + 1]))
					{
						if (compare(container[index * 2], container[index]))
						{
							std::swap(container[index], container[index * 2]);
							index *= 2;
						}
						else
							break;
					}
					else
					{
						if (compare(container[index * 2 + 1], container[index]))
						{
							std::swap(container[index], container[index * 2 + 1]);
							index = index * 2 + 1;
						}
						else
							break;
					}
				}
			}
		}

		void swap(Heap<V>& h)
		{
			this->container.swap(h.container);
		}
	private:
		
	public:

	//private:
		bool (*compare)(const V& first, const V& second);
		vector<V> container;
	};
}