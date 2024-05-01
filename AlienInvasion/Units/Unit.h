#pragma once
#include <iostream>

class Game;
enum class UnitType {
	EarthSoldier,
	Tank,
	Gunnery,
	HealingUnit,
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
	int firstAttackTime;
	int DestructionTime;
	int Health;
	int Power;
	int AttackCapacity;
	int intialHealth;
	bool Attacked;
protected:
	static int last_Earth_Id;
	static int last_Alien_Id;
public:

	Unit(UnitType type,int id,  int jointime, int health, int power, int attackcapacity);
	virtual void Attack(Game* gameptr, bool isSilent) = 0;
	virtual UnitType getType() const;
	virtual int getID() const;
	virtual int getJoinTime() const;
	virtual int getFirstAttackTime() const;
	virtual void setFirstAttackTime(int Ta);
	virtual int getDestructionTime() const;
	virtual void setDestructionTime(int Td);
	virtual bool IsAttacked() const;
	virtual void makeAttacked(bool makeatt);
	virtual int getHealth() const;
	virtual int getPower() const;
	virtual int getAttackCapacity() const;
	virtual void decrementHealth(int damage);
	virtual int getIntialHealth() const;
	friend std::ostream& operator<<(std::ostream& stream, Unit* unit)
	{
		if (unit)
			stream << unit->ID;
		return stream;
	}
};
