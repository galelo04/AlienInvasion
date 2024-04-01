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
	Unit(){}
	virtual void Attack()=0;
};