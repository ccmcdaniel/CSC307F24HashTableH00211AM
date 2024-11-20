#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

template<class T>
class HashEntry
{
public:
	string key;
	T value;

	int GetHash(int table_size)
	{
		return GetASCIISumKey() % table_size;
	}

private:

	int GetASCIISumKey()
	{
		int sum = 0;

		for (int i = 0; i < key.size(); i++)
			sum += int(key[i]);

		return sum;
	}

};

template<class T>
class HashTable
{
private:
	vector<HashEntry<T>>* hash_table;
	int size;
	int capacity;

public:
	HashTable(int capacity = 211)
	{
		size = 0;
		this->capacity = capacity;

		hash_table = new vector<HashEntry<T>>[capacity];
	}

	bool Insert(string key, T value)
	{
		HashEntry<T> new_item;
		new_item.key = key;
		new_item.value = value;

		int hash = new_item.GetHash(capacity);

		for (int i = 0; i < hash_table[hash].size(); i++)
		{
			if (hash_table[hash][i].key == key)
				return false;
		}

		if ((size * 1.0) / capacity >= 0.75)
			grow_table();

		hash_table[hash].push_back(new_item);
		size++;
		return true;
	}


	bool Search(string key, T& ret_value)
	{
		HashEntry<T> temp;
		temp.key = key;
		int hash = temp.GetHash(capacity);

		for (int i = 0; i < hash_table[hash].size(); i++)
		{
			if (hash_table[hash][i].key == key)
			{
				ret_value = hash_table[hash][i].value;
				return true;
			}
		}

		return false;
	}
	bool Remove(string key)
	{
		HashEntry<T> temp;
		temp.key = key;
		int hash = temp.GetHash(capacity);

		for (int i = 0; i < hash_table[hash].size(); i++)
		{
			if (hash_table[hash][i].key == key)
			{
				hash_table[hash].erase(hash_table[hash].begin() + i);
				size--;

				return true;
			}
		}

		return false;
	}

	bool Update(string key, T new_value)
	{
		HashEntry<T> temp;
		temp.key = key;
		int hash = temp.GetHash(capacity);

		for (int i = 0; i < hash_table[hash].size(); i++)
		{
			if (hash_table[hash][i].key == key)
			{
				hash_table[hash][i].value = new_value;
				return true;
			}
		}

		return false;
	}

	T& operator[](const string& key)
	{
		//Hash they key and create a temporary 
		//HashEntry object.
		HashEntry<T> temp;
		temp.key = key;
		int hash = temp.GetHash(capacity);

		//Lookup the key to see if it exists.  If so,
		//return a reference to the value in the entry.
		for (int i = 0; i < hash_table[hash].size(); i++)
		{
			if (hash_table[hash][i].key == key)
			{
				return hash_table[hash][i].value;
			}
		}
		//If not, add the temporary key to the table and
		//return the value back to main as a reference(hence
		//the T& return type)
		hash_table[hash].push_back(temp);
		size_t size = hash_table[hash].size();
		return hash_table[hash][size - 1].value;
	}

private:
	void grow_table()
	{
		int new_size = GetNewTableSize();
		int old_size = capacity;
		capacity = new_size;

		vector<HashEntry<T>>* old_table = hash_table;
		hash_table = new vector<HashEntry<T>>[new_size];

		for (int i = 0; i < old_size; i++)
		{
			for (auto j : old_table[i])
				Insert(j.key, j.value);
		}
		
		delete[] old_table;
	}

	int GetNewTableSize()
	{
		int start_size = size * 2 + 1;
		
		while(IsPrime(start_size) == false)
			start_size++;

		return start_size;
	}

	bool IsPrime(int num)
	{
		for (int i = 2; i <= num / 2; i++)
		{
			if (num % i == 0)
				return false;
		}

		return true;
	}
};