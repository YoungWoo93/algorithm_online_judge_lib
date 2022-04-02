#pragma once


#include "linkedList.h"

namespace _DataStructures_
{
	template <typename V>
	class Deque {
		//https://www.cplusplus.com/reference/deque/deque/
		//https://stackoverflow.com/questions/2297164/stl-deque-accessing-by-index-is-o1
	public:
		Deque()
		{

		}
		~Deque()
		{

		}

	private:


	public:

	private:
		LinkedList<V> container;
	};
}