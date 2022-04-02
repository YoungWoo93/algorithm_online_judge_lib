#pragma once

#include "linkedList.h"

namespace _DataStructures_
{
	template <typename V>
	class Queue {
		// https://www.cplusplus.com/reference/queue/queue/
	public:
		Queue()
		{

		}
		~Queue()
		{

		}

		bool empty()
		{
			return container.empty();
		}
		int size()
		{
			return container.size();
		}
		V front()
		{
			return container.head->value;
		}
		V back()
		{
			return container.tail->value;
		}
		void push(V value)
		{
			container.push_front(value);
		}
		//void emplace()
		//https://www.cplusplus.com/reference/queue/queue/emplace/
		void pop()
		{
			container.pop_back();
		}
		void swap(Queue<V>& queue)
		{
			this->container.swap(queue.container);
		}
	private:


	public:

	private:
		LinkedList<V> container;
	};
}