#pragma once

#include <string.h>
#include <typeinfo>

#include "LinkedList.h"
#include "Vector.h"
#include "../algorithm/hash/md5.h"

namespace _DataStructures_
{
	template <typename K, typename V>
	class HashTableNode {
	public:
		HashTableNode()
		{
		}
		~HashTableNode()
		{

		}
	public:
		K key;
		V value;
	};

	template <typename K, typename V>
	class HashTable {
	public:
		HashTable(int _size = 1024)
		{
			maxSize = _size;
			table = new LinkedList<HashTableNode<K, V>>[maxSize];
		}
		~HashTable()
		{
			delete[] table;
		}

		bool empty()
		{
			return itemCount == 0;
		}
		unsigned int size()
		{
			return itemCount;
		}

		void clear()
		{
			delete[] table;

			table = new LinkedList<V>[maxSize];
			itemCount = 0;
		}

		void insert(K key, V value)
		{
			at(key) = value;
		}

		void erase(K key)
		{
			unsigned int index = keyToIndex(key);
			unsigned int eraseIndex = 0;

			auto ptr = table[index].head;
			while (ptr != table[index].tail)
			{
				if (ptr->key == key)
				{
					table[index].erase(eraseIndex);
					break;
				}

				ptr = ptr->next;
				eraseIndex++;
			}

			itemCount--;
		}

		V& at(K key)
		{
			unsigned int index = keyToIndex(key);

			auto ptr = table[index].head;
			while (ptr != nullptr)
			{
				if (ptr->value.key == key)
					return (V&)(ptr->value.value);

				ptr = ptr->next;
			}
			
			HashTableNode<K, V> temp;
			temp.key = key;

			table[index].push_back(temp);
			itemCount++;

			return(V&)(table[index].tail->value.value);
		}

		V& operator[](K key)
		{
			unsigned int index = keyToIndex(key);

			auto ptr = table[index].head;
			while (ptr != nullptr)
			{
				if (ptr->value.key == key)
					return (V&)(ptr->value.value);

				ptr = ptr->next;
			}

			HashTableNode<K, V> temp;
			temp.key = key;

			table[index].push_back(temp);
			itemCount++;

			return(V&)(table[index].tail->value.value);
		}

	private:
		template <typename K2 = K>
		int keyToIndex(K2 key)
		{
			unsigned int index;
			
			memcpy_s(&index, sizeof(index), md5.digestMemory((BYTE*)&key, sizeof(key)), sizeof(index));
			
			return index % maxSize;
		}

		template <>
		int keyToIndex(std::string key)
		{
			unsigned int index;

			memcpy_s(&index, sizeof(index), md5.digestMemory((BYTE*)((std::string)key).c_str(), ((std::string)key).length()), sizeof(index));

			return index % maxSize;
		}

	public:
		int maxSize;
		int itemCount;
	private:
		LinkedList<HashTableNode<K, V>>* table;
		MD5 md5;
	};



}