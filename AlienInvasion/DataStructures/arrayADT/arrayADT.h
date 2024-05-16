#pragma once
#include <iostream>

using namespace std;

template<typename T>
class arrayADT
{
	enum { MAX_SIZE = 1000 };
private:
	T items[MAX_SIZE];
	int count;
public:
	arrayADT()
	{
		
		count = 0;
	}
	bool isEmpty() const
	{
		return count == 0;
	}
	
	bool add(const T& newEntry)
	{
		if (count == MAX_SIZE - 1)
			return false;
		items[count++] = newEntry;
		return true;
	}

	bool remove(T& removedEntry)
	{
		if (isEmpty()) return false;
		int randomindex = rand() % count;
		removedEntry = items[randomindex];
		items[randomindex] = items[count - 1];
		count--;
		return true;
	}
	bool peekRandomly(T& removedEntry)
	{
		if (isEmpty()) return false;
		int randomindex = rand() % count;
		removedEntry = items[randomindex];
		return true;
	}
	int getcount() const
	{
		return count;
	}
	void printlist() const
	{
		cout << "[";
		for (int i = 0; i < count; i++)
		{
			cout << items[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "]\n";
	}
};

