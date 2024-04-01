#pragma once
class Unit 
{

private:
	int ID;
	int JoinTime;
	int Health;
	int Power;
	int AttackCapacity;

public:

	virtual bool Add (Unit * newEntry) = 0;
	virtual bool Remove (Unit * removedEntry) = 0;
	virtual void PrintList () = 0;
};