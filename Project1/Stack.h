#pragma once

#include "linkedList.h"

namespace _DataStructures_
{
	template <typename V>
	class Stack {
		// https://www.cplusplus.com/reference/stack/stack/
	public:
		Stack()
		{

		}
		~Stack()
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
		V top()
		{
			return container.head->value;
		}
		void push(V value)
		{
			container.push_back(value);
		}
		//void emplace()
		//https://www.cplusplus.com/reference/stack/stack/emplace/
		void pop()
		{
			container.pop_back();
		}
		void swap(Stack<V> &stack)
		{
			this->container.swap(stack.container);
		}

	private:


	public:

	private:
		LinkedList<V> container;
	};
}