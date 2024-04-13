#pragma once
#include <iostream>

enum class UnitType {
	EarthSoldier,
	Tank,
	Gunnery,
	AlienSoldier,
	Monster,
	Drone
};

class Unit 
{

private:
	int ID;
	UnitType Type;
	int JoinTime;
	int Health;
	int Power;
	int AttackCapacity;
protected:
	static int last_Earth_Id;
	static int last_Alien_Id;
public:

	Unit(UnitType type,int id,  int jointime, int health, int power, int attackcapacity);
	virtual void Attack()=0;
	virtual int getID() const;
	virtual int getJoinTime() const;
	virtual int getHealth() const;
	virtual int getPower() const;
	virtual int getAttackCapacity() const;
	virtual void decrementHealth(int damage);
	friend std::ostream& operator<<(std::ostream& stream, Unit* unit)
	{
		if (unit)
			stream << unit->ID;
		return stream;
	}
};
