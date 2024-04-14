#pragma once
#include <iostream>

using namespace std;

template<typename T>
class arrayMonsterADT
{
	enum { MAX_SIZE = 1000 };
private:
	T monsters[MAX_SIZE];
	int count;
public:
	arrayMonsterADT()
	{
		srand((unsigned)time(NULL));
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
		monsters[count++] = newEntry;
		return true;
	}

	bool remove(T& removedEntry)
	{
		if (isEmpty()) return false;
		int randomindex = rand() % count;
		removedEntry = monsters[randomindex];
		monsters[randomindex] = monsters[count - 1];
		count--;
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
			cout << monsters[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "]\n";
	}
};

